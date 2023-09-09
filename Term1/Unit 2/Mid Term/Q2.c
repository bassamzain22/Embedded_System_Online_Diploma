/*c function to take an integer number and calculate it's square root */
#include <stdio.h>
#include <math.h>
void square_root (double num)
{
printf("%.3lf", sqrt(num));
}
int main()
{
double num;
scanf("%lf",&num);
square_root(num);
}