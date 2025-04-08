import sys
import os
import json
import uuid
import random
import hashlib
import threading
import urllib.request
import zipfile
import tempfile
from pathlib import Path

# 尝试导入PyQt5，若不存在则提示安装
try:
    from PyQt5.QtWidgets import (QApplication, QMainWindow, QWidget, QVBoxLayout, QHBoxLayout, 
                               QLabel, QLineEdit, QPushButton, QProgressBar, QComboBox, 
                               QCheckBox, QTabWidget, QTextEdit, QFileDialog, QSpinBox,
                               QGroupBox, QRadioButton, QMessageBox, QScrollArea, QSizePolicy)
    from PyQt5.QtCore import Qt, QThread, pyqtSignal, QUrl
    from PyQt5.QtGui import QFont, QDesktopServices
except ImportError:
    print("PyQt5 未安装。请运行: pip install PyQt5")
    sys.exit(1)

# 尝试导入datasets，若不存在则提示安装
try:
    from datasets import load_dataset
except ImportError:
    print("datasets 未安装。请运行: pip install datasets")
    sys.exit(1)

# 尝试导入git，若不存在则提示安装
try:
    import git
except ImportError:
    print("GitPython 未安装。请运行: pip install GitPython")
    sys.exit(1)

# 尝试导入requests，若不存在则提示安装
try:
    import requests
except ImportError:
    print("requests 未安装。请运行: pip install requests")
    sys.exit(1)

class DatasetWorker(QThread):
    """后台工作线程，用于处理耗时的数据集操作"""
    progress_signal = pyqtSignal(int)
    status_signal = pyqtSignal(str)
    error_signal = pyqtSignal(str)
    finished_signal = pyqtSignal(bool, str)  # 成功/失败, 消息
    
    def __init__(self, params):
        super().__init__()
        self.params = params
        self.is_running = True
    
    def stop(self):
        self.is_running = False
        self.wait(1000)  # 等待线程结束，设置超时时间，避免卡死
    
    def run(self):
        try:
            # 提取参数
            source_type = self.params.get('source_type')
            dataset_name = self.params.get('dataset_name')
            dataset_url = self.params.get('dataset_url')
            github_repo = self.params.get('github_repo')
            output_formats = self.params.get('output_formats', {})
            output_dir = self.params.get('output_dir')
            filter_non_ascii = self.params.get('filter_non_ascii', True)
            random_seed = self.params.get('random_seed', 42)
            split_sizes = self.params.get('split_sizes', {'train': 0, 'val': 0, 'test': 0})
            
            self.status_signal.emit("开始处理...")
            self.progress_signal.emit(5)
            
            # 根据来源类型获取数据
            data = None
            if source_type == "huggingface":
                data = self._load_from_huggingface(dataset_name)
            elif source_type == "github":
                data = self._load_from_github(github_repo)
            elif source_type == "url":
                data = self._load_from_url(dataset_url)
            elif source_type == "local":
                data = self._load_from_local(self.params.get('local_file'))
            else:
                raise ValueError(f"不支持的数据源类型: {source_type}")
            
            if not self.is_running:
                return
                
            self.progress_signal.emit(30)
            self.status_signal.emit(f"数据加载完成，共 {len(data)} 条记录")
            
            # 随机打乱数据
            all_data = list(data)
            random.seed(random_seed)
            random.shuffle(all_data)
            
            self.progress_signal.emit(40)
            
            # 过滤非ASCII字符（如果需要）
            if filter_non_ascii:
                self.status_signal.emit("正在过滤非ASCII字符...")
                filtered_data, filtered_count = self._filter_non_ascii(all_data)
                self.status_signal.emit(f"过滤了 {filtered_count}/{len(all_data)} 条记录 ({filtered_count/len(all_data)*100:.2f}%)")
                all_data = filtered_data
            
            self.progress_signal.emit(50)
            
            # 检查数据量是否足够
            total_needed = sum(split_sizes.values())
            if len(all_data) < total_needed:
                self.status_signal.emit(f"警告: 可用数据量({len(all_data)})少于要求数量({total_needed})，将按比例调整...")
                ratio = len(all_data) / total_needed
                for key in split_sizes:
                    split_sizes[key] = int(split_sizes[key] * ratio)
                split_sizes['test'] = min(split_sizes['test'], len(all_data) - split_sizes['train'] - split_sizes['val'])
            
            # 划分数据集
            self.status_signal.emit("正在划分数据集...")
            train_size = split_sizes.get('train', 0)
            val_size = split_sizes.get('val', 0)
            test_size = split_sizes.get('test', 0)
            
            train_data = all_data[:train_size]
            val_data = all_data[train_size:train_size + val_size]
            test_data = all_data[train_size + val_size:train_size + val_size + test_size]
            
            # 检查数据交叉污染
            self.status_signal.emit("检查数据集间的交叉污染...")
            sets = {
                "train": train_data,
                "val": val_data,
                "test": test_data
            }
            name_mapping = {
                "train": "训练集",
                "val": "验证集",
                "test": "测试集"
            }
            
            if not self._check_dataset_overlap(sets, name_mapping):
                self.error_signal.emit("数据集之间存在交叉污染！请尝试调整随机种子或数据集大小。")
                self.finished_signal.emit(False, "处理失败：数据集交叉污染")
                return
                
            self.progress_signal.emit(70)
            
            # 保存数据集
            self.status_signal.emit("正在保存数据集...")
            saved_files = []
            
            # 确保输出目录存在
            os.makedirs(output_dir, exist_ok=True)
            
            # 保存训练集
            if train_size > 0:
                train_format = output_formats.get('train', 'json')
                train_filename = os.path.join(output_dir, f"train_{train_size}.{train_format}")
                self._save_dataset(train_data, train_filename, 'train', train_format)
                saved_files.append(train_filename)
            
            # 保存验证集
            if val_size > 0:
                val_format = output_formats.get('val', 'jsonl')
                val_filename = os.path.join(output_dir, f"val_{val_size}.{val_format}")
                self._save_dataset(val_data, val_filename, 'val', val_format)
                saved_files.append(val_filename)
            
            # 保存测试集
            if test_size > 0:
                test_format = output_formats.get('test', 'jsonl')
                test_filename = os.path.join(output_dir, f"test_{test_size}.{test_format}")
                self._save_dataset(test_data, test_filename, 'test', test_format)
                saved_files.append(test_filename)
            
            self.progress_signal.emit(90)
            
            # 验证保存的数据
            self.status_signal.emit("验证保存的数据集...")
            if self._verify_saved_datasets(saved_files, output_formats):
                self.progress_signal.emit(100)
                self.status_signal.emit("数据集处理完成！")
                self.finished_signal.emit(True, f"成功处理数据集并保存到 {output_dir}")
            else:
                self.error_signal.emit("数据集验证失败！请检查保存的文件。")
                self.finished_signal.emit(False, "处理失败：数据集验证未通过")
        
        except Exception as e:
            self.error_signal.emit(f"处理过程中发生错误: {str(e)}")
            self.finished_signal.emit(False, f"处理失败: {str(e)}")
    
    def _load_from_huggingface(self, dataset_name):
        """从Hugging Face加载数据集"""
        self.status_signal.emit(f"正在从Hugging Face加载数据集: {dataset_name}...")
        dataset = load_dataset(dataset_name)
        main_split = list(dataset.keys())[0]
        return dataset[main_split]
    
    def _load_from_github(self, repo_url):
        """从GitHub加载数据集"""
        self.status_signal.emit(f"正在从GitHub克隆仓库: {repo_url}...")
        
        # 创建临时目录
        temp_dir = tempfile.mkdtemp()
        
        try:
            # 克隆仓库
            git.Repo.clone_from(repo_url, temp_dir, depth=1)
            
            # 查找JSON文件
            data = []
            json_files = list(Path(temp_dir).glob('**/*.json')) + list(Path(temp_dir).glob('**/*.jsonl'))
            
            if not json_files:
                raise ValueError(f"在仓库中未找到JSON或JSONL数据文件")
            
            # 使用最大的JSON文件
            largest_file = max(json_files, key=lambda x: x.stat().st_size)
            self.status_signal.emit(f"找到数据文件: {largest_file.name}")
            
            # 读取数据
            with open(largest_file, 'r', encoding='utf-8') as f:
                if largest_file.suffix == '.json':
                    data = json.load(f)
                else:  # .jsonl
                    data = [json.loads(line) for line in f]
            
            return data
            
        finally:
            # 清理临时目录
            import shutil
            shutil.rmtree(temp_dir, ignore_errors=True)
    
    def _load_from_url(self, url):
        """从URL下载并加载数据集"""
        self.status_signal.emit(f"正在从URL下载数据: {url}...")
        
        # 创建临时文件
        temp_file = tempfile.NamedTemporaryFile(delete=False)
        temp_file.close()
        
        try:
            # 下载文件
            urllib.request.urlretrieve(url, temp_file.name)
            
            # 检查文件类型
            data = []
            
            # 如果是JSON或JSONL
            if url.endswith('.json') or url.endswith('.jsonl'):
                with open(temp_file.name, 'r', encoding='utf-8') as f:
                    if url.endswith('.json'):
                        data = json.load(f)
                    else:  # .jsonl
                        data = [json.loads(line) for line in f]
            
            # 如果是ZIP
            elif url.endswith('.zip'):
                temp_dir = tempfile.mkdtemp()
                
                with zipfile.ZipFile(temp_file.name, 'r') as zip_ref:
                    zip_ref.extractall(temp_dir)
                
                # 查找JSON文件
                json_files = list(Path(temp_dir).glob('**/*.json')) + list(Path(temp_dir).glob('**/*.jsonl'))
                
                if not json_files:
                    raise ValueError("ZIP文件中未找到JSON或JSONL数据文件")
                
                # 使用最大的JSON文件
                largest_file = max(json_files, key=lambda x: x.stat().st_size)
                self.status_signal.emit(f"在ZIP文件中找到数据: {largest_file.name}")
                
                with open(largest_file, 'r', encoding='utf-8') as f:
                    if largest_file.suffix == '.json':
                        data = json.load(f)
                    else:  # .jsonl
                        data = [json.loads(line) for line in f]
                
                # 清理临时目录
                import shutil
                shutil.rmtree(temp_dir, ignore_errors=True)
            
            else:
                raise ValueError(f"不支持的文件类型: {url}，目前仅支持 .json, .jsonl 和 .zip")
            
            return data
            
        finally:
            # 清理临时文件
            if os.path.exists(temp_file.name):
                os.unlink(temp_file.name)
    
    def _load_from_local(self, file_path):
        """从本地文件加载数据集"""
        self.status_signal.emit(f"正在加载本地文件: {file_path}...")
        data = []
        try:
            if file_path.endswith('.json'):
                with open(file_path, 'r', encoding='utf-8') as f:
                    data = json.load(f)
            elif file_path.endswith('.jsonl'):
                with open(file_path, 'r', encoding='utf-8') as f:
                    data = [json.loads(line) for line in f]
            else:
                raise ValueError("不支持的文件格式，仅支持 .json 和 .jsonl")
        except Exception as e:
            self.error_signal.emit(f"加载本地文件失败: {str(e)}")
            raise
        return data
    
    def _filter_non_ascii(self, data):
        """过滤包含非ASCII字符的数据"""
        filtered_data = []
        filtered_count = 0
        
        for i, item in enumerate(data):
            if not self.is_running:
                break
                
            # 每处理100条数据更新一次进度
            if i % 100 == 0:
                self.status_signal.emit(f"过滤进度: {i}/{len(data)}")
            
            # 检查所有字符串字段
            is_ascii_item = True
            for key, value in item.items():
                if isinstance(value, str) and not self._is_ascii(value):
                    is_ascii_item = False
                    break
            
            if is_ascii_item:
                filtered_data.append(item)
            else:
                filtered_count += 1
        
        return filtered_data, filtered_count
    
    def _is_ascii(self, s):
        """检查字符串是否只包含ASCII字符"""
        # 确保s不是None
        if s is None:
            return True
        return all(ord(c) < 128 for c in s)
    
    def _check_dataset_overlap(self, sets, name_mapping):
        """检查数据集之间是否有重叠"""
        # 使用问题内容的哈希值作为唯一标识
        problem_hashes = {}
        
        for set_name, dataset in sets.items():
            for item in dataset:
                # 提取问题文本（尝试不同的字段名）
                problem = item.get("problem", "") or item.get("instruction", "") or \
                         item.get("question", "") or item.get("text", "") or ""
                
                problem_hash = hashlib.md5(problem.encode()).hexdigest()
                
                if problem_hash in problem_hashes:
                    self.status_signal.emit(f"警告: 发现重复问题!")
                    self.status_signal.emit(f"在 {name_mapping[set_name]} 和 {name_mapping[problem_hashes[problem_hash]]} 中发现相同问题")
                    return False
                
                problem_hashes[problem_hash] = set_name
        
        return True
    
    def _save_dataset(self, data_subset, filename, split_type, file_format):
        """保存数据集到指定格式"""
        self.status_signal.emit(f"正在保存{split_type}集到: {filename}")
        
        if split_type == 'train':
            # 训练集通常使用指令调优格式
            items = []
            for item in data_subset:
                # 尝试适配不同数据集格式
                problem = item.get("problem", "") or item.get("instruction", "") or \
                         item.get("question", "") or item.get("text", "") or ""
                
                solution = item.get("solution", "") or item.get("output", "") or \
                          item.get("answer", "") or item.get("response", "") or ""
                
                record = {
                    "instruction": problem,
                    "input": "",
                    "output": solution or ""
                }
                items.append(record)
            
            # 保存为指定格式
            if file_format.lower() == 'json':
                with open(filename, 'w', encoding='utf-8') as f:
                    json.dump(items, f, ensure_ascii=True, indent=2)
            else:  # jsonl
                with open(filename, 'w', encoding='utf-8') as f:
                    for item in items:
                        f.write(json.dumps(item, ensure_ascii=True) + '\n')
        
        elif split_type == 'val':
            # 验证集通常使用与训练集相同的格式
            with open(filename, 'w', encoding='utf-8') as f:
                if file_format.lower() == 'json':
                    items = []
                    for item in data_subset:
                        problem = item.get("problem", "") or item.get("instruction", "") or \
                                 item.get("question", "") or item.get("text", "") or ""
                        
                        solution = item.get("solution", "") or item.get("output", "") or \
                                  item.get("answer", "") or item.get("response", "") or ""
                        
                        record = {
                            "instruction": problem,
                            "input": "",
                            "output": solution or ""
                        }
                        items.append(record)
                    json.dump(items, f, ensure_ascii=True, indent=2)
                else:  # jsonl
                    for item in data_subset:
                        problem = item.get("problem", "") or item.get("instruction", "") or \
                                 item.get("question", "") or item.get("text", "") or ""
                        
                        solution = item.get("solution", "") or item.get("output", "") or \
                                  item.get("answer", "") or item.get("response", "") or ""
                        
                        record = {
                            "instruction": problem,
                            "input": "",
                            "output": solution or ""
                        }
                        f.write(json.dumps(record, ensure_ascii=True) + '\n')
        
        elif split_type == 'test':
            # 测试集通常使用问答评估格式
            with open(filename, 'w', encoding='utf-8') as f:
                if file_format.lower() == 'json':
                    items = []
                    for item in data_subset:
                        problem = item.get("problem", "") or item.get("instruction", "") or \
                                 item.get("question", "") or item.get("text", "") or ""
                        
                        answer = item.get("answer", "") or item.get("output", "") or \
                                item.get("response", "") or ""
                        
                        solution = item.get("solution", "") or item.get("explanation", "") or \
                                  item.get("reasoning", "") or ""
                        
                        record = {
                            "id": str(uuid.uuid4()),
                            "question": problem,
                            "answer": answer or "",
                            "solution": solution or ""
                        }
                        items.append(record)
                    json.dump(items, f, ensure_ascii=True, indent=2)
                else:  # jsonl
                    for item in data_subset:
                        problem = item.get("problem", "") or item.get("instruction", "") or \
                                 item.get("question", "") or item.get("text", "") or ""
                        
                        answer = item.get("answer", "") or item.get("output", "") or \
                                item.get("response", "") or ""
                        
                        solution = item.get("solution", "") or item.get("explanation", "") or \
                                  item.get("reasoning", "") or ""
                        
                        record = {
                            "id": str(uuid.uuid4()),
                            "question": problem,
                            "answer": answer or "",
                            "solution": solution or ""
                        }
                        f.write(json.dumps(record, ensure_ascii=True) + '\n')
    
    def _verify_saved_datasets(self, saved_files, output_formats):
        """验证保存的数据集"""
        try:
            for file_path in saved_files:
                if not os.path.exists(file_path):
                    self.error_signal.emit(f"验证失败: 文件不存在 {file_path}")
                    return False
                
                # 检查文件大小
                file_size = os.path.getsize(file_path)
                if file_size == 0:
                    self.error_signal.emit(f"验证失败: 文件为空 {file_path}")
                    return False
                
                # 尝试读取文件确保格式正确
                try:
                    if file_path.endswith('.json'):
                        with open(file_path, 'r', encoding='utf-8') as f:
                            json.load(f)
                    elif file_path.endswith('.jsonl'):
                        with open(file_path, 'r', encoding='utf-8') as f:
                            for line in f:
                                json.loads(line)
                    else:
                        self.error_signal.emit(f"验证失败: 不支持的文件格式 {file_path}")
                        return False
                except json.JSONDecodeError as e:
                    self.error_signal.emit(f"验证失败: JSON格式错误 {file_path} - {str(e)}")
                    return False
                
                self.status_signal.emit(f"验证通过: {file_path}")
            
            return True
        except Exception as e:
            self.error_signal.emit(f"验证过程中发生错误: {str(e)}")
            return False


class DatasetToolUI(QMainWindow):
    """数据集处理工具的图形界面"""
    
    def __init__(self):
        super().__init__()
        
        self.worker = None
        self.output_dir = os.path.expanduser("~/Desktop")  # 默认保存到桌面
        
        self.init_ui()
    
    def init_ui(self):
        """初始化用户界面"""
        self.setWindowTitle("数据集处理工具")
        self.setMinimumWidth(800)
        self.setMinimumHeight(600)
        
        # 创建中央部件和主布局
        central_widget = QWidget()
        main_layout = QVBoxLayout(central_widget)
        self.setCentralWidget(central_widget)
        
        # 创建标题
        title_label = QLabel("数据集处理工具")
        title_font = QFont()
        title_font.setPointSize(16)
        title_font.setBold(True)
        title_label.setFont(title_font)
        title_label.setAlignment(Qt.AlignCenter)
        main_layout.addWidget(title_label)
        
        # 创建选项卡
        tabs = QTabWidget()
        main_layout.addWidget(tabs)
        
        # 数据源选项卡
        source_tab = QWidget()
        source_layout = QVBoxLayout(source_tab)
        tabs.addTab(source_tab, "数据源")
        
        # 数据源类型
        source_type_group = QGroupBox("选择数据源类型")
        source_type_layout = QVBoxLayout(source_type_group)
        
        self.hf_radio = QRadioButton("Hugging Face 数据集")
        self.github_radio = QRadioButton("GitHub 仓库")
        self.url_radio = QRadioButton("URL 链接")
        self.local_radio = QRadioButton("本地文件")  # 新增本地文件选项
        self.hf_radio.setChecked(True)
        
        source_type_layout.addWidget(self.hf_radio)
        source_type_layout.addWidget(self.github_radio)
        source_type_layout.addWidget(self.url_radio)
        source_type_layout.addWidget(self.local_radio)  # 添加到布局中
        
        source_layout.addWidget(source_type_group)
        
        # 连接信号
        self.hf_radio.toggled.connect(self.toggle_source_type)
        self.github_radio.toggled.connect(self.toggle_source_type)
        self.url_radio.toggled.connect(self.toggle_source_type)
        self.local_radio.toggled.connect(self.toggle_source_type)
        
        # Hugging Face配置
        self.hf_group = QGroupBox("Hugging Face 设置")
        hf_layout = QVBoxLayout(self.hf_group)
        
        hf_name_layout = QHBoxLayout()
        hf_name_label = QLabel("数据集名称:")
        self.hf_name_input = QLineEdit("AI-MO/NuminaMath-1.5")
        hf_name_layout.addWidget(hf_name_label)
        hf_name_layout.addWidget(self.hf_name_input)
        
        hf_browse_button = QPushButton("浏览数据集")
        hf_browse_button.clicked.connect(self.browse_huggingface)
        
        hf_layout.addLayout(hf_name_layout)
        hf_layout.addWidget(hf_browse_button)
        source_layout.addWidget(self.hf_group)
        
        # GitHub配置
        self.github_group = QGroupBox("GitHub 设置")
        github_layout = QVBoxLayout(self.github_group)
        
        github_repo_layout = QHBoxLayout()
        github_repo_label = QLabel("仓库URL:")
        self.github_repo_input = QLineEdit("https://github.com/username/repo")
        github_repo_layout.addWidget(github_repo_label)
        github_repo_layout.addWidget(self.github_repo_input)
        
        github_layout.addLayout(github_repo_layout)
        self.github_group.setVisible(False)
        source_layout.addWidget(self.github_group)
        
        # URL配置
        self.url_group = QGroupBox("URL 设置")
        url_layout = QVBoxLayout(self.url_group)
        
        url_input_layout = QHBoxLayout()
        url_label = QLabel("数据URL:")
        self.url_input = QLineEdit("https://example.com/dataset.json")
        url_input_layout.addWidget(url_label)
        url_input_layout.addWidget(self.url_input)
        
        url_layout.addLayout(url_input_layout)
        self.url_group.setVisible(False)
        source_layout.addWidget(self.url_group)
        
        # 本地文件配置
        self.local_group = QGroupBox("本地文件设置")
        local_layout = QVBoxLayout(self.local_group)

        local_file_layout = QHBoxLayout()
        local_file_label = QLabel("选择文件:")
        self.local_file_input = QLineEdit()
        self.local_file_input.setReadOnly(True)
        local_file_button = QPushButton("浏览...")
        local_file_button.clicked.connect(self.browse_local_file)
        local_file_layout.addWidget(local_file_label)
        local_file_layout.addWidget(self.local_file_input)
        local_file_layout.addWidget(local_file_button)

        local_layout.addLayout(local_file_layout)
        self.local_group.setVisible(False)  # 默认隐藏
        source_layout.addWidget(self.local_group)
        
        # 输出配置选项卡
        output_tab = QWidget()
        output_layout = QVBoxLayout(output_tab)
        tabs.addTab(output_tab, "输出配置")
        
        # 数据集大小设置
        size_group = QGroupBox("数据集划分大小")
        size_layout = QVBoxLayout(size_group)
        
        train_size_layout = QHBoxLayout()
        train_size_label = QLabel("训练集大小:")
        self.train_size_input = QSpinBox()
        self.train_size_input.setRange(0, 1000000)
        self.train_size_input.setValue(10000)
        train_size_layout.addWidget(train_size_label)
        train_size_layout.addWidget(self.train_size_input)
        
        val_size_layout = QHBoxLayout()
        val_size_label = QLabel("验证集大小:")
        self.val_size_input = QSpinBox()
        self.val_size_input.setRange(0, 1000000)
        self.val_size_input.setValue(3000)
        val_size_layout.addWidget(val_size_label)
        val_size_layout.addWidget(self.val_size_input)
        
        test_size_layout = QHBoxLayout()
        test_size_label = QLabel("测试集大小:")
        self.test_size_input = QSpinBox()
        self.test_size_input.setRange(0, 1000000)
        self.test_size_input.setValue(500)
        test_size_layout.addWidget(test_size_label)
        test_size_layout.addWidget(self.test_size_input)
        
        size_layout.addLayout(train_size_layout)
        size_layout.addLayout(val_size_layout)
        size_layout.addLayout(test_size_layout)
        output_layout.addWidget(size_group)
        
        # 文件格式设置
        format_group = QGroupBox("输出文件格式")
        format_layout = QVBoxLayout(format_group)
        
        train_format_layout = QHBoxLayout()
        train_format_label = QLabel("训练集格式:")
        self.train_format_combo = QComboBox()
        self.train_format_combo.addItems(["json", "jsonl"])
        train_format_layout.addWidget(train_format_label)
        train_format_layout.addWidget(self.train_format_combo)
        
        val_format_layout = QHBoxLayout()
        val_format_label = QLabel("验证集格式:")
        self.val_format_combo = QComboBox()
        self.val_format_combo.addItems(["jsonl", "json"])
        val_format_layout.addWidget(val_format_label)
        val_format_layout.addWidget(self.val_format_combo)
        
        test_format_layout = QHBoxLayout()
        test_format_label = QLabel("测试集格式:")
        self.test_format_combo = QComboBox()
        self.test_format_combo.addItems(["jsonl", "json"])
        test_format_layout.addWidget(test_format_label)
        test_format_layout.addWidget(self.test_format_combo)
        
        format_layout.addLayout(train_format_layout)
        format_layout.addLayout(val_format_layout)
        format_layout.addLayout(test_format_layout)
        output_layout.addWidget(format_group)
        
        # 其他设置
        other_group = QGroupBox("其他设置")
        other_layout = QVBoxLayout(other_group)
        
        self.filter_ascii_checkbox = QCheckBox("过滤非ASCII字符")
        self.filter_ascii_checkbox.setChecked(True)
        
        random_seed_layout = QHBoxLayout()
        random_seed_label = QLabel("随机种子:")
        self.random_seed_input = QSpinBox()
        self.random_seed_input.setRange(0, 1000000)
        self.random_seed_input.setValue(42)
        random_seed_layout.addWidget(random_seed_label)
        random_seed_layout.addWidget(self.random_seed_input)
        
        output_dir_layout = QHBoxLayout()
        output_dir_label = QLabel("输出目录:")
        self.output_dir_input = QLineEdit(self.output_dir)
        self.output_dir_input.setReadOnly(True)
        output_dir_button = QPushButton("浏览...")
        output_dir_button.clicked.connect(self.browse_output_dir)
        output_dir_layout.addWidget(output_dir_label)
        output_dir_layout.addWidget(self.output_dir_input)
        output_dir_layout.addWidget(output_dir_button)
        
        other_layout.addWidget(self.filter_ascii_checkbox)
        other_layout.addLayout(random_seed_layout)
        other_layout.addLayout(output_dir_layout)
        output_layout.addWidget(other_group)
        
        # 执行选项卡
        execute_tab = QWidget()
        execute_layout = QVBoxLayout(execute_tab)
        tabs.addTab(execute_tab, "执行")
        
        # 状态显示
        log_group = QGroupBox("处理日志")
        log_layout = QVBoxLayout(log_group)
        
        self.log_text = QTextEdit()
        self.log_text.setReadOnly(True)
        log_layout.addWidget(self.log_text)
        
        execute_layout.addWidget(log_group)
        
        # 进度条
        progress_layout = QHBoxLayout()
        progress_label = QLabel("进度:")
        self.progress_bar = QProgressBar()
        self.progress_bar.setRange(0, 100)
        progress_layout.addWidget(progress_label)
        progress_layout.addWidget(self.progress_bar)
        
        execute_layout.addLayout(progress_layout)
        
        # 按钮
        buttons_layout = QHBoxLayout()
        self.start_button = QPushButton("开始处理")
        self.start_button.clicked.connect(self.start_processing)
        self.stop_button = QPushButton("停止处理")
        self.stop_button.clicked.connect(self.stop_processing)
        self.stop_button.setEnabled(False)
        
        buttons_layout.addWidget(self.start_button)
        buttons_layout.addWidget(self.stop_button)
        
        execute_layout.addLayout(buttons_layout)
        
        # 添加底部说明
        footer_label = QLabel("由GitHub Copilot生成 | © 2025")
        footer_label.setAlignment(Qt.AlignCenter)
        main_layout.addWidget(footer_label)
        
        # 更新初始界面
        self.toggle_source_type()
        
        # 窗口居中
        self.center()
    
    def center(self):
        """将窗口居中显示"""
        geometry = self.frameGeometry()
        screen = QApplication.desktop().screenNumber(QApplication.desktop().cursor().pos())
        centerPoint = QApplication.desktop().screenGeometry(screen).center()
        geometry.moveCenter(centerPoint)
        self.move(geometry.topLeft())
    
    def toggle_source_type(self):
        """根据选择的数据源类型显示/隐藏对应的配置项"""
        self.hf_group.setVisible(self.hf_radio.isChecked())
        self.github_group.setVisible(self.github_radio.isChecked())
        self.url_group.setVisible(self.url_radio.isChecked())
        self.local_group.setVisible(self.local_radio.isChecked())  # 添加本地文件选项的显示/隐藏
    
    def browse_huggingface(self):
        """打开浏览器以查看Hugging Face数据集"""
        QDesktopServices.openUrl(QUrl("https://huggingface.co/datasets"))
    
    def browse_output_dir(self):
        """选择输出目录"""
        dir_path = QFileDialog.getExistingDirectory(self, "选择输出目录", self.output_dir)
        if (dir_path):
            self.output_dir = dir_path
            self.output_dir_input.setText(dir_path)
    
    def browse_local_file(self):
        """选择本地文件"""
        file_path, _ = QFileDialog.getOpenFileName(self, "选择本地数据集文件", "", "JSON 文件 (*.json *.jsonl);;所有文件 (*)")
        if file_path:
            self.local_file_input.setText(file_path)
    
    def start_processing(self):
        """开始处理数据集"""
        # 准备参数
        params = {
            'random_seed': self.random_seed_input.value(),
            'filter_non_ascii': self.filter_ascii_checkbox.isChecked(),
            'output_dir': self.output_dir,
            'split_sizes': {
                'train': self.train_size_input.value(),
                'val': self.val_size_input.value(),
                'test': self.test_size_input.value()
            },
            'output_formats': {
                'train': self.train_format_combo.currentText(),
                'val': self.val_format_combo.currentText(),
                'test': self.test_format_combo.currentText()
            }
        }
        
        # 根据选择的数据源类型设置参数
        if self.hf_radio.isChecked():
            params['source_type'] = 'huggingface'
            params['dataset_name'] = self.hf_name_input.text().strip()
            
            if not params['dataset_name']:
                QMessageBox.warning(self, "输入错误", "请输入Hugging Face数据集名称")
                return
        
        elif self.github_radio.isChecked():
            params['source_type'] = 'github'
            params['github_repo'] = self.github_repo_input.text().strip()
            
            if not params['github_repo'] or not params['github_repo'].startswith('https://'):
                QMessageBox.warning(self, "输入错误", "请输入有效的GitHub仓库URL")
                return
        
        elif self.url_radio.isChecked():
            params['source_type'] = 'url'
            params['dataset_url'] = self.url_input.text().strip()
            
            if not params['dataset_url'] or not params['dataset_url'].startswith('http'):
                QMessageBox.warning(self, "输入错误", "请输入有效的数据集URL")
                return
        
        elif self.local_radio.isChecked():
            params['source_type'] = 'local'
            params['local_file'] = self.local_file_input.text().strip()

            if not params['local_file'] or not os.path.exists(params['local_file']):
                QMessageBox.warning(self, "输入错误", "请选择有效的本地文件")
                return
        
        # 清空日志并重置进度条
        self.log_text.clear()
        self.progress_bar.setValue(0)
        
        # 更新UI状态
        self.start_button.setEnabled(False)
        self.stop_button.setEnabled(True)
        
        # 创建并启动工作线程
        self.worker = DatasetWorker(params)
        self.worker.progress_signal.connect(self.update_progress)
        self.worker.status_signal.connect(self.update_status)
        self.worker.error_signal.connect(self.show_error)
        self.worker.finished_signal.connect(self.processing_finished)
        self.worker.start()
    
    def stop_processing(self):
        """停止处理"""
        if self.worker and self.worker.isRunning():
            self.update_status("正在停止处理...")
            self.worker.stop()
            self.worker.wait(1000)  # 等待线程结束，设置超时时间，避免卡死
            self.update_status("处理已停止")
        
        # 更新UI状态
        self.start_button.setEnabled(True)
        self.stop_button.setEnabled(False)
    
    def update_progress(self, value):
        """更新进度条"""
        self.progress_bar.setValue(value)
    
    def update_status(self, message):
        """更新状态日志"""
        self.log_text.append(message)
        # 滚动到底部
        self.log_text.verticalScrollBar().setValue(self.log_text.verticalScrollBar().maximum())
    
    def show_error(self, message):
        """显示错误消息"""
        self.log_text.append(f"<span style='color:red;'>{message}</span>")
        # 滚动到底部
        self.log_text.verticalScrollBar().setValue(self.log_text.verticalScrollBar().maximum())
    
    def processing_finished(self, success, message):
        """处理完成的回调"""
        # 更新UI状态
        self.start_button.setEnabled(True)
        self.stop_button.setEnabled(False)
        
        if success:
            QMessageBox.information(self, "处理完成", message)
        else:
            QMessageBox.warning(self, "处理失败", message)
        
        # 显示在日志中
        status_message = f"处理{'成功' if success else '失败'}: {message}"
        self.update_status(status_message)


if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = DatasetToolUI()
    window.show()
    sys.exit(app.exec_())