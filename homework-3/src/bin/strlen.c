#include<stdio.h>

int strlen(char*);

int main(){
  char* testStr = "Hello";
  int count = strlen(testStr);
  printf("%d\n", count);
  return 0;
}

int strlen(char* str) {
  int Length = 0;
  while(*str ++){
    ++ Length;
  }
  return Length;
}