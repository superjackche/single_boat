#include <stdio.h>
int main(){
    int n=129;
    char ch;
    float f=3.14;
      
    ch=n;
    n=f;
    printf("%d %d %.2f\n",n,ch,f);
}