#include <stdio.h>


void multiply_ptrs(int*, int*, int*);


int main(){
  int z;
  int x = 5;
  int y = 6;
  multiply_ptrs(&x,&y,&z);
  printf("%d\n", z);
  return 0;
}

void multiply_ptrs(int* x, int* y, int* z){
 int a = *x;
 int b = *y;
 *z = a * b;
}