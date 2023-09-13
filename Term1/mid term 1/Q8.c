 /*c function to take an array and revers its elements?*/
 #include <stdio.h>
 #include <math.h>
 void reverse_array(int arr[],int size)
 {
   int n=size-1,i=0,temp;
   while(i<n)
   {
     temp=arr[i];
     arr[i]=arr[n];
     arr[n]=temp; 
     n--;i++;
   }
}
int main()
{
    int size;
    printf("Enter size of array >>>");
    fflush(stdout);
    scanf("%d",&size);
    int arr[size];
    printf("Enter elements of array >>>");
    int i;
    for(i=0;i<size;i++)
    scanf("%d",&arr[i]);
    reverse_array(arr, size);
    for(i=0;i<size;i++)
     printf("%d ",arr[i]);
}