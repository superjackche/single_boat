# import mymodule_01
# add = mymodule_01.test01(3, 4)
# print(add)

# import mymodule_01 as mm
# add = mm.test01(3, 4)
# print(add)

# from mymodule_01 import test01
# add = test01(4, 5)
# print(add)

# from mymodule_01 import test01 as t1
# add = t1(4, 5)
# print(add)

from mymodule_01 import *
add = test01(3, 4)
# test02(3, 4)不在all的范围内，故未导入
print(add)