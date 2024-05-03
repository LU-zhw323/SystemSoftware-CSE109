#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

void* removeItem(BST* bst, void* query){
  if(query == NULL){
    return NULL;
  }
  int* target = (int* )query;
  Node* current;
  current = (Node* ) malloc(sizeof(bst->tree_root));
  if(current == NULL){
    exit(1);
  }
  current = bst->tree_root;
  if(current == NULL){
    return NULL;
  }
  Node* parent = NULL;
  int* Item = (int* )current->item;
  while(current != NULL){
    Item = (int* )current->item;
    
    if(*target == *Item){
      break;
    }
    parent = current;

    
    if(*target > *Item){
      current = current->right;
    }
    else{
      current = current->left;
    }
  }
  
  if(current == NULL){
    return NULL;
  }//query is not found
  int* PItem;
  if(parent != NULL){
    PItem = (int* )parent->item;
  }
  

  if(current->left==NULL && current->right==NULL){ //delete leaf without children
    
    if(parent==NULL){
     
      bst->tree_root = NULL;
      return current->item;
    }//case for delete root without any children
    else{
      
      if(*Item < *PItem){
        
        bst->depth --;
        parent->left = NULL;
        return current->item;
      }
      else{
        
        bst->depth --;
        parent->right = NULL;
        return current->item;
      }
    }
  }
  else if(current->left == NULL && current->right != NULL){ //delete leaf with only one child
    
    if(parent == NULL){
      //query is at the root 
        bst->tree_root = current->right;
        current->right = NULL;
        bst->depth --;
        return current->item;
    }
    
    else{
      if(*target < *PItem){
        //fingure out where to put the child of deleted node
        if(current->right == NULL){
          parent->left = current->right;
        }
        else{
          parent->left = current->right;
        }
        bst->depth --;
        return current->item;
      }
      else{
        if(current->left == NULL){
          parent->right = current->right;
        }
        else{
          parent->right = current->left;
        }
       
        bst->depth --;
        return current->item;
      }
    }
  }
  else if(current->left != NULL && current->right == NULL){
    if(parent == NULL){
      
        bst->tree_root = current->left;
        current->left = NULL;
        bst->depth --;
        return current->item;
    }
    else{
      if(*target < *PItem){
        parent->left = current->left;
        bst->depth --;
        return current->item;
      }
      else{
        parent->right = current->left;
        bst->depth--;
        return current->item;
      }
    }
  }
  else{//find the rightmost child at left subtree
    
    Node* RightMostParent;
    
    RightMostParent = (Node* )malloc(sizeof(current));
    if(RightMostParent == NULL){
      return NULL;
    }
    
    RightMostParent = current;
    
    Node* RightMost;
    
    RightMost = (Node* )malloc(sizeof(current->nodes[0]));
    if(RightMost == NULL){
      return NULL;
    }
    
    RightMost = current->left;
    ////////
    
    while(RightMost->right != NULL){
      RightMostParent = RightMost;
      RightMost = RightMost->right;
    }
    if(parent == NULL){
      bst->tree_root->item = RightMost->item;
      RightMostParent->right = RightMost->left;
      RightMost = NULL;
      bst->depth--;
      return query;
    }
    else if(current == parent->left){
      parent->left->item = RightMost->item;
      parent->left->left = NULL;
      
      bst->depth--;
      return query;
    }
    else if(current == parent->right){
      parent->right->item = RightMost->item;
      parent->right->left = NULL;
      
      bst->depth--;
      return query;
    }
    else{
      current->item = RightMost->item;
      RightMostParent->right = RightMost->left;
      bst->depth--;
      return query;
    }
    
  }
  return NULL;


}