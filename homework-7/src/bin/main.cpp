#include <stdexcept>
#include<vector>
#include<stdio.h>
#include<stdlib.h>
#include"pack109.hpp"
#include<fstream>
#include<iostream>


using namespace std;

int main() {

  //write
  struct Person ann = { age:10, height:1.109, name:"Ann" };
  vec bytes16 = pack109::serialize(ann);
  ofstream my_bin("person.pack109", ofstream::binary);
  
  if(!my_bin.is_open()){
    printf("not open\n");
    return 0;
  }
  
  for(int i = 0 ; i < bytes16.size(); i++){
    u8 byte = bytes16[i];
    my_bin.put(byte);
  }
  my_bin.flush();
  my_bin.close();



  //read
  struct Person Ann;
  vec Bytes;
  ifstream my_read ("person.pack109", ifstream::binary);
  if(!my_read.is_open()){
    printf("not open\n");
    return 0;
  }
  for(int i = 0; i < bytes16.size();i++){
    u8 bytes = my_read.get();
    Bytes.push_back(bytes);
  }
  my_read.close();
  Ann = pack109::deserialize_person(Bytes);
  printf("original struct:\n");
  pack109::printVec(bytes16);
  printf("Readed struct:\n");
  pack109::printVec(Bytes);

  printf("oringinal age: %x , Readed age: %x\n", ann.age, Ann.age);
  printf("oringinal height: %f , Readed height: %f\n", ann.height, Ann.height);
  printf("oringinal name: %s , Readed name: %s\n", ann.name, Ann.name);
  return 0;
}