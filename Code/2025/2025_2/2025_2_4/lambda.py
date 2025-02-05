# lambda匿名函数
def test_func(compute):
    result = compute(1, 2)
    print(f"结果是{result}")

test_func(lambda x, y: x + y)   