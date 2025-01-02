#include <stdio.h>

int main(void)
{
    int n, t, sign;
    double sum = 0;
    scanf("%d %d", &n, &t);

    int ch[n][2];           // 存储重量和价值
    double density[n];      // 存储价值密度
    int used[n];            // 标记物品是否已被使用

    for (int i = 0; i < n; i++)
    {
        scanf("%d %d", &ch[i][0], &ch[i][1]);
        density[i] = (double)ch[i][1] / ch[i][0];
        used[i] = 0; // 初始化为未使用
    }

    while (t > 0)
    {
        double maxDensity = -1.0;
        int sign = -1;

        // 寻找当前未使用的价值密度最高的物品
        for (int i = 0; i < n; i++)
        {
            if (!used[i] && density[i] > maxDensity)
            {
                maxDensity = density[i];
                sign = i;
            }
        }

        // 如果没有可选的物品，跳出循环
        if (sign == -1)
            break;

        if (t >= ch[sign][0])
        {
            t -= ch[sign][0];
            sum += ch[sign][1];
            used[sign] = 1; // 标记物品已使用
        }
        else
        {
            sum += density[sign] * t;
            t = 0;
        }
    }
    printf("%.2f\n", sum);
    return 0;
}