#include <stdio.h>
int main(){
    char arr1[] = "welcome to NewYork!!!!!";
    char arr2[] = "#######################";
    
    int left = 0;
    int right = strlen(arr1) - 1;
    int i = 1;
    while(left <= right)
    {
    arr2[left] = arr1[left];
    arr2[right] = arr1[right];
    printf("%s\n", arr2);
    sleep(i);
    left++;
    right--;
    i = i - 0.1;
    }
    return 0;
}