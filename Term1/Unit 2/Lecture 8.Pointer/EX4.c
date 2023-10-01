/*Question :Write a program in C to print the elements of an array in reverse order?
 *
 * EX4.c
 *
 *  Created on: Sep 27, 2023
 *      Author: bassam zain
 */
#include <stdio.h>
int main()
{
	int arr[15],n;
	printf("Input the number of elements to store in the array (max 15) : ");
	fflush(stdout);
	scanf("%d",&n);
	printf("Input %d number of elements in the array : \n",n);
	int i;
	for(i=0;i<n;i++)
	{
		printf("element-%d : ",i+1);
		fflush(stdout);
		scanf("%d",&arr[i]);
	}
	i=n-1;
	int *p=&arr[i];
	printf("\n\nThe elements of array in reverse order are :\n");
	for(;i>=0;i--,p--)
	{
		printf("element-%d : %d\n",i+1,*p);
	}

}
