/*
 ============================================================================
Question: C Program to Check Vowel or Consonant?
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>

int main(void)
{
char c;
printf("Enter your alphabet : ");
fflush(stdout);
scanf("%c",&c);
if(c=='A'||c=='a'||c=='E'||c=='e'||c=='o'||c=='O'||c=='u'||c=='U'||c=='i'||c=='I')
	printf("%c is a vowel.",c);
else printf("%c is a consonant.",c);
}
