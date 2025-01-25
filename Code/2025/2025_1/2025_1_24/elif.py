import sys
num = int(input("请输入一个三位正整数:"))
if num % 1 != 0:
    print("输入错误")
    sys.exit(0)
if num > 500:
    if num % 2 == 0:
        print("这是一个大于500的偶数")
    else:
        print("这是一个大于500的奇数")
elif num > 0 and num <= 500:
    if num % 2 == 0:
        print("这是一个不大于500的偶数")
    else:
        print("这是一个不大于500的奇数")
else:
    print("输入错误")