/**
* Author: John Bernier
* Date: 11/3/14
* get_random_line.c
*   given the name of a file containing lines delimted by newlines,
*   this program returns a random line from that file
*   
*/


#include <stdio.h>
#include <stdlib.h>

/**
* variable to denote whether the seed has been set for
* the random number generator, we only set it once.
*/
int rand_set = 0;

/**
* returns a random double between 0 and 1
*/
double randomDouble(){
  if(!rand_set){
    srand(time(NULL));
    rand_set = 1;
  }
  return (double) (rand()/(float) RAND_MAX);
}

/**
* Determines whether to keep a given line
*
* In order to choose a random element from a list of an
* unknown size, we make the probability to choose element
* n from a list (where n starts at 1) 1/n
*/
int keep_line(double line_num){
  double probability = 1.0/line_num;
  int keep_line = 0;
  if(randomDouble() <= probability){
    keep_line = 1;
  }
  return keep_line;
}

/**
* Selects a random line from a file
*
* iterate through whole file, select a line based on method
* described in keep_line(), by giving each line a chance to
* be selected, the probability that any given line is selected
* is the same, the last line that is selected is the one that
* is returned.
*/
char** get_random_line(char *fn){
  int delim = '\n';
  FILE *fp = fopen(fn,"r");
  char **current_line = malloc(sizeof(char*));
  char **random_line = malloc(sizeof(char*));
  ssize_t line_length = 0;
  double line_num = 1.0;

  while(getline(current_line,&line_length,fp) != -1){
    if(keep_line(line_num)){
      *random_line = *current_line;
      *current_line = NULL; 
    }
    line_num++;  
  }
 
  free(*current_line);
  free(current_line);

  return random_line;
}
