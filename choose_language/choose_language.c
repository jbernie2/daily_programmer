/**
* Author: John Bernier
* Date: 11/3/14
* choose_language.c
*   given a file containing line delimted by newline, this program 
*   prints a random line from that file
*   
*   This is used to help me choose which language to use for coding
*   challenges.
*
*/

#include <stdio.h>
#include <stdlib.h>
#include "get_random_line.h"

/*
* prints a random line from a text file
*/
int main(){
  char *languages_file_name = "languages.txt";
  char **language = get_random_line(languages_file_name);
  printf("Today's programming challenge will be written in %sGood Luck!", *language);
  free(*language);
  free(language);
  return 0;
}


 

 
