 #include "reg52.h"

sbit LED1 = P2^0;
void delay_10us(u16 ten_us)//当传入Ten_us=1时，延时10us
{
    while(ten_us--);
}
void main()
{
    while(1)
    {
        
    }
}