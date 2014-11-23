/**
* Author: John Bernier
* Date: 11/16/14
* linked_list.c
*   An implementation of a generic linked list data structure
*
*/
#ifndef LINKED_LIST_H
#define LINKED_LIST_H

typedef struct linked_list t_linked_list;

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
t_linked_list* t_linked_list_init();

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
void** t_linked_list_destroy(t_linked_list *ll);

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
void t_linked_list_insert_first(t_linked_list *ll, void *data);

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
void t_linked_list_insert_last(t_linked_list *ll, void *data);

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
*     in that node.
*/
void* t_linked_list_remove_first(t_linked_list *ll);

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
void* t_linked_list_remove_last(t_linked_list *ll);

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
*     to t_linked_list_remove_first.
*/
void* t_linked_list_delete_first(t_linked_list *ll);

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
*     to t_linked_list_remove_last.
*/
void* t_linked_list_delete_last(t_linked_list *ll);

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
void* t_linked_list_get_first(t_linked_list *ll);

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
void* t_linked_list_get_last(t_linked_list *ll);

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
void* t_linked_list_iterator(t_linked_list *ll, void **iterator);

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
int t_linked_list_get_length(t_linked_list *ll);

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
  t_linked_list *ll, void (*node_free_fn)(void*));

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
  t_linked_list *ll, char* (*node_to_string_fn)(void*));

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
char* t_linked_list_to_string(t_linked_list *ll);

#endif
