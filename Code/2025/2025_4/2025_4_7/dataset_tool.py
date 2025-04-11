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
import time
from pathlib import Path
import traceback  # 用于更详细的错误跟踪
import io  # 用于内存流处理

# 尝试导入可选依赖
OPTIONAL_DEPENDENCIES = {
    'ijson': '流式处理大型JSON文件',
    'tqdm': '提供进度条显示',
}

missing_dependencies = []
for package, description in OPTIONAL_DEPENDENCIES.items():
    try:
        __import__(package)
    except ImportError:
        missing_dependencies.append(f"{package} (用途: {description})")

# 尝试导入PyQt5，若不存在则提示安装
try:
    from PyQt5.QtWidgets import (QApplication, QMainWindow, QWidget, QVBoxLayout, QHBoxLayout, 
                               QLabel, QLineEdit, QPushButton, QProgressBar, QComboBox, 
                               QCheckBox, QTabWidget, QTextEdit, QFileDialog, QSpinBox,
                               QGroupBox, QRadioButton, QMessageBox, QScrollArea, QSizePolicy,
                               QStyleFactory, QFrame, QDialog, QTableWidget, QTableWidgetItem,
                               QHeaderView, QDialogButtonBox)
    from PyQt5.QtCore import Qt, QThread, pyqtSignal, QUrl, QSize, QTimer, QObject, QRunnable, QThreadPool
    from PyQt5.QtGui import QFont, QDesktopServices, QIcon, QColor, QPalette
except ImportError:
    print("PyQt5 未安装。请运行: pip install PyQt5")
    sys.exit(1)

# 尝试导入必要的依赖
REQUIRED_DEPENDENCIES = {
    'datasets': 'load_dataset',
    'git': 'Repo',
    'requests': 'get',
}

for package, function in REQUIRED_DEPENDENCIES.items():
    try:
        module = __import__(package)
        # 验证模块是否包含预期的功能
        if function not in dir(module) and '.' not in function:
            print(f"警告: {package} 已安装，但可能不是正确的版本")
    except ImportError:
        print(f"{package} 未安装。请运行: pip install {package}")
        sys.exit(1)

# 成功导入所需的模块
# 设置环境变量，使用hf-mirror.com作为镜像
os.environ["HF_ENDPOINT"] = "https://hf-mirror.com"
os.environ["HF_HUB_DISABLE_SYMLINKS_WARNING"] = "1"  # 禁用符号链接警告
os.environ["HF_HUB_DISABLE_IMPLICIT_TOKEN"] = "1"    # 禁用隐式令牌验证

from datasets import load_dataset
from requests.adapters import HTTPAdapter
from urllib3.util.retry import Retry
import git
import requests

# 尝试导入可选模块，用于流式处理和进度条
try:
    import ijson
    IJSON_AVAILABLE = True
except ImportError:
    IJSON_AVAILABLE = False

try:
    from tqdm import tqdm
    TQDM_AVAILABLE = True
except ImportError:
    TQDM_AVAILABLE = False

# 如果有缺失的可选依赖，在启动时显示一次警告
if missing_dependencies:
    print("警告: 以下可选依赖未安装，某些功能可能受限:")
    for dep in missing_dependencies:
        print(f"  - {dep}")
    print("可以通过以下命令安装全部可选依赖:")
    print(f"  pip install {' '.join([dep.split()[0] for dep in missing_dependencies])}")
    print("程序将继续运行，但部分功能可能受限。")

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
            if (speed < 1024):
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
            # 新增: 分层抽样参数
            use_stratified_sampling = self.params.get('use_stratified_sampling', False)
            subsets = self.params.get('subsets', {})

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

            self.status_signal.emit("准备加载数据...")
            self.progress_signal.emit(progress_stages['load_data'][0])

            data = None
            if source_type == "huggingface":
                if use_stratified_sampling and subsets:
                    # 使用分层抽样时，需要分别加载每个子集
                    data = self._load_from_huggingface_with_subsets(dataset_name, subsets)
                else:
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

            # 处理数据
            # 检查是否加载了有分级结构的子集
            if use_stratified_sampling and isinstance(data, dict) and 'subsets' in data and 'split_structure' in data:
                self.status_signal.emit("检测到多级子集结构...")
                subset_data = data['subsets']
                split_structure = data['split_structure']
                total_count = data['total_count']
                
                # 预处理：根据分级结构整理数据
                structured_data = {
                    'train': [],
                    'val': [],
                    'test': []
                }
                
                # 处理各子集数据
                for subset_key, subset_items in subset_data.items():
                    if not self.is_running:
                        return
                    
                    # 判断子集是否属于预定义分级
                    target_split = None
                    if '/' in subset_key:
                        subset_name, split_name = subset_key.split('/')
                        if split_name == 'train':
                            target_split = 'train'
                        elif split_name in ('test'):
                            target_split = 'test'
                        elif split_name in ('val', 'validation'):
                            target_split = 'val'
                    
                    if target_split:
                        # 直接按对应分级处理
                        self.status_signal.emit(f"处理子集 '{subset_key}' ({len(subset_items)} 条记录) 到 {target_split}...")
                        
                        # 随机打乱
                        random.seed(random_seed)
                        subset_items_list = list(subset_items)
                        random.shuffle(subset_items_list)
                        
                        # 过滤非ASCII字符（如果需要）
                        if filter_non_ascii:
                            filtered_items, filtered_count = self._filter_non_ascii(
                                subset_items_list, 
                                progress_stages['process_data'][0], 
                                progress_stages['process_data'][0] + (progress_stages['process_data'][1] - progress_stages['process_data'][0]) / len(subset_data)
                            )
                            self.status_signal.emit(f"子集 '{subset_key}' 过滤掉 {filtered_count}/{len(subset_items_list)} 条非ASCII记录")
                            structured_data[target_split].extend(filtered_items)
                        else:
                            structured_data[target_split].extend(subset_items_list)
                    else:
                        # 没有明确分级的子集，后续进行分层抽样
                        self.status_signal.emit(f"子集 '{subset_key}' 没有明确分级，将按需分配...")
                        
                        # 随机打乱
                        random.seed(random_seed)
                        subset_items_list = list(subset_items)
                        random.shuffle(subset_items_list)
                        
                        # 过滤非ASCII字符（如果需要）
                        if filter_non_ascii:
                            filtered_items, filtered_count = self._filter_non_ascii(
                                subset_items_list,
                                progress_stages['process_data'][0],
                                progress_stages['process_data'][0] + (progress_stages['process_data'][1] - progress_stages['process_data'][0]) / len(subset_data)
                            )
                            self.status_signal.emit(f"子集 '{subset_key}' 过滤掉 {filtered_count}/{len(subset_items_list)} 条非ASCII记录")
                            # 暂存未分配的数据，后续根据需要分配
                            structured_data.setdefault('unallocated', []).extend(filtered_items)
                        else:
                            structured_data.setdefault('unallocated', []).extend(subset_items_list)
                
                # 检查是否有训练/验证/测试集的大小要求
                required_sizes = {
                    'train': split_sizes.get('train', 0),
                    'val': split_sizes.get('val', 0),
                    'test': split_sizes.get('test', 0)
                }
                
                # 检查是否存在数据不足的情况
                for split_name in ['train', 'val', 'test']:
                    if len(structured_data.get(split_name, [])) < required_sizes[split_name]:
                        shortage = required_sizes[split_name] - len(structured_data.get(split_name, []))
                        self.status_signal.emit(f"⚠️ {split_name} 数据集数量不足，缺少 {shortage} 条记录")
                        
                        # 如果有未分配数据，从中补充
                        if 'unallocated' in structured_data and structured_data['unallocated']:
                            available = min(shortage, len(structured_data['unallocated']))
                            if available > 0:
                                self.status_signal.emit(f"从未分配数据中补充 {available} 条记录到 {split_name}")
                                structured_data.setdefault(split_name, []).extend(structured_data['unallocated'][:available])
                                structured_data['unallocated'] = structured_data['unallocated'][available:]
                
                # 最终分配数据
                train_data = structured_data.get('train', [])[:required_sizes['train']] if required_sizes['train'] > 0 else []
                val_data = structured_data.get('val', [])[:required_sizes['val']] if required_sizes['val'] > 0 else []
                test_data = structured_data.get('test', [])[:required_sizes['test']] if required_sizes['test'] > 0 else []
                
                # 如果仍有数据不足，输出警告
                for split_name, data_list in zip(['训练集', '验证集', '测试集'], [train_data, val_data, test_data]):
                    if len(data_list) < required_sizes[split_name.replace('训练集', 'train').replace('验证集', 'val').replace('测试集', 'test')]:
                        self.status_signal.emit(f"⚠️ {split_name}数据不足，请检查数据源或减少需求量")
                
                self.status_signal.emit(f"数据分配完成: 训练集={len(train_data)}, 验证集={len(val_data)}, 测试集={len(test_data)}")
            # 原有的处理逻辑保持不变
            elif use_stratified_sampling and isinstance(data, dict) and 'subsets' in data:
                self.status_signal.emit("使用分层抽样处理多个子集...")
                subset_data = data['subsets']
                total_count = data['total_count']
                self.status_signal.emit(f"数据加载完成，共 {total_count} 条记录，{len(subset_data)} 个子集")

                # 处理各子集数据
                processed_subset_data = {}
                for subset_name, subset_items in subset_data.items():
                    if not self.is_running:
                        return
                    self.status_signal.emit(f"处理子集 '{subset_name}' ({len(subset_items)} 条记录)...")

                    # 随机打乱
                    random.seed(random_seed)
                    subset_items_list = list(subset_items)
                    random.shuffle(subset_items_list)

                    # 过滤非ASCII字符（如果需要）
                    if filter_non_ascii:
                        filtered_items, filtered_count = self._filter_non_ascii(
                            subset_items_list, 
                            progress_stages['process_data'][0], 
                            progress_stages['process_data'][0] + (progress_stages['process_data'][1] - progress_stages['process_data'][0]) / len(subset_data)
                        )
                        self.status_signal.emit(f"子集 '{subset_name}' 过滤掉 {filtered_count}/{len(subset_items_list)} 条非ASCII记录")
                        processed_subset_data[subset_name] = filtered_items
                    else:
                        processed_subset_data[subset_name] = subset_items_list

                # 按比例分层抽样
                train_data, val_data, test_data = self._stratified_split(
                    processed_subset_data,
                    split_sizes['train'],
                    split_sizes['val'],
                    split_sizes['test']
                )
                self.progress_signal.emit(progress_stages['split_data'][1])
            else:
                # 常规处理: 随机打乱数据
                all_data = list(data)
                self.status_signal.emit(f"数据加载完成，共 {len(all_data)} 条记录")
                self.status_signal.emit("正在随机打乱数据...")
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

            # 检查数据交叉污染（确保没有重复数据）
            if len(train_data) > 0 or len(val_data) > 0 or len(test_data) > 0:
                self.status_signal.emit("检查数据集间的交叉污染...")
                
                # 使用集合记录已分配的数据哈希，检测重复
                all_data_hashes = set()
                duplicate_count = 0
                
                # 检查训练集
                if train_data:
                    clean_train_data = []
                    for item in train_data:
                        item_hash = hashlib.md5(str(item).encode()).hexdigest()
                        if item_hash not in all_data_hashes:
                            all_data_hashes.add(item_hash)
                            clean_train_data.append(item)
                        else:
                            duplicate_count += 1
                    
                    if duplicate_count > 0:
                        self.status_signal.emit(f"⚠️ 从训练集移除 {duplicate_count} 条重复记录")
                    train_data = clean_train_data
                
                # 检查验证集
                if val_data:
                    duplicate_count = 0
                    clean_val_data = []
                    for item in val_data:
                        item_hash = hashlib.md5(str(item).encode()).hexdigest()
                        if item_hash not in all_data_hashes:
                            all_data_hashes.add(item_hash)
                            clean_val_data.append(item)
                        else:
                            duplicate_count += 1
                    
                    if duplicate_count > 0:
                        self.status_signal.emit(f"⚠️ 从验证集移除 {duplicate_count} 条重复记录")
                    val_data = clean_val_data
                
                # 检查测试集
                if test_data:
                    duplicate_count = 0
                    clean_test_data = []
                    for item in test_data:
                        item_hash = hashlib.md5(str(item).encode()).hexdigest()
                        if item_hash not in all_data_hashes:
                            all_data_hashes.add(item_hash)
                            clean_test_data.append(item)
                        else:
                            duplicate_count += 1
                    
                    if duplicate_count > 0:
                        self.status_signal.emit(f"⚠️ 从测试集移除 {duplicate_count} 条重复记录")
                    test_data = clean_test_data
                
                self.status_signal.emit(f"✅ 数据去重完成，确保数据集间无交叉污染")
            
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
            if train_data and len(train_data) > 0:
                self.status_signal.emit(f"正在保存训练集 ({len(train_data)} 条记录)...")
                train_format = output_formats.get('train', 'json')
                train_filename = os.path.join(output_dir, f"train_{len(train_data)}.{train_format}")
                self._save_dataset(train_data, train_filename, 'train', train_format)
                saved_files.append(train_filename)
                current_progress += save_progress_increment
                self.progress_signal.emit(int(current_progress))

            # 保存验证集
            if val_data and len(val_data) > 0:
                self.status_signal.emit(f"正在保存验证集 ({len(val_data)} 条记录)...")
                val_format = output_formats.get('val', 'jsonl')
                val_filename = os.path.join(output_dir, f"val_{len(val_data)}.{val_format}")
                self._save_dataset(val_data, val_filename, 'val', val_format)
                saved_files.append(val_filename)
                current_progress += save_progress_increment
                self.progress_signal.emit(int(current_progress))

            # 保存测试集
            if test_data and len(test_data) > 0:
                self.status_signal.emit(f"正在保存测试集 ({len(test_data)} 条记录)...")
                test_format = output_formats.get('test', 'jsonl')
                test_filename = os.path.join(output_dir, f"test_{len(test_data)}.{test_format}")
                self._save_dataset(test_data, test_filename, 'test', test_format)
                saved_files.append(test_filename)
                current_progress += save_progress_increment
                self.progress_signal.emit(int(current_progress))

            self.progress_signal.emit(progress_stages['verify_data'][0])

            # 验证保存的数据
            if saved_files:
                self.status_signal.emit("验证保存的数据集...")
                if self._verify_saved_datasets(saved_files, output_formats):
                    self.status_signal.emit(f"✅ 处理完成! 已保存 {len(saved_files)} 个数据集文件")
                    self.finished_signal.emit(True, f"处理完成。已保存数据集到: {output_dir}")
                else:
                    self.status_signal.emit("⚠️ 部分文件验证失败，请检查保存的数据集")
                    self.finished_signal.emit(False, "处理部分完成，但验证失败。请检查日志了解详情。")
            else:
                self.status_signal.emit("⚠️ 没有数据需要保存")
                self.finished_signal.emit(True, "处理完成，但没有数据需要保存")
        except Exception as e:
            import traceback
            self.error_signal.emit(f"❌ 处理过程中发生错误: {str(e)}")
            self.error_signal.emit(traceback.format_exc())
            self.finished_signal.emit(False, f"处理失败: {str(e)}")

    def _load_from_huggingface_with_subsets(self, dataset_name, subsets):
        """从 Hugging Face 加载多个子集的数据集，支持子集中的分级结构如train/test/val"""
        self.status_signal.emit(f"🔄 正在从 Hugging Face 镜像站点加载数据集 '{dataset_name}' 的多个子集...")
        result = {
            'subsets': {},
            'split_structure': {},  # 新增：记录子集是否有分级结构
            'total_count': 0
        }

        # 检查每个子集是否包含预定义的split
        predefined_splits = ['train', 'test', 'validation', 'val']
        
        for subset_name, subset_info in subsets.items():
            self.status_signal.emit(f"检查子集 '{subset_name}' 的结构...")
            
            # 尝试获取子集的split信息
            try:
                # 先检查子集是否有明确的分级结构
                available_splits = []
                for split in predefined_splits:
                    try:
                        # 使用小样本加载测试是否存在该split
                        test_data = load_dataset(dataset_name, name=subset_name, split=split, streaming=True)
                        # 尝试获取一条记录，确认split有效
                        next(iter(test_data))
                        available_splits.append(split)
                        self.status_signal.emit(f"✓ 子集 '{subset_name}' 包含 '{split}' 分级")
                    except Exception:
                        continue
                
                if available_splits:
                    # 子集有明确的分级结构
                    result['split_structure'][subset_name] = available_splits
                    
                    # 为每个有效的split加载数据
                    for split in available_splits:
                        split_key = f"{subset_name}/{split}"
                        self.status_signal.emit(f"正在加载子集 '{subset_name}' 的 '{split}' 分级...")
                        try:
                            split_data = load_dataset(dataset_name, name=subset_name, split=split)
                            data_count = len(split_data)
                            self.status_signal.emit(f"✅ 已加载 '{split_key}'，包含 {data_count} 条记录")
                            result['subsets'][split_key] = split_data
                            result['total_count'] += data_count
                        except Exception as e:
                            self.error_signal.emit(f"❌ 加载 '{split_key}' 时出错: {str(e)}")
                else:
                    # 子集没有明确的分级，使用默认的train分级
                    self.status_signal.emit(f"子集 '{subset_name}' 没有明确的分级结构，使用默认split")
                    try:
                        subset_dataset = load_dataset(dataset_name, name=subset_name, split='train')
                        data_count = len(subset_dataset)
                        self.status_signal.emit(f"✅ 已加载子集 '{subset_name}'，包含 {data_count} 条记录")
                        result['subsets'][subset_name] = subset_dataset
                        result['total_count'] += data_count
                    except Exception as e:
                        self.error_signal.emit(f"❌ 从加载子集 '{subset_name}' 时出错: {str(e)}")
            except Exception as e:
                self.error_signal.emit(f"❌ 检查子集 '{subset_name}' 结构时出错: {str(e)}")
                
        self.status_signal.emit(f"✅ 所有子集加载完成，总计 {result['total_count']} 条记录")
        return result

    def _stratified_split(self, subset_data, train_size, val_size, test_size):
        """按比例进行分层抽样，保持各子集的原始比例

        Args:
            subset_data: 子集数据字典 {subset_name: [items...], ...}
            train_size: 训练集目标大小
            val_size: 验证集目标大小
            test_size: 测试集目标大小

        Returns:
            (train_data, val_data, test_data): 三个数据集列表
        """
        self.status_signal.emit("执行按比例分层抽样...")
        total_count = sum(len(items) for items in subset_data.values())
        total_target_size = train_size + val_size + test_size

        if total_count < total_target_size:
            self.status_signal.emit(f"⚠️ 可用数据量({total_count})少于目标数量({total_target_size})，将按比例缩减")
            ratio = total_count / total_target_size
            train_size = int(train_size * ratio)
            val_size = int(val_size * ratio)
            test_size = int(test_size * ratio)
            self.status_signal.emit(f"调整后目标大小: 训练集={train_size}, 验证集={val_size}, 测试集={test_size}")

        train_data = []
        val_data = []
        test_data = []

        # 计算各子集应贡献的数量
        subset_contributions = {}
        for subset_name, items in subset_data.items():
            # 计算占比量
            ratio = len(items) / total_count
            
            # 按比例分配
            subset_train = max(1, int(train_size * ratio)) if train_size > 0 else 0
            subset_val = max(1, int(val_size * ratio)) if val_size > 0 else 0
            subset_test = max(1, int(test_size * ratio)) if test_size > 0 else 0

            total_needed = subset_train + subset_val + subset_test
            if total_needed > len(items):
                # 按比例缩减
                scale_ratio = len(items) / total_needed
                subset_train = int(subset_train * scale_ratio)
                subset_val = int(subset_val * scale_ratio)
                subset_test = min(len(items) - subset_train - subset_val, subset_test)

            subset_contributions[subset_name] = {
                'ratio': ratio,
                'train': subset_train,
                'val': subset_val,
                'test': subset_test
            }

        # 记录每个子集的贡献
        contribution_info = []
        for name, contribution in subset_contributions.items():
            subset_info = f"'{name}' (占比 {contribution['ratio']:.1%}): 训练={contribution['train']}, 验证={contribution['val']}, 测试={contribution['test']}"
            contribution_info.append(subset_info)
        self.status_signal.emit("子集贡献分布:\n" + "\n".join(contribution_info))

        # 从各子集按计算出的数量抽取样本
        for subset_name, items in subset_data.items():
            contribution = subset_contributions[subset_name]
            current_items = items.copy()

            # 抽取训练集
            train_data.extend(current_items[:contribution['train']])
            current_pos = contribution['train']
            
            # 抽取验证集
            val_data.extend(current_items[current_pos:current_pos + contribution['val']])
            current_pos += contribution['val']

            # 抽取测试集
            test_data.extend(current_items[current_pos:current_pos + contribution['test']])

        # 最后再次打乱各数据集，避免连续出现同一子集的数据
        random.shuffle(train_data)
        random.shuffle(val_data)
        random.shuffle(test_data)

        self.status_signal.emit(f"分层抽样完成: 训练集={len(train_data)}, 验证集={len(val_data)}, 测试集={len(test_data)}")
        return train_data, val_data, test_data

    def _load_from_huggingface(self, dataset_name):
        """从 Hugging Face 加载数据集"""
        self.status_signal.emit(f"🔄 正在从 Hugging Face 镜像站点加载数据集: {dataset_name}...")
        try:
            dataset = load_dataset(dataset_name, split='train')
            self.status_signal.emit(f"✅ 成功从 Hugging Face 镜像站点加载数据集: {dataset_name}")
            return dataset
        except Exception as e:
            self.error_signal.emit(f"❌ 无法从 ModelScope 镜像站点加载数据集: {str(e)}")
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
        """从URL下载并加载数据集，使用流式处理减少内存占用"""
        import time
        self.status_signal.emit(f"🔄 正在从URL下载数据: {url}...")

        # 创建临时文件
        temp_file = tempfile.NamedTemporaryFile(delete=False)
        temp_file.close()

        try:
            # 检查URL是否可访问
            try:
                session = self._create_session_with_retry()
                response = session.head(url, allow_redirects=True, timeout=10)

                # 检查响应状态码
                if (response.status_code >= 400):
                    error_message = f"URL不可访问: HTTP错误 {response.status_code}"
                    if response.status_code == 404:
                        error_message = f"资源不存在 (404): 请检查URL是否正确"
                    elif response.status_code == 403:
                        error_message = f"访问被拒绝 (403): 可能需要权限或网站禁止爬虫"
                    elif response.status_code >= 500:
                        error_message = f"服务器错误 ({response.status_code}): 请稍后再试"
                    self.error_signal.emit(f"❌ {error_message}")
                    raise requests.RequestException(error_message)

                total_size = int(response.headers.get('content-length', 0))
            except requests.exceptions.ConnectionError:
                self.error_signal.emit("❌ 连接错误: 无法连接到服务器，请检查网络连接")
                raise
            except requests.exceptions.Timeout:
                self.error_signal.emit("❌ 连接超时: 服务器响应时间过长，请稍后再试")
                raise
            except requests.RequestException as e:
                self.error_signal.emit(f"❌ 请求错误: {str(e)}")
                raise

            # 使用requests下载并显示进度
            self.status_signal.emit("开始下载文件...")
            start_time = time.time()
            downloaded_size = 0
            last_update_time = 0

            with session.get(url, stream=True) as r:
                r.raise_for_status()
                with open(temp_file.name, 'wb') as f:
                    # 更大的块大小，提高下载速度 (8KB -> 64KB)
                    chunk_size = 65536  # 64KB
                    for chunk in r.iter_content(chunk_size=chunk_size):
                        if not self.is_running:
                            raise InterruptedError("下载被用户取消")
                        if chunk:  # 过滤keep-alive新块
                            f.write(chunk)
                            downloaded_size += len(chunk)

                            # 每0.5秒更新一次进度，避免频繁更新UI导致卡顿
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

            # 检查文件类型并处理
            data = []
            file_extension = os.path.splitext(url)[1].lower()

            # JSONL文件 - 使用流式处理
            if file_extension == '.jsonl':
                self.status_signal.emit("逐行解析JSONL文件...")
                with open(temp_file.name, 'r', encoding='utf-8') as f:
                    line_count = 0
                    last_update_time = time.time()

                    for line in f:
                        if not line.strip():  # 跳过空行
                            continue
                        try:
                            item = json.loads(line)
                            data.append(item)
                            line_count += 1
                            if line_count % 1000 == 0:
                                current_time = time.time()
                                if current_time - last_update_time >= 1.0:
                                    self.status_signal.emit(f"已解析 {line_count} 条记录...")
                                    last_update_time = current_time
                        except json.JSONDecodeError as e:
                            error_message = f"JSON解析错误 (行 {line_count+1}): {str(e)}"
                            self.error_signal.emit(error_message)
                            # 继续处理，跳过错误行
                            continue
                self.status_signal.emit(f"✅ JSONL文件解析完成，加载了 {line_count} 条记录")

            # JSON文件 - 对大文件使用流式处理
            elif file_extension == '.json':
                file_size = os.path.getsize(temp_file.name)
                is_large_file = file_size > 100 * 1024 * 1024  # 100MB
                if is_large_file and IJSON_AVAILABLE:
                    self.status_signal.emit("检测到大型JSON文件，使用流式解析...")
                    with open(temp_file.name, 'rb') as f:
                        count = 0
                        last_update_time = time.time()
                        for item in ijson.items(f, 'item'):
                            data.append(item)
                            count += 1
                            current_time = time.time()
                            if count % 1000 == 0:
                                current_time = time.time()
                                if current_time - last_update_time >= 1.0:
                                    self.status_signal.emit(f"已解析 {count} 条记录...")
                                    last_update_time = current_time
                        self.status_signal.emit(f"✅ 解析完成，加载了 {count} 条记录")
                else:
                    self.status_signal.emit("解析JSON文件...")
                    try:
                        with open(temp_file.name, 'r', encoding='utf-8') as f:
                            data = json.load(f)
                            self.status_signal.emit(f"✅ 解析完成，加载了 {len(data)} 条记录")
                    except UnicodeDecodeError:
                        self.status_signal.emit("UTF-8解码失败，尝试其他编码...")
                        for encoding in ['latin1', 'cp1252']:
                            try:
                                with open(temp_file.name, 'r', encoding=encoding) as f:
                                    data = json.load(f)
                                    self.status_signal.emit(f"✅ 使用 {encoding} 编码成功解析，加载了 {len(data)} 条记录")
                                    break
                            except Exception:
                                continue
                        else:
                            raise UnicodeDecodeError("无法解码JSON文件，请确保文件编码正确")

            # ZIP文件
            elif file_extension == '.zip':
                self.status_signal.emit("解压ZIP文件...")
                temp_dir = tempfile.mkdtemp()
                try:
                    with zipfile.ZipFile(temp_file.name, 'r') as zip_ref:
                        zip_ref.extractall(temp_dir)
                    self.status_signal.emit("查找JSON/JSONL文件...")
                    json_files = list(Path(temp_dir).glob('**/*.json')) + list(Path(temp_dir).glob('**/*.jsonl'))
                    if not json_files:
                        error_message = "ZIP文件中未找到JSON或JSONL数据文件"
                        self.error_signal.emit(f"❌ {error_message}")
                        raise FileNotFoundError(error_message)
                    json_files.sort(key=lambda x: x.stat().st_size, reverse=True)
                    largest_file = json_files[0]
                    file_size_mb = largest_file.stat().st_size / (1024 * 1024)
                    self.status_signal.emit(f"找到 {len(json_files)} 个文件，使用最大的文件: {largest_file.name} ({file_size_mb:.2f}MB)")
                    if largest_file.suffix.lower() == '.jsonl':
                        line_count = 0
                        with open(largest_file, 'r', encoding='utf-8') as f:
                            for line in f:
                                if line.strip():
                                    data.append(json.loads(line))
                                    line_count += 1
                        self.status_signal.emit(f"✅ JSONL文件解析完成，加载了 {line_count} 条记录")
                    else:  # .json
                        is_large_json = file_size_mb > 100  # 大于100MB视为大文件
                        if is_large_json and IJSON_AVAILABLE:
                            count = 0
                            with open(largest_file, 'rb') as f:
                                for item in ijson.items(f, 'item'):
                                    data.append(item)
                                    count += 1
                            self.status_signal.emit(f"✅ 大型JSON文件解析完成，加载了 {count} 条记录")
                        else:
                            with open(largest_file, 'r', encoding='utf-8') as f:
                                data = json.load(f)
                            self.status_signal.emit(f"✅ JSON文件解析完成，加载了 {len(data)} 条记录")
                finally:
                    import shutil
                    self.status_signal.emit("已清理临时解压文件")
                    shutil.rmtree(temp_dir, ignore_errors=True)

            # 其他文件类型
            else:
                supported_formats = ".json, .jsonl, .zip"
                error_message = f"不支持的文件类型: {file_extension}，目前仅支持 {supported_formats}"
                self.error_signal.emit(f"❌ {error_message}")
                raise ValueError(error_message)

            return data
        except requests.RequestException as e:
            if "未能解析" in str(e) or "getaddrinfo failed" in str(e):
                self.error_signal.emit("❌ DNS解析失败: 无法解析域名，请检查URL是否正确")
            elif "ConnectTimeoutError" in str(e.__class__.__name__):
                self.error_signal.emit("❌ 连接超时: 服务器响应超时，请检查网络连接或稍后再试")
            elif "Max retries exceeded" in str(e):
                self.error_signal.emit("❌ 连接失败: 多次重试后仍然无法连接，请检查网络或URL")
            else:
                self.error_signal.emit(f"❌ 下载失败: {str(e)}")
            raise
        except json.JSONDecodeError as e:
            self.error_signal.emit(f"❌ JSON解析错误: {str(e)}")
            raise
        except zipfile.BadZipFile:
            self.error_signal.emit("❌ 无效的ZIP文件: 文件损坏或不是ZIP格式")
            raise
        except Exception as e:
            self.error_signal.emit(f"❌ 加载数据时出错: {str(e)}")
            raise
        finally:
            try:
                if os.path.exists(temp_file.name):
                    os.unlink(temp_file.name)
            except Exception as e:
                self.error_signal.emit(f"警告: 清理临时文件失败: {str(e)}")

    def _load_from_local(self, file_path):
        """从本地文件加载数据集，对大文件使用流式处理"""
        self.status_signal.emit(f"🔄 正在加载本地文件: {file_path}...")
        data = []
        try:
            file_size = os.path.getsize(file_path)
            file_size_mb = file_size / (1024 * 1024)
            self.status_signal.emit(f"文件大小: {file_size_mb:.2f}MB")

            # 判断是否为大文件 (>100MB)
            is_large_file = file_size > 100 * 1024 * 1024
            if file_path.endswith('.json'):
                # 对于大型JSON文件，尝试使用ijson进行流式解析
                if is_large_file and IJSON_AVAILABLE:
                    self.status_signal.emit("检测到大型JSON文件，使用流式解析...")
                    with open(file_path, 'rb') as f:
                        generator = ijson.items(f, 'item')
                        count = 0
                        last_update_time = time.time()
                        for item in generator:
                            data.append(item)
                            count += 1
                            if count % 1000 == 0:
                                current_time = time.time()
                                if current_time - last_update_time >= 1.0:
                                    self.status_signal.emit(f"已处理 {count} 条记录...")
                                    last_update_time = current_time
                            if not self.is_running:
                                self.status_signal.emit("处理被用户中断")
                                return []
                    self.status_signal.emit(f"✅ 流式解析完成，加载了 {len(data)} 条记录")
                else:
                    with open(file_path, 'r', encoding='utf-8') as f:
                        self.status_signal.emit("解析JSON文件...")
                        data = json.load(f)
                        self.status_signal.emit(f"✅ 解析完成，加载了 {len(data)} 条记录")
            elif file_path.endswith('.jsonl'):
                self.status_signal.emit("逐行解析JSONL文件...")
                with open(file_path, 'r', encoding='utf-8') as f:
                    count = 0
                    last_update_time = time.time()
                    for line in f:
                        if not line.strip():
                            continue
                        try:
                            item = json.loads(line)
                            data.append(item)
                            count += 1
                            if count % 1000 == 0:
                                current_time = time.time()
                                if current_time - last_update_time >= 1.0:
                                    progress_percentage = min(99, int(f.tell() / file_size * 100))
                                    self.status_signal.emit(f"已处理 {count} 行... ({progress_percentage}%)")
                                    last_update_time = current_time
                            if not self.is_running:
                                self.status_signal.emit("处理被用户中断")
                                return []
                        except json.JSONDecodeError as e:
                            line_number = count + 1
                            error_message = f"第 {line_number} 行JSON解析错误: {str(e)}"
                            self.error_signal.emit(error_message)
                            continue
                self.status_signal.emit(f"✅ 解析完成，加载了 {len(data)} 条记录")
            else:
                supported_formats = ".json 或 .jsonl"
                error_message = f"不支持的文件格式: {os.path.splitext(file_path)[1]}，目前仅支持 {supported_formats}"
                self.error_signal.emit(f"❌ {error_message}")
                raise ValueError(error_message)
        except MemoryError:
            error_message = "内存不足，无法加载整个文件。建议使用更小的数据集或增加系统内存。"
            self.error_signal.emit(f"❌ {error_message}")
            raise
        except ValueError as e:
            self.error_signal.emit(f"❌ 文件格式错误: {str(e)}")
            raise
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

        self.progress_signal.emit(end_progress)
        return filtered_data, filtered_count

    def _is_ascii(self, s):
        """检查字符串是否只包含ASCII字符"""
        if s is None:
            return True
        return all(ord(c) < 128 for c in s)

    def _check_dataset_overlap(self, sets, name_mapping):
        """检查数据集之间是否有重叠"""
        problem_hashes = {}

        for set_name, dataset in sets.items():
            if not dataset:
                continue

            self.status_signal.emit(f"检查 {name_mapping[set_name]} 的唯一性...")
            for item in dataset:
                item_hash = hashlib.md5(str(item).encode()).hexdigest()
                if item_hash in problem_hashes and problem_hashes[item_hash] != set_name:
                    self.status_signal.emit(f"⚠️ 发现重叠: {name_mapping[set_name]} 和 {name_mapping[problem_hashes[item_hash]]} 之间存在相同内容")
                    return False
                else:
                    problem_hashes[item_hash] = set_name

        return True

    def _save_dataset(self, data, filename, split_type, format_type):
        """保存数据集到文件"""
        try:
            with open(filename, 'w', encoding='utf-8') as f:
                if format_type.lower() == 'json':
                    # 转换数据格式
                    converted_data = [self._convert_to_target_format(item, split_type == 'test') for item in data]
                    json.dump(converted_data, f, ensure_ascii=False, indent=4)
                else:  # jsonl
                    for item in data:
                        # 转换为目标格式
                        converted_item = self._convert_to_target_format(item, split_type == 'test')
                        f.write(json.dumps(converted_item, ensure_ascii=False) + '\n')
            return True
        except Exception as e:
            self.error_signal.emit(f"❌ 保存文件 {filename} 失败: {str(e)}")
            return False

    def _convert_to_target_format(self, item, is_test=False):
        """
        将原始数据项转换为目标格式:
        {
            "instruction": "问题或指示",
            "input": "",
            "output": "答案"
        }
        """
        # 尝试从不同可能的字段名中获取值
        instruction = ""
        output = ""
        input_text = ""
        
        # 获取instruction字段 (可能是question、prompt等)
        for field in ['question', 'instruction', 'prompt', 'task', 'problem', 
                      'Task Description', 'Guide', 'Prompt']:
            if field in item:
                instruction = str(item[field])
                break
        
        # 获取output字段 (可能是answer、response等)
        for field in ['answer', 'output', 'response', 'result', 'solution',
                     'Result', 'Outcome', 'Generated Output', 'Output Data']:
            if field in item:
                output = str(item[field]) if item[field] is not None else ""
                break
        
        # 获取input字段
        for field in ['input', 'context', 'data', 
                     'Data Input', 'Source Data', 'Input Variable', 'Feed-in']:
            if field in item:
                input_text = str(item[field]) if item[field] is not None else ""
                break
        
        # 如果是测试集且答案为空或NULL，确保为空字符串
        if is_test and (output is None or output.lower() == "null"):
            output = ""
        
        # 如果上面的字段匹配失败，则使用item的第一个字段作为instruction
        if not instruction and item:
            instruction = str(next(iter(item.values())))
        
        return {
            "instruction": instruction,
            "input": input_text,
            "output": output
        }

    def _verify_saved_datasets(self, file_paths, output_formats):
        """验证保存的数据集文件"""
        for path in file_paths:
            try:
                if path.endswith('.json'):
                    with open(path, 'r', encoding='utf-8') as f:
                        data = json.load(f)
                        self.status_signal.emit(f"✅ 验证成功: {path} ({len(data)} 条记录)")
                elif path.endswith('.jsonl'):
                    count = 0
                    with open(path, 'r', encoding='utf-8') as f:
                        for line in f:
                            if line.strip():
                                json.loads(line)
                                count += 1
                    self.status_signal.emit(f"✅ 验证成功: {path} ({count} 条记录)")
            except Exception as e:
                self.error_signal.emit(f"❌ 验证失败: {path} - {str(e)}")
                return False
        return True

# 取消图形化UI设计，统一在代码开头设置参数
import os
import random
from modelscope.msdatasets import MsDataset

"""
********************************************************************************
********************************************************************************
********************************************************************************
"""
# 配置参数
DATASET_NAME = "dahaizei/cnn_dailymail"  # 数据集名称
SUBSET_NAME = "2.0.0" # 子集名称
OUTPUT_DIR = f"./output/{DATASET_NAME}/2.0.0"  # 输出目录
FILE_FORMAT = "json"  # 文件格式
SPLIT_SIZES = {"train": 3000, "val": 0, "test": 200}  # 数据集划分大小
FILTER_NON_ASCII = True  # 是否过滤非ASCII字符
RANDOM_SEED = 42  # 随机种子
"""
********************************************************************************
********************************************************************************
********************************************************************************
"""

# 设置随机种子
random.seed(RANDOM_SEED)

# 加载数据集
print(f"🔄 正在从 ModelScope 加载数据集: {DATASET_NAME}...")
try:
    all_data = []
    total_records = 0
    
    # 检查是否指定子集
    if SUBSET_NAME is None:
        # 直接加载整个数据集
        print(f"🔄 未指定子集，加载完整数据集...")
        
        # 尝试加载完整数据集，自动检测可用的分割
        available_splits = []
        for split_name in ["train", "test", "val", "validation", "dev"]:
            try:
                # 尝试加载此分割以检查是否存在
                test_load = MsDataset.load(DATASET_NAME, split=split_name)
                available_splits.append(split_name)
                print(f"✓ 数据集包含分割: {split_name}")
            except Exception:
                pass
        
        if not available_splits:
            # 如果没有找到任何预定义分割，尝试不指定split参数
            try:
                dataset = MsDataset.load(DATASET_NAME)
                total_records = len(dataset)
                all_data = list(dataset)  # 转换为列表
                print(f"✅ 完整数据集加载成功（无分割），共 {total_records} 条记录")
            except Exception as e:
                print(f"❌ 数据集加载失败: {str(e)}")
                exit(1)
        else:
            # 优先使用train分割，然后是其他分割
            for preferred_split in ["train", "test", "val", "validation", "dev"]:
                if preferred_split in available_splits:
                    try:
                        print(f"🔄 加载 '{preferred_split}' 分割...")
                        dataset = MsDataset.load(DATASET_NAME, split=preferred_split)
                        total_records = len(dataset)
                        all_data = list(dataset)  # 转换为列表
                        print(f"✅ 分割 '{preferred_split}' 加载成功，共 {total_records} 条记录")
                        break
                    except Exception as e:
                        print(f"⚠️ 尝试加载 '{preferred_split}' 分割时出错: {str(e)}")
                        continue
    else:
        # 处理指定的子集
        subset_names = SUBSET_NAME.split(',')
        
        for subset in subset_names:
            subset_name = subset.strip()
            print(f"🔄 正在加载子集: {subset_name}...")
            
            # 检查子集有哪些可用的分割
            available_subset_splits = []
            for split_name in ["train", "test", "val", "validation", "dev"]:
                try:
                    # 尝试加载此分割以检查是否存在
                    test_load = MsDataset.load(DATASET_NAME, subset_name=subset_name, split=split_name)
                    available_subset_splits.append(split_name)
                    print(f"✓ 子集 '{subset_name}' 包含分割: {split_name}")
                except Exception:
                    pass
            
            if not available_subset_splits:
                # 如果没有找到任何预定义分割，尝试不指定split参数
                try:
                    subset_data = MsDataset.load(DATASET_NAME, subset_name=subset_name)
                    subset_data_list = list(subset_data)  # 转换为列表
                    print(f"✅ 子集 '{subset_name}' 加载成功（无分割），共 {len(subset_data_list)} 条记录")
                    all_data.extend(subset_data_list)
                    total_records += len(subset_data_list)
                except Exception as e:
                    print(f"❌ 子集 '{subset_name}' 加载失败: {str(e)}")
            else:
                # 优先使用train分割，然后是其他分割
                loaded = False
                for preferred_split in ["train", "test", "val", "validation", "dev"]:
                    if preferred_split in available_subset_splits:
                        try:
                            print(f"🔄 加载子集 '{subset_name}' 的 '{preferred_split}' 分割...")
                            subset_data = MsDataset.load(DATASET_NAME, subset_name=subset_name, split=preferred_split)
                            subset_data_list = list(subset_data)  # 转换为列表
                            print(f"✅ 子集 '{subset_name}' 的 '{preferred_split}' 分割加载成功，共 {len(subset_data_list)} 条记录")
                            all_data.extend(subset_data_list)
                            total_records += len(subset_data_list)
                            loaded = True
                            break
                        except Exception as e:
                            print(f"⚠️ 尝试加载子集 '{subset_name}' 的 '{preferred_split}' 分割时出错: {str(e)}")
                            continue
                
                if not loaded:
                    print(f"❌ 无法加载子集 '{subset_name}' 的任何分割")

        if total_records == 0:
            print("❌ 所有子集加载失败，请检查数据集名称或子集名称是否正确")
            exit(1)
            
    print(f"✅ 数据集加载完成，共加载 {total_records} 条记录")
except Exception as e:
    print(f"❌ 加载数据集失败: {str(e)}")
    exit(1)

# 随机打乱数据 - 现在all_data已经是列表，可以正常打乱
print("🔄 正在随机打乱数据...")
random.shuffle(all_data)

# 过滤非ASCII字符
if FILTER_NON_ASCII:
    print("🔄 正在过滤非ASCII字符...")
    filtered_data = []
    for item in all_data:
        if all(ord(c) < 128 for c in str(item)):
            filtered_data.append(item)
    print(f"✅ 过滤完成，剩余 {len(filtered_data)} 条记录")
    all_data = filtered_data

# 检查数据量是否足够
if len(all_data) < sum(SPLIT_SIZES.values()):
    print("WARING! 数据量不足，无法按指定比例划分.可能会出现划分不满的情况")

# 划分数据集
print("🔄 正在划分数据集...")
train_data = all_data[:SPLIT_SIZES["train"]]
val_data = all_data[SPLIT_SIZES["train"]:SPLIT_SIZES["train"] + SPLIT_SIZES["val"]]
test_data = all_data[SPLIT_SIZES["train"] + SPLIT_SIZES["val"]:SPLIT_SIZES["train"] + SPLIT_SIZES["val"] + SPLIT_SIZES["test"]]
print(f"✅ 数据集划分完成: 训练集={len(train_data)}, 验证集={len(val_data)}, 测试集={len(test_data)}")

# 保存数据集
for split_name, split_data in zip(["train", "val", "test"], [train_data, val_data, test_data]):
    if len(split_data) == 0:
        print(f"⚠️ {split_name} 数据集为空，跳过保存")
        continue

    # 创建文件夹
    split_dir = os.path.join(OUTPUT_DIR, split_name)
    os.makedirs(split_dir, exist_ok=True)

    # 定义文件名
    file_suffix = "dataset" if split_name == "train" else "val" if split_name == "val" else "benchmark"
    output_path = os.path.join(split_dir, f"{split_name}_{file_suffix}_{len(split_data)}.{FILE_FORMAT}")

    print(f"🔄 正在保存 {split_name} 数据集到 {output_path}...")

    # 转换数据格式
    def convert_to_target_format(item, is_test=False):
        """将原始数据项转换为目标格式"""
        instruction = ""
        output = ""
        input_text = ""
        
        # 获取instruction字段
        for field in ['question', 'instruction', 'prompt', 'task', 'problem', 
                      'Task Description', 'Guide', 'Prompt']:
            if field in item:
                instruction = str(item[field])
                break
        
        # 获取output字段
        for field in ['answer', 'output', 'response', 'result', 'solution',
                     'Result', 'Outcome', 'Generated Output', 'Output Data']:
            if field in item:
                output = str(item[field]) if item[field] is not None else ""
                break
        
        # 获取input字段
        for field in ['input', 'context', 'data', 
                     'Data Input', 'Source Data', 'Input Variable', 'Feed-in']:
            if field in item:
                input_text = str(item[field]) if item[field] is not None else ""
                break
        
        # 如果是测试集且答案为空或NULL，确保为空字符串
        if is_test and (output is None or output.lower() == "null"):
            output = ""
        
        # 如果上面的字段匹配失败，则使用item的第一个值作为instruction
        if not instruction and item:
            instruction = str(next(iter(item.values())))
        
        return {
            "instruction": instruction,
            "input": input_text,
            "output": output
        }

    # 转换所有数据
    is_test = (split_name == "test")
    converted_data = [convert_to_target_format(item, is_test) for item in split_data]
    
    # 保存为JSON或JSONL
    with open(output_path, "w", encoding="utf-8") as f:
        if FILE_FORMAT.lower() == "json":
            # 整个数组保存为一个JSON
            json.dump(converted_data, f, ensure_ascii=False, indent=4)
        else:
            # 每行一个JSON对象
            for item in converted_data:
                json_line = json.dumps(item, ensure_ascii=False)
                f.write(f"{json_line}\n")
    
    print(f"✅ {split_name} 数据集保存完成")

print("🎉 数据处理完成")
