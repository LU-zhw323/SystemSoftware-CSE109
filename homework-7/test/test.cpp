#include <stdexcept>
#include<vector>
#include<stdio.h>
#include<stdlib.h>
#include"pack109.hpp"

template <class T>
int test(const char* label, T lhs, T rhs) {
  printf("%s: ", label);
  if (lhs==rhs) {
    printf("Passed\n");
    return 1;
  } else {
    printf("Failed\n");
    printf("  lhs=%x\n", lhs);
    printf("  rhs=%x\n", rhs);
    exit(1);
  }
}

int testvec(const char* label, vec lhs, vec rhs) {
  printf("%s: ", label);
  if (lhs==rhs) {
    printf("Passed\n");
    return 1;
  } else {
    printf("Failed\n");
    printf("  lhs="); pack109::printVec(lhs); printf("\n");
    printf("  rhs="); pack109::printVec(rhs); printf("\n");
    exit(1);
  }
}

int testvec64(const char* label, std::vector<u64> lhs, std::vector<u64> rhs) {
  printf("%s: ", label);
  if (lhs==rhs) {
    printf("Passed\n");
    return 1;
  } else {
    printf("Failed\n");
    printf("  lhs="); pack109::printVec64(lhs); printf("\n");
    printf("  rhs="); pack109::printVec64(rhs); printf("\n");
    exit(1);
  }
}//test method for vector<u64>

int testvecf64(const char* label, std::vector<f64> lhs, std::vector<f64> rhs) {
  printf("%s: ", label);
  if (lhs==rhs) {
    printf("Passed\n");
    return 1;
  } else {
    printf("Failed\n");
    printf("  lhs="); pack109::printVecf64(lhs); printf("\n");
    printf("  rhs="); pack109::printVecf64(rhs); printf("\n");
    exit(1);
  }
}//test method for vector<f64>

int testvecS(const char* label, std::vector<string> lhs, std::vector<string> rhs) {
  printf("%s: ", label);
  if (lhs==rhs) {
    printf("Passed\n");
    return 1;
  } else {
    printf("Failed\n");
    printf("  lhs="); pack109::printVecS(lhs); printf("\n");
    printf("  rhs="); pack109::printVecS(rhs); printf("\n");
    exit(1);
  }
}//test method for vector<f64>


int main() {

  // Test bool

  // True
  vec v1{0xa0};
  vec bytes1 = pack109::serialize(true);
  testvec("Test 1 - true ser", bytes1, v1);

  bool bool_true = pack109::deserialize_bool(bytes1);
  test("Test 2 - true de", bool_true, true);
 

  // False
  vec v2{0xa1};
  vec bytes2 = pack109::serialize(false);
  testvec("Test 3 - false ser", bytes2, v2);

  bool bool_false = pack109::deserialize_bool(bytes2); 
  test("Test 4 - false de", bool_false, false);

  // Test Integers

  // u8
  u8 item1 = 0x42;
  vec v3{0xa2, 0x42};
  vec bytes3 = pack109::serialize(item1);
  testvec("Test 5 - u8 ser", bytes3, v3);
  
  u8 int_u8 = pack109::deserialize_u8(bytes3);  
  test("Test 6 - u8 de", int_u8, item1);


  // u32
  u32 item2 = 0x12345678;
  vec v4 = {0xa3,0x12,0x34,0x56,0x78};
  vec bytes4 = pack109::serialize(item2);
  testvec("Test 7 - u32 ser", bytes4, v4);

  u32 int_u32 = pack109::deserialize_u32(bytes4);
  test("Test 8 - u32 de", int_u32, item2);


  // u64
  u64 item3 = 0x1234567812345678;
  vec v5 = {0xa4,0x12,0x34,0x56,0x78,0x12,0x34,0x56,0x78};
  vec bytes5 = pack109::serialize(item3);
  testvec("Test 9 - u64 ser", bytes5, v5);
  
  u64 int_u64 = pack109::deserialize_u64(bytes5);
  test("Test 10 - u64 de", int_u64, item3);



  // i8
  i8 item4 = -66;
  vec v6 = {0xa5,0xBE};
  vec bytes6 = pack109::serialize(item4);
  testvec("Test 11 - i8 ser", bytes6, v6);

  i8 int_i8 = pack109::deserialize_i8(bytes6);
  test("Test 12 - i8 de", int_i8, item4);


  // i32
  i32 item5 = -66;//0xBE125678;
  vec v7 = {0xa6, 0xFF, 0xFF, 0xFF, 0xBE};//0xa6, 0xBE, 0x12, 0x56, 0x78
  vec bytes7 = pack109::serialize(item5);
  testvec("Test 13 - i32 ser", bytes7, v7);

  i32 int_i32 = pack109::deserialize_i32(bytes7);
  test("Test 14 - i32 de", int_i32, item5);


  // i64
  i64 item6 = -66;
  vec v8 = {0xa7, 0xFF,0xFF,0xFF,0xFF, 0xFF, 0xFF,0xFF,0xBE};
  vec bytes8 = pack109::serialize(item6);
  testvec("Test 15 - i32 ser", bytes8, v8);

  i64 int_i64 = pack109::deserialize_i64(bytes8);
  test("Test 16 - i32 de", int_i64, item6);


  // Test Float

  // f32   
  f32 num = 1.109; 
  u32* casted_num_pointer = (u32*)&num;
  //printf("%x\n",*casted_num_pointer);
  vec v9 = {0xa8,0x3f,0x8d,0xf3,0xb6};
  vec bytes9 = pack109::serialize(num);
  testvec("Test 17 - f32 ser", bytes9, v9);

  f32 int_f32 = pack109::deserialize_f32(bytes9);
  test("Test 18 - f32 de", int_f32, num);
  
  // f64
  f64 item8 = 1.109;
  u64* cop = (u64*)&item8;
  //printf("%x\n",*cop);
  vec v10 = {0xa9,0x3f,0xf1,0xbe,0x76,0xc8,0xb4,0x39,0x58};
  vec bytes10 = pack109::serialize(item8);
  testvec("Test 19 - f64 ser", bytes10, v10);

  f64 int_f64 = pack109::deserialize_f64(bytes10);
  test("Test 20 - f64 de", int_f64, item8);


  // Test Strings

  // s8
  string item9 = "Hello";
  u8 len = item9.length();
  vec v11 = {0xaa,0x5,'H','e','l','l','o'};
  vec bytes11 = pack109::serialize(item9);
  testvec("Test 21 - s8 ser", bytes11, v11);

  string str = pack109::deserialize_string(bytes11);
  printf("Test 22 - s8 de: ");
  if(str == item9){
    printf("Passed\n");
  }
  else{
    const char* STR = str.c_str();
    const char* Item9 = item9.c_str();
    printf("lhs: %s\n",STR);
    printf("rhs: %s\n", Item9);
  }
  
  

  // Test Arrays

  // a8 for u8
  u8 element1 = 0x42;
  u8 element2 = 0x11;
  std::vector<u8> array1;
  array1 = {element1, element2};
  vec v12 = {0xac, 0x02, 0xa2,0x42,0xa2,0x11};
  vec bytes12 = pack109::serialize(array1);
  testvec("Test 23 - a8 for u8 ser", bytes12, v12);

  std::vector<u8> Array1 = pack109::deserialize_vec_u8(bytes12);
  testvec("Test 24 - a8 for u8 de", Array1, array1);


  // a8 for u64
  u64 e3 = 0x42;
  u64 e4 = 0x11;
  std::vector<u64> array2;
  array2 = {e3, e4};
  vec v13 = {0xac, 0x02,0xa4, 0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x42,0xa4,0x00,0x00,0x00,0x00,0x00,0x00,0x00,0x11};
  vec bytes13 = pack109::serialize(array2);
  testvec("Test 25 - a8 for u64 ser", bytes13, v13);

  std::vector<u64> Array2 = pack109::deserialize_vec_u64(bytes13);
  testvec64("Test 26 - a8 for u64 de", Array2, array2);


  // a8 for f64
  f64 e5 = 1.109;
  f64 e6 = 2.109;
  std::vector<f64> array3;
  array3 = {e5, e6};
  vec v14 = {0xac, 0x02, 0xa9,0x3f,0xf1,0xbe,0x76,0xc8,0xb4,0x39,0x58,0xa9, 0x40,0x00,0xDF,0x3B,0x64,0x5A,0x1C,0xAC};
  vec bytes14 = pack109::serialize(array3);
  testvec("Test 27 - a8 for f64 ser", bytes14, v14);

  std::vector<f64> Array3 = pack109::deserialize_vec_f64(bytes14);
  testvecf64("Test 28 - a8 for f64 de", Array3, array3);


  // a8 for string
  string s1 = "Hello";
  string s2 = "World";
  std::vector<string> array4;
  array4 = {s1,s2};
  vec v15 = {0xac, 0x02, 0xaa,0x5,'H','e','l','l','o', 0xaa,0x05,'W','o','r','l','d'};
  vec bytes15 = pack109::serialize(array4);
  testvec("Test 29 - a8 for string ser", bytes14, v14);

  std::vector<string> Array4 = pack109::deserialize_vec_string(bytes15);
  testvecS("Test 30 - a9 for string de", Array4, array4);
 

  // Test Maps

  // m8
  struct Person ann = { age:10, height:1.109, name:"Ann" };//u8 , f32, string 0xa8,0x3f,0x8d,0xf3,0xb6
  vec bytes16 = pack109::serialize(ann);
  vec v16 = {0xae,0x01, 0xaa,0x06,'P','e','r','s','o','n',0xae,0x03,0xaa,0x03,'a','g','e',0xa2,0x0a,0xaa,0x06,'h','e','i','g','h','t',0xa8,0x3f,0x8d,0xf3,0xb6,0xaa,0x04,'n','a','m','e',0xaa,0x03,'A','n','n'};
  testvec("Test 31 - m8 ser", bytes16, v16);//12
  
  struct Person DE = pack109::deserialize_person(bytes16);
  
  if(DE.age==ann.age && DE.height==ann.height && DE.name==ann.name){
    printf("Test 32 - m8 de: Passed\n");
  }
  else{
    printf("Test 32 - m8 de: Failed\n");
  }

  return 0;
}