my_str = "123 456 789 123"

# 通过下标索引
value_1 = my_str[1]
value_2 = my_str[-14]
print(f"从字符串{my_str}取下标为1的元素,为{value_1};从字符串{my_str}取下标为-15的元素,为{value_2}")

# 原字符串无法被更改or替换
# my_str[1] = "2"     # 会报错
print(my_str)

# index方法
value = my_str.index("123")
print(f"在字符串{my_str}中查找123,其起始下标是:{value}")

# replace方法 本质上是返回了一个新的被更改过的字符串
my_str_new = my_str.replace("123", "321")    # 将字符串内的全部"字符串1"替换为"字符串2"并返回一个新的字符串
print(f"原来的字符串是{my_str},现在的字符串是{my_str_new}")

# split方法
my_str = "abc def ghi jkl"
my_str_list = my_str.split(" ")
print(f"将字符串{my_str}进行split切分后得到:{my_str_list}, 类型是:{type(my_str_list)}")

# srtip方法
my_str = "  abcd 123 abcd   "
print(my_str.strip())   # 去除前后空格
my_str = "12abcd 123 abcd21"
print(my_str.strip("12"))   # 去前后指定字符串.传入的是"12",其实就是"1"和"2"都会移除,是按照单个字符

# while循环
index = 0
while index < len(my_str):
    print(my_str[index])
    index += 1

# for循环
for i in my_str:
    print(i)