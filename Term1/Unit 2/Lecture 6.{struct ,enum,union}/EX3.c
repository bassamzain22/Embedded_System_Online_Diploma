/*Question : C Program to Add Two Complex Numbers by Passing Structure to a Function?
 * EX3.c
 *
 *  Created on: Sep 13, 2023
 *      Author: bassam zain
 */
#include <stdio.h>
struct Complex_Numbers {
	float real,img;

};
struct Complex_Numbers add()
{
	struct Complex_Numbers num1,num2;
	printf("For 1st complex number\n");
	printf("Enter real and imaginary respectively: ");
	fflush(stdout);
	scanf("%f %f",&num1.real,&num1.img);
	printf("For 2nd complex number\n");
	printf("Enter real and imaginary respectively: ");
	fflush(stdout);
	scanf("%f %f",&num2.real,&num2.img);
	struct Complex_Numbers  sum;
	sum.real=num1.real+num2.real;
	sum.img=num1.img+num2.img;
	return  sum;
}
int main()
{
	struct Complex_Numbers sum=add();
	printf("sum = %.1f + %.1fi",sum.real,sum.img);
}
