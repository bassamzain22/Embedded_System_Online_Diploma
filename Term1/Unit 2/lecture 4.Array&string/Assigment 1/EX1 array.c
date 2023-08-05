/*
 ============================================================================
 Question : Write a C program to find sum of two matrix of order 2* 2 using multidimensional arrays where, elements of matrix are entered by user?
 ============================================================================
 */
#include <stdio.h>
#include <stdlib.h>

int main(void) {
	float a[2][2],b[2][2];
	char c;
	printf("Enter the elements of 1st matrix\n");
	for(int i=0;i<2;i++)
	{
		for(int j=0;j<2;j++)
		{
			printf("Enter a%d%d: ",i+1,j+1);
			fflush(stdin); fflush(stdout);
			scanf("%f%c",&a[i][j],&c);

		}
	}
	printf("Enter the elements of 2nd matrix\n");

	for(int i=0;i<2;i++)
	{
		for(int j=0;j<2;j++)
		{
			printf("Enter b%d%d: ",i+1,j+1);
			fflush(stdin);fflush(stdout);
			scanf("%f%c",&b[i][j],&c);

		}
	}
	printf("Sum Of Matrix:\n");
	for(int i=0;i<2;i++)
	{
		for(int j=0;j<2;j++)
		{
			printf("%.1f   ",a[i][j]+b[i][j]);

		} printf("\n");

	}
}
