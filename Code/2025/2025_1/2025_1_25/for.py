name = 'jack'

for x in name:
    # 将name的内容,挨个取出赋予x临时变量
    print(x)

str1 = input("请输入要检测的字符串:")
str2 = input("请输入要检测的字母:")

time = 0
for x in str1:
    if str2 == x:
        time += 1

print("字符串%s中共含有%d个字母%s" %(str1, time, str2))