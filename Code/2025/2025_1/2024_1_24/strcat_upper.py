str1 = "can"
str2 = "do"
str3 = "u"
str4 = "what %s i %s for %s" %(str1, str2, str3)
print(str4)

num1 = 2025
num2 = 1
num3 = 24
num4 = 12
num5 = 13
str5 = "曾经是 %s 年 %s 月 %s 日 %s 时 %s 分" %(num1, num2, num3, num4, num5)
print(str5)

str6 = ", so "

print(str5 + str6 + str4)

str_final = "%s%s%s" %(str5, str6, str4)
print(str_final)

name = "jack"
age = 18
height = 1.78
weight = 71.2
# %n.m+s/d/f n是长度(宽度), m是精度
message = "my name is %s. i am %d years old. my height is %.2fm, and my weight is %.2fkg" %(name, age, height, weight)
print(message)
# 另 可用f直接快速格式化填充(仅填充,无长度和精度控制)
print(f"my name is {name}. i am {age} years old. my height is {height}m, and my weight is {weight}kg")