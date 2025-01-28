# 使用 range(6) 生成从0到5的序列
for x in range(6):
    print(x, end='')
print()  # 换行

# 使用 range(4,9) 生成从4到8的序列
for x in range(4, 9):
    print(x, end='')
print()  # 换行

# 使用 range(2,9,3) 生成从2开始，步长为3，到8为止的序列
for x in range(2, 9, 3):
    print(x, end='')
print()  # 换行

# 用for实现循环
for x in range(10):
    print(f"第{x+1}次循环")