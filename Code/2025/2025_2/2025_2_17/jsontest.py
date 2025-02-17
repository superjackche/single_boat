import json
# 准备列表，列表内每一个元素都是字典，准备转化为json
data = [{"name": "jack", "age":11}, {"name": "mick", "age":11}, {"name": "dick", "age":11}]
json_str = json.dumps(data)
print(type(json_str))
print(json_str)

# 准备字典，将字典转换成json
d = {"name":"陈望舒", "age":16}
json_str = json.dumps(d, ensure_ascii=False)    # 不以ascii码格式输出，便于显示中文
print(type(json_str))
print(json_str)

# 将json字符串转换为python数据类型[{k: v, k: v}, {k: v, k: v}]
s = '[{"name": "jack", "age":11}, {"name": "mick", "age":11}, {"name": "dick", "age":11}]'
l = json.loads(s)
print(type(l))
print(l)

# 将json字符串转换为python数据类型{k: v, k: v}
s = '{"name":"陈望舒", "age":16}'
d = json.loads(s)
print(type(d))
print(d)