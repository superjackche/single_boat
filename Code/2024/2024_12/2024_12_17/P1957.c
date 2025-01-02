//keys：先用fgets读进去，再用sscanf二次解析
#include <stdio.h>
#include <string.h>

int main(void) {
    int i;
    scanf("%d", &i);
    getchar(); // 清除缓冲区中的换行符

    char op = '\0'; // 存储当前运算符

    while (i--) {
        char line[100];
        // 读取一整行输入
        fgets(line, sizeof(line), stdin);

        // 变量声明
        char temp_op;
        int num1, num2;
        int count;

        // 尝试解析三个参数
        sscanf(line, "%c %d %d", &temp_op, &num1, &num2);

        if (temp_op >= 'a' && temp_op <= 'c') {
            op = temp_op;
        } else {
            sscanf(line, "%d %d", &num1, &num2);
        }

        // 计算结果并输出
        int result;
        char expression[100];

        switch (op) {
            case 'a':
                result = num1 + num2;
                sprintf(expression, "%d+%d=%d", num1, num2, result);
                break;
            case 'b':
                result = num1 - num2;
                sprintf(expression, "%d-%d=%d", num1, num2, result);
                break;
            case 'c':
                result = num1 * num2;
                sprintf(expression, "%d*%d=%d", num1, num2, result);
                break;
            default:
                continue;
        }

        // 输出结果和表达式长度
        printf("%s\n", expression);
        printf("%lu\n", strlen(expression));
    }

    return 0;
}