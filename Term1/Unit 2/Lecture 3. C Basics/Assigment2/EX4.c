/*
 ============================================================================
Question: C Program to Check Whether a Number is Positive or Negative?
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	float x;
		printf("Enter a number: ");
		fflush(stdout);
		scanf("%f",&x);
		if(x)
		{
			if(x>0)printf("%.2f is positive.",x);
			else printf("%.2f is negative.",x);
		}
		else printf("You entered zero.");
}
