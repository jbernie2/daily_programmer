#include <stdlib.h>

typedef void** t_hash_table;
t_hash_table hash = NULL;
char** hash_keys = NULL;
int num_entries = 0;
int hash_size = 0;

t_hash_table init (int size){
  if(size = 0){
    size = 128;
  } 
  resize_hash(size);
  return hash;
}

void resize_hash(int new_hash_size){
  if(new_hash_size < hash_size){
    new_hash_size = hash_size * 2;
  }
  copy_hash(hash,size,new_hash_size);
  hash_size = new_hash_size;
}

void copy_hash(t_hash_table old_hash,int old_hash_size, int new_hash_size){
  t_hash_table new_hash = malloc(sizeof(void*)*new_hash_size);
  char** new_hash_keys = malloc(sizeof(char*)*new_hash_size);
  int i = 0;
  for(i < old_hash_size; i++){
    //new_hash[i] = old_hash[i];
    //have to rehash elements hash positions change when the hash size changes
  }
  free(old_hash);
  old_hash = new_hash;
}

void insert(char* key, void* value){
  int key_len = len(key);
  int i = hash_index = 0;
  for(;i < key_len; i++){
    hash_index += (key[i] << 8);
  }
  hash_index = hash_index % hash_size;
}
