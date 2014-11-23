#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "linked_list.h"

/**
* the struct that will be used to test the list
*/
typedef struct my_struct my_struct;
struct my_struct{
  char *my_data;
};

/**
* a wrapper around the list's to_string function for printing the list
*/
void print_list(t_linked_list *ll){
  char *list_string = t_linked_list_to_string(ll);
  printf("%s \n",list_string);
  free(list_string); 
}

/*
* gets the number of digits in a number, used to allocate the correct amount
* of memory in the my_struct_init function, and the int_to_string function
*/
int num_places (int n) {
  if (n < 0) return 1 + num_places (-n);
  if (n < 10) return 1;
  return 1 + num_places (n / 10);
}

/*
* initialized a my_struct and makes its char* member testXX where XX is the
* int passed to the function
*/
my_struct* my_struct_init(int i){
    my_struct *my_node_data = (my_struct*)malloc(sizeof(my_struct));
    char *my_data = malloc(sizeof(char)*6);
    
    sprintf(my_data,"test%d",i); 
    my_node_data -> my_data = my_data;
    
    return my_node_data;
}

/**
* to_string function passed to the list to stringify my_struct. This is used 
* by the list's to_string function
*/
char* my_struct_to_string(void* a){
  my_struct *my_node_data = (my_struct*) a;
  char* stringified_my_struct = malloc(sizeof(char)*(strlen(my_node_data->my_data)+1));
  sprintf(stringified_my_struct,"%s\n",my_node_data->my_data);
  return stringified_my_struct;
}

/**
* free function for freeing my_struct, passed to the list to be used for
* destroying list nodes and for destroying the whole list.
*/
void my_struct_free(void* a){
  my_struct *my_node_data = (my_struct*) a;
  free(my_node_data -> my_data);
  free(my_node_data);
}

/**
* reverses a string, used to demonstrate list iteration
*/
void reverse_string(char *a){
 
  char *front = a;
  char *back = &a[strlen(a) - 1];
 
  while(front < back){
    char temp = *front;
    *front = *back;
    *back = temp;
    front++;
    back--;
  }
}

/**
* the to_string function used in the second example with ints
*/
char* int_to_string(void* a){
  int *i = (int*) a;
  
  char *int_string = malloc(sizeof(char)*(num_places(*i)+1));

  sprintf(int_string,"%d\n",*i);

  return int_string;
}

/**
* the free function used in the second example with ints. Yes, this function
* is supposed to be empty. For primitive types you do not have to free them
* explicitly, but we still need to set the node_free_fn in the list so that
* it works correctly.
*/
void free_int(void* a){
}

/**
* since using the to_string function frees the itermediate forms of the strings
* the string being stored in the list can be passed in directly, a copy of it
* has to be made.
*/
char* string_to_string(void *a){
  char* string_copy = (char*)malloc(sizeof(char*) * (strlen((char*)a) + 1));
  sprintf(string_copy,"%s\n",(char*)a);
  return string_copy;
}

int main(){
 
  /////////////////////////////////////////////////////
  // this first example will show how to use the list
  // with structs being stored in the list
  ////////////////////////////////////////////////////
  printf("EXAMPLE 1: a list of structs \n");


  //variables that will be used throughout the examples
  t_linked_list *my_list;
  char *stringified_my_list;
  my_struct *my_node_data;
  int i;

  //creating a new list
  my_list = t_linked_list_init();
  
  //adding ten elements to the list
  for(i = 0; i < 10; i++){
    //initialize struct and data
    my_struct *my_node_data = my_struct_init(i);

    //insert at the start of the list
    t_linked_list_insert_first(my_list,my_node_data);
  }

  //set printing function for my_struct, if you do not set this function
  //the function t_linked_list_to_string() returns NULL
  t_linked_list_set_node_to_string_fn(my_list,my_struct_to_string);

  //printing list, its a good idea to write a separate function to do this
  //so you can print in one simple call, from now on, I'll call the function
  //print_list() which I defined above.
  printf("added ten elements to the front of the list\n");
  stringified_my_list = t_linked_list_to_string(my_list);
  printf("%s\n",stringified_my_list);
  free(stringified_my_list);

  //retrieve first element from list without removing it
  printf("retrieiving first element in list\n");
  my_node_data = t_linked_list_get_first(my_list);
  printf("first node: %s\n\n",my_node_data -> my_data);

  //retrieve last element from list without removing it
  printf("retrieiving last element in list\n");
  my_node_data = t_linked_list_get_last(my_list);
  printf("last node: %s\n\n",my_node_data -> my_data);

  //insert at the back of the list
  my_node_data = my_struct_init(++i);
  t_linked_list_insert_last(my_list,my_node_data);

  //using function to handle the stringifying/printing/freeing of the stringified list
  printf("added new element to the end of the list\n");
  print_list(my_list);

  //removing first element from the list, the element being removed is returned
  printf("removing first element from the list\n");
  my_node_data = (my_struct*)t_linked_list_remove_first(my_list);
  printf("removed node: %s \n",my_node_data->my_data);
  free(my_node_data);
  printf("list after first element is removed: \n");
  print_list(my_list);

  //removing last element from the list, the element being removed is returned
  printf("removing last element from the list\n");
  my_node_data = (my_struct*)t_linked_list_remove_last(my_list);
  printf("removed node: %s \n",my_node_data->my_data);
  free(my_node_data);
  printf("list after last element is removed: \n");
  print_list(my_list);

  //setting the 'free' function for my struct
  t_linked_list_set_node_free_fn(my_list,my_struct_free);

  printf("deleting first node from list\n");
  //deleting first node from list, if this is called before
  //t_linked_list_set_node_free_fn() this function acts identically
  //to t_linked_list_remove_first()
  t_linked_list_delete_first(my_list);
  printf("list after first element is deleted: \n");
  print_list(my_list);

  printf("deleting last node from list\n");
  //deleting last node from list, if this is called before
  t_linked_list_delete_last(my_list);
  printf("list after last element is deleted: \n");
  print_list(my_list);


  //iterating over the list and reversing all the strings contained in 
  //the my_data field of the my_struct structs in the nodes
  
  printf("iterating over list and reversing the string in the structs at each node: \n");
  
  void *iterator = NULL;
  while((my_node_data = (my_struct*) t_linked_list_iterator(my_list,&iterator)) != NULL){
    reverse_string(my_node_data -> my_data); 
  }
  
  print_list(my_list);
  
  //destroying the list frees all memory associated with the list. Unless the 'free'
  //function has not been set for the nodes, then an array is returned containing the
  //data in the list.
  printf("destroying list\n\n");
  t_linked_list_destroy(my_list);
  
  
  
  /////////////////////////////////////////////////////
  // this second example will show how to use the list
  // with primitives being stored in the list
  ////////////////////////////////////////////////////
  
  printf("EXAMPLE 2: a list of ints (primitive type) \n");
  //used throughout example to get elements from list
  int *j;
  my_list = t_linked_list_init();
  
  //printf("adding 10 numbers to the list\n");
  int num_array[11] = {0,1,2,3,4,5,6,7,8,9,10};
  for(i = 0; i < 10; i++){
    t_linked_list_insert_first(my_list,&num_array[i]);
  }
  
  t_linked_list_set_node_to_string_fn(my_list,int_to_string);

  //the function free_int does not do anything
  //because the ints in the list do not have to be 
  //freed, but if we do not set this function,
  //then when we destroy the list, an array will
  //be passed back containing the elements.
  t_linked_list_set_node_free_fn(my_list,free_int);

  print_list(my_list);
  
  //retrieve first element from list without removing it
  printf("retrieiving first element in list\n");
  j = t_linked_list_get_first(my_list);
  printf("first node: %d\n\n",*j);

  //retrieve last element from list without removing it
  printf("retrieiving last element in list\n");
  j = t_linked_list_get_last(my_list);
  printf("first node: %d\n\n",*j);


  //insert at the back of the list
  j = &num_array[10];
  t_linked_list_insert_last(my_list,(void*)j);
  printf("added new element to the end of the list\n");
  print_list(my_list);

  //removing first element from the list, the element being removed is returned
  printf("removing first element from the list\n");
  j = (int*)t_linked_list_remove_first(my_list);
  printf("removed node: %d \n",*j);
  printf("list after first element is removed: \n");
  print_list(my_list);

  //removing last element from the list, the element being removed is returned
  printf("removing last element from the list\n");
  j = (int*)t_linked_list_remove_last(my_list);
  printf("removed node: %d \n",*j);
  printf("list after last element is removed: \n");
  print_list(my_list);
  
  printf("deleting first node from list\n");
  //deleting first node from list, if this is called before
  //t_linked_list_set_node_free_fn() this function acts identically
  //to t_linked_list_remove_first()
  t_linked_list_delete_first(my_list);
  printf("list after first element is deleted: \n");
  print_list(my_list);

  printf("deleting last node from list\n");
  //deleting last node from list, if this is called before 
  //t_linked_list_set_node_free_fn it behaves the same as 
  //t_linked_list_remove_first
  t_linked_list_delete_last(my_list);
  printf("list after last element is deleted: \n");
  print_list(my_list);

  printf("iterating over list and adding 1 to the number in each node: \n");
  iterator = NULL;
  while((j = (int*) t_linked_list_iterator(my_list,&iterator)) != NULL){
     (*j)++;
  }
  print_list(my_list);
  
  printf("destroying list\n\n");
  t_linked_list_destroy(my_list);

  
  /////////////////////////////////////////////////////
  // this third example will show how to use the list
  // with strings being stored in the list
  ////////////////////////////////////////////////////
   
  printf("EXAMPLE 3: a list of const strings \n");

  //this will be used throughout this example to retrieve items from the list
  char *k;

  my_list = t_linked_list_init();
  t_linked_list_set_node_to_string_fn(my_list,string_to_string);
  
  t_linked_list_insert_first(my_list,"one");
  t_linked_list_insert_first(my_list,"two");
  t_linked_list_insert_first(my_list,"three");
  t_linked_list_insert_first(my_list,"four");
  t_linked_list_insert_first(my_list,"five");
  t_linked_list_insert_first(my_list,"six");

  print_list(my_list);
  
  //retrieve first element from list without removing it
  printf("retrieiving first element in list\n");
  k = t_linked_list_get_first(my_list);
  printf("first node: %s\n\n",k);

  //retrieve last element from list without removing it
  printf("retrieiving last element in list\n");
  k = t_linked_list_get_last(my_list);
  printf("first node: %s\n\n",k);


  //insert at the back of the list
  t_linked_list_insert_last(my_list,"seven");
  printf("added new element to the end of the list\n");
  print_list(my_list);

  //removing first element from the list, the element being removed is returned
  printf("removing first element from the list\n");
  k = t_linked_list_remove_first(my_list);
  printf("removed node: %s \n",k);
  printf("list after first element is removed: \n");
  print_list(my_list);

  //removing last element from the list, the element being removed is returned
  printf("removing last element from the list\n");
  k = t_linked_list_remove_last(my_list);
  printf("removed node: %s \n",k);
  printf("list after last element is removed: \n");
  print_list(my_list);
  
  printf("deleting first node from list\n");
  //deleting first node from list, if this is called before
  //t_linked_list_set_node_free_fn() this function acts identically
  //to t_linked_list_remove_first()
  t_linked_list_delete_first(my_list);
  printf("list after first element is deleted: \n");
  print_list(my_list);

  printf("deleting last node from list\n");
  //deleting last node from list, if this is called before 
  //t_linked_list_set_node_free_fn it behaves the same as 
  //t_linked_list_remove_first
  t_linked_list_delete_last(my_list);
  printf("list after last element is deleted: \n");
  print_list(my_list);

  printf("iterating over list, but can not alter them, they are consts \n");
  iterator = NULL;
  while((k = (char*) t_linked_list_iterator(my_list,&iterator)) != NULL){
    printf("iterating: %s \n",k);
  }
  
  printf("destroying list\n");
  t_linked_list_destroy(my_list);

  return 0;
}
