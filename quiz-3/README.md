# CSE 109 - Quiz 3

**Due: 2/23/2021 End of Day**

Make at least one commit per question. You can write your answers in this file, `README.md`. You can use the Gitlab interface to edit this file if you prefer.

## Question 1

Describe the purpose and usage of the following operators:

~~~
* Dereference operator, get the content of an address
& Reference operator, get the memory address of a variable
~~~

## Question 2

How are pointers and arrays equivalent in C?
Pointer will point to the address of an variable. Arrays is also a pointer(eg.char* a = "sss"). The array char* a's content will be "sss", but it is also the address of a's characters. If we apply *a, it will find the the content of the first character of a, which is 's', pointed by a.

## Question 3

What is the dofference between the following lines of code:

~~~
*foo + 1
add the content of the address pointed by foo by 1.
*(foo + 1)
find the next content of the address pointed by foo
foo[1]
= *(f+1) find the next content of the address pointed by foo
~~~

## Homework 2 Extra Credit

If you had trouble with HW2, no worries! You now have an opportunity to make up some extra points, up to 25% (Maximum of 100% for the assignment).

Answer the following question: what are the top 3 challenges you faced in completing HW2, and what is your plan for overcoming them for the future?





