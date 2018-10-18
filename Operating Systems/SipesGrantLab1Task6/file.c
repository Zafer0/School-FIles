/**
* Name: Grant Sipes
* Lab/task: Lab 1 Task 6
* Date: 9/6/16
**/

#include <stdio.h>

int main(void) {
	/* file handles */
	FILE *output_file=NULL;
	FILE *input_file;
	char c; 
	
	/* open files for writing*/
	output_file = fopen("cwork.dat", "w");
	if(output_file == NULL)
	{
		printf("Error in opening cwork");
		return(1);    /* need to do explicit ERROR CHECKING */
	}
	
	input_file = fopen("data.txt", "r");
	if(input_file == NULL)
	{
		printf("Error in opening data");
		return(1);
	}

	do
	{
		c = fgetc(input_file);
		fputc(c, output_file);
	}while(!feof(input_file));

	/* don’t forget to close file handles */
	fclose(output_file);
	fclose(input_file);

    return 0;
}
