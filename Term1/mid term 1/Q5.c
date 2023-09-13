 /*c function to count number of ones in binary number?*/
 #include <stdio.h>
 #include <math.h>
 int number_of_ones(int num)
 {
   int temp=0;
   while(num>0)
   {
       if(num%2)temp++;
       num/=2;
   }
    return temp;
 }
int main()
 {
int num;
scanf("%d", &num);
printf("%d", number_of_ones (num));
 }