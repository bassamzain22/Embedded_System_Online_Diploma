/*
 ============================================================================
Question: C Program to Make a Simple Calculator to Add, Subtract, Multiply or Divide Using switch...case?
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void) {
	        char c;
	        float x,y;
			printf("Enter operator either + or - or * or /:");
			fflush(stdout);
			scanf("%c",&c);
			printf("Enter two operands: ");
		    fflush(stdout);
		    scanf("%f%f",&x,&y);
		    switch(c)
			{
				case '+':
				{
					printf("%f %c %f = %.1f",x,c,y,x+y);
				}
				break;

				case '-':
				{
					printf("%f %c %f = %.1f",x,c,y,x-y);
				}
		        
				break;
				case '*':
				{
					printf("%f %c %f = %.1f",x,c,y,x*y);
				}
				break;

				case '/': 
				{
					 printf("%f %c %f = %.1f",x,c,y,x/y);
				}
		       break;
			
			}
			
}
