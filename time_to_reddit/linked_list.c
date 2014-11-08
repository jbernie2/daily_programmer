#include <stdlib.h>
#include <stdio.h>

typedef struct ll_node t_ll_node;
typedef struct linked_list t_linked_list;
void t_ll_node_destroy(t_ll_node *n);
t_ll_node* t_ll_node_init();



struct ll_node
{
  t_ll_node *prev;
  t_ll_node *next;
  void *data;
};

struct linked_list
{
  int length;
  char *data_type;
  t_ll_node *head;
  t_ll_node *tail;
};

t_linked_list* t_linked_list_init(){
  
  t_linked_list *ll = malloc(sizeof(t_linked_list));
  ll -> length = 0;
  //ll -> data_type = data_type;
  
  ll -> head = malloc(sizeof(t_ll_node)); 
  ll -> tail = malloc(sizeof(t_ll_node));
  
  ll -> head -> prev = NULL;
  ll -> head -> next = ll -> tail;
   
  ll -> tail -> prev = ll -> head;
  ll -> tail -> next = NULL; 
  
  return ll;
}

void destroy(t_linked_list *ll){

}

void insert(t_linked_list *ll, void *data){
  t_ll_node *new_node = t_ll_node_init();
  new_node -> data = data;
  new_node -> prev = ll -> head;
  new_node -> next = ll -> head -> next;
  ll -> head -> next -> prev = new_node;
  ll -> head -> next = new_node; 
}

void remove_first(t_linked_list *ll){
  t_ll_node *removed_node = ll -> head -> next;
  ll -> head -> next -> next -> prev = ll -> head;
  ll -> head -> next = ll-> head -> next -> next;
  t_ll_node_destroy(removed_node);
}



void remove_last(t_linked_list *ll){

}

void** get_first(t_linked_list *ll){
  return ll -> head -> next -> data;
}

void** get_last(t_linked_list *ll){

}

void** get_next(t_linked_list *ll, int *index){

}

t_ll_node* t_ll_node_init(){
  t_ll_node *n = malloc(sizeof(t_ll_node));
  return n;
}

void t_ll_node_destroy(t_ll_node *n){
  n -> next = NULL;
  n -> prev = NULL;
  //free(*(n->data));
  free(n->data);
  free(n);
}


struct{
  char *test;
} test_data;

int main(){
  t_linked_list *ll = t_linked_list_init();
   
  struct test_data *test1 = malloc(sizeof(struct test_data));
  test1 -> test = "test";
  
  struct test_data *test2 = malloc(sizeof(struct test_data));
  test2 -> test = "test2";

  insert(ll,test1);
  insert(ll,test2);
/*
  struct test_data *test1 = (struct test 
  printf("%s \n",test);

  remove_first(ll);

  test = (char*)(*get_first(ll));
  printf("%s \n",test);

  free(ll);
*/
}
