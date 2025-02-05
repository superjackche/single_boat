# sorted排序    排序的结果会变成list
my_list = [5, 3, 1, 6, 2, 4]
my_tuple = [5, 3, 1, 6, 2, 4]
my_str = "fbaiucwebg"
my_set = [5, 3, 1, 6, 2, 4]
my_dict = {"key3": 1, "key4": 3, "key5": 2, "key2": 4, "key1": 2}

# 从小到大排序
print(sorted(my_list))
print(sorted(my_tuple))
print(sorted(my_str))
print(sorted(my_set))
print(sorted(my_dict))

print(sorted(my_list, reverse=True))
print(sorted(my_tuple, reverse=True))
print(sorted(my_str, reverse=True))
print(sorted(my_set, reverse=True))
print(sorted(my_dict, reverse=True))