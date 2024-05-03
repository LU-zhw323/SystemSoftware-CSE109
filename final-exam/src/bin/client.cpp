
//Reference from Homework-9: https://gitlab.com/zhw323-cse109/homework-9.git
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


using namespace std;

vec readFile(char* filename){
  // open the file:
    
    ifstream file(filename, ifstream::binary);

    // get its size:
    file.seekg(0, std::ios::end);
    size_t fileSize = file.tellg();
    file.seekg(0, std::ios::beg);

    // read the data:
    vec fileData(fileSize);
    file.read((char*) &fileData[0], fileSize);
    file.close();
    return fileData;
}

void writeFile(string place, vec context){
  const char* Place = place.c_str();
  ofstream my_bin(Place, ofstream::binary);
  if(!my_bin.is_open()){
    std::cout << "not open" << endl;
    exit(1);
  }
  for(int i = 0 ; i < context.size(); i++){
    u8 byte = context[i];
    my_bin.put(byte);
  }
  my_bin.flush();
  my_bin.close();
}


int main(int argc, char* argv[]){
  
  if(argc > 5){
    //printf("Sending and requesting at the same time\n");
    exit(1);
  }
  if(argv[1] == NULL || argv[2] == NULL){
    //printf("Without hostname\n");
    exit(1);
  }//check the host name
  
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
  //char* command = argv[3];
  free(host);
  struct File my_file; 
  
  struct sockaddr_in serv_addr;
  struct hostent *server;
  
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) {
      perror("ERROR opening socket");
      exit(1);
   }
   server = gethostbyname(address);
   if (server == NULL) {
      fprintf(stderr,"ERROR, no such host\n");
      exit(0);
   }
   bzero((char *) &serv_addr, sizeof(serv_addr));//set structe to NULLbytes
   serv_addr.sin_family = AF_INET;
   bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);//copy
   serv_addr.sin_port = htons(portno);
    
   /* Now connect to the server */
   if (connect(sockfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)) < 0) {
      perror("ERROR connecting");
      exit(1);
   }
  //start looping
  printf("--------------------------------------------\n");
  while(true){
    //Reference from : https://blog.csdn.net/mylovepan/article/details/7940719
    //get the command
    std::cout << "Please enter the command:(--send or --request) " << endl;
    char command[20];
    std::cin >> command;
    //send file
    if(strcmp(command, "--send") == 0){
      char info[20];
      std::cout << "Please enter the file name and its directory: " << endl;
      std::cin >> info;
      my_file.bytes = readFile(info);//read file into vector

      char** name = (char** )malloc(sizeof(char**));
      char* Token = strtok(info, "/");
      int i = 0;
      while(Token != NULL){
        name[i] = Token;
        Token = strtok(NULL, "/");
        i++;
      }//tokenlize the name of the file
      char* target = name[1];
      free(name);
      my_file.name = target;
      
      //serialize the struct
      vec Files = pack109::serialize(my_file);
    
      //encryption
      for(int i = 0; i < Files.size(); i++){
        Files[i] = Files[i] ^ KEY;
      }
      unsigned char* buffer = (unsigned char* )malloc(Files.size());
      for(int i = 0; i < Files.size(); i++){
        *(buffer+i) = Files[i];
      }
      
      /* Send message to the server */
      int n = send(sockfd, buffer, Files.size(),0);
      if (n < 0) {
          perror("ERROR writing to socket");
          exit(1);
      }
      free(buffer);
      std::cout << "File sent successfully" << endl;
      printf("--------------------------------------------\n");
      
    }






    //request file
    else if(strcmp(command,"--request")==0){
      char target[20];
      std::cout << "Please enter the file name: " << endl;
      std::cin >> target;
      struct Request my_request;
      my_request.name = target;
      //serialize the struct
      vec request = pack109::serialize(my_request);
      //encryption
      for(int i = 0; i < request.size(); i++){
        request[i] = request[i] ^ KEY;
      }
      unsigned char* buffer = (unsigned char* )malloc(request.size());
      for(int i = 0; i < request.size(); i++){
        *(buffer+i) = request[i];
      }
      //send the request to the server
      int n = send(sockfd, buffer, request.size(), 0);
      if (n < 0) {
          perror("ERROR writing to socket");
          exit(1);
      }
      std::cout << "Request sent successfully" << endl;
      free(buffer);
      //receive the message
      unsigned char* Buffer = (unsigned char* )malloc(65413);
      //cause I do not know the size of file that will be received, I just initalize the size of buffer to be 65413(Biggest size that the server would send back)
      //But I still write the serilization and deserilization function that can read upto 2^16 Bytes
      n = recv(sockfd, Buffer, 65413,0);
      if (n < 0) {
        perror("ERROR reading from socket");
        exit(1);
      }
      std::cout << "File received successfully" << endl;
      vec Read;
      for(size_t i = 0; i < 65413; i++){
        //if(*(Buffer+i) != NULL){
        Read.push_back(*(Buffer+i));
        //}
      }
      
      for(int i = 0; i < Read.size(); i++){
        Read[i] = Read[i] ^ KEY;
      }
      struct File sentFile;
      sentFile = pack109::deserialize_file(Read);
      string route = "received/";
      route.append(sentFile.name);
      writeFile(route, sentFile.bytes);
      printf("%s received\n", sentFile.name.c_str());
      printf("--------------------------------------------\n");
      
    }
    else{
      printf("No such command\n");
      printf("--------------------------------------------\n");
    }
  }
  
  


}
