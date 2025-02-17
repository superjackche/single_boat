def test01():
    print("test01 start")
    1 / 0
    print("test01 end")


def test02():
    print("test02 start")
    test01()
    print("test02 end")

def main():
    test02()


try:
    main()
except Exception as e:
    print(f"Wrong because: {e}")