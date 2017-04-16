#include <stdio.h>
#include <math.h>
 
int main(void)
{
    printf("signbit(+0.0) = %d\n", signbit(+0.0));
    printf("signbit(-0.0) = %d\n", signbit(-0.0));
}
