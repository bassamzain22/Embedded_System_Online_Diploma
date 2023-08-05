/*
 ============================================================================
Question : C Program to Find Transpose of a Matrix?
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int r,c;
	printf("Enter rows and column of matrix: ");
	fflush(stdin);fflush(stdout);
	scanf("%d %d",&r,&c);
	int a[r][c],b[c][r];
	printf("Enter elements of matrix:\n");
	for(int i=0;i<r;i++)
	{
		for(int j=0;j<c;j++)
		{
			printf("Enter elements ");
			fflush(stdin);fflush(stdout);
			printf("a%d%d:",i+1,j+1);
			fflush(stdin);fflush(stdout);
			scanf("%d",&a[i][j]);
			b[j][i]=a[i][j];
		}
	}
	printf("Entered Matrix:\n");
	for(int i=0;i<r;i++)
	{
		for(int j=0;j<c;j++)
		{
			printf("%d ",a[i][j]);
		}printf("\n");
	}
	printf("Transpose of Matrix: \n");
		for(int i=0;i<c;i++)
		{
			for(int j=0;j<r;j++)
			{
				printf("%d ",b[i][j]);
			}printf("\n");
		}
}
