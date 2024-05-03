#include "bst.h"
#include <stdio.h>
#include <stdlib.h>

//Reference: https://www.geeksforgeeks.org/convert-normal-bst-balanced-bst/ for how to rebalance

void rebalanceTree(BST* bst){
  Node* root;
  root = (Node* )malloc(sizeof(bst->tree_root));
  if(root == NULL){
    exit(1);
  }
  root = (Node* )bst->tree_root;
  int size = CountNode(root);
  void* BSTlist[size];
  int count = 0;
  
  //store items in BST into arry BSTlist
  Inorder(root,BSTlist,count);
  
  root = rebalance(BSTlist, 0 , (sizeof(BSTlist)/sizeof(BSTlist[0])-1));
  bst->tree_root = root;
}
//Reference: https://stackoverflow.com/questions/29582431/convert-binary-tree-to-array-in-c for how to put BST into array
int Inorder(Node* node,void* BSTlist[], int count){
  
  if(node == NULL){
    return count;
  }
  
  if(node->left != NULL){
    count = Inorder(node->left,BSTlist,count);
  }
  
  BSTlist[count] = node->item;
  count++;
  
  if(node->right != NULL){
    count = Inorder(node->right, BSTlist, count);
  }
  return count;
  
}
Node* rebalance(void* BSTlist[], int start, int end){
  if(start > end){
    return NULL;
  }
  int mid = (start + end)/2;
  Node* newRoot;
  newRoot = (Node* )malloc(sizeof(Node));
  if(newRoot == NULL){
    return NULL;
  }
  newRoot->item= BSTlist[mid];
  newRoot->left = rebalance(BSTlist, start, mid-1);
  newRoot->right = rebalance(BSTlist,mid+1, end);
  return newRoot;
}

int CountNode(Node* node){
  int num = 1;
  if(node == NULL){
    return 0;
  }
  num += CountNode(node->left);
  num += CountNode(node->right);
  return num;
}