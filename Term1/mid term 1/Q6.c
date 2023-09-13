/*c function to return unique number in array with one loop?*/
 #include <stdio.h>
 #include <math.h>
 int unique_number(int fr[], int max)
 {
  int i;
  for(i=0;i<max;i++)
  { 
    if(fr[i]==1)
      {
        return i;
      }
  }
 }
int main()
 {
    int size;
    printf("Enter size of array then enter elements>>>");
    fflush(stdout);
    scanf("%d",&size);
    int arr[100000], fr[100000]={},i,max;
    for(i=0;i<size;i++)
    {
      scanf("%d",&arr[i]); 
      fr[arr[i]]++;
      if(i==0) max-arr[0];
      else {
         if(arr[i]>max)max=arr[i];
        }
}
printf("%d", unique_number(fr, max));
}