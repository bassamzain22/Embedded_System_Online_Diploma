/*
 ============================================================================
 Name        : EX8.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	        char c;
	        float x,y;
			printf("Enter operator either + or - or * or /:");
			fflush(stdout);
			scanf("%c",&c);
			printf("Enter two operands: ");
		    fflush(stdout);
		    scanf("%f%f",&x,&y);
		    if(c=='+')printf("%f %c %f = %.1f",x,c,y,x+y);
		    if(c=='-')printf("%f %c %f = %.1f",x,c,y,x-y);
		    if(c=='*')printf("%f %c %f = %.1f",x,c,y,x*y);
		    if(c=='/')printf("%f %c %f = %.1f",x,c,y,x/y);
}
