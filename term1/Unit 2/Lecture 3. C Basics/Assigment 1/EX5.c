/*
 ============================================================================
 Name        : EX5.c
 Author      : bassam
 Version     :
 Copyright   : 
 Description : Hello World in C, Ansi-style
 ============================================================================float a,b;
	printf("Enter value of a: ");
	fflush(stdout);
	scanf("%f\n",&a);
	printf("Enter value of b: ");
		fflush(stdout);
		scanf("%f %f",&x,&y);
	printf("Product %f",x*y);
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	char c;
	printf("Enter a character: ");
	fflush(stdout);
	scanf("%c",&c);
	printf("ASCII value of G = %d",c);

}
