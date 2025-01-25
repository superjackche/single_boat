# 用while循环实现打印整齐的99乘法表
num1 = 1
num2 = 1

while num2 < 10:
    while num1 <= num2:
        print("%d*%d=%d\t" %(num1, num2, num1*num2), end='')
        num1 += 1
    print("\n", end='')
    num1 = 1
    num2 += 1