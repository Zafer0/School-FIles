/**
* Name: Grant Sipes
* Lab/task: Lab 1 Task 2
* Date: 08/31/16
**/

#include <stdio.h>
#define DANGERLEVEL 5    /* C Preprocessor -
			- substitution on appearance */
				/* like Java ‘final’ */
int main(void)
{
	float level=1;
	printf("What level is your gas at?:");
	scanf ("%f", &level);
	/* if-then-else as in Java */

	if (level <= DANGERLEVEL) /*replaced by 5*/
      		printf("Low on gas!\n");
	else
		printf("Good driver !\n");
}
