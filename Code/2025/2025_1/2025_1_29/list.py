my_list = ['111', 222, '333']

# .index    检索
print(my_list.index(222))
# print(my_list.index('222'))

# .insert   插入
my_list.insert(1, '22')
print(my_list)

# .append   尾插单个元素
my_list.append(444)
print(my_list)

# .extend   尾插list
my_list.extend([555, 555, '666'])
print(my_list)

# .del  删除    or   .pop    取出元素(删除)并返回元素
del my_list[3]
print(my_list)
list_del = my_list.pop(3)  # 注意下标变化
print(list_del)
print(my_list)

# .remove   删除某元素在列表中的第一个匹配项
my_list.remove(555)
print(my_list)

# .clear    清空列表
my_list.clear()
print(my_list)

# .count    统计某元素在列表中的数量
my_list = ['111', '22', 222, '333', 444, 555, 555, '666']
num = my_list.count(555)
print(num)

# .len  统计列表内有多少元素
print(len(my_list))