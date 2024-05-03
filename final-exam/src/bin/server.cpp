//Reference from Homework-9: https://gitlab.com/zhw323-cse109/homework-9.git
//Reference from Homework-8: https://gitlab.com/zhw323-cse109/homework-8.git

#include<fstream>
#include<iostream>
#include <string.h>
#include "pack109.hpp"
#include <stdexcept>
#include<stdio.h>
#include<stdlib.h>
#include <netdb.h>
#include <netinet/in.h>

#define KEY 42



//Reference from Homework-6: https://gitlab.com/zhw323-cse109/homework-6.git
//Below is the hash map function
typedef struct{
  string key;
  vec value;
}Node;

typedef struct{
    Node* table;
    int size;
}Hash;



//insert function
bool insert(Hash map, string key, vec value){
  //get the hash code of the key
  const char* item = key.c_str();
  unsigned long h = 5381;
  int c;
  while (c = *item++) { 
    h = ((h << 5) + h) + c;
  }
  int position = h % map.size;

  //case for no value for the key
  if(map.table[position].value.empty()){
    map.table[position].key = key;
    for(int i = 0 ; i < value.size(); i++){
      map.table[position].value.push_back(value[i]);
    }
    return true;
  }
  //case for non empty value for the key
  else if(map.table[position].value.size()!=0){
    map.table[position].key = key;
    map.table[position].value.clear();
    for(int i = 0 ; i < value.size(); i++){
      map.table[position].value.push_back(value[i]);
    }
    return true;
  }
  else{
    return false;
  }

}

//find function
vec find(Hash map, string key){
  //get the hash code of the key
  const char* item = key.c_str();
  unsigned long h = 5381;
  int c;
  while (c = *item++) { 
    h = ((h << 5) + h) + c;
  }
  int position = h % map.size;
  //case for key does not exist
  if(map.table[position].key.empty()){
    printf("Key does not exist\n");
  }
  else{
    return map.table[position].value;
  }
}



int main(int argc, char* argv[]){
  if(argc < 3){
    printf("Need host name\n");
    exit(1);
  }
  int portno,count;
  char** host = (char** )malloc(sizeof(int));
  char* token = strtok(argv[2], ":");
  char* IP = argv[2];////////copy for the address and port incase tokenlize change the argument
  while(token != NULL){
    host[count] = token;
    token = strtok(NULL,":");
    count++;
  }//tokenlize the address
  char* address = host[0];
  portno = atoi(host[1]); //convert from string to int
  int sockfd, newsockfd;
  struct sockaddr_in serv_addr, cli_addr;
  

  /* First call to socket() function */
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
    perror("ERROR opening socket");
    exit(1);
  }

  //intializing struct
  bzero((char *) &serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_addr.s_addr = INADDR_ANY;
  serv_addr.sin_port = htons(portno);
  socklen_t slilen = sizeof(serv_addr);

  /* Now bind the host address using bind() call.*/
  if (bind(sockfd, (struct sockaddr *)&serv_addr, slilen) < 0) {
    perror("ERROR on binding");
    exit(1);
  }
    /* Now listen the connection */
    printf("Waiting for connection\n");
    listen(sockfd,5);
    socklen_t clilen = sizeof(cli_addr);
    /* Accept actual connection from the client */
    newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
    if (newsockfd < 0) {
        perror("ERROR on accept");
        exit(1);
    }
    //initialize the hash map
    Hash* my_hash = (Hash* )malloc(sizeof(Hash));
    my_hash->size = 30;
    my_hash->table = (Node* )malloc(sizeof(Node)*my_hash->size);
    printf("--------------------------------------------\n");
    //Start looping
    while(true){
      printf("Waiting for new client message\n");
      /* Start to receive file or request from client */
      unsigned char* buffer = (unsigned char* )malloc(654130);
      int n = recv( newsockfd,buffer,654130,0);
      if (n < 0) {
          perror("ERROR reading from socket");
          exit(1);
      }
      
      //Put the content in buffer into a vector
      vec Read;
      for(size_t i = 0; i < 65413; i++){
        
        Read.push_back(*(buffer+i));
        
      }
      free(buffer);
      //Dectypt the message
      for(int i = 0; i < Read.size(); i++){
          Read[i] = Read[i] ^ KEY;
      }
      //De the message
      int ROF = pack109::deserializeMessage(Read);
      
      //Request
      if(ROF == 1){
        printf("Request received\n");
        struct File sentfile;
        struct Request request;
        request = pack109::deserialize_request(Read);
        vec bytes = find(*my_hash, request.name);
        //Not found in hash map
        if(bytes.empty()){
          printf("No such file\n");
          printf("--------------------------------------------\n");
        }
        //Found in hash map
        else{
          sentfile.name = request.name;
          for(int i = 0; i < bytes.size(); i++){
            sentfile.bytes.push_back(bytes[i]);
          }
          //SE the file struct
          vec files = pack109::serialize(sentfile);
          //Encrypt the vector
          for(int i = 0; i < files.size(); i++){
            files[i] = files[i] ^ KEY;
          }
          //send the file
          unsigned char* Buffer = (unsigned char* )malloc(files.size());
          for(int i = 0; i < files.size(); i++){
            *(Buffer+i) = files[i];
          }
          int m = send(newsockfd, Buffer, files.size(),0);
          printf("%s sent\n", sentfile.name.c_str());
          printf("%d Bytes sent\n", files.size());
          printf("--------------------------------------------\n");
          free(Buffer);
        }
      }
      //Send
      else if(ROF == 2){
        printf("File recived\n");
        struct File recfile;
        recfile = pack109::deserialize_file(Read);
        string key = recfile.name;
        vec val = recfile.bytes;
        
        
        bool result = insert(*my_hash, key, val);
        
        if(result == true){
          printf("%s received\n", key.c_str());
          printf("%d Bytes received\n", val.size());
          printf("--------------------------------------------\n");
        }
        else{
          printf("Fail to receive\n");
          printf("--------------------------------------------\n");
        }
      }

      else{
        printf("no such option\n");
        printf("--------------------------------------------\n");
      }
    }
    



}