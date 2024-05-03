# CSE 109 - Quiz 4

**Due: 3/2/2021 End of Day**

Make at least one commit per question. You can write your answers in this file, `README.md`. You can use the Gitlab interface to edit this file if you prefer.

## Question 1

How do you allocate variables to the stack? Using static allocation
How do you allocate variables to the heap? Using dynamic allocation(eg.malloc)

## Question 2

What are the pros and cons of stack allocated memory? Finite space, Fast to access, Contiguous, Automatically managed, variables have shorter life time
What are the pros and cons of heap allocated memory? Can grow due to memory demands, Slower, Fragmented, Manually Managed, Variables have longer life time 

## Question 3

Consider the following C program. The variables in this program are all stack allocated. Modify this program so that all variables are heap allocated. Make sure to free all heap allocated memory before the program ends.

```c
#include <stdio.h>
#include <stdlib.h>
double multiplyByThree(double input) {
  double thrice = (double* )malloc(8);
  if(thrice == NULL){
    exit(1);
  }
  thrice = input * 2.0;
  free(thrice);
  return thrice;
}

int main() {
  int age = (int* )malloc(4);
  if(age == NULL){
    exit(1);
  }
  age = 30;
  double salary = (double* )malloc(8);
  if(salary == NULL){
    exit(1);
  }
  salary = 12345.67;
  double myList = (double* )malloc(24);
  if(myList == NULL){
    exit(1);
  }
  myList[3] = {1.2, 2.3, 3.4};
  printf("3x your salary is %.3f\n", multiplyByThree(salary));
  free(salary);
  free(age);
  free(myList);
  return 0;
}
```

