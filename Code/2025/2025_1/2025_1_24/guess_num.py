# 生成一个随机变量
import random
num = random.randint(1, 999)

guess_num = int(input("请输入你猜的三位整数:\n"))

sign = False
time = 0
while sign != True:
    if guess_num == num:
        sign = True
        time += 1
    else:
        if guess_num > num:
            print("大了")
            guess_num = int(input("请再次输入你猜的三位整数:\n"))
            time += 1
        else:
            print("小了")
            guess_num = int(input("请再次输入你猜的三位整数:\n"))
            time += 1

print(f"恭喜你猜对了!,用了{time}次.")