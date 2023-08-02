/*
 ============================================================================
 Name        : EX4.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
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
