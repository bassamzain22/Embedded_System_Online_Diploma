/*
 ============================================================================
Question:C program to Calculate Factorial ofa Number Using Recursion?
 ============================================================================
 */

#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
int x=1;
int factorial(int x)
{
    if(x==1)return 1;
    return x*(factorial(x-1));
}
int main()
{
	int x;
	printf("Enter an positive integer: ");
	fflush(stdout);fflush(stdin);
	scanf("%d",&x);
printf("Factorial of %d = %d",x,factorial(x));
}
