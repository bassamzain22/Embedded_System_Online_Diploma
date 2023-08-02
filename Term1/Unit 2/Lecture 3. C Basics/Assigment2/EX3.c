/*
 ============================================================================
Question: C Program to Find the Largest Number Among Three Numbers?
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	float x,y,z;
	printf("Enter three numbers: ");
	fflush(stdout);
	scanf("%f%f%f",&x,&y,&z);
	if(x<y)x=y;
	if(x<z)x=z;
	printf("Largest number = %.2f",x);
}
