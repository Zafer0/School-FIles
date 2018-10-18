/**
* Name: Grant Sipes
* Lab/task: Lab 1 Task 7
* Date: 09/7/16
**/

#include <stdio.h>
#include <string.h>

#define MAX_WORD_LENGTH 16

void swap(char *, char *);

int main(void) 
{
  char str1[] = "doodle";
  char str2[] = "diddle";
  printf("str1 = %s and str2 = %s\n", str1, str2);
  swap(str1, str2);
  printf("str1 = %s and str2 = %s\n", str1, str2);

  return(0);
}

void swap(char s1[], char s2[]) 
{ /* passed and returned by reference */
  char temp[MAX_WORD_LENGTH];

  strcpy(temp, s1);
  strcpy(s1, s2);
  strcpy(s2, temp);
}
