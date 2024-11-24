#include<stdio.h>

#define        LEN        100

//调整函数 
void distribute(int * bullets , int size , int number ) ;

int main()
{
    int        bullets[LEN] ;
    int        n , m , i ;    
         
    scanf("%d" , &n ) ;    //读入战士总数 
    for( i = 0 ; i < n ; i++ )
    {
        scanf("%d" , &bullets[i] ) ;//读入每个战士手中初始的子弹数 
    }
    scanf("%d" , &m ) ;//读入调整的次数（m>0) 
    distribute(bullets , n , m ) ;//调整 
    for( i = 0 ; i < n - 1 ; i++ )//输出调整后结果 
    {
        printf("%d " , bullets[i] ) ;
    }
    printf("%d\n" , bullets[i] ) ;
    
    return 0;    
}

int is_equal(int bullets[], int n)
{
    int sign = 0;
    for (int i = 0; i < n-1; i++)
    {
        if (bullets[i] != bullets[i+1]) sign = 1;
    }
    return sign;
}

void distribute(int * bullets , int size , int number )
{
    if (is_equal != 0)//子弹数不相等就一直进行
    {
        while (number--)//进行次数
        {
            //初始化temp
            int b[LEN] = {0};

            //使子弹为偶数
            for (int j = 0; j < size; j++)
            {
                if (bullets[j] % 2 == 1)
                {
                    bullets[j] += 1;
                }
            }

            //同时分出一半
            for (int i = 0; i < size; i++)
            {
                bullets[i] /= 2;
                b[i] = bullets[i];
            }
            //同时分给下一个人
            for (int j = 0; j < size-1; j++)
            {
                bullets[j+1] += b[j];
            }
            //最后一人分给第一个人
            bullets[0] += b[size-1];
        }
    }
    
}