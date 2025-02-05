def user_info(name, age, gender):
    print(f"您的名字是{name},年龄是{age}, 性别是{gender}")

# 关键字传参    可以不按照固定顺序
user_info(gender="male", name="小明", age=20)
# 可以和位置参数混用    位置参数必须在前,且匹配参数顺序
user_info("小明", gender="male", age=20) 

# 缺省参数(默认值)
def user_info(name, age, gender='male'):
    print(f"姓名是{name},年龄是{age},性别是{gender}")

user_info('小天', 18)
user_info('小红', 16, 'female')

# 不定长 - 位置不定长, *号
# 不动产定义的形式参数会作为元组存在,接收不定长数量的参数传入
def user_info(*args):
    print(f"args参数的类型是{type(args)},内容是{args}")

user_info(1, 2, 3, '小刚', 'boy')

# 不定长 - 关键字不定长, **号
def user_info(**kwargs):
    print(f"args参数的类型是{type(kwargs)}, 内容是{kwargs}")

user_info(name='小王', age=23, gender='male')