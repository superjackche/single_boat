#include <stdio.h>
int main()
{
    for(;;)
    {
        for(;;)
        {
            for(;;)
            goto error;//可用于跳出到指定步骤
        }
    }
    error:

}