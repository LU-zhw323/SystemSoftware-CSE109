#include<stdio.h>
#include<string.h>

int main(int argc, char** argv){
  for(int i = 0 ; i < argc; i++){
    printf("argv[%d], content:%s, address:%x\n", i, argv[i], &argv[i]);
  }
  
  
  for(int i = 0; i < argc; i++){
    int Length = strlen(argv[i]);
    for(int j = 0; j < Length; j++){
      printf("argv[%d][%d], content:%c, address:%x\n", i, j, argv[i][j], &argv[i][j]);
    }
  }
  
  return 0;
}