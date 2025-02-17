__all__ = ['test01']

def test01(a, b):
    return a + b

def test02(a, b):
    return a - b

if __name__ == "__main__":
    add = test01(1, 2)
    print(add)

    minus = test02(2, 3)      
    print(minus)