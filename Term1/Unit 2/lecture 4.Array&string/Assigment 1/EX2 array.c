/*
 ============================================================================
 Question : C Program to Calculate Average Using Arrays?
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int n;
	printf("Enter the numbers of data: ");
	fflush(stdin);fflush(stdout);
	scanf("%d",&n);
	float arr[n],sum=0;
	for(int i=0;i<n;i++)
	{
		printf("%d. Enter number : ",i+1);
		fflush(stdin);fflush(stdout);
		scanf("%f",&arr[i]);
		sum+=arr[i];
	}
	sum/=n;
	printf("Average = %.2f",sum);
}
