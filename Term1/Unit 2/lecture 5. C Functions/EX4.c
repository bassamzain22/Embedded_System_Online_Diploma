/*
 ============================================================================
Question : C program to Calculate the Power ofa Number Using Recursion?
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
int z,x,y;
int power(int x,int y)
{
	if(y==1)return x;
      x*=z;

      y--;

     return power(x, y);
}
int main(void) {

	printf("Enter base number: ");
	    fflush(stdout);
	    fflush(stdin);
	    scanf("%d",&x);
	printf("Enter power number(positive integer) : ");
		fflush(stdout);
		fflush(stdin);
		scanf("%d",&y);
        z=x;

	    printf("%d^%d=%d",x,y,power( x, y));

}
