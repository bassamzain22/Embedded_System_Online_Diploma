/*Question : C Program to Store Information of Students Using Structure?
 * EX4.c
 *
 *  Created on: Sep 13, 2023
 *      Author: bassam zain
 */
#include <stdio.h>
struct datat_student
{
	char name[50];
	int roll,marks;
};
int main()
{
	struct datat_student student[10];
	int i;
	printf("Enter information of students:\n");
	for(i=0;i<10;i++)
	{    student[i].roll=i+1;
	printf("For roll number %d\n",student[i].roll);
	printf("Enter name : ");
	fflush(stdout);
	scanf("%s",student[i].name);
	printf("Enter marks : ");
	fflush(stdout);
	scanf("%d",&student[i].marks);
	}
	printf("Displaying information of students:\n");
	for(i=0;i<10;i++)
	{
		printf("Information For roll number %d\n",student[i].roll);
		printf("Name: %s\n",student[i].name);
		printf("Marks : %d\n\n",student[i].roll);
	}

}
