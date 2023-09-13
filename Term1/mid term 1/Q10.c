 /*c function to count the max number of ones between two zeros?*/
 #include <stdio.h>
 #include <math.h>
int max_one(int num)
{
   int temp=0,max=0,numz=num;
   while(num>0)
   {
    if(num%2==0)
       {
       if(max<temp)max=temp;
       temp=0;
       }
     else
       {
       temp++; 
       }
      num/=2;
   }
   if (numz%2==0&&temp>max)max=temp;
   return max;
}
int main()
{
    int num;
  scanf("%d", &num);
  printf("%d",max_one(num));
}