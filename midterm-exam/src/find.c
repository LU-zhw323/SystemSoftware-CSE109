#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

void* findItem(BST* bst, void* query){
  if(query == NULL){
    return NULL;
  }
  void* target = query;
  
  Node* current;
  current = (Node* ) malloc(sizeof(bst->tree_root));
  if(current == NULL){
    exit(1);
  }
  current = bst->tree_root;
  
  if(current == NULL){
    return NULL;
  }
  
  while(current != NULL){
    void* Item = current->item;
    if(bst->item_size == 4){//case for int
      if(compareInt(target,Item)==2){
     
        return current->item;
      }
      else{
        if(compareInt(target,Item)==0){
          current = current->left;
          
        }
        else if(compareInt(target,Item)==1){
          current = current->right;
          
        }
      }
    }
    else if(bst->item_size == 1){//case for char
      if(compareChar(target,Item)==2){
     
        return current->item;
      }
      else{
        if(compareChar(target,Item)==0){
          current = current->left;
          
        }
        else if(compareChar(target,Item)==1){
          current = current->right;
          
        }
      }
    }
    else if(bst->item_size == 8){//case for String
      if(compareString(target,Item)==2){
     
        return current->item;
      }
      else{
        if(compareString(target,Item)==0){
          current = current->left;
          
        }
        else if(compareString(target,Item)==1){
          current = current->right;
          
        }
      }
    }
    
    
  }
  return NULL;
}