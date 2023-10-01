/*Question : Write a program in C to print a string in reverse using a pointer?
 * EX3.c
 *
 *  Created on: Sep 27, 2023
 *      Author: bassam zain
 */
#include <stdio.h>
#include <string.h>
int main()
{
	char s[100000];
	printf("Input a string : ");
	fflush(stdout);
	gets(s);
	int i=strlen(s)-1;
	char *p=&s[i];
	printf("Reverse of the string is : ");
		fflush(stdout);
	for(;i>=0;i--,p--)
	{
		printf("%c",*p);
	}
}
