/**
* Author: John Bernier
* Date: 11/16/14
* linked_list.c
*   An implementation of a generic linked list data structure
*
*/
#include <stdlib.h>
#include <string.h>
#include "linked_list.h"

typedef struct ll_node t_ll_node;

/**
* ll_node
*   A linked list node
*   fields
*     t_ll_node *prev
*       a link to the previous node in the list
*     t_ll_node *next
*       a link to the next node in the list
*     void *data
*       a pointer to the data of the node
*/
struct ll_node
{
  t_ll_node *prev;
  t_ll_node *next;
  void *data;
};

/**
* linked_list
*   A generic doubley linked list
*   fields
*     int length
*       the number of elements in the list
*     char *data_type 
*       a string description of the type of data stored in the lists nodes
*     void (*node_free_fn)(void*)
*       a function pointer to the free function of the structs stored in the
*       list
*     char* (node_to_string_fn)(void*)
        a function pointer to the to_string function for the structs stored
        in the list
*     t_ll_node *head
*       a pointer to the first node in the list, the data of this list element
*       will always be NULL
*     t_ll node *tail
*       a pointer to the last node in the list, the data of this list element
*       will always be NULL
*/
struct linked_list
{
  int length;
  char *data_type;
  void (*node_free_fn)(void*);
  char* (*node_to_string_fn)(void*);
  t_ll_node *head;
  t_ll_node *tail;
};

/**
* t_ll_node* t_ll_node_init
*   args
*     void
*   returns
*     t_ll_node *n
*       pointer to the newly created linked list node
*   description
*     intializes a linked list node
*/
t_ll_node* t_ll_node_init(){
  t_ll_node *n = malloc(sizeof(t_ll_node));
  return n;
}

/**
* t_ll_node* t_ll_node_remove_first_node
*   args
*     t_linked_list *ll
*       pointer to linked list being operated on
*   returns
*     t_ll_node *n
*       pointer to the removed node
*   description
*     removes the first node from the list
*/
t_ll_node* t_ll_node_remove_first_node(t_linked_list *ll){
  t_ll_node *removed_node = ll -> head -> next;
  ll -> head -> next -> next -> prev = ll -> head;
  ll -> head -> next = ll-> head -> next -> next;
  removed_node -> next = NULL;
  removed_node -> prev = NULL;
  return removed_node;
}

/**
* t_ll_node* t_ll_node_remove_last_node
*   args
*     t_linked_list *ll
*       pointer to linked list being operated on
*   returns
*     t_ll_node *n
*       pointer to the removed node
*   description
*     removes the last node from the list
*/
t_ll_node* t_ll_node_remove_last_node(t_linked_list *ll){
  t_ll_node *removed_node = ll -> tail -> prev;
  ll -> tail -> prev -> prev -> next = ll -> tail;
  ll -> tail -> prev = ll-> tail -> prev -> prev;
  removed_node -> next = NULL;
  removed_node -> prev = NULL;
  return removed_node;
}

/**
* void t_ll_node_destroy
*   args
*     t_ll_node *n
*       pointer to the linked list node being operated on
*   returns
*       void
*   description
*     frees the linked list node struct
*/

void t_ll_node_destroy(t_ll_node *n){
  n -> next = NULL;
  n -> prev = NULL;
  n -> data = NULL;
  free(n);
}

/**
* void t_ll_node_destroy_data
*   args
*     t_linked_list *ll
*       pointer to the linked list containing the node being operated on
*     t_ll_node *n
*       pointer to the linked list node being operated on
*   returns
*       void* node_data
*         If the node_free_fn is NULL the data contained in the node will be
*         returned, otherwise NULL will be returned.
*   description
*     frees the linked list node data, unless the node_free_fn is not defined,
*     then it will return the node's data.
*/
void* t_ll_node_destroy_data(t_linked_list *ll, void *node_data){
  if(ll -> node_free_fn != NULL){
    ll -> node_free_fn(node_data);
    node_data = NULL;
  } 
  return node_data;
}

/**
* t_linked_list* t_linked_list_init
*   args
*     none
*   returns
*     t_linked_list *ll
*       a pointer to the newly created list
*   description
*     allocates memory for linked list and intializes all of its fields
*/
t_linked_list* t_linked_list_init(){
  
  t_linked_list *ll = malloc(sizeof(t_linked_list));
  ll -> length = 0;
  ll -> node_free_fn = NULL;
  ll -> node_to_string_fn = NULL;
  //ll -> data_type = data_type;
  
  ll -> head = malloc(sizeof(t_ll_node)); 
  ll -> tail = malloc(sizeof(t_ll_node));
  
  ll -> head -> prev = NULL;
  ll -> head -> next = ll -> tail;
   
  ll -> tail -> prev = ll -> head;
  ll -> tail -> next = NULL; 
  
  return ll;
}

/**
* void* t_linked_list_destroy
*   args
*     t_linked_list *ll
*       pointer to linked list being operated on
*   returns
*     void** node_data_array
*       if free_node_fn is not defined, then an array of all the data is
*       returned, otherwise NULL is returned.
*   description
*     frees the entire linked list. If a node_free_fn is not defined, an array
*     of the data stored in the linked list is returned, otherwise NULL is
*     returned.
*/
void** t_linked_list_destroy(t_linked_list *ll){
  
  void** node_data_array = NULL;
  if(ll -> node_free_fn == NULL){
    node_data_array = (void**)malloc(sizeof(void**) * ll -> length);
    int i = 0;
    while(ll -> length > 0){
      node_data_array[i] = t_linked_list_remove_first(ll); 
      i++;
    } 
  }else{
    while(ll -> length > 0){
      t_linked_list_delete_first(ll); 
    }
  }
  free(ll -> head);
  free(ll -> tail);
  ll -> head = NULL;
  ll -> tail = NULL;
  ll -> node_free_fn = NULL;
  ll -> node_to_string_fn = NULL;
  free(ll);

  return node_data_array;
}

/**
* void t_linked_list_insert_first
*   args
*     t_linked_list *ll
*       pointer to linked list being operated on
*     void *data
*       pointer to the data being inserted into the list
*   returns
*     none
*   description
*     inserts an element at the front of the list directly following the 
*     head node
*/
void t_linked_list_insert_first(t_linked_list *ll, void *data){
  t_ll_node *new_node = t_ll_node_init();
  new_node -> data = data;
  new_node -> prev = ll -> head;
  new_node -> next = ll -> head -> next;
  ll -> head -> next -> prev = new_node;
  ll -> head -> next = new_node;
  ll -> length++;
}

/**
* void t_linked_list_insert_last
*   args
*     t_linked_list *ll
*       pointer to linked list being operated on
*     void *data
*       pointer to the data being inserted into the list
*   returns
*     none
*   description
*     inserts an element at the end of the list directly preceding the 
*     tail node
*/
void t_linked_list_insert_last(t_linked_list *ll, void *data){
  t_ll_node *new_node = t_ll_node_init();
  new_node -> data = data;
  new_node -> next = ll -> tail;
  new_node -> prev = ll -> tail -> prev;
  ll -> tail -> prev -> next = new_node;
  ll -> tail -> prev = new_node;
  ll -> length++;
}

/**
* void* t_linked_list_remove_first
*   args
*     t_linked_list *ll
*       pointer to linked list being operated on
*   returns
*     void *node_data
*       pointer to the data of the node that was removed from the list
*   description
*     removes the first element from the list and returns the data contained
*     in that node. Updates list length and frees node data structure
*/
void* t_linked_list_remove_first(t_linked_list *ll){
  t_ll_node *first_node = NULL;
  void *node_data = NULL;
  if(ll -> length > 0){
    first_node = t_ll_node_remove_first_node(ll);
    node_data = first_node->data;
    t_ll_node_destroy(first_node);
    ll -> length--;
  }
  return node_data; 
}

/**
* void* t_linked_list_remove_last
*   args
*     t_linked_list *ll
*       pointer to linked list being operated on
*   returns
*     void *node_data
*       pointer to the data of the node that was removed from the list
*   description
*     removes the last element from the list and returns the data contained
*     in that node. Updates list length and frees node data structure
*/
void* t_linked_list_remove_last(t_linked_list *ll){
  t_ll_node *last_node = NULL;
  void *node_data = NULL;
  if(ll -> length > 0){
    last_node = t_ll_node_remove_last_node(ll);
    node_data = last_node -> data;
    t_ll_node_destroy(last_node);
    ll -> length--;
  }
  return node_data;
}

/**
* void* t_linked_list_delete_first
*   args
*     t_linked_list *ll
*       pointer to linked list being operated on
*   returns
*     void *node_data
*       if there is a node_free_fn defined in the t_linked_list* passed in 
*       then this function will return NULL, otherwise a pointer to the data
*       of the node that was removed from the list will be returned
*   description
*     deletes the first element in the list, if the linked list does not
*     have node_free_fn defined, then this function will operate identically
*     to t_linked_list_remove_first. Updates list length and frees node data
*     structure
*/
void* t_linked_list_delete_first(t_linked_list *ll){
  
  void *node_data = NULL;
  if(ll -> length > 0){
    node_data = t_ll_node_destroy_data(ll,t_linked_list_remove_first(ll));
  }
  return node_data;
}

/**
* void* t_linked_list_delete_last
*   args
*     t_linked_list *ll
*       pointer to linked list being operated on
*   returns
*     void *node_data
*       if there is a node_free_fn defined in the t_linked_list* passed in 
*       then this function will return NULL, otherwise a pointer to the data
*       of the node that was removed from the list will be returned
*   description
*     deletes the last node in the list, if the linked list does not
*     have node_free_fn defined, then this function will operate identically
*     to t_linked_list_remove_last. Updates list length and frees node data
*     structure.
*/
void* t_linked_list_delete_last(t_linked_list *ll){
  void *node_data = NULL;
  if(ll -> length > 0){
    node_data = t_ll_node_destroy_data(ll,t_linked_list_remove_last(ll));
  }
  return node_data;
}

/**
* void* t_linked_list_get_first
*   args
*     t_linked_list *ll
*       pointer to linked list being operated on
*   returns
*     void* 
*       a pointer to the data contained in first node of the list
*   description
*     retrieves the data in the first node of the list. It DOES NOT remove or
*     delete the node after it retrieves the data
*/
void* t_linked_list_get_first(t_linked_list *ll){
  return ll -> head -> next -> data;
}

/**
* void* t_linked_list_get_last
*   args
*     t_linked_list *ll
*       pointer to linked list being operated on
*   returns
*     void* 
*       a pointer to the data contained in last node of the list
*   description
*     retrieves the data in the last node of the list. It DOES NOT remove or
*     delete the node after it retrieves the data
*/
void* t_linked_list_get_last(t_linked_list *ll){
  return ll -> tail -> prev -> data;
}

/**
* void* t_linked_list_iterator
*   args
*     t_linked_list *ll
*       pointer to linked list being operated on
*     void **iterator
*       a pointer to the current node being iterated over.
*   returns
*     void* current_node_data
*       a pointer to the current node's data, or NULL if the current node is 
*       the tail node of the list.
*   description
*     Iterates over all the nodes in the linked list returning a pointer to
*     each node's data. Returns NULL when it reaches the end of the list
*/
void* t_linked_list_iterator(t_linked_list *ll, void **iterator){
  
  t_ll_node *current_node = (t_ll_node*)(*iterator);
  void *current_node_data = NULL;

  if((current_node) == NULL && ll -> length > 0){
    current_node = ll -> head -> next;
  }else if(current_node -> next != ll -> tail){
    current_node = current_node -> next;
  }else{
    current_node = NULL;
  }

  if(current_node != NULL){
    current_node_data = current_node -> data;
    *iterator = (void*)current_node;
  }else{
    //should this be iterator = NULL; or *iterator = NULL;  ?
    *iterator = NULL;
  }

  return current_node_data;
}

/**
* void t_linked_list_get_length
*   args
*     t_linked_list *ll
*       pointer to linked list being operated on
*   returns
*     int length
*       the number of nodes in the list, not including the head and tail nodes
*   description
*     returns the length of the list. which is the number of nodes in the list
*     not including the head and tail nodes.
*/
int t_linked_list_get_length(t_linked_list *ll){
  return ll -> length;
}

/**
* void t_linked_list_set_node_free_fn
*   args
*     t_linked_list *ll
*       pointer to linked list being operated on
*     void (*node_free_fn)(void*)
*       a pointer to the free function for the linked list data
*   returns
*     void
*   description
*     sets the linked list's node_free_fn which is a function for freeing the
*     the struct in the linked list nodes.
*/
void t_linked_list_set_node_free_fn(
  t_linked_list *ll, void (*node_free_fn)(void*)){
  ll -> node_free_fn = node_free_fn;
}

/**
* void t_linked_list_set_node_to_string_fn
*   args
*     t_linked_list *ll
*       pointer to linked list being operated on
*     void (*node_to_string_fn)(void*)
*       a pointer to the to string function for the linked list data
*   returns
*     void
*   description
*     sets the linked list's node_to_string_fn which is a function for
*     stringifying the struct in the linked list nodes.
*/
void t_linked_list_set_node_to_string_fn(
  t_linked_list *ll, char* (*node_to_string_fn)(void*)){
  ll -> node_to_string_fn = node_to_string_fn;
}

/**
* void flatten_string_list
*   args
*     char **node_strings
*       an array of the stringified linked list nodes
*     list_length
*       the number of stringified nodes in the array
*   returns
*     char* flat_string
*       a single string made up of concatenated stringified nodes separated by
*       newlines
*   description
*    flattens the array of strings into a single string made up of concatenated
*    stringified nodes.
*/
char* flatten_string_list(char **node_strings, int list_length){

  char *flat_string, *flat_string_index;
  size_t num_chars = 0;
  char null_terminate = '\0';
  int i = 0;
  for(i = 0; i < list_length; i++){
    num_chars += strlen(node_strings[i]);
  }
  flat_string = (char*) malloc(sizeof(char)*(num_chars + 1));
  flat_string_index = flat_string;
  for(i = 0; i < list_length; i++){
    size_t node_string_len = strlen(node_strings[i]);
    memmove(flat_string_index,node_strings[i],strlen(node_strings[i]));
    flat_string_index += node_string_len;
  }
  //null terminating string
  memmove(flat_string_index,&null_terminate,1);
  return flat_string;
}

/**
* void t_linked_list_to_string
*   args
*     t_linked_list *ll
*       pointer to linked list being operated on
*   returns
*     char* string_list
*       stringified version of the list, unless node_to_string_fn 
*       has not been set, then null is returned
*   description
*    returns a stringified version of the list, unless node_to_string_fn 
*    has not been set, then null is returned. A single string is returned
*    instead an array of strings so that the to_string functionality can
*    be recursively applied in the case of nested lists.     
*/
char* t_linked_list_to_string(t_linked_list *ll){
  
  char* string_list = NULL;
  if(ll -> node_to_string_fn != NULL){
    int i = 0;
    int list_length = ll -> length;
    char **node_strings = (char**) malloc(sizeof(char*)* list_length);
    void *iterator = NULL;
    void *current_data;
    while((current_data = t_linked_list_iterator(ll,&iterator)) != NULL){
      node_strings[i] = ll -> node_to_string_fn(current_data);
      i++;
    }
    string_list = flatten_string_list(node_strings,i);

    for(i = 0; i < list_length; i++){
      free(node_strings[i]);
    }
    free(node_strings);
  }
  return string_list;
}


