# 集合 无需不可重复 可修改不支持下标索引访问
# add
my_set = {"hello", "world"}
my_set.add("abc")
print(my_set)

# remove
my_set.remove("abc")
print(my_set)

# pop随机取出一个元素
my_set = {"123", "456", "789", "abc", "def"}
element = my_set.pop()
print(f"集合{my_set}中被随机取出的元素是{element}") # 取出后原集合就没有被取出的元素了

# clear清空集合
my_set.clear()
print(my_set)

"""
    取出两个集合的差集
    集合1.difference(集合2),取出集合1有而集合2没有的
"""
set1 = {1, 2, 3}
set2 = {1, 3, 5, 6}
set3 = set1.difference(set2)
print(set1)
print(set2)
print(set3)

"""
    消除两个集合的差集
    集合1.difference_update(集合2),在集合1内,删除和集合2相同的元素
    其中集合1被修改,集合2不变
"""
set1 = {1, 2, 3}
set2 = {1, 5, 6}
set1.difference_update(set2)
print(set1)
print(set2)

"""
    合并两个集合
    集合1.union(集合2),返回合并的新集合
    原集合不变
"""
set1 = {1, 2, 3}
set2 = {1, 5, 6}
set3 = set1.union(set2)
print(set1)
print(set2)
print(set3)

# 遍历只能用for循环
set1 = {1, 2, 3, 4, 5, 6, 7, 8, 9}
for element in set1:
    print(element)