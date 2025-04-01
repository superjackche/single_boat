import numpy as np
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# 定义二维Softmax函数
def softmax_2d(z1, z2):
    exp_z = np.exp([z1, z2])
    return exp_z / np.sum(exp_z)

# 生成输入数据
z1 = np.linspace(-5, 5, 100)
z2 = np.linspace(-5, 5, 100)
Z1, Z2 = np.meshgrid(z1, z2)

# 计算Softmax输出
S1 = np.zeros_like(Z1)
S2 = np.zeros_like(Z1)
for i in range(len(z1)):
    for j in range(len(z2)):
        s = softmax_2d(Z1[i,j], Z2[i,j])
        S1[i,j] = s[0]
        S2[i,j] = s[1]

# 绘制3D曲面图
fig = plt.figure(figsize=(12, 6))

# 子图1：s1的曲面
ax1 = fig.add_subplot(121, projection='3d')
ax1.plot_surface(Z1, Z2, S1, cmap='viridis')
ax1.set_xlabel('z1')
ax1.set_ylabel('z2')
ax1.set_zlabel('s1')
ax1.set_title('Softmax Output s1')

# 子图2：s2的曲面
ax2 = fig.add_subplot(122, projection='3d')
ax2.plot_surface(Z1, Z2, S2, cmap='viridis')
ax2.set_xlabel('z1')
ax2.set_ylabel('z2')
ax2.set_zlabel('s2')
ax2.set_title('Softmax Output s2')

plt.tight_layout()
plt.show()