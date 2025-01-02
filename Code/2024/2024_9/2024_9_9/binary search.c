#include <stdio.h>
int main()
{
    int arr[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int k = 7;
    int left = 0;
    int right = 9;
    while (left <= right)
    {
        int mid = (left + right) / 2;
        if(arr[mid] < k)
        {
            left = mid + 1;
        }
        else if(arr[mid] > k)
        {
            right = mid - 1;
        }
        else
        {
            printf("真相就是%d是它的下标", mid);
            break;
        }
    }
    if (left > right)
    {
        printf("不存在");
    }
    return 0;
}