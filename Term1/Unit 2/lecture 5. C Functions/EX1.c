/*
Question : Prime Numbers Between two Intervals by Making User-defined Function?
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>
void prime(int start,int end)
{
	printf("Prime numbers between %d and %d are: ",start,end);
	if(start<=2)printf("2 ");
	if(!(start%2))start++;
	int i,j;

	for(i=start;i<=end;i+=2)
	{
		j=2;
		bool x=true;
	    for(;j<=sqrt(i);j++)
	    {
		if(!(i%j))
		{
			x=false;
			break;
		}
	    }

	    if(x&&i!=1)printf("%d ",i);
	}
}
int main(void) {
	int start,end;
	printf("Enter two numbers(intervals) :");
	fflush(stdout);	fflush(stdin);
	scanf("%d %d",&start,&end);
	prime(start,end);

}
