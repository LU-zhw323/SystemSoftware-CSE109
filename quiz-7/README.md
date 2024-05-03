# CSE 109 - Quiz 7

**Due: 4/8/2021 End of Day**

Make at least one commit per question. You can write your answers in this file, `README.md`. You can use the Gitlab interface to edit this file if you prefer.

## Question 1

Name the following operators and describe what they do:


- `<<` - Bitwise left shift, left shift the whole variable to the left with given bit
- `>>` - Bitwise Right shift, right shift the whole variable to the right with given bit
- `|` - Bitwise OR, input = 0|1,output = 1; input = 1|1, output = 1; input = 0|0, output = 0
- `&` -Bitwise AND, input = 0&1,output = 0; input = 1&1, output = 1; input = 0&0, output = 0
- `^` -Bitwise XOR, input = 0^1,output = 1; input = 1^1, output = 0; input = 0^0, output = 0
- `~` -Bitwise Not, input = 0~1,output = 0; input = 1~1, output = 0; input = 0~0, output = 1; input = 1~0, output = 1; For individual variable, it will turn 0 to 1, turn 1 to 0.


## Question 2

Evaluate the following expressions. Express all answers in hexadecimal. Note the below code is not specific to any language. `u32` denotes a 32 bit unsigned integer. `u8` denotes an 8 bit unsigned integer. The prefix `0b` denotes a binary literal (base 2). The prefix `0d` denotes a decimal literal (base 10). The prefix `0x` denotes a hexadecimal literal (base 16).

```rust

u32 a = 0xAB;
u8  b = 0xAB;
u8  c = 0b10110010;b2
u8  d = 0b11001011;cb
u32 e = 0d10;
u8  f = 0d20;





```

```rust
a >> 4 = 0x0000000A
b >> 4 << 4 =0x000000A0
c | d = 0xFB
c + d = 0x7D
c & d = 0xC2
c ^ d = 0x79
~d = 0x34
e << 2 = 0x000028
f >> 2 = 0x05
f << 4 = 0x40

```

## Question 3

Write an expression using binary operators and the variable `u32 x = 0xAB` to produce the number `u32 y = 0xAB2AC54`
 u32 y = x | 0x002AC54;

## Extra Credit

If you had trouble with HW6, no worries! You now have an opportunity to make up some extra points, up to 10% (Maximum of 100% for the assignment).

Write an implementation for the function `memcpy`, which copies the bytes of one pointer to another pointer.

```c
void* memcpy(void* destination, const void* source, size_t n) {
    int mask = 0x000000;
    *(destination) = (int)malloc(n);
    if(dest == NULL){
        exit(1);
    }
    *destination = *source | mask;
}

// Usage:
int x = 0x12345678;
int y = 0;
memcpy(&y,&x,4);

y == x // True;

```




