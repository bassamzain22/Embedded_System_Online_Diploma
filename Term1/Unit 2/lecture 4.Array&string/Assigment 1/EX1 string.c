/*
 ============================================================================
question : C Program to Find the Frequency of Characters in a String?
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char s[100000];
	printf("Enter a string: ");
	fflush(stdin);fflush(stdout);
	gets(s);
    char c;
    printf("Enter a character to find frequency: ");
    fflush(stdin);fflush(stdout);
    scanf("%c",&c);
    int fr=0;
    for(int i=0;i<strlen(s);i++)
    {
    	if(s[i]==c)fr++;
    }
    printf("Frequency of %c = %d",c,fr);

}
