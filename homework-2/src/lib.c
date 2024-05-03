#include <stdbool.h>
#include <unistd.h>
#include <stdio.h>
#include<string.h>
#include <stdlib.h>

int access();
bool file_exists(char* path) {
  int path_excute = access(path,X_OK);
    if(path_excute == 0){
      return true;
    }
    else{
      return false;
    }
}