/*
 ============================================================================
Question : C Program to Reverse String Without Using Library Function?
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int main(void) {
	char s[100000];
	printf("Enter the string : ");
	fflush(stdin);fflush(stdout);
	gets(s);
	char c;
	int j=strlen(s)-1;
	for(int i=0;i<strlen(s)/2;i++,j--)
	{
		 c=s[i];
		 s[i]=s[j];
		 s[j]=c;

	}
printf("%s",s);
}
