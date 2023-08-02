/*
 ============================================================================
 Name        : EX6.c
 Author      : 
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
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
