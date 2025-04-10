import tkinter as tk
from tkinter import ttk, messagebox
import json
import hashlib
import re
from datasets import load_dataset
import requests
import os
from ttkthemes import ThemedTk

class DatasetExtractor:
    def __init__(self):
        # 初始化窗口，使用现代化主题
        self.window = ThemedTk(theme="arc")
        self.window.title("测试集抽取工具")
        self.window.geometry("600x500")
        self.setup_ui()

    def setup_ui(self):
        """设置图形化界面"""
        # 数据源选择
        tk.Label(self.window, text="数据源").pack(pady=5)
        self.source_var = tk.StringVar(value="Hugging Face")
        ttk.Combobox(self.window, textvariable=self.source_var, 
                     values=["Hugging Face", "URL", "本地"]).pack()

        # 数据集名称或链接输入
        tk.Label(self.window, text="数据集名称/链接").pack(pady=5)
        self.link_entry = ttk.Entry(self.window, width=50)
        self.link_entry.pack()

        # 代理设置
        tk.Label(self.window, text="代理 (可选, 格式: http://proxy:port)").pack(pady=5)
        self.proxy_entry = ttk.Entry(self.window, width=50)
        self.proxy_entry.pack()

        # 输出格式选择
        tk.Label(self.window, text="输出格式").pack(pady=5)
        self.format_var = tk.StringVar(value="JSON")
        ttk.Radiobutton(self.window, text="JSON", variable=self.format_var, value="JSON").pack()
        ttk.Radiobutton(self.window, text="JSONL", variable=self.format_var, value="JSONL").pack()

        # 字段映射输入
        tk.Label(self.window, text="字段映射 (JSON 格式, 如 {\"text\": \"instruction\"})").pack(pady=5)
        self.mapping_text = tk.Text(self.window, height=4, width=50)
        self.mapping_text.pack()

        # 其他设置
        self.ascii_var = tk.BooleanVar(value=True)
        ttk.Checkbutton(self.window, text="保留非 ASCII 字符", variable=self.ascii_var).pack(pady=5)

        tk.Label(self.window, text="抽取数据量 (留空表示全部)").pack(pady=5)
        self.amount_entry = ttk.Entry(self.window, width=10)
        self.amount_entry.pack()

        self.layer_var = tk.BooleanVar(value=False)
        ttk.Checkbutton(self.window, text="分层抽取 (适用于大数据集)", variable=self.layer_var).pack(pady=5)

        # 开始抽取按钮
        ttk.Button(self.window, text="开始抽取", command=self.extract_data).pack(pady=20)

    def extract_data(self):
        """执行数据抽取逻辑"""
        # 获取用户输入
        source = self.source_var.get()
        link = self.link_entry.get()
        proxy = self.proxy_entry.get() or None
        try:
            mapping = json.loads(self.mapping_text.get("1.0", tk.END).strip() or "{}")
        except json.JSONDecodeError:
            messagebox.showerror("错误", "字段映射格式不正确，请输入有效的 JSON。")
            return
        amount = self.amount_entry.get()
        amount = int(amount) if amount.isdigit() else None
        output_format = self.format_var.get()

        # 加载数据
        try:
            if source == "Hugging Face":
                data = load_dataset(link, split="test")
                data = data.to_dict()  # 转换为字典列表
            elif source == "URL":
                proxies = {"http": proxy, "https": proxy} if proxy else None
                response = requests.get(link, proxies=proxies)
                response.raise_for_status()
                data = response.json()  # 假设为 JSON 文件
            else:  # 本地文件
                with open(link, "r", encoding="utf-8") as f:
                    data = json.load(f)
        except Exception as e:
            messagebox.showerror("错误", f"加载数据失败: {e}")
            return

        # 处理数据
        unique_data = self.remove_duplicates(data, mapping, amount)
        self.save_data(unique_data, output_format)

        messagebox.showinfo("成功", "数据抽取完成！")

    def remove_duplicates(self, data, mapping, amount):
        """去重并处理数据"""
        seen = set()
        result = []
        for item in data[:amount] if amount else data:
            # 根据字段映射转换数据
            formatted_item = {k: item.get(v) for k, v in mapping.items() if v in item}
            if not self.ascii_var.get():
                # 去除非 ASCII 字符
                formatted_item = {k: re.sub(r'[^\x00-\x7F]+', '', v or '') 
                                  for k, v in formatted_item.items()}
            item_str = json.dumps(formatted_item, sort_keys=True)
            hash_val = hashlib.md5(item_str.encode()).hexdigest()
            if hash_val not in seen:
                seen.add(hash_val)
                result.append(formatted_item)
        return result

    def save_data(self, data, format):
        """保存数据到文件"""
        filename = "output." + ("json" if format == "JSON" else "jsonl")
        if format == "JSON":
            with open(filename, "w", encoding="utf-8") as f:
                json.dump(data, f, ensure_ascii=False, indent=4)
        else:  # JSONL
            with open(filename, "w", encoding="utf-8") as f:
                for item in data:
                    f.write(json.dumps(item, ensure_ascii=False) + "\n")

    def run(self):
        """运行程序"""
        self.window.mainloop()

if __name__ == "__main__":
    app = DatasetExtractor()
    app.run()