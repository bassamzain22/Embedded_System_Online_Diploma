/*
 ============================================================================
Question:C Program to Find Factorial ofa Number?
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	long long x;
	printf("Enter an integer: ");
	fflush(stdout);
	scanf("%lld",&x);
	if(x<0)printf("Error!!! factorial of negative number doesn't exist.");
	else
	{
		if(x==0)printf("1");
		else
			{
			long long y=x;
			for(int i=1;i<y;i++)x*=i;
			printf("Factorial = %lld",x);
			}
	}

}
