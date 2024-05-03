#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

void initBinaryTree(BST* bst, int size){
  bst->tree_root = NULL;
  bst->item_size = size;
  bst->depth = 0;
}

//Reference: https://en.wikipedia.org/wiki/Binary_search_tree
//print the tree by Preorder
void Preorder(Node* node){
  if(node == NULL){
    return;
  }
  
  printf("%d\t", *(int* )node->item);
  Preorder(node->left);
  Preorder(node->right);
  
}
void PreorderChar(Node* node){
  if(node == NULL){
    return;
  }
  
  printf("%c\t", *(char* )node->item);
  Preorder(node->left);
  Preorder(node->right);
}
void PreorderString(Node* node){
  if(node == NULL){
    return;
  }
  
  printf("%s\t", (char* )node->item);
  Preorder(node->left);
  Preorder(node->right);
}
void printTree(BST* bst){
  Node* root;
  root = (Node* )malloc(sizeof(bst->tree_root));
  if(root == NULL){
    exit(1);
  }
  root = (Node* )bst->tree_root;
  if(bst->item_size = sizeof(4)){
    Preorder(root);
  }
  else if(bst->item_size = sizeof(1)){
    PreorderChar(root);
  }
  else if(bst->item_size = sizeof(8)){
    PreorderString(root);
  }
  printf("\n");
  return;
}

//Reference: https://stackoverflow.com/questions/9181146/freeing-memory-of-a-binary-tree-c
//Free the node by recursive
void freeNodes(BST* bst){
  Node* root;
  root = (Node* )malloc(sizeof(bst->tree_root));
  if(root == NULL){
    exit(1);
  }
  root = bst->tree_root;
  free_tree(root);//
}
void free_tree(Node* node){
  if(node == NULL){
    return;
  }
  free(node->left);
  free(node->right);
  free(node);
}