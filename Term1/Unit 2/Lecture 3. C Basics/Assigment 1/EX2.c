/*
 ============================================================================
 Question: Write C Program to Print a Integer Entered by a User?
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	printf("Enter a integer: ");
	fflush(stdout);
	int x;
	scanf("%d",&x);
	printf("You entered: %d",x);
}
