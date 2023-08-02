/*
 ============================================================================
Question: C Program to Calculate Sum of Natural Numbers?
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int x;
	printf("Enter an integer : ");
	fflush(stdout);
	scanf("%d",&x);
	int y=x*(x+1)/2;
	printf("sum = %d",y);
}
