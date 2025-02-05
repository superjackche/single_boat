"""
    对文件的读取
"""
import time
# 打开文件
f = open("d:/Code/single_boat/Code/2025/2025_2/2025_2_4/第三人称.txt", "r", encoding="UTF-8")
print(type(f))

# 读取文件  read()
print(f"读取10个字节的结果:{f.read(10)}")   # 注意光标变化
print(f"read all:{f.read()}")

print("------------------------------------------------")

# 读取文件  readlines()
f = open("d:/Code/single_boat/Code/2025/2025_2/2025_2_4/第三人称.txt", "r", encoding="UTF-8")
lines = f.readlines()   # 读取文件的全部行,封装到列表中
print(f"lines对象的类型:{type(lines)}")
print(f"lines对象的内容是:{lines}")

# 读取文件  readline()  每次单行读取
f = open("d:/Code/single_boat/Code/2025/2025_2/2025_2_4/第三人称.txt", "r", encoding="UTF-8")
line1 = f.readline()
line2 = f.readline()
line3 = f.readline()
print(f"第一行数据是:{line1}")
print(f"第二行数据是:{line2}")
print(f"第三行数据是:{line3}")

# for循环读取文件行
f = open("d:/Code/single_boat/Code/2025/2025_2/2025_2_4/第三人称.txt", "r", encoding="UTF-8")
for line in f:
    print(f"每一行数据是:{line}")

# 程序等待
time.sleep(5)

# 文件的关闭
f.close()

# with open 语法操作文件    方便自动关闭
with open("d:/Code/single_boat/Code/2025/2025_2/2025_2_4/第三人称.txt", "r", encoding="UTF-8") as f:
    for line in f:
        print(f"每一行数据是:{line}") 