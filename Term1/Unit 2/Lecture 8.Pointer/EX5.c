/*Question : Write a program in C to show a pointer to an array which contents are pointer to structure?
 * EX5.c
 *
 *  Created on: Sep 27, 2023
 *      Author: bassam Zain
 */
#include <stdio.h>
struct employee
{
	char s[100];
	int id;
}*arr[2],*(*p)[2];
int main()
{
	struct employee emp1={"Alex",1002},emp2={"man",2334};
	arr[0]=&emp1,arr[1]=&emp2;
	p=&arr;
	printf("Exmployee Name :%s\n",(**(*p)).s);
	printf("Employee ID : %d",(**(*p)).id);


}
