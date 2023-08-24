/*
 ============================================================================
Question : C program to Reverse a Sentence Using Recursion?
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int i=0;
int reverse(char s[],int n)
{
	if(i>=n)return 1;
	char c=s[i];
	s[i]=s[n];
	s[n]=c;
	i++;n--;
	return reverse(s,n);
}
int main(void)
{
	char s[100000];
	printf("Enter a sentence: ");
	fflush(stdout);fflush(stdin);
	gets(s);
	int n=strlen(s);
    reverse(s,n-1);
    printf("%s",s);
}
