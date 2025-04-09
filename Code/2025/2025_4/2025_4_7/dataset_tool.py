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
import time  # 添加time模块导入，之前缺失
from pathlib import Path

# 尝试导入PyQt5，若不存在则提示安装
try:
    from PyQt5.QtWidgets import (QApplication, QMainWindow, QWidget, QVBoxLayout, QHBoxLayout, 
                               QLabel, QLineEdit, QPushButton, QProgressBar, QComboBox, 
                               QCheckBox, QTabWidget, QTextEdit, QFileDialog, QSpinBox,
                               QGroupBox, QRadioButton, QMessageBox, QScrollArea, QSizePolicy,
                               QStyleFactory, QFrame)
    from PyQt5.QtCore import Qt, QThread, pyqtSignal, QUrl, QSize, QTimer
    from PyQt5.QtGui import QFont, QDesktopServices, QIcon, QColor, QPalette
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
    from requests.adapters import HTTPAdapter
    from urllib3.util.retry import Retry
except ImportError:
    print("requests 未安装。请运行: pip install requests")
    sys.exit(1)

class DownloadProgressTracker:
    """用于跟踪下载进度的类"""
    def __init__(self, status_callback, total_size=None):
        self.status_callback = status_callback
        self.total_size = total_size
        self.current_size = 0
        self.last_report_time = 0
        self.start_time = time.time()
    
    def update(self, block_count, block_size, total_size):
        """更新下载进度"""
        if self.total_size is None:
            self.total_size = total_size
            
        current_time = time.time()
        self.current_size = block_count * block_size
        
        # 每0.5秒更新一次，避免频繁更新UI
        if current_time - self.last_report_time >= 0.5:
            percentage = min(100, int(self.current_size * 100 / self.total_size)) if self.total_size > 0 else 0
            elapsed_time = current_time - self.start_time
            speed = self.current_size / elapsed_time if elapsed_time > 0 else 0
            
            # 格式化速度显示
            if speed < 1024:
                speed_str = f"{speed:.2f} B/s"
            elif speed < 1024 * 1024:
                speed_str = f"{speed/1024:.2f} KB/s"
            else:
                speed_str = f"{speed/(1024*1024):.2f} MB/s"
                
            # 估计剩余时间
            if speed > 0 and self.total_size > 0:
                remaining_bytes = self.total_size - self.current_size
                remaining_time = remaining_bytes / speed
                if remaining_time < 60:
                    time_str = f"{remaining_time:.0f}秒"
                elif remaining_time < 3600:
                    time_str = f"{remaining_time/60:.1f}分钟"
                else:
                    time_str = f"{remaining_time/3600:.1f}小时"
                
                status = f"下载进度: {percentage}% ({self.current_size/1024/1024:.1f}MB/{self.total_size/1024/1024:.1f}MB) - {speed_str} - 剩余时间: {time_str}"
            else:
                status = f"下载进度: {percentage}% ({self.current_size/1024/1024:.1f}MB) - {speed_str}"
                
            self.status_callback(status)
            self.last_report_time = current_time

class DatasetWorker(QThread):
    """后台工作线程，用于处理耗时的数据集操作"""
    progress_signal = pyqtSignal(int)
    status_signal = pyqtSignal(str)
    error_signal = pyqtSignal(str)
    finished_signal = pyqtSignal(bool, str)  # 成功/失败, 消息
    download_progress_signal = pyqtSignal(int, int)  # 当前大小, 总大小
    
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
            
            self.status_signal.emit("初始化数据处理流程...")
            self.progress_signal.emit(1)
            
            # 设置每个阶段的进度比例
            progress_stages = {
                'load_data': (0, 30),      # 加载数据阶段: 0-30%
                'process_data': (30, 50),  # 处理数据阶段: 30-50%
                'split_data': (50, 70),    # 拆分数据阶段: 50-70%
                'save_data': (70, 90),     # 保存数据阶段: 70-90%
                'verify_data': (90, 100)   # 验证数据阶段: 90-100%
            }
            
            # 根据来源类型获取数据
            self.status_signal.emit("准备加载数据...")
            self.progress_signal.emit(progress_stages['load_data'][0])
            
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
                
            self.progress_signal.emit(progress_stages['process_data'][0])
            self.status_signal.emit(f"数据加载完成，共 {len(data)} 条记录")
            
            # 随机打乱数据
            self.status_signal.emit("正在随机打乱数据...")
            all_data = list(data)
            random.seed(random_seed)
            random.shuffle(all_data)
            
            self.progress_signal.emit(progress_stages['process_data'][0] + 5)
            
            # 过滤非ASCII字符（如果需要）
            if filter_non_ascii:
                self.status_signal.emit("正在过滤非ASCII字符...")
                filtered_data, filtered_count = self._filter_non_ascii(all_data, 
                                                                     progress_stages['process_data'][0] + 5, 
                                                                     progress_stages['process_data'][1])
                self.status_signal.emit(f"过滤了 {filtered_count}/{len(all_data)} 条记录 ({filtered_count/len(all_data)*100:.2f}%)")
                all_data = filtered_data
            else:
                self.progress_signal.emit(progress_stages['process_data'][1])
            
            # 检查数据量是否足够
            total_needed = sum(split_sizes.values())
            if len(all_data) < total_needed:
                self.status_signal.emit(f"警告: 可用数据量({len(all_data)})少于要求数量({total_needed})，将按比例调整...")
                ratio = len(all_data) / total_needed
                for key in split_sizes:
                    split_sizes[key] = int(split_sizes[key] * ratio)
                split_sizes['test'] = min(split_sizes['test'], len(all_data) - split_sizes['train'] - split_sizes['val'])
                self.status_signal.emit(f"调整后的数据集大小: 训练集={split_sizes['train']}, 验证集={split_sizes['val']}, 测试集={split_sizes['test']}")
            
            # 划分数据集
            self.status_signal.emit("正在划分数据集...")
            self.progress_signal.emit(progress_stages['split_data'][0])
            
            train_size = split_sizes.get('train', 0)
            val_size = split_sizes.get('val', 0)
            test_size = split_sizes.get('test', 0)
            
            train_data = all_data[:train_size] if train_size > 0 else []
            val_data = all_data[train_size:train_size + val_size] if val_size > 0 else []
            test_data = all_data[train_size + val_size:train_size + val_size + test_size] if test_size > 0 else []
            
            self.progress_signal.emit(progress_stages['split_data'][0] + 10)
            
            # 检查数据交叉污染
            if train_size > 0 or val_size > 0 or test_size > 0:
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
            
            self.progress_signal.emit(progress_stages['split_data'][1])
            
            # 保存数据集
            self.status_signal.emit("正在保存数据集...")
            saved_files = []
            
            # 确保输出目录存在
            os.makedirs(output_dir, exist_ok=True)
            
            # 计算保存进度增量
            save_progress_increment = (progress_stages['save_data'][1] - progress_stages['save_data'][0]) / 3  # 3个数据集
            current_progress = progress_stages['save_data'][0]
            
            # 保存训练集
            if train_size > 0:
                self.status_signal.emit(f"正在保存训练集 ({train_size} 条记录)...")
                train_format = output_formats.get('train', 'json')
                train_filename = os.path.join(output_dir, f"train_{train_size}.{train_format}")
                self._save_dataset(train_data, train_filename, 'train', train_format)
                saved_files.append(train_filename)
                current_progress += save_progress_increment
                self.progress_signal.emit(int(current_progress))
            
            # 保存验证集
            if val_size > 0:
                self.status_signal.emit(f"正在保存验证集 ({val_size} 条记录)...")
                val_format = output_formats.get('val', 'jsonl')
                val_filename = os.path.join(output_dir, f"val_{val_size}.{val_format}")
                self._save_dataset(val_data, val_filename, 'val', val_format)
                saved_files.append(val_filename)
                current_progress += save_progress_increment
                self.progress_signal.emit(int(current_progress))
            
            # 保存测试集
            if test_size > 0:
                self.status_signal.emit(f"正在保存测试集 ({test_size} 条记录)...")
                test_format = output_formats.get('test', 'jsonl')
                test_filename = os.path.join(output_dir, f"test_{test_size}.{test_format}")
                self._save_dataset(test_data, test_filename, 'test', test_format)
                saved_files.append(test_filename)
                current_progress += save_progress_increment
                self.progress_signal.emit(int(current_progress))
            
            self.progress_signal.emit(progress_stages['verify_data'][0])
            
            # 验证保存的数据
            if saved_files:
                self.status_signal.emit("验证保存的数据集...")
                if self._verify_saved_datasets(saved_files, output_formats):
                    self.progress_signal.emit(100)
                    self.status_signal.emit("✅ 数据集处理成功！")
                    
                    # 汇总处理结果
                    summary = []
                    if train_size > 0:
                        summary.append(f"训练集: {train_size} 条记录")
                    if val_size > 0:
                        summary.append(f"验证集: {val_size} 条记录")
                    if test_size > 0:
                        summary.append(f"测试集: {test_size} 条记录")
                    
                    summary_text = "、".join(summary)
                    self.finished_signal.emit(True, f"成功处理并保存了{summary_text}到 {output_dir}")
                else:
                    self.error_signal.emit("❌ 数据集验证失败！请检查保存的文件。")
                    self.finished_signal.emit(False, "处理失败：数据集验证未通过")
            else:
                self.status_signal.emit("⚠️ 没有数据需要保存")
                self.finished_signal.emit(True, "处理完成，但没有数据需要保存")
        
        except Exception as e:
            import traceback
            self.error_signal.emit(f"❌ 处理过程中发生错误: {str(e)}")
            self.error_signal.emit(traceback.format_exc())
            self.finished_signal.emit(False, f"处理失败: {str(e)}")
    
    def _load_from_huggingface(self, dataset_name):
        """从Hugging Face加载数据集"""
        self.status_signal.emit(f"🔄 正在从Hugging Face加载数据集: {dataset_name}...")
        
        try:
            dataset = load_dataset(dataset_name)
            self.status_signal.emit(f"✅ 成功加载数据集: {dataset_name}")
            
            # 选择第一个可用的分片
            main_split = list(dataset.keys())[0]
            self.status_signal.emit(f"使用数据集分片: {main_split}，包含 {len(dataset[main_split])} 条记录")
            
            return dataset[main_split]
        except Exception as e:
            self.error_signal.emit(f"❌ 无法加载Hugging Face数据集: {str(e)}")
            raise
    
    def _create_session_with_retry(self):
        """创建带有重试机制的HTTP会话"""
        session = requests.Session()
        retry = Retry(
            total=5,
            backoff_factor=0.3,
            status_forcelist=[500, 502, 503, 504]
        )
        adapter = HTTPAdapter(max_retries=retry)
        session.mount('http://', adapter)
        session.mount('https://', adapter)
        return session
    
    def _load_from_github(self, repo_url):
        """从GitHub加载数据集"""
        self.status_signal.emit(f"🔄 正在从GitHub克隆仓库: {repo_url}...")
        
        # 创建临时目录
        temp_dir = tempfile.mkdtemp()
        
        try:
            # 克隆仓库
            git.Repo.clone_from(repo_url, temp_dir, depth=1)
            self.status_signal.emit("✅ 仓库克隆完成")
            
            # 查找JSON文件
            data = []
            json_files = list(Path(temp_dir).glob('**/*.json')) + list(Path(temp_dir).glob('**/*.jsonl'))
            
            if not json_files:
                raise ValueError(f"在仓库中未找到JSON或JSONL数据文件")
            
            self.status_signal.emit(f"找到 {len(json_files)} 个JSON/JSONL文件")
            
            # 使用最大的JSON文件
            largest_file = max(json_files, key=lambda x: x.stat().st_size)
            file_size_mb = largest_file.stat().st_size / (1024 * 1024)
            self.status_signal.emit(f"选择最大的数据文件: {largest_file.name} ({file_size_mb:.2f}MB)")
            
            # 读取数据
            with open(largest_file, 'r', encoding='utf-8') as f:
                if largest_file.suffix == '.json':
                    data = json.load(f)
                    self.status_signal.emit(f"加载JSON数据, 包含 {len(data)} 条记录")
                else:  # .jsonl
                    data = [json.loads(line) for line in f]
                    self.status_signal.emit(f"加载JSONL数据, 包含 {len(data)} 条记录")
            
            return data
            
        finally:
            # 清理临时目录
            import shutil
            self.status_signal.emit("清理临时文件...")
            shutil.rmtree(temp_dir, ignore_errors=True)
    
    def _load_from_url(self, url):
        """从URL下载并加载数据集"""
        import time
        self.status_signal.emit(f"🔄 正在从URL下载数据: {url}...")
        
        # 创建临时文件
        temp_file = tempfile.NamedTemporaryFile(delete=False)
        temp_file.close()
        
        try:
            # 使用requests下载并显示进度
            self.status_signal.emit("开始下载文件...")
            
            # 先获取文件大小
            session = self._create_session_with_retry()
            response = session.head(url, allow_redirects=True)
            total_size = int(response.headers.get('content-length', 0))
            
            # 下载文件并显示进度
            start_time = time.time()
            downloaded_size = 0
            last_update_time = 0
            
            # 打开流式请求
            with session.get(url, stream=True) as r:
                r.raise_for_status()
                with open(temp_file.name, 'wb') as f:
                    for chunk in r.iter_content(chunk_size=8192):
                        if not self.is_running:
                            raise InterruptedError("下载被用户取消")
                        
                        if chunk:  # 过滤keep-alive新块
                            f.write(chunk)
                            downloaded_size += len(chunk)
                            
                            # 每0.5秒更新一次进度
                            current_time = time.time()
                            if current_time - last_update_time > 0.5:
                                elapsed = current_time - start_time
                                speed = downloaded_size / elapsed if elapsed > 0 else 0
                                
                                # 格式化速度
                                if speed < 1024:
                                    speed_str = f"{speed:.1f} B/s"
                                elif speed < 1024 * 1024:
                                    speed_str = f"{speed/1024:.1f} KB/s"
                                else:
                                    speed_str = f"{speed/(1024*1024):.1f} MB/s"
                                
                                # 计算剩余时间
                                percent = (downloaded_size / total_size * 100) if total_size > 0 else 0
                                
                                if total_size > 0 and speed > 0:
                                    remaining_bytes = total_size - downloaded_size
                                    estimated_time = remaining_bytes / speed
                                    
                                    if estimated_time < 60:
                                        time_str = f"{estimated_time:.1f}秒"
                                    elif estimated_time < 3600:
                                        time_str = f"{estimated_time/60:.1f}分钟"
                                    else:
                                        time_str = f"{estimated_time/3600:.1f}小时"
                                    
                                    progress_msg = f"下载进度: {percent:.1f}% ({downloaded_size/(1024*1024):.1f}MB/{total_size/(1024*1024):.1f}MB) - {speed_str} - 预计剩余: {time_str}"
                                else:
                                    progress_msg = f"下载进度: {percent:.1f}% ({downloaded_size/(1024*1024):.1f}MB) - {speed_str}"
                                
                                self.status_signal.emit(progress_msg)
                                self.download_progress_signal.emit(downloaded_size, total_size)
                                last_update_time = current_time
            
            self.status_signal.emit(f"✅ 文件下载完成 ({downloaded_size/(1024*1024):.2f}MB)")
            
            # 检查文件类型
            data = []
            
            # 如果是JSON或JSONL
            if url.endswith('.json') or url.endswith('.jsonl'):
                with open(temp_file.name, 'r', encoding='utf-8') as f:
                    if url.endswith('.json'):
                        self.status_signal.emit("解析JSON文件...")
                        data = json.load(f)
                        self.status_signal.emit(f"解析完成, 包含 {len(data)} 条记录")
                    else:  # .jsonl
                        self.status_signal.emit("解析JSONL文件...")
                        data = [json.loads(line) for line in f]
                        self.status_signal.emit(f"解析完成, 包含 {len(data)} 条记录")
            
            # 如果是ZIP
            elif url.endswith('.zip'):
                self.status_signal.emit("解压ZIP文件...")
                temp_dir = tempfile.mkdtemp()
                
                with zipfile.ZipFile(temp_file.name, 'r') as zip_ref:
                    zip_ref.extractall(temp_dir)
                    
                self.status_signal.emit("查找JSON/JSONL文件...")
                json_files = list(Path(temp_dir).glob('**/*.json')) + list(Path(temp_dir).glob('**/*.jsonl'))
                
                if not json_files:
                    raise ValueError("ZIP文件中未找到JSON或JSONL数据文件")
                
                # 使用最大的JSON文件
                largest_file = max(json_files, key=lambda x: x.stat().st_size)
                file_size_mb = largest_file.stat().st_size / (1024 * 1024)
                self.status_signal.emit(f"使用最大的文件: {largest_file.name} ({file_size_mb:.2f}MB)")
                
                with open(largest_file, 'r', encoding='utf-8') as f:
                    if largest_file.suffix == '.json':
                        self.status_signal.emit("解析JSON文件...")
                        data = json.load(f)
                    else:  # .jsonl
                        self.status_signal.emit("解析JSONL文件...")
                        data = [json.loads(line) for line in f]
                
                self.status_signal.emit(f"解析完成, 包含 {len(data)} 条记录")
                
                # 清理临时目录
                import shutil
                shutil.rmtree(temp_dir, ignore_errors=True)
            
            else:
                raise ValueError(f"不支持的文件类型: {url}，目前仅支持 .json, .jsonl 和 .zip")
            
            return data
            
        except requests.RequestException as e:
            self.error_signal.emit(f"下载失败: {str(e)}")
            raise
        except json.JSONDecodeError as e:
            self.error_signal.emit(f"JSON解析错误: {str(e)}")
            raise
        except Exception as e:
            self.error_signal.emit(f"加载URL数据时出错: {str(e)}")
            raise
        finally:
            # 清理临时文件
            if os.path.exists(temp_file.name):
                os.unlink(temp_file.name)
    
    def _load_from_local(self, file_path):
        """从本地文件加载数据集"""
        self.status_signal.emit(f"🔄 正在加载本地文件: {file_path}...")
        data = []
        try:
            file_size_mb = os.path.getsize(file_path) / (1024 * 1024)
            self.status_signal.emit(f"文件大小: {file_size_mb:.2f}MB")
            
            if file_path.endswith('.json'):
                with open(file_path, 'r', encoding='utf-8') as f:
                    self.status_signal.emit("解析JSON文件...")
                    data = json.load(f)
                    self.status_signal.emit(f"✅ 解析完成, 加载了 {len(data)} 条记录")
            elif file_path.endswith('.jsonl'):
                with open(file_path, 'r', encoding='utf-8') as f:
                    self.status_signal.emit("逐行解析JSONL文件...")
                    line_count = 0
                    for line in f:
                        data.append(json.loads(line))
                        line_count += 1
                        if line_count % 1000 == 0:  # 每1000行更新一次
                            self.status_signal.emit(f"已处理 {line_count} 行...")
                    self.status_signal.emit(f"✅ 解析完成, 加载了 {len(data)} 条记录")
            else:
                raise ValueError("不支持的文件格式，仅支持 .json 和 .jsonl")
        except Exception as e:
            self.error_signal.emit(f"❌ 加载本地文件失败: {str(e)}")
            raise
        return data
    
    def _filter_non_ascii(self, data, start_progress, end_progress):
        """过滤包含非ASCII字符的数据, 并更新进度"""
        filtered_data = []
        filtered_count = 0
        total_items = len(data)
        
        self.status_signal.emit(f"开始过滤非ASCII字符 (共 {total_items} 条记录)...")
        
        for i, item in enumerate(data):
            if not self.is_running:
                break
                
            # 更新进度
            if i % 100 == 0 or i == total_items - 1:
                progress = start_progress + (end_progress - start_progress) * (i / total_items)
                self.progress_signal.emit(int(progress))
                
                # 每100条更新一次状态
                if i % 1000 == 0:
                    self.status_signal.emit(f"过滤进度: {i}/{total_items} ({i/total_items*100:.1f}%)")
            
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
        
        # 最终进度更新
        self.progress_signal.emit(end_progress)
        
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
            if not dataset:  # 跳过空数据集
                continue
                
            self.status_signal.emit(f"检查 {name_mapping[set_name]} 的唯一性...")
            
            for item in dataset:
                # 提取问题文本（尝试不同的字段名）
                problem = item.get("problem", "") or item.get("instruction", "") or \
                         item.get("question", "") or item.get("text", "") or ""
                
                problem_hash = hashlib.md5(problem.encode()).hexdigest()
                
                if problem_hash in problem_hashes:
                    self.status_signal.emit(f"⚠️ 警告: 发现重复问题!")
                    self.status_signal.emit(f"在 {name_mapping[set_name]} 和 {name_mapping[problem_hashes[problem_hash]]} 中发现相同问题")
                    return False
                
                problem_hashes[problem_hash] = set_name
        
        self.status_signal.emit("✅ 数据集检查通过，没有发现重复内容")
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
                    self.error_signal.emit(f"❌ 验证失败: 文件不存在 {file_path}")
                    return False
                
                # 检查文件大小
                file_size = os.path.getsize(file_path)
                if (file_size == 0):
                    self.error_signal.emit(f"❌ 验证失败: 文件为空 {file_path}")
                    return False
                
                file_size_kb = file_size / 1024
                
                # 尝试读取文件确保格式正确
                try:
                    if file_path.endswith('.json'):
                        with open(file_path, 'r', encoding='utf-8') as f:
                            data = json.load(f)
                            self.status_signal.emit(f"✅ JSON验证通过: {file_path} ({file_size_kb:.1f}KB, {len(data)} 条记录)")
                    elif file_path.endswith('.jsonl'):
                        line_count = 0
                        with open(file_path, 'r', encoding='utf-8') as f:
                            for line in f:
                                json.loads(line)
                                line_count += 1
                        self.status_signal.emit(f"✅ JSONL验证通过: {file_path} ({file_size_kb:.1f}KB, {line_count} 条记录)")
                    else:
                        self.error_signal.emit(f"❌ 验证失败: 不支持的文件格式 {file_path}")
                        return False
                except json.JSONDecodeError as e:
                    self.error_signal.emit(f"❌ 验证失败: JSON格式错误 {file_path} - {str(e)}")
                    return False
            
            return True
        except Exception as e:
            self.error_signal.emit(f"❌ 验证过程中发生错误: {str(e)}")
            return False


class DatasetToolUI(QMainWindow):
    """数据集处理工具的图形界面"""
    
    def __init__(self):
        super().__init__()
        
        self.worker = None
        self.output_dir = os.path.expanduser("~/Desktop")  # 默认保存到桌面
        
        # 设置应用样式
        self.setup_style()
        self.init_ui()
    
    def setup_style(self):
        """设置应用的样式表，实现更现代的外观"""
        # 使用Fusion风格作为基础
        QApplication.setStyle(QStyleFactory.create('Fusion'))
        
        # 创建自定义调色板
        palette = QPalette()
        
        # 设置基础颜色
        palette.setColor(QPalette.Window, QColor(240, 240, 245))
        palette.setColor(QPalette.WindowText, QColor(35, 35, 35))
        palette.setColor(QPalette.Base, QColor(255, 255, 255))
        palette.setColor(QPalette.AlternateBase, QColor(245, 245, 250))
        palette.setColor(QPalette.Text, QColor(35, 35, 35))
        palette.setColor(QPalette.Button, QColor(250, 250, 252))
        palette.setColor(QPalette.ButtonText, QColor(35, 35, 35))
        
        # 设置高亮颜色
        palette.setColor(QPalette.Highlight, QColor(72, 118, 255))
        palette.setColor(QPalette.HighlightedText, QColor(255, 255, 255))
        
        # 设置禁用状态的颜色
        palette.setColor(QPalette.Disabled, QPalette.Text, QColor(150, 150, 150))
        palette.setColor(QPalette.Disabled, QPalette.ButtonText, QColor(150, 150, 150))
        
        # 应用调色板
        QApplication.setPalette(palette)
        
        # 设置全局样式表 - 修复：通过获取当前应用程序实例来设置样式表
        app = QApplication.instance()
        app.setStyleSheet("""
            QMainWindow {
                background-color: #F0F0F5;
            }
            
            QTabWidget::pane {
                border: 1px solid #dcdcdc;
                border-radius: 4px;
                background-color: white;
            }
            
            QTabBar::tab {
                background-color: #f0f0f0;
                border: 1px solid #dcdcdc;
                border-bottom: none;
                border-top-left-radius: 4px;
                border-top-right-radius: 4px;
                padding: 8px 16px;
                margin-right: 2px;
            }
            
            QTabBar::tab:selected {
                background-color: white;
                border-bottom: none;
            }
            
            QGroupBox {
                font-weight: bold;
                border: 1px solid #dcdcdc;
                border-radius: 4px;
                margin-top: 12px;
                padding-top: 24px;
                background-color: white;
            }
            
            QGroupBox::title {
                subcontrol-origin: margin;
                subcontrol-position: top left;
                left: 8px;
                padding: 0 5px;
            }
            
            QPushButton {
                background-color: #4876FF;
                color: white;
                border: none;
                border-radius: 4px;
                padding: 8px 16px;
                min-width: 80px;
                font-weight: bold;
            }
            
            QPushButton:hover {
                background-color: #5A87FF;
            }
            
            QPushButton:pressed {
                background-color: #3A67E0;
            }
            
            QPushButton:disabled {
                background-color: #CCCCCC;
            }
            
            QLineEdit, QComboBox, QSpinBox {
                border: 1px solid #dcdcdc;
                border-radius: 4px;
                padding: 6px;
                background-color: white;
            }
            
            QProgressBar {
                border: 1px solid #dcdcdc;
                border-radius: 4px;
                background-color: #f0f0f0;
                text-align: center;
                height: 24px;
            }
            
            QProgressBar::chunk {
                background-color: qlineargradient(x1:0, y1:0, x2:1, y2:0, stop:0 #4876FF, stop:1 #5A87FF);
                border-radius: 4px;
            }
            
            QTextEdit {
                border: 1px solid #dcdcdc;
                border-radius: 4px;
                background-color: white;
                padding: 4px;
                selection-background-color: #4876FF;
                selection-color: white;
            }
            
            QRadioButton::indicator {
                width: 16px;
                height: 16px;
            }
            
            QCheckBox::indicator {
                width: 16px;
                height: 16px;
            }
        """)
        
    def init_ui(self):
        """初始化用户界面"""
        self.setWindowTitle("数据集处理工具")
        self.setMinimumWidth(800)
        self.setMinimumHeight(600)
        
        # 创建中央部件和主布局
        central_widget = QWidget()
        main_layout = QVBoxLayout(central_widget)
        main_layout.setContentsMargins(20, 20, 20, 20)
        main_layout.setSpacing(15)
        self.setCentralWidget(central_widget)
        
        # 创建标题
        title_layout = QHBoxLayout()
        title_label = QLabel("数据集处理工具")
        title_font = QFont()
        title_font.setPointSize(18)
        title_font.setBold(True)
        title_label.setFont(title_font)
        title_label.setAlignment(Qt.AlignCenter)
        
        # 添加标题分隔线
        title_line = QFrame()
        title_line.setFrameShape(QFrame.HLine)
        title_line.setFrameShadow(QFrame.Sunken)
        
        main_layout.addWidget(title_label)
        main_layout.addWidget(title_line)
        
        # 创建选项卡
        tabs = QTabWidget()
        tabs.setDocumentMode(True)  # 使标签页更现代
        main_layout.addWidget(tabs)
        
        # 数据源选项卡
        source_tab = QWidget()
        source_layout = QVBoxLayout(source_tab)
        source_layout.setContentsMargins(15, 15, 15, 15)
        source_layout.setSpacing(15)
        tabs.addTab(source_tab, "数据源")
        
        # 数据源类型
        source_type_group = QGroupBox("选择数据源类型")
        source_type_layout = QVBoxLayout(source_type_group)
        source_type_layout.setContentsMargins(15, 30, 15, 15)
        source_type_layout.setSpacing(10)
        
        self.hf_radio = QRadioButton("Hugging Face 数据集")
        self.github_radio = QRadioButton("GitHub 仓库")
        self.url_radio = QRadioButton("URL 链接")
        self.local_radio = QRadioButton("本地文件")
        self.hf_radio.setChecked(True)
        
        source_type_layout.addWidget(self.hf_radio)
        source_type_layout.addWidget(self.github_radio)
        source_type_layout.addWidget(self.url_radio)
        source_type_layout.addWidget(self.local_radio)
        
        source_layout.addWidget(source_type_group)
        
        # 连接信号
        self.hf_radio.toggled.connect(self.toggle_source_type)
        self.github_radio.toggled.connect(self.toggle_source_type)
        self.url_radio.toggled.connect(self.toggle_source_type)
        self.local_radio.toggled.connect(self.toggle_source_type)
        
        # Hugging Face配置
        self.hf_group = QGroupBox("Hugging Face 设置")
        hf_layout = QVBoxLayout(self.hf_group)
        hf_layout.setContentsMargins(15, 30, 15, 15)
        hf_layout.setSpacing(10)
        
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
        github_layout.setContentsMargins(15, 30, 15, 15)
        github_layout.setSpacing(10)
        
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
        url_layout.setContentsMargins(15, 30, 15, 15)
        url_layout.setSpacing(10)
        
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
        local_layout.setContentsMargins(15, 30, 15, 15)
        local_layout.setSpacing(10)

        local_file_layout = QHBoxLayout()
        local_file_label = QLabel("选择文件:")
        self.local_file_input = QLineEdit()
        self.local_file_input.setReadOnly(True)
        local_file_button = QPushButton("浏览...")
        local_file_button.setMaximumWidth(100)
        local_file_button.clicked.connect(self.browse_local_file)
        local_file_layout.addWidget(local_file_label)
        local_file_layout.addWidget(self.local_file_input)
        local_file_layout.addWidget(local_file_button)

        local_layout.addLayout(local_file_layout)
        self.local_group.setVisible(False)
        source_layout.addWidget(self.local_group)
        
        # 输出配置选项卡
        output_tab = QWidget()
        output_layout = QVBoxLayout(output_tab)
        output_layout.setContentsMargins(15, 15, 15, 15)
        output_layout.setSpacing(15)
        tabs.addTab(output_tab, "输出配置")
        
        # 数据集大小设置
        size_group = QGroupBox("数据集划分大小")
        size_layout = QVBoxLayout(size_group)
        size_layout.setContentsMargins(15, 30, 15, 15)
        size_layout.setSpacing(10)
        
        train_size_layout = QHBoxLayout()
        train_size_label = QLabel("训练集大小:")
        train_size_label.setMinimumWidth(80)
        self.train_size_input = QSpinBox()
        self.train_size_input.setRange(0, 1000000)
        self.train_size_input.setValue(10000)
        train_size_layout.addWidget(train_size_label)
        train_size_layout.addWidget(self.train_size_input)
        
        val_size_layout = QHBoxLayout()
        val_size_label = QLabel("验证集大小:")
        val_size_label.setMinimumWidth(80)
        self.val_size_input = QSpinBox()
        self.val_size_input.setRange(0, 1000000)
        self.val_size_input.setValue(3000)
        val_size_layout.addWidget(val_size_label)
        val_size_layout.addWidget(self.val_size_input)
        
        test_size_layout = QHBoxLayout()
        test_size_label = QLabel("测试集大小:")
        test_size_label.setMinimumWidth(80)
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
        format_layout.setContentsMargins(15, 30, 15, 15)
        format_layout.setSpacing(10)
        
        train_format_layout = QHBoxLayout()
        train_format_label = QLabel("训练集格式:")
        train_format_label.setMinimumWidth(80)
        self.train_format_combo = QComboBox()
        self.train_format_combo.addItems(["json", "jsonl"])
        train_format_layout.addWidget(train_format_label)
        train_format_layout.addWidget(self.train_format_combo)
        
        val_format_layout = QHBoxLayout()
        val_format_label = QLabel("验证集格式:")
        val_format_label.setMinimumWidth(80)
        self.val_format_combo = QComboBox()
        self.val_format_combo.addItems(["jsonl", "json"])
        val_format_layout.addWidget(val_format_label)
        val_format_layout.addWidget(self.val_format_combo)
        
        test_format_layout = QHBoxLayout()
        test_format_label = QLabel("测试集格式:")
        test_format_label.setMinimumWidth(80)
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
        other_layout.setContentsMargins(15, 30, 15, 15)
        other_layout.setSpacing(10)
        
        self.filter_ascii_checkbox = QCheckBox("过滤非ASCII字符")
        self.filter_ascii_checkbox.setChecked(True)
        
        random_seed_layout = QHBoxLayout()
        random_seed_label = QLabel("随机种子:")
        random_seed_label.setMinimumWidth(80)
        self.random_seed_input = QSpinBox()
        self.random_seed_input.setRange(0, 1000000)
        self.random_seed_input.setValue(42)
        random_seed_layout.addWidget(random_seed_label)
        random_seed_layout.addWidget(self.random_seed_input)
        
        output_dir_layout = QHBoxLayout()
        output_dir_label = QLabel("输出目录:")
        output_dir_label.setMinimumWidth(80)
        self.output_dir_input = QLineEdit(self.output_dir)
        self.output_dir_input.setReadOnly(True)
        output_dir_button = QPushButton("浏览...")
        output_dir_button.setMaximumWidth(100)
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
        execute_layout.setContentsMargins(15, 15, 15, 15)
        execute_layout.setSpacing(15)
        tabs.addTab(execute_tab, "执行")
        
        # 状态显示
        log_group = QGroupBox("处理日志")
        log_layout = QVBoxLayout(log_group)
        log_layout.setContentsMargins(15, 30, 15, 15)
        log_layout.setSpacing(10)
        
        self.log_text = QTextEdit()
        self.log_text.setReadOnly(True)
        # 设置等宽字体以便于阅读日志
        log_font = QFont("Consolas, Monaco, Monospace")
        log_font.setPointSize(9)
        self.log_text.setFont(log_font)
        log_layout.addWidget(self.log_text)
        
        execute_layout.addWidget(log_group)
        
        # 下载进度显示
        self.download_progress_bar = QProgressBar()
        self.download_progress_bar.setRange(0, 100)
        self.download_progress_bar.setValue(0)
        self.download_progress_bar.setFormat("下载进度: %p%")
        self.download_progress_bar.setVisible(False)  # 默认隐藏，只在需要时显示
        execute_layout.addWidget(self.download_progress_bar)
        
        # 进度条
        progress_group = QGroupBox("处理进度")
        progress_layout = QVBoxLayout(progress_group)
        progress_layout.setContentsMargins(15, 30, 15, 15)
        progress_layout.setSpacing(10)
        
        self.progress_bar = QProgressBar()
        self.progress_bar.setRange(0, 100)
        self.progress_bar.setValue(0)
        self.progress_bar.setTextVisible(True)
        self.progress_bar.setFormat("%p% 完成")
        
        progress_layout.addWidget(self.progress_bar)
        execute_layout.addWidget(progress_group)
        
        # 按钮
        buttons_layout = QHBoxLayout()
        buttons_layout.setSpacing(15)
        
        self.start_button = QPushButton("开始处理")
        self.start_button.clicked.connect(self.start_processing)
        
        self.stop_button = QPushButton("停止处理")
        self.stop_button.clicked.connect(self.stop_processing)
        self.stop_button.setEnabled(False)
        
        # 设置按钮样式，停止按钮使用不同的颜色
        self.stop_button.setStyleSheet("""
            QPushButton {
                background-color: #F44336;
            }
            QPushButton:hover {
                background-color: #FF5252;
            }
            QPushButton:pressed {
                background-color: #D32F2F;
            }
            QPushButton:disabled {
                background-color: #CCCCCC;
            }
        """)
        
        buttons_layout.addStretch()
        buttons_layout.addWidget(self.start_button)
        buttons_layout.addWidget(self.stop_button)
        buttons_layout.addStretch()
        
        execute_layout.addLayout(buttons_layout)
        
        # 添加底部说明
        footer_line = QFrame()
        footer_line.setFrameShape(QFrame.HLine)
        footer_line.setFrameShadow(QFrame.Sunken)
        
        footer_label = QLabel("superjackche | 2025")
        footer_label.setAlignment(Qt.AlignCenter)
        footer_font = QFont()
        footer_font.setPointSize(8)
        footer_label.setFont(footer_font)
        
        main_layout.addWidget(footer_line)
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
            
            # 将下载进度条设置为可见
            self.download_progress_bar.setVisible(True)
            self.download_progress_bar.setValue(0)
        
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
        self.worker.download_progress_signal.connect(self.update_download_progress)
        self.worker.start()
    
    def update_download_progress(self, current, total):
        """更新下载进度"""
        if total > 0:
            percentage = min(100, int(current * 100 / total))
            self.download_progress_bar.setValue(percentage)
            self.download_progress_bar.setFormat(f"下载进度: {percentage}% ({current/(1024*1024):.1f}MB/{total/(1024*1024):.1f}MB)")
        else:
            self.download_progress_bar.setValue(0)
            self.download_progress_bar.setFormat(f"下载进度: 0% ({current/(1024*1024):.1f}MB)")
    
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
        
        # 隐藏下载进度条
        self.download_progress_bar.setVisible(False)
    
    def update_progress(self, value):
        """更新进度条"""
        self.progress_bar.setValue(value)
    
    def update_status(self, message):
        """更新状态日志"""
        # 添加时间戳
        import time
        timestamp = time.strftime("%H:%M:%S", time.localtime())
        
        # 格式化消息，根据内容添加图标
        formatted_message = f"[{timestamp}] {message}"
        
        # 根据消息类型添加不同的格式
        if "✅" in message:
            html_message = f"<span style='color:#4CAF50;'>{formatted_message}</span>"
        elif "❌" in message or "失败" in message or "错误" in message:
            html_message = f"<span style='color:#F44336;'>{formatted_message}</span>"
        elif "⚠️" in message or "警告" in message:
            html_message = f"<span style='color:#FF9800;'>{formatted_message}</span>"
        elif "下载进度" in message:
            html_message = f"<span style='color:#2196F3;'>{formatted_message}</span>"
        else:
            html_message = formatted_message
            
        self.log_text.append(html_message)
        # 滚动到底部
        self.log_text.verticalScrollBar().setValue(self.log_text.verticalScrollBar().maximum())
    
    def show_error(self, message):
        """显示错误消息"""
        # 添加时间戳
        import time
        timestamp = time.strftime("%H:%M:%S", time.localtime())
        
        formatted_message = f"[{timestamp}] {message}"
        self.log_text.append(f"<span style='color:#F44336;'>{formatted_message}</span>")
        # 滚动到底部
        self.log_text.verticalScrollBar().setValue(self.log_text.verticalScrollBar().maximum())
    
    def processing_finished(self, success, message):
        """处理完成的回调"""
        # 更新UI状态
        self.start_button.setEnabled(True)
        self.stop_button.setEnabled(False)
        
        # 隐藏下载进度条
        self.download_progress_bar.setVisible(False)
        
        # 显示结果对话框
        if success:
            QMessageBox.information(self, "处理完成", message)
        else:
            QMessageBox.warning(self, "处理失败", message)
        
        # 显示在日志中
        status_message = f"处理{'成功' if success else '失败'}: {message}"
        if success:
            self.update_status(f"✅ {status_message}")
        else:
            self.show_error(status_message)


if __name__ == "__main__":
    app = QApplication(sys.argv)
    window = DatasetToolUI()
    window.show()
    sys.exit(app.exec_())