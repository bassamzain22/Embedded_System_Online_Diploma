/*
 ============================================================================
Question : C Program to Insert an element in an Array?
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	int n , x , ind ;
	printf("Enter no of elements : ");
	fflush(stdin);fflush(stdout);
	scanf("%d",&n);
	int a[n],b[n+1];
	for(int i=0;i<n;i++)scanf("%d",&a[i]);
	printf("Enter the element to be inserted : ");
	fflush(stdin);fflush(stdout);
	scanf("%d",&x);
	printf("Enter the location : ");
	fflush(stdin);fflush(stdout);
	scanf("%d",&ind);
	for (int i=0;i<=n;i++)
	{
		if(i+1==ind)b[i]=x;
		else if(i+1<ind)b[i]=a[i];
		else b[i]=a[i-1];
	}
	for (int i=0;i<=n;i++)printf("%d ",b[i]);

}
