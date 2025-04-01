import uuid
import json
import random
import hashlib
from datasets import load_dataset

# 加载NuminaMath-1.5数据集
print("正在加载数据集...")
try:
    dataset = load_dataset("AI-MO/NuminaMath-1.5")
    # 确定数据集的主要部分
    main_split = list(dataset.keys())[0]
    data = dataset[main_split]
    print(f"成功加载数据集! 拆分: {main_split}, 总样本数: {len(data)}")
except Exception as e:
    print(f"加载数据集失败: {e}")
    print("请检查网络连接或手动下载数据集")
    exit(1)

# 将数据集转换为列表并随机打乱
all_data = list(data)
random.seed(42)  # 设置随机种子确保可重复性
random.shuffle(all_data)

# 确定集合大小
train_size = 10000
val_size = 3000
test_size = 500

# 划分数据集
train_data = all_data[:train_size]
val_data = all_data[train_size:train_size + val_size]
test_data = all_data[train_size + val_size:train_size + val_size + test_size]

# 检查数据交叉污染
def check_dataset_overlap(sets, name_mapping):
    """检查数据集之间是否有重叠"""
    print("检查数据集交叉污染...")
    
    # 使用问题内容的哈希值作为唯一标识
    problem_hashes = {}
    
    for set_name, dataset in sets.items():
        for item in dataset:
            problem = item.get("problem", "")
            problem_hash = hashlib.md5(problem.encode()).hexdigest()
            
            if problem_hash in problem_hashes:
                print(f"警告: 发现重复问题!")
                print(f"  在 {name_mapping[set_name]} 和 {name_mapping[problem_hashes[problem_hash]]} 中发现相同问题")
                print(f"  问题开头: {problem[:100]}...")
                return False
            
            problem_hashes[problem_hash] = set_name
    
    print("检查完成: 三个数据集之间没有交叉污染")
    return True

# 保存训练数据集函数 - 使用JSON格式
def save_train_dataset(data_subset, filename):
    train_items = []
    for item in data_subset:
        # 创建记录 - 训练集格式
        record = {
            "instruction": item.get("problem", ""),
            "input": "",
            "output": item.get("solution", "") 
        }
        train_items.append(record)
    
    # 将整个列表保存为一个JSON文件
    with open(filename, 'w', encoding='utf-8') as f:
        json.dump(train_items, f, ensure_ascii=False, indent=2)
    
    print(f"已保存 {len(data_subset)} 条记录到 {filename} (JSON格式)")

# 保存验证数据集函数 - 使用JSONL格式
def save_val_dataset(data_subset, filename):
    with open(filename, 'w', encoding='utf-8') as f:
        for item in data_subset:
            # 创建记录 - 验证集格式
            record = {
                "instruction": item.get("problem", ""),
                "input": "",
                "output": item.get("solution", "") 
            }
            f.write(json.dumps(record, ensure_ascii=False) + '\n')
    print(f"已保存 {len(data_subset)} 条记录到 {filename} (JSONL格式)")

# 保存测试数据集函数 - 使用JSONL格式
def save_test_dataset(data_subset, filename):
    with open(filename, 'w', encoding='utf-8') as f:
        for item in data_subset:
            # 创建记录 - 测试集格式
            record = {
                "id": str(uuid.uuid4()),
                "question": item.get("problem", ""),
                "answer": item.get("answer", "") or "",  # 确保answer不为null
                "solution": item.get("solution", "")
            }
            f.write(json.dumps(record, ensure_ascii=False) + '\n')
    print(f"已保存 {len(data_subset)} 条记录到 {filename} (JSONL格式)")

# 检查数据集重叠
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

if check_dataset_overlap(sets, name_mapping):
    # 保存三个数据集
    save_train_dataset(train_data, "numina_train_10k.json")
    save_val_dataset(val_data, "numina_val_3k.jsonl")
    save_test_dataset(test_data, "numina_test_500.jsonl")
    print("数据集划分完成!")
else:
    print("数据集划分失败: 发现交叉污染")

# 额外验证函数 - 确保没有重复并验证格式
def verify_datasets():
    print("\n进行最终数据验证...")
    
    # 加载保存的数据进行验证
    train_items = []
    val_items = []
    test_items = []
    
    # 读取保存的文件
    with open("numina_train_10k.json", 'r', encoding='utf-8') as f:
        train_items = json.load(f)
    
    with open("numina_val_3k.jsonl", 'r', encoding='utf-8') as f:
        for line in f:
            val_items.append(json.loads(line))
    
    with open("numina_test_500.jsonl", 'r', encoding='utf-8') as f:
        for line in f:
            test_items.append(json.loads(line))
    
    # 验证数量
    if len(train_items) != train_size or len(val_items) != val_size or len(test_items) != test_size:
        print(f"错误: 数据数量不匹配! 训练集: {len(train_items)}/{train_size}, " 
              f"验证集: {len(val_items)}/{val_size}, 测试集: {len(test_items)}/{test_size}")
        return False
    
    # 验证格式
    train_format_ok = all(
        "instruction" in item and "input" in item and "output" in item 
        for item in train_items
    )
    
    val_format_ok = all(
        "instruction" in item and "input" in item and "output" in item 
        for item in val_items
    )
    
    test_format_ok = all(
        "id" in item and "question" in item and "answer" in item and "solution" in item
        and item["answer"] is not None  # 确保answer不为null
        for item in test_items
    )
    
    if not (train_format_ok and val_format_ok and test_format_ok):
        print("错误: 数据格式不正确!")
        return False
    
    # 检查内容重复
    all_instructions = set()
    all_questions = set()
    
    # 训练集中的instruction不应与验证集重复
    for item in train_items:
        instr_hash = hashlib.md5(item["instruction"].encode()).hexdigest()
        all_instructions.add(instr_hash)
    
    for item in val_items:
        instr_hash = hashlib.md5(item["instruction"].encode()).hexdigest()
        if instr_hash in all_instructions:
            print("错误: 训练集和验证集之间有重复的instruction!")
            return False
        all_instructions.add(instr_hash)
    
    # 测试集中的question不应与训练/验证集中的instruction重复
    for item in test_items:
        ques_hash = hashlib.md5(item["question"].encode()).hexdigest()
        if ques_hash in all_instructions:
            print("错误: 测试集的question与训练/验证集的instruction有重复!")
            return False
        all_questions.add(ques_hash)
    
    print("验证成功: 所有数据集格式正确，没有交叉污染!")
    
    # 打印样例
    print("\n训练集样例 (JSON格式):")
    print(json.dumps(train_items[0], ensure_ascii=False)[:500] + "...")
    
    print("\n验证集样例 (JSONL格式):")
    print(json.dumps(val_items[0], ensure_ascii=False)[:500] + "...")
    
    print("\n测试集样例 (JSONL格式):")
    print(json.dumps(test_items[0], ensure_ascii=False)[:500] + "...")
    
    return True

verify_datasets()