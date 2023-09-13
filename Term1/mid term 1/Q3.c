/*c function to print all prime numbers between two numbers? */
#include <stdio.h>
#include <math.h>
void prime_numbers (int start, int end)
 {
 int i,j,x=1;
 for(i=start;i<=end;i++)
 { 
    x=1;
   for(j=1;j<=sqrt(i);j++)
   {
    if(j>1&&i%j==0)
     {
     x=0;
     break;
     }
   }
  if(x) printf("%d ",i);
 }

 }
int main()
{
 int start, end;
 scanf("%d %d", &start, &end);
 prime_numbers (start, end);
}