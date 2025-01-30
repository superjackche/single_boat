# 元组  不可被更改
t1 = (1, "hello", True)
t2 = ()
t3 = tuple()
print(type(t1))
print(type(t2))
print(type(t3))
print(t1)
print(t2)
print(t3)

# 定义单个元素
t4 = ("hello", )
print(f"t4类型是{type(t4)},内容是{t4}")