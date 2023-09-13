/*c function to revers digits in number?*/
#include <stdio.h>
#include <math.h>
int reverse_digits(int num)
 {
    int temp=0;
    while(num>0)
        { 
            temp+=num%10;
            num/=10;
            temp*=10;
        }
        return temp/10;
}

int main()
{
int num;
scanf("%d", &num);
printf("%d",reverse_digits (num));
}