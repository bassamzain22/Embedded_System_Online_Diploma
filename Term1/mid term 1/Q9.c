/*c function to reverse words in string?*/
#include <stdio.h>
#include <ctype.h>
#include <string.h>
void reverse_words(char s[],char res[][100])
{
int i,row=0,col=0,x=0;
if(s[strlen(s)-1]=='.')x=1;
for(i=0;i<strlen(s);i++)
{
    if(i<strlen(s)-2&&s[i]==' '&&isalpha(s[i+1]))
    {
      row++;
      col=0;
    }
    if((i==strlen(s)-1&&s[i]=='.'));
    else if(s[i]!=' ')
    {
      res[row][col]=s[i];
      col++;   
    }
}
strcpy(s,res[row]);
int j=row-1; 
 for(;j>=0;j--)
 {
    strcat(s," ");
    strcat(s,res[j]);
 }
 if(x)strcat(s,".");
}
int main()
{
  char s[10000],res[100][100];
  gets(s);
  reverse_words(s,res);
 printf("%s",s);
}
