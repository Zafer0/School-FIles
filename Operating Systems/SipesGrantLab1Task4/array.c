/**
* Name: Grant Sipes
* Lab/task: Lab 1 Task 3
* Date: 08/31/16
**/

#include <stdio.h>

#define NUM_OF_CELLS 12

int main(void) 
{
    int number[NUM_OF_CELLS]; /* 12 cells, one cell per student */
    int index = 0, input = 0;
    float average = 0, sum = 0;
		/* Always initialize array before use */
    for (index = 0; index < NUM_OF_CELLS; index++) {
        scanf("%d", &input);
	   number[index] = input; 
    }
    /* now, number[index]=index; will cause error:why ?*/
    printf("Data: ");
    for (index = 0; index < NUM_OF_CELLS; index = index + 1) {
        if(index == NUM_OF_CELLS - 1)
            printf("%d.0", number[index]);
        else
            printf("%d.0, ", number[index]);
	sum += number[index];  /* sum array elements */
    }

    average = (float)sum/(float)NUM_OF_CELLS;
    printf("\nAverage: %.1f\n", average);
	
    return 0;
}
