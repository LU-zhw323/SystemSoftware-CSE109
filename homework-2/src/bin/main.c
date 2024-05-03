#include <whichtools.h>
#include <stdio.h>
#include<string.h>
#include <stdlib.h>
#include <stdbool.h>


int main(int argc, char** argv) {
  
  int flag = 0;
  if(argv[1][0] == '-'){
    if(strcmp(argv[1],"-a") == 0){
      flag = 1;
    }
    else{
      printf("which: illegal option %s\n", argv[1]);
      printf("useage: which [as] program");
      return 2;
    }
  }

  int count = 0;
  char** PATH_LIST = (char **)malloc(1000);
  char* PATH_token = getenv("PATH");
  
  char* str[1000];
  strcpy(str, PATH_token);
  char* token = strtok(str, ":");
  while(token != NULL){
    PATH_LIST[count] = token;
    token = strtok(NULL, ":");
    count++;
  }
  
  int result = 0;
  if(flag != 1){
    for(int i = 1; i < argc; i++){
      char target [30]= "/";
      strcat(target,argv[i]);
      //char target_buf[200];
      for(int j = 0; j < count; j++){
        if(result == 2){
          break;
        }
        char buffer[1000];
        strcpy(buffer,PATH_LIST[j]);
        //strcat(target_buf, PATH_LIST[j]);
        strcat(buffer , target);
        if(file_exists(buffer)){
          printf("%s ", buffer);
          result++;
        }
        else{
          
        }
      }
      
    }
   }
  
  
  else{
    for(int i = 2; i < argc; i++){
      char target[30] = "/";
      strcat(target,argv[i]);
      for(int j = 0; j < count; j++){
        char buffer[1000];
        strcpy(buffer,PATH_LIST[j]);
        strcat(buffer, target);
        if(file_exists(buffer)){
          printf("%s ", buffer);
          result++;
        }
        else{
        }
      
      }
    }
  }
  if(result != 0){
    return 0;
  }
  else{
    return 1;
  }
  
}





 
   