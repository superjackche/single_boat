"""
    字典    {key:value}
    不能重复 可以嵌套(key不能为字典)
"""
# {"aaa": 100, "bbb": 99, "ccc": 98}
my_dict1 = {"aaa": 100, "bbb": 99, "ccc": 98}
my_dict2 = {}
my_dict3 = dict()
print(f"字典1的内容是{my_dict1},类型{type(my_dict1)}")
print(f"字典2的内容是{my_dict2},类型{type(my_dict2)}")
print(f"字典3的内容是{my_dict3},类型{type(my_dict3)}")

# 获取
print(my_dict1["aaa"])

# 新增元素
my_dict1["apple"] = 123
print(my_dict1)

# 更新元素
my_dict1["apple"] = 321
print(my_dict1)

# 删除元素  .pop  返回并删除指定key的value
value = my_dict1.pop("apple")
print(value)
print(my_dict1)

# 清空字典  .clear  清空
my_dict1.clear()
print(my_dict1)

# 获取全部的key .keys
my_dict1 = {"aaa": 100, "bbb": 99, "ccc": 98}
keys = my_dict1.keys()
print(keys)

# for遍历
for key in my_dict1:
    print(f"key是{key},value是{my_dict1[key]}") 