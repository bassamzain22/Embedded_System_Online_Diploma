/*Question :" C Program to Add Two Distances (in inch-feet) System Using Structures"?
 * EX2.c
 *
 *  Created on: Sep 13, 2023
 *      Author: bassam zain
 */
#include <stdio.h>
struct distance
{
	int feet;
	float inch;
};
int main()
{
	struct distance dis1,dis2;
	printf("Enter information for 1st distance\n");
	printf("Enter feet : ");
	fflush(stdout);
	scanf("%d",&dis1.feet);
	printf("Enter inch  : ");
	fflush(stdout);
	scanf("%f",&dis1.inch);
	printf("Enter information for 2nd distance\n");
	printf("Enter feet : ");
	fflush(stdout);
	scanf("%d",&dis2.feet);
	printf("Enter inch  : ");
	fflush(stdout);
	scanf("%f",&dis2.inch);
	int sumf=dis1.feet+dis2.feet;
	float sumi=dis1.inch+dis2.inch;
	if(sumi>=12)
	{
		sumf+=sumi/12;
		sumi-=12*((int)sumi/12);
	}
	printf("Sum of distances= %d - %.1f ",sumf,sumi);
}
