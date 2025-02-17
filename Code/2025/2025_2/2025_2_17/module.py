# 直接使用import导入time.py，调用其中的sleep函数
# import time
# for second in {1, 2, 3}:
#     print(second)
#     time.sleep(1)
#     second += 1

# 使用from导入time中的sleep函数
from time import sleep
print("你好吗")
sleep(3)
print("我很好")

# 使用*导入所有函数
from time import *
sleep(5)    # 此处直接调用sleep()
print("over")

# as别名
import time as tt
tt.sleep(3)

from time import sleep as sl
sl(3)