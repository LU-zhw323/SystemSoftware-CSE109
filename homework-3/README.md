# CSE 109 - Homework 3

**Due Date: 2/24/2021 EOD**

## Instructions 

**Read thoroughly before starting your project:**

1. Fork this repository into your CSE109 project namespace. [Instructions](https://docs.gitlab.com/ee/workflow/forking_workflow.html#creating-a-fork)
2. Clone your newly forked repository onto your development machine. [Instructions](https://docs.gitlab.com/ee/gitlab-basics/start-using-git.html#clone-a-repository) 
3. As you are writing code you should commit patches along the way. *i.e.* don't just submit all your code in one big commit when you're all done. Commit your progress as you work. **You should make at least one commit per question.**
4. When you've committed all of your work, there's nothing left to do to submit the assignment.

## Assignment

Answer the following questions about pointers in C. Make at least one commit per question. Each question is worth 1 point for a total of 5 points for the assignment. This will be scaled to 100% for your HW grade.

### Question 1

For each problem, write the English interpretation of the given line of C code. In the provided table, give the state of the memory after the line of code is executed. You can assume each block of memory can hold up to 32 bits of memory, and that pointers are 32 bits wide. Also assume that memory is aligned to 32 bit blocks (i.e. if a variable is not large enough to fill an entire block, it still occupies the entire block). You can start your memory range at an arbitrary address for the purpose of this problem. Write the contents and memory address as a 32 bit big-endian hexadecimal number.

For instance:
```c
  // Example
  int foo = 10;
  // Interpretation: Declare an integer called foo with the value 10
  // Memory:
  //         ┌──────────┬──────────┬──────────┬──────────┐
  //    label│foo       │          │          │          │
  //         ├──────────┼──────────┼──────────┼──────────┤
  //  address│0x12345678│          │          │          │
  //         ├──────────┼──────────┼──────────┼──────────┤
  // contents│0x0000000A│          │          │          │
  //         └──────────┴──────────┴──────────┴──────────┘
```

```c
int main() {
  // Problem 1
  char* a;
  // Interpretation: Declare a array(pointer) of character(string) a without initializeing the content of it(Null pointer)
  // Memory:
  // ┌──────────┬──────────┬──────────┬──────────┐
  // │a         │          │          │          │
  // ├──────────┼──────────┼──────────┼──────────┤
  // │0x12345678│          │          │          │
  // ├──────────┼──────────┼──────────┼──────────┤
  // │          │          │          │          │
  // └──────────┴──────────┴──────────┴──────────┘
  
  
  // Problem 2
  int* b;
  // Interpretation: Declare a pointer b as an integer type without initializeing the content of it(Null pointer)
  // Memory:
  // ┌──────────┬──────────┬──────────┬──────────┐
  // │a         │b         │          │          │
  // ├──────────┼──────────┼──────────┼──────────┤
  // │0x12345678│0x12345679│          │          │
  // ├──────────┼──────────┼──────────┼──────────┤
  // │          │          │          │          │
  // └──────────┴──────────┴──────────┴──────────┘

  // Problem 3
  int c = 1632
  // Interpretation: Declare an integer variable c with a value of 1632
  // Memory:
  // ┌──────────┬──────────┬──────────┬──────────┐
  // │a         │b         │c         │          │
  // ├──────────┼──────────┼──────────┼──────────┤
  // │0x12345678│0x12345679│0x12345680│          │
  // ├──────────┼──────────┼──────────┼──────────┤
  // │          │          │0x00000660│          │
  // └──────────┴──────────┴──────────┴──────────┘

  // Problem 4
  char d = 96;
  // Interpretation:Declare a character variable d with the decimal value 96(which is equivalent to "`“ based on ASCII code)
  // Memory:
  // ┌──────────┬──────────┬──────────┬──────────┐
  // │a         │b         │c         │d         │
  // ├──────────┼──────────┼──────────┼──────────┤
  // │0x12345678│0x12345679│0x12345680│0x12345681│
  // ├──────────┼──────────┼──────────┼──────────┤
  // │          │          │0x00000660│0x00000060│
  // └──────────┴──────────┴──────────┴──────────┘

  // Problem 5
  b = &c;
  // Interpretation: seting the content of pointer b to the address of interger c
  // Memory:
  // ┌──────────┬──────────┬──────────┬──────────┐
  // │a         │b         │c         │d         │
  // ├──────────┼──────────┼──────────┼──────────┤
  // │0x12345678│0x12345679│0x12345680│0x12345681│
  // ├──────────┼──────────┼──────────┼──────────┤
  // │          │0x12345680│0x00000660│0x00000060│
  // └──────────┴──────────┴──────────┴──────────┘
  
  // Problem 6
  a = &d;
  // Interpretation: seting the content of pointer a to the address of character a
  // Memory:
  // ┌──────────┬──────────┬──────────┬──────────┐
  // │a         │b         │c         │d         │
  // ├──────────┼──────────┼──────────┼──────────┤
  // │0x12345678│0x12345679│0x12345680│0x12345681│
  // ├──────────┼──────────┼──────────┼──────────┤
  // │0x12345681│0x12345680│0x00000660│0x00000060│
  // └──────────┴──────────┴──────────┴──────────┘

  // Problem 7
  *a = *b;
  // Interpretation: seting the content of address pointed by a(d's address) to the content of address pointed by b(c'address)
  // Memory:
  // ┌──────────┬──────────┬──────────┬──────────┐
  // │a         │b         │c         │d         │
  // ├──────────┼──────────┼──────────┼──────────┤
  // │0x12345678│0x12345679│0x12345680│0x12345681│
  // ├──────────┼──────────┼──────────┼──────────┤
  // │0x12345681│0x12345680│0x00000660│0x00000660│
  // └──────────┴──────────┴──────────┴──────────┘

  return 0;
}
```

### Question 2

In a the space below, write a function with the signature `void multiply_ptrs(int* x, int* y, int* z);`.

This function returns nothing. The body of the fuction should multiply the contents of `x` and `y` and store the result in `z`. For example, you could use it like this:

```c
int z;
int x = 5;
int y = 6;
multiply_ptrs(&x,&y,&z);
// z should be 30 after the above line is executed.
```

```c
void multiply_ptrs(int* x, int* y, int* z) {
  int a = *x;
  int b = *y;
  *z = a * b;
}
```

Reproduce the above function in a file called `multiply_ptrs.c`, and include a `main()` function that demonstrates its usage.

### Question 3

Using pointer arithmatic and what you know about c-strings, implement the function `int strlen(char *str);` in the space below. This function takes a c-string and returns the number of characters in the string.

```c
int strlen(char* str) {
  int Length = 0;
  while(*str ++){
  ++ Length;
```

Reproduce the above function in a file called `strlen.c`, and include a `main()` function that demonstrates its usage.

### Question 4

In Homework 2 we used the `char** argv` argument vector to modify the behavior of a program depending on how it's called. Let's say we have a program called `a.out`, and we call it as follows:

```bash
$ ./a.out one two three
```

Conceptually we know that a double pointer like `argv` can be thought of as a 2D table. But we also know that memory only has one dimension. So what exactly does `argv` look like in memory? How can we encode a 2D table in one dimension? In the space below, write a program that will print out the memory locations of the entire `argv` datastructure. *i.e.*:

```
a[0]
a[1]
a[2]
a[3]
a[0][0]
a[0][1]
etc...
```

Start by considering specifically the example I gave above (you can hardcode numbers since you know the size of all the arguments), but then try to generalize it for any `argv`. Write your program below:

```c
int main(int argc, char** argv) {
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
```

Reproduce the above function in a file called `argv.c`.

Explain below in words how argv is laid out. Fill out a table in the style of Question 1 with actual memory addresses and values from one of your test runs. You'll probably need more columns, as the block size on your machine will be 1 byte instead of 4 as in Q1.

```
Write explanation here...
For each string(argv[i]) in the argv, they will occupy 8-bytes for each, which is 8 blocks, in the memory, and the next string(argv[i+1]) will be stored in the next memory block which is 8-bit away from the previous one. However, for the individual character(argv[i][j]) in argv[i], they will start with another address location since argv[i] is a pointer pointing to the adress of each individual character, and each one will only occupy 1 byte of memory(1 block), but the character's of next string(arv[i+1][j]) will be stored 2 byte away from the end character of previous string
┌──────────┬──────────┬──────────┬──────────┐
│argv[0]   │argv[1]   │argv[2]   │          │
├──────────┼──────────┼──────────┼──────────┤
│0xebf0fb88│0xebf0fb90│0xebf0fb98│          │
├──────────┼──────────┼──────────┼──────────┤
│./a.out   |one       |two       |          |
│0xebf0fca8│0xebf0fcb0│ebf0fcb4  │          |
└-─────────┴──────────┴──────────┴──────────┘

┌──────────┬──────────┬──────────┬──────────┐
│argv[0][0]│argv[0][1]│          │argv[0][6]│
├──────────┼──────────┼──────────┼──────────┤
│0xebf0fca8│0xebf0fca9│          │0xebf0fcae│
├──────────┼──────────┼──────────┼──────────┤
│.         │/         │          │t         │
└──────────┴──────────┴──────────┴──────────┘

┌──────────┬──────────┬──────────┬──────────┐
│argv[1][0]│argv[1][1]│          │          │
├──────────┼──────────┼──────────┼──────────┤
│0xebf0fcb0│0xebf0fcb1│          │          │
├──────────┼──────────┼──────────┼──────────┤
│o         │n         │          │          │
└──────────┴──────────┴──────────┴──────────┘
```

## Question 5

Write a `Makefile` with five directives:

1. multiply_ptrs - builds `multiply_ptrs.c` into an executable `multiply_ptrs`.
2. strlen - builds `strlen.c` into an executable `my_strlen`.
3. argv - builds `argv.c` into an executable `argv`.
4. all - builds `multiply_ptrs`, `my_strlen`, `argv`. This directive should move the binaries into `build/bin`.
5. clean - deletes `multiply_ptrs`, `my_strlen`, `argv`.
