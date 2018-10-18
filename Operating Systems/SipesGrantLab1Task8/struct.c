/**
* Name: Grant Sipes
* Lab/task: Lab 1 Task 8
* Date: 09/7/16
**/

#include <stdio.h>
#include "person.h"
#include "person.c"
#define MAX_EMPLOYEES 128

int main() 
{
  	Birthday mybday;	/* - no ‘new’ needed ! */
 				/* then, it’s just like Java ! */

	Birthday employees[MAX_EMPLOYEES];
	
  	scanf("%d/%d/%d", &mybday.month, &mybday.day, &mybday.year);
  	printf("I was born on %d/%d/%d\n", mybday.month, mybday.day, mybday.year);
}
