/*
 ============================================================================
 Name        : EX6.c
 Author      : bassam
 Version     :
 Copyright   : 
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	float a,b;
		printf("Enter value of a: ");
		fflush(stdout);
		scanf("%f",&a);
		printf("Enter value of b: ");
			fflush(stdout);
			scanf("%f",&b);
			float x=b;
			b=a;
			a=x;
			printf("After swapping, value of a = %f\n",a);
			printf("After swapping, value of b = %f",b);
}