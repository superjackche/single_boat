#include <stdio.h>
int main(){
    char a[]="Action"; 
    char b[10]= "World"; 
    char *from=a,*to=b;
    while (*to++=*from++);
    printf("%s,%s\n",a,b);
}