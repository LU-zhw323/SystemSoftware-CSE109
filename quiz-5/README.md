# CSE 109 - Quiz 5

**Due: 3/9/2021 End of Day**

Make at least one commit per question. You can write your answers in this file, `README.md`. You can use the Gitlab interface to edit this file if you prefer.

## Question 1

What is the benefit of having multiple frontends to a compiler?
By having multiple frontends, the compiler will be abale to accept multiple different programing languages with different grammar, which will be compile as a same common format, like generic.
## Question 2

What do we mean when we say that compiling a program's source code is just translating it from one language to another?
That means that we will just transform the original source code into a stream of byte in parser, and transform futher into generic, gimple, SSA in compiler.

## Question 3

What happens during the preprocessing phase of the C compilation pipeline?

it will find the compiler directives of all the head files we included in the source code and combine all the head files with the source file, and also apply Macro Expansion.
