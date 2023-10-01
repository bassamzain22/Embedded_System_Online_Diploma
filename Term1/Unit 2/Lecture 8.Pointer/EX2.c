/*Question : Write a program in C to print all the alphabets using a pointer?
 * EX2.c
 *
 *  Created on: Sep 27, 2023
 *      Author: bassam zain
 */
#include <stdio.h>
int main()
{
	char s[]="ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	char *p=s;
	int i;
	for(i=0;i<sizeof(s);i++,p++)
	{
		printf("%c ",*p);
	}
}
