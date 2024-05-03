#include "bst.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int compareInt(void* target, void* current){
  int* Target = (int* )target;
  int* Current = (int* )current;
  if(*Target > *Current){
    return 1;
  }
  else if(*Target < *Current){
    return 0;
  }
  else{
    return 2;
  }
}
int compareChar(void* target, void* current){
  if(*(char* )target > *(char* )current){
    return 1;
  }
  else if(*(char* )target < *(char* )current){
    return 0;
  }
  else{
    return 2;
  }
}
int compareString(void* target, void* current){
  if(strcmp((char* )target, (char* )current)< 0){
    return 0;
  }
  else if(strcmp((char* )target, (char* )current) > 0){
    return 1;
  }
  else{
    return 2;
  }
}
int insertItem(BST* bst, void* item){
  void* p = item;//pointer of item
  
  Node* new;
  new = (Node* ) malloc(sizeof(Node));
  if(new == NULL){
    exit(1);
  }
  new->item = item;
  new->left = NULL;
  new->right = NULL;
  if(bst->tree_root == NULL){
    bst->tree_root = new;
    
    
    return 0;
  }
  else{
    Node* current;
    current = bst->tree_root;
    Node* parent;
    
    void* x = current->item;
    while(current != NULL){
      x = current->item;//pointer of current node's item
      parent = current;
      if(bst->item_size == 4){//case for inputing int
        if(compareInt(p,x) == 0){
          if(current->left == NULL){
            current->left = new;
            return 0;
          }
          else{
            current = current->left;
            //continue going left
            
            
          }
        }
        else if(compareInt(p,x) == 1){
          if(current->right == NULL){
            current->right = new;
            return 0;
          }
          else{
            current = current->right;
            //continue going right
            
          }
        }
        else{
          //duplicate node
          return 1;
        }
      }
      else if(bst->item_size == 1){//case for inputing char
          if(compareChar(p,x) == 0){
            if(current->left == NULL){
              current->left = new;
              return 0;
            }
            else{
              current = current->left;
              //continue going left
              
              
            }
          }
          else if(compareChar(p,x) == 1){
            if(current->right == NULL){
              current->right = new;
              return 0;
            }
            else{
              current = current->right;
              //continue going right
              
            }
          }
          else{
            //duplicate node
            return 1;
          }
      }
      else if(bst->item_size == 8){//case for inputing string
          if(compareString(p,x) == 0){
            if(current->left == NULL){
              current->left = new;
              return 0;
            }
            else{
              current = current->left;
              //continue going left
              
              
            }
          }
          else if(compareString(p,x) == 1){
            if(current->right == NULL){
              current->right = new;
              return 0;
            }
            else{
              current = current->right;
              //continue going right
              
            }
          }
          else{
            //duplicate node
            return 1;
          }
      }
      
    }
    
  }
  
}
