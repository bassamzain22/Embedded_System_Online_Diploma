 /*c function to take a number and sum all digits */
#include <stdio.h>
int sum_digits (int num)
{
 int sum=0;
 while(num>0)
  {
 sum+=num%10;
 num/=10;
  }
 return sum;
 }
 int main()
 {
 int num;
 scanf("%d", &num);
 printf("%d", sum_digits(num));
}
