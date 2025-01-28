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

# 用for循环实现打印整齐的99乘法表
num1 = 1
num2 = 1

for num2 in range(1, 10):
    for num1 in range(1, num2+1):
        print("%d*%d=%d\t" %(num1, num2, num1*num2), end='')
        num1 += 1
    print("\n", end='')

# 二者存在差别