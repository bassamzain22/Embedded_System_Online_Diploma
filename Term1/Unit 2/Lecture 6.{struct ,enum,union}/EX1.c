/* Question : "C Program to Store Information(name, roll and marks) of a Student Using Structure"?
 * EX1.c
 *
 *  Created on: Sep 13, 2023
 *      Author: bassam zain
 */
#include <stdio.h>
struct students{
	char name[50];
	int roll;
	float marks;
};
int main()
{
	struct students s;
	printf("Enter name : ");
	fflush(stdout);
	scanf("%s",s.name);
	printf("Enter roll number  : ");
	fflush(stdout);
	scanf("%d",&s.roll);
	printf("Enter marks : ");
	fflush(stdout);
	scanf("%f",&s.marks);
	printf("\nName : %s\n",s.name);
	printf("Roll : %d\n",s.roll);
	printf("Marks : %.2f\n",s.marks);



}
