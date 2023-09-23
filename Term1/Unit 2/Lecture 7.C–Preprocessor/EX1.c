/*
 * EX1.c
 *
 *  Created on: Sep 23, 2023
 *      Author: bassam zain
 */
#include <stdio.h>
#define pi 3.1416
#define area(r) pi*r*r
int main()
{
	float  redius ;
	printf("Enter the redius : ");
	fflush(stdout);
	scanf("%f",&redius);
	printf("Area = %.2f",area(redius));
}
