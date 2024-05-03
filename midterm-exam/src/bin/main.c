#include "bst.h"
#include <stdio.h>
#include <stdlib.h>
int test(char* label, int a, int b) {
  printf("%s: ", label);
  if (a==b) {
    printf("Passed\n");
    return 1;
  } else {
    printf("Failed. lhs=%x, rhs= %x\n",a,b);
    exit(1);
  }
}

int main(){
  BST* bst;
  bst = (BST* )malloc(sizeof(BST));
  if(bst == NULL){
    exit(1);
  }
  int size = 4;
  initBinaryTree(bst,sizeof(size));
  
  
  int n = 1;
  int m = 2;
  int a = 3;
  int h = 4;
  insertItem(bst, &n);
  insertItem(bst, &m);
  insertItem(bst, &a);
  insertItem(bst, &h);
  printf("BST used to demonstrate rebalance and free fuctions: (Pointed by Preorder)\n");
  printTree(bst);
  rebalanceTree(bst);
  printTree(bst);
  freeNodes(bst);
  printf("After free BST, new BST used to test insert, remove and find functions: \n");
  int x = 10;
  int y = 6;
  int z = 7;
  int i = 3;
  int u = 21;
  int c = 11;
  int b = 22;

  
  insertItem(bst, &x);
  insertItem(bst, &y);
  insertItem(bst, &z);
  insertItem(bst, &i);
  insertItem(bst, &u);
  insertItem(bst, &c);
  insertItem(bst, &b);
  printTree(bst);
  
  
  test("Test1, findItem:x", *(int* )findItem(bst,&x), 10);
  test("Test2, findItem:b", *(int* )findItem(bst,&b), 22);
  test("Test3, removeItem:y",*(int* )removeItem(bst,&y), 6);
  printf("After remove 6\n");
  printTree(bst);
  test("Test4, removeItem:u", *(int* )removeItem(bst,&u), 21);
  printf("After remove 21\n");
  printTree(bst);
  test("Test5, removeItem:x", *(int* )removeItem(bst,&x), 10);
  printf("After remove 10\n");
  printTree(bst);
  
  
  //int* result = (int* )findItem(bst, &b);
  //printf("target found: %d\n", *result);
  //int* Result = (int* )removeItem(bst,&y);
  //printf("removed: %d\n", *Result);
  
  
  return 0;
}