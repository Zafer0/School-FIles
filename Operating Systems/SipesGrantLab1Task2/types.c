#include <stdio.h>

/**
* Name: Grant Sipes
* Lab/task: Lab 1 Task 2
* Date: 08/31/16
**/

int main(void)
{
	int nstudents,nfaculty = 0; /* Initialization, required */
	float nratio = 0;
	
	printf("How many students does CSUCI have ?:");
 	scanf ("%d", &nstudents);  /* Read input */
 	printf("How many faculty does CSUCI have ?:");
 	scanf ("%d", &nfaculty);

 	nratio = (float)nstudents/(float)nfaculty;
 	
	printf("CSUCI has %.1f students per faculty.\n", nratio); 

	return 0;
}


