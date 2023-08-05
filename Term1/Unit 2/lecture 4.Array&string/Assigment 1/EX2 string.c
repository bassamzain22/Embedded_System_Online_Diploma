/*
 ============================================================================
Question : C Program to Find the Length of a String?
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
int main(void) {
	    char s[100000];
		printf("Enter a string: ");
		fflush(stdin);fflush(stdout);
		gets(s);
	    int len=0;
	    for(int i=0;i<100000;i++)
	    {
	    	if(isalpha(s[i])||s[i]==' ')len++;
	    	else break;
	    }
	    printf("Length of string: %d",len);
}
