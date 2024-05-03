# 1 "src/bin/main.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 365 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "src/bin/main.c" 2
# 1 "include/mylib.h" 1
# 1 "include/otherheader.h" 1
// This function subtracts two integers
int sub(int x, int y);
# 2 "include/mylib.h" 2

// Add two integers
int add(int x, int y);
# 2 "src/bin/main.c" 2

// This is the main function
int main(    ) {

  int x = add(1,2);
  int y = sub(3,4);
  x = x + y;

  return x;
}
