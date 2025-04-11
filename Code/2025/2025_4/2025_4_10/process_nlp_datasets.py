import os
import sys
import json
import subprocess
from pathlib import Path

# 设置工作目录为当前脚本所在目录
script_dir = os.path.dirname(os.path.abspath(__file__))
os.chdir(script_dir)

# 创建输出根目录
output_root = Path(script_dir) / "dataset_output"
os.makedirs(output_root, exist_ok=True)

# 读取nlp.json中的数据集信息
nlp_json_path = Path(script_dir).parent / "2025_4_7" / "nlp.json"
with open(nlp_json_path, 'r', encoding='utf-8') as f:
    nlp_data = json.load(f)

# 获取dataset_tool.py的路径
dataset_tool_path = Path(script_dir).parent / "2025_4_7" / "dataset_tool.py"

# 处理函数
def process_dataset(dataset_info):
    dataset_name = dataset_info["name"]
    dataset_link = dataset_info["link"]
    
    # 从链接中提取Hugging Face数据集ID
    dataset_id = dataset_link.replace("https://hf-mirror.com/datasets/", "")
    print(f"正在处理数据集: {dataset_name} ({dataset_id})")
    
    # 创建该数据集的输出目录
    dataset_output_dir = output_root / dataset_name.replace("/", "_").replace(" ", "_")
    os.makedirs(dataset_output_dir, exist_ok=True)
    
    # 构建命令行参数
    cmd_args = [
        sys.executable,  # 当前Python解释器
        str(dataset_tool_path),
        "--source", "huggingface",
        "--dataset", dataset_id,
        "--benchmark-size", "200",
        "--dataset-size", "3000",
        "--filter-non-ascii", "True",
        "--stratified-sampling", "True",
        "--output-dir", str(dataset_output_dir),
        "--output-format", "json",
        "--limit-download", "True"  # 限制下载大小，只下载需要的部分
    ]
    
    # 执行命令
    try:
        print(f"执行命令: {' '.join(cmd_args)}")
        subprocess.run(cmd_args, check=True)
        print(f"✅ 成功处理数据集: {dataset_name}")
        
        # 记录成功状态
        with open(output_root / "processing_status.txt", "a", encoding="utf-8") as f:
            f.write(f"成功: {dataset_name} ({dataset_id})\n")
            
    except subprocess.CalledProcessError as e:
        print(f"❌ 处理数据集失败: {dataset_name}, 错误: {e}")
        
        # 记录失败状态
        with open(output_root / "processing_status.txt", "a", encoding="utf-8") as f:
            f.write(f"失败: {dataset_name} ({dataset_id}), 错误: {e}\n")

# 修改dataset_tool.py，添加命令行参数支持
def patch_dataset_tool():
    """为dataset_tool.py添加命令行参数支持"""
    cli_code = """
# 新增: 命令行参数处理
if __name__ == "__main__":
    import argparse
    
    parser = argparse.ArgumentParser(description="数据集处理工具命令行版")
    parser.add_argument("--source", choices=["huggingface", "github", "url", "local"], 
                      default="huggingface", help="数据源类型")
    parser.add_argument("--dataset", type=str, help="数据集名称或URL")
    parser.add_argument("--benchmark-size", type=int, default=200, 
                      help="Benchmark样本数量")
    parser.add_argument("--dataset-size", type=int, default=3000, 
                      help="Dataset样本数量")
    parser.add_argument("--output-dir", type=str, default="./output", 
                      help="输出目录")
    parser.add_argument("--output-format", choices=["json", "jsonl"], 
                      default="json", help="输出格式")
    parser.add_argument("--filter-non-ascii", type=bool, default=True, 
                      help="是否过滤非ASCII字符")
    parser.add_argument("--stratified-sampling", type=bool, default=True, 
                      help="是否使用分层抽样")
    parser.add_argument("--random-seed", type=int, default=42, 
                      help="随机种子")
    parser.add_argument("--limit-download", type=bool, default=False,
                      help="是否限制下载大小")
                      
    args = parser.parse_args()
    
    # 构建参数字典
    params = {
        'source_type': args.source,
        'random_seed': args.random_seed,
        'filter_non_ascii': args.filter_non_ascii,
        'output_dir': args.output_dir,
        'split_sizes': {
            'train': args.benchmark_size,  # benchmark样本
            'val': args.dataset_size,      # dataset样本
            'test': 0                      # 不需要test样本
        },
        'output_formats': {
            'train': args.output_format,
            'val': args.output_format,
            'test': args.output_format
        },
        'use_stratified_sampling': args.stratified_sampling
    }
    
    # 根据源类型设置特定参数
    if args.source == 'huggingface':
        params['dataset_name'] = args.dataset
    elif args.source == 'github':
        params['github_repo'] = args.dataset
    elif args.source == 'url':
        params['dataset_url'] = args.dataset
    elif args.source == 'local':
        params['local_file'] = args.dataset
    
    # 创建并启动无界面的工作线程
    worker = DatasetWorker(params)
    
    # 连接信号到打印函数
    worker.status_signal.connect(print)
    worker.error_signal.connect(lambda msg: print(f"错误: {msg}"))
    
    worker.run()  # 直接运行，而不是启动线程
    print("处理完成")
"""
    
    # 读取原始文件
    with open(dataset_tool_path, 'r', encoding='utf-8') as f:
        content = f.read()
    
    # 检查是否已经有命令行参数处理代码
    if "argparse" not in content:
        # 如果没有，添加到文件末尾
        with open(dataset_tool_path, 'a', encoding='utf-8') as f:
            f.write(cli_code)
        print("✅ 已添加命令行参数支持到dataset_tool.py")
    else:
        print("dataset_tool.py已经具有命令行参数支持")

# 主执行函数
def main():
    print("开始处理NLP数据集")
    
    # 添加命令行参数支持到dataset_tool.py
    patch_dataset_tool()
    
    # 处理每个数据集
    for dataset_info in nlp_data["datasets"]:
        process_dataset(dataset_info)
    
    print(f"所有数据集处理完成，输出目录: {output_root}")

if __name__ == "__main__":
    main()