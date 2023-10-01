/* Question: Write a program in C to demonstrate how to handle the pointers in the program?
 * EX1.c
 *
 *  Created on: Sep 27, 2023
 *      Author: bassam zain
 */
#include <stdio.h>
int main()
{
	int m=29;
	printf("Address of m : 0x%p \nValue of m : %d\n\n",&m,m);
	printf("Now ab is assigned with the address of m.\n\n");
	int *ab=&m;
	printf("Address of pointer ab : 0x%p \ncontent of pointer ab : %d\n\n",ab,*ab);
	printf("The value of m assigned to 34 now.\n\n");
	m=34;
	printf("Address of pointer ab : 0x%p \ncontent of pointer ab : %d\n\n",ab,*ab);
	printf("The pointer variable ab is assigned with the value 7 now.\n\n");
	*ab=7;
	printf("Address of m : 0x%p \nValue of m : %d\n",&m,m);/**/

}
