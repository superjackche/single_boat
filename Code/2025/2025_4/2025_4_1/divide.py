import uuid
import json
import random
from datasets import load_dataset

# 加载NuminaMath-1.5数据集
print("正在加载数据集...")
dataset = load_dataset("AI-MO/NuminaMath-1.5")

# 确定数据集的主要部分
main_split = list(dataset.keys())[0]  # 使用第一个可用的拆分
data = dataset[main_split]
print(f"使用数据拆分: {main_split}, 总样本数: {len(data)}")

# 检查数据集样本结构
if len(data) > 0:
    sample = data[0]
    print(f"数据样本字段: {list(sample.keys())}")

# 将数据集转换为列表并随机打乱
all_data = list(data)
random.seed(42)  # 设置随机种子以确保可重复性
random.shuffle(all_data)

# 确定集合大小
train_size = 10000
val_size = 3000
test_size = 500

# 划分数据集
train_data = all_data[:train_size]
val_data = all_data[train_size:train_size + val_size]
test_data = all_data[train_size + val_size:train_size + val_size + test_size]

# 保存数据集函数
def save_dataset(data_subset, filename):
    with open(filename, 'w', encoding='utf-8') as f:
        for item in data_subset:
            # 根据实际数据集字段名调整映射
            record = {
                "id": str(uuid.uuid4()),
                "question": item.get("problem", ""),  # 使用problem字段作为question
                "answer": item.get("answer", ""),     # 保持answer字段不变
                "solution": item.get("solution", "")  # 保持solution字段不变
            }
            f.write(json.dumps(record, ensure_ascii=False) + '\n')
    
    # 验证数据格式
    with open(filename, 'r', encoding='utf-8') as f:
        sample_line = f.readline().strip()
        sample_record = json.loads(sample_line)
        print(f"已保存 {len(data_subset)} 条记录到 {filename}")
        print(f"样本记录: id={sample_record['id'][:8]}..., question长度={len(sample_record['question'])}, "
              f"answer长度={len(sample_record['answer'])}, solution长度={len(sample_record['solution'])}")

# 保存三个数据集
save_dataset(train_data, "numina_train_10k.jsonl")
save_dataset(val_data, "numina_val_3k.jsonl")
save_dataset(test_data, "numina_test_500.jsonl")

print("数据集划分完成!")