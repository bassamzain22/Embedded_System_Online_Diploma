/*
 ============================================================================
question : C Program to Search an element in Array ?
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	    int n;
	    printf("Enter no of elements : ");
		fflush(stdin);fflush(stdout);
		scanf("%d",&n);
		int a[n];
		for(int i=0;i<n;i++)scanf("%d",&a[i]);
		printf("Enter the elements to be searched : ");
		fflush(stdin);fflush(stdout);
		int x;
		scanf("%d",&x);
		int i=0;
		for(;i<n;i++)
			if(a[i]==x)
			{
				printf("Number found at the location = %d",i+1);
				break;
			}
		if(i==n)printf("Not found");
}
