/*
 ============================================================================
Question: Write C Program to Check Whether a Number is Even or Odd?
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int x;
	printf("Enter an integer you want to check: ");
	fflush(stdout);
	scanf("%d",&x);
	if(x%2)printf("%d is odd",x);
	else printf("%d is even",x);
}
