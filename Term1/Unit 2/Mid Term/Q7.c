/*c  function to sum numbers from 1 to 100 (without loop)?*/
 #include <stdio.h>
 #include <math.h>
 int sum_numbers(int num)
 {
 return num*(num+1)/2;
 }
 int main()
 {
 int num=100;
 printf("%d", sum_numbers (num));
 }