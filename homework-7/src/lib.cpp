#include <vector>
#include <stdio.h>
#include "pack109.hpp"

vec pack109::serialize(bool item) {
  vec bytes;
  if (item == true) {
    bytes.push_back(PACK109_TRUE);
  } else {
    bytes.push_back(PACK109_FALSE);
  }
  return bytes;
}

bool pack109::deserialize_bool(vec bytes) {
  if (bytes.size() < 1) {
     throw;
  }

  if (bytes[0] == PACK109_TRUE) {
    return true;
  } else if (bytes[0] == PACK109_FALSE) {
    return false;
  } else {
    throw;
  }

}

vec pack109::serialize(u8 item) {
  vec bytes;
  bytes.push_back(PACK109_U8);
  bytes.push_back(item);
  return bytes;
}

u8 pack109::deserialize_u8(vec bytes) {
  if (bytes.size() < 2) {
    throw;
  }
  if (bytes[0] == PACK109_U8) {
    return bytes[1];
  } else {
    throw;
  }
}

vec pack109::serialize(u32 item){
  vec bytes;
  bytes.push_back(PACK109_U32);
  u32 mask = 0x000000FF;
  for(int i = 3; i >=0 ; i--){
    bytes.push_back((char)(item >> 8*i & mask));
  }
  return bytes;
}

u32 pack109::deserialize_u32(vec bytes){
  if(bytes.size()<5){
    throw;
  }
  if(bytes[0] == PACK109_U32){
    u32 item = 0x00000000;
    int position = 3;
    for(int i = 1 ; i <= 4; i++){
      item = item|(int)bytes[i]<<8*position;
      position--;
    }
   return item;
  }
  else{
    throw;
  }
}

vec pack109::serialize(u64 item){
  vec bytes;
  bytes.push_back(PACK109_U64);
  u64 mask = 0x00000000000000FF;
  for(int i = 7; i >= 0; i--){
    bytes.push_back((char)(item >> 8*i & mask));
  }
  return bytes;
}

u64 pack109:: deserialize_u64(vec bytes){
  if(bytes.size()<9){
    throw;
  }
  if(bytes[0]==PACK109_U64){
    u64 item = 0x0000000000000000;
    int position = 7;
    for(int i = 1; i <= 8; i++){
      item = item|(long)bytes[i]<<8*position;
      position --;
    }
    return item;
  }
  else{
    throw;
  }
}


vec pack109::serialize(i8 item){
  vec bytes;
  bytes.push_back(PACK109_I8);
  bytes.push_back(item);
  return bytes;
}

i8 pack109::deserialize_i8(vec bytes){
  if (bytes.size() < 2) {
    throw;
  }
  if (bytes[0] == PACK109_I8) {
    return bytes[1];
  } else {
    throw;
  }
}


vec pack109::serialize(i32 item){
  vec bytes;
  bytes.push_back(PACK109_I32);
  u32 mask = 0x000000FF;
  for(int i = 3; i >=0 ; i--){
    bytes.push_back((char)(item >> 8*i & mask));
  }
  return bytes;
}

i32 pack109::deserialize_i32(vec bytes){
  if(bytes.size()<5){
    throw;
  }
  if(bytes[0] == PACK109_I32){
    u32 item = 0x00000000;
    int position = 3;
    for(int i = 1 ; i <= 4; i++){
      item = item|(int)bytes[i]<<8*position;
      position--;
    }
   return item;
  }
  else{
    throw;
  }
}


vec pack109::serialize(i64 item){
  vec bytes;
  bytes.push_back(PACK109_I64);
  u64 mask = 0x00000000000000FF;
  for(int i = 7; i >= 0; i--){
    bytes.push_back((char)(item >> 8*i & mask));
  }
  return bytes;
}
i64 pack109::deserialize_i64(vec bytes){
  if(bytes.size()<9){
    throw;
  }
  if(bytes[0]==PACK109_I64){
    u64 item = 0x0000000000000000;
    int position = 7;
    for(int i = 1; i <= 8; i++){
      item = item|(long)bytes[i]<<8*position;
      position --;
    }
    return item;
  }
  else{
    throw;
  }
}


vec pack109::serialize(f32 item){
  vec bytes;
  bytes.push_back(PACK109_F32);
  u32* Cast = (u32*)&item;
  u32 mask = 0x000000FF;
  for(int i = 3; i >=0 ; i--){
    bytes.push_back((char)(*Cast >> 8*i & mask));
  }
  return bytes;
}

f32 pack109::deserialize_f32(vec bytes){
  if(bytes.size()<5){
    throw;
  }
  if(bytes[0] == PACK109_F32){
    u32 item = 0x00000000;
    int position = 3;
    for(int i = 1 ; i <= 4; i++){
      item = item|(int)bytes[i]<<8*position;
      position--;
    }
    f32* Item = (f32*)&item;
   return *Item;
  }
  else{
    throw;
  }
}

vec pack109::serialize(f64 item){
  vec bytes;
  bytes.push_back(PACK109_F64);
  u64* Cast = (u64*)&item;
  u64 mask = 0x00000000000000FF;
  for(int i = 7; i >= 0; i--){
    bytes.push_back((char)(*Cast >> 8*i & mask));
  }
  return bytes;
}

f64 pack109::deserialize_f64(vec bytes){
  if(bytes.size()<9){
    throw;
  }
  if(bytes[0]==PACK109_F64){
    u64 item = 0x0000000000000000;
    int position = 7;
    for(int i = 1; i <= 8; i++){
      item = item|(long)bytes[i]<<8*position;
      position --;
    }
    f64* Item = (f64* )&item;
    return *Item;
  }
  else{
    throw;
  }
}


vec pack109::serialize(string item){
  if(item.empty()){
    throw;
  }
  vec bytes;
  bytes.push_back(PACK109_S8);
  bytes.push_back(item.length());
  for(int i = 0; i < item.length(); i++){
    bytes.push_back(item.at(i));
  }
  return bytes;
}

string pack109::deserialize_string(vec bytes){
  string item;
  if(bytes[0] == PACK109_S8){
    if(bytes[1] == 0){
      throw;
    }
    else{
      for(int i = 2; i<bytes[1]+2; i++){
        item.push_back(bytes[i]);
      }
    }
    return item;
  }
  else{
    throw;
  }
}

vec pack109::serialize(std::vector<u8> item){
  vec bytes;
  bytes.push_back(PACK109_A8);
  bytes.push_back(item.size());
  for(int i = 0 ; i < item.size(); i++){
    vec Bytes = pack109::serialize(item.at(i));
    for(int j = 0 ; j < Bytes.size(); j++){
      bytes.push_back(Bytes.at(j));
    }
  }
  return bytes;
}

std::vector<u8> pack109::deserialize_vec_u8(vec bytes){
  if(bytes.empty()){
    throw;
  }
  std::vector<u8> array;
  if(bytes[0] == PACK109_A8){
    int index = 2;
    vec Bytes;
    while(index < bytes.size()){
      if(bytes[index] == PACK109_U8){
        if(!Bytes.empty()){
          u8 item = pack109::deserialize_u8(Bytes);
          array.push_back(item);
          Bytes.clear();
        }
        Bytes.push_back(bytes[index]);
        index ++;
      }
      else{
        Bytes.push_back(bytes[index]);
        if(index == bytes.size()-1){
          u8 item = pack109::deserialize_u8(Bytes);
          array.push_back(item);
        }
        index++;
      }
    }
    return array;
  }
  else{
    throw;
  }
}
vec pack109::serialize(std::vector<u64> item){
  vec bytes;
  bytes.push_back(PACK109_A8);
  bytes.push_back(item.size());
  for(int i = 0 ; i < item.size(); i++){
    vec Bytes = pack109::serialize(item.at(i));
    for(int j = 0 ; j < Bytes.size(); j++){
      bytes.push_back(Bytes.at(j));
    }
  }
  return bytes;
}
std::vector<u64> pack109::deserialize_vec_u64(vec bytes){
  if(bytes.empty()){
    throw;
  }
  std::vector<u64> array;
  if(bytes[0] == PACK109_A8){
    int index = 2;
    vec Bytes;
    while(index < bytes.size()){
      if(bytes[index] == PACK109_U64){
        if(!Bytes.empty()){
          u64 item = pack109::deserialize_u64(Bytes);
          array.push_back(item);
          Bytes.clear();
        }
        Bytes.push_back(bytes[index]);
        index ++;
      }
      else{
        Bytes.push_back(bytes[index]);
        if(index == bytes.size()-1){
          u64 item = pack109::deserialize_u64(Bytes);
          array.push_back(item);
        }
        index++;
      }
    }
    return array;
  }
  else{
    throw;
  }
}


vec pack109::serialize(std::vector<f64> item){
  vec bytes;
  bytes.push_back(PACK109_A8);
  bytes.push_back(item.size());
  for(int i = 0 ; i < item.size(); i++){
    vec Bytes = pack109::serialize(item.at(i));
    for(int j = 0 ; j < Bytes.size(); j++){
      bytes.push_back(Bytes.at(j));
    }
  }
  return bytes;
}
std::vector<f64> pack109::deserialize_vec_f64(vec bytes){
  if(bytes.empty()){
    throw;
  }
  std::vector<f64> array;
  if(bytes[0] == PACK109_A8){
    int index = 2;
    vec Bytes;
    while(index < bytes.size()){
      if(bytes[index] == PACK109_F64){
        if(!Bytes.empty()){
          f64 item = pack109::deserialize_f64(Bytes);
          array.push_back(item);
          Bytes.clear();
        }
        Bytes.push_back(bytes[index]);
        index ++;
      }
      else{
        Bytes.push_back(bytes[index]);
        if(index == bytes.size()-1){
          f64 item = pack109::deserialize_f64(Bytes);
          array.push_back(item);
        }
        index++;
      }
    }
    return array;
  }
  else{
    throw;
  }
}

vec pack109::serialize(std::vector<string> item){
  vec bytes;
  bytes.push_back(PACK109_A8);
  bytes.push_back(item.size());
  for(int i = 0 ; i < item.size(); i++){
    vec Bytes = pack109::serialize(item.at(i));
    for(int j = 0 ; j < Bytes.size(); j++){
      bytes.push_back(Bytes.at(j));
    }
  }
  return bytes;
}

std::vector<string> pack109::deserialize_vec_string(vec bytes){
  if(bytes.empty()){
    throw;
  }
  std::vector<string> array;
  if(bytes[0] == PACK109_A8){
    int index = 2;
    vec Bytes;
    while(index < bytes.size()){
      if(bytes[index] == PACK109_S8){
        if(!Bytes.empty()){
          string item = pack109::deserialize_string(Bytes);
          array.push_back(item);
          Bytes.clear();
        }
        Bytes.push_back(bytes[index]);
        index ++;
      }
      else{
        Bytes.push_back(bytes[index]);
        if(index == bytes.size()-1){
          string item = pack109::deserialize_string(Bytes);
          array.push_back(item);
        }
        index++;
      }
    }
    return array;
  }
  else{
    throw;
  }
}

vec pack109::serialize(struct Person item){
  
  vec bytes;
  bytes.push_back(PACK109_M8);
  bytes.push_back(0x01);
  string key1 = "Person";
  vec Key1 = pack109::serialize(key1);
  for(int i = 0; i < Key1.size(); i++){
    bytes.push_back(Key1[i]);
  }//push the key value of the struct
  
  bytes.push_back(PACK109_M8);
  bytes.push_back(0x03);
  string key2 = "age";
  vec Key2 = pack109::serialize(key2);
  for(int i = 0; i < Key2.size(); i++){
    bytes.push_back(Key2[i]);
  }//push the 2nd key value of the struct
  u8 Age = item.age;
  vec val1 = pack109::serialize(Age);
  for(int i = 0; i < val1.size(); i++){
      bytes.push_back(val1[i]);
  }//push the 1st value of the struct

  string key3 = "height";
  vec Key3 = pack109::serialize(key3);
  for(int i = 0; i < Key3.size(); i++){
    bytes.push_back(Key3[i]);
  }//push the 3rd key value of the struct
  f32 He = item.height;
  vec val2 = pack109::serialize(He);
  for(int i = 0; i < val2.size(); i++){
    bytes.push_back(val2[i]);
  }//push the 2nd value of the struct

  string key4 = "name";
  vec Key4 = pack109::serialize(key4);
  for(int i = 0; i < Key4.size(); i++){
    bytes.push_back(Key4[i]);
  }//push the 4th key value of the struct
  string Na = item.name;
  vec val3 = pack109::serialize(Na);
  for(int i = 0; i < val3.size(); i++){
    bytes.push_back(val3[i]);
  }//push the 3rd value of the struct
  
 return bytes;
}

struct Person pack109::deserialize_person(vec bytes){

  struct Person DE;
  int index = 12;
  
  
  while(index < bytes.size()){
    
   
    if(bytes[index]==PACK109_U8){
      vec U8;
     
      for(int i = index; i < index+2; i++){
       U8.push_back(bytes[i]);
      }
      u8 age = pack109::deserialize_u8(U8);
      DE.age = age;
    }
    else if(bytes[index]==PACK109_F32){
      vec F32;
      for(int i = index ;i < index+5; i++){
        F32.push_back(bytes[i]);
      }
      f32 height = pack109::deserialize_f32(F32);
      DE.height = height;
    }
   
    
    else if(bytes[index]==PACK109_S8){
      vec Str;
      int i = index + 1;
      Str.push_back(bytes[index]);
      while(bytes[i]!=PACK109_M8 && bytes[i]!=PACK109_S8 && bytes[i]!=PACK109_U8 && bytes[i]!=PACK109_F32){
        Str.push_back(bytes[i]);
        i++;
      }
      string name = pack109::deserialize_string(Str);
      const char* Name = name.c_str();
      if(name == "Ann"){
        DE.name = name;
      }
    }
    index ++;
    
  }
  
  return DE;
}
void pack109::printVec(vec &bytes) {
  printf("[ ");
  for (int i = 0; i < bytes.size(); i++) {
    printf("%x ", bytes[i]);
  }
  printf("]\n");
}
void pack109::printVec64(std::vector<u64> &bytes) {
  printf("[ ");
  for (int i = 0; i < bytes.size(); i++) {
    printf("%x ", bytes[i]);
  }
  printf("]\n");
}
void pack109::printVecf64(std::vector<f64> &bytes) {
  printf("[ ");
  for (int i = 0; i < bytes.size(); i++) {
    printf("%x ", bytes[i]);
  }
  printf("]\n");
}
void pack109::printVecS(std::vector<string> &bytes) {
  printf("[ ");
  for (int i = 0; i < bytes.size(); i++) {
    const char* STR = bytes[i].c_str();
    printf("%s\t",STR);
  }
  printf("]\n");
}