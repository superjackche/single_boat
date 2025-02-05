def test_func():
    result = compute(1, 2)
    print(f"compute参数的类型是{type(compute)}")
    print(f"计算结果{result}")

def compute(x, y):
    return x + y

test_func()