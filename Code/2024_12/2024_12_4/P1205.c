#include <stdio.h>
#include <string.h>

int compareArrays(char arr1[][11], char arr2[][11], int n) {
    for (int i = 0; i < n; i++) {
        if (strcmp(arr1[i], arr2[i]) != 0) {
            return 0; // 不相等
        }
    }
    return 1; // 相等
}

//注意要使用额外的temp存储中间量，避免被错误覆盖
void turn90(char start[][11], char temp[][11], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            temp[i][j] = start[n - j - 1][i];
        }
        temp[i][n] = '\0';  // 添加字符串结束符
    }
}

void reflect(char start[][11], char temp[][11], int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            temp[i][j] = start[i][n - j - 1];
        }
        temp[i][n] = '\0';  // 添加字符串结束符
    }
}

int main (void)
{
    int n;
    scanf("%d", &n);
    char start[11][11];
    char end[11][11];
    char temp1[11][11];
    char temp2[11][11];
    char temp3[11][11];
    char temp4[11][11];

    // 读取开始矩阵
    for (int i = 0; i < n; i++)
    {
        scanf("%s", start[i]);
    }
    // 读取结束矩阵
    for (int i = 0; i < n; i++)
    {
        scanf("%s", end[i]);
    }

    // 变换 1：顺时针旋转 90 度
    turn90(start, temp1, n);
    if (compareArrays(temp1, end, n))
    {
        printf("1\n");
        return 0;
    }

    // 变换 2：顺时针旋转 180 度
    turn90(temp1, temp2, n);
    if (compareArrays(temp2, end, n))
    {
        printf("2\n");
        return 0;
    }

    // 变换 3：顺时针旋转 270 度
    turn90(temp2, temp3, n);
    if (compareArrays(temp3, end, n))
    {
        printf("3\n");
        return 0;
    }

    // 变换 4：反射
    reflect(start, temp4, n);
    if (compareArrays(temp4, end, n))
    {
        printf("4\n");
        return 0;
    }

    // 变换 5：反射后旋转 90 度、180 度、270 度
    turn90(temp4, temp1, n);
    if (compareArrays(temp1, end, n))
    {
        printf("5\n");
        return 0;
    }
    turn90(temp1, temp2, n);
    if (compareArrays(temp2, end, n))
    {
        printf("5\n");
        return 0;
    }
    turn90(temp2, temp3, n);
    if (compareArrays(temp3, end, n))
    {
        printf("5\n");
        return 0;
    }

    // 变换 6：不改变
    if (compareArrays(start, end, n))
    {
        printf("6\n");
        return 0;
    }

    // 变换 7：无效转换
    printf("7\n");
    return 0;
}