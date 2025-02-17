# 捕获异常
try:
    print(name)
    1 / 0
except (NameError, ZeroDivisionError) as e:
    print("出现了变量未定义 或者 除以零的异常情况")

try:
    f = open("d:/test.txtf", "r", encoding="UTF-8")
except Exception as e:  # 可单独except
    print("出现了异常情况")
    f = open("d:/test.txtf", "w", encoding="UTF-8")
else:
    print("没有出现异常")
finally:
    print("over")
    f.close() 
