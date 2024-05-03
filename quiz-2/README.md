# CSE 109 - Quiz 2

**Due: 2/16/2021 End of Day**

Make at least one commit per question. You can write your answers in this file, `README.md`. You can use the Gitlab interface to edit this file if you prefer.

## Question 1

What are the four tenents of the Unix Philosophy? Give an example of each tenent in practice.
Make each program do one thing well
output of one program should be the input to another
build and test often and early
use tools

## Question 2

What is the purpose of a library, and why would we want to write code in a library rather than just writing all of our code in one `main.c` file? Give two reasons.
Library stores the functions that we will use in the main file. 
1, writing all the codes in the main file could make main file too cumbersome
2, It can make the whole program more readable 

## Question 3

Consider the Makefile in the [project template](https://gitlab.com/lehigh-cse-109/spring-2021/course-info/-/blob/master/project-template.zip) when answering the following:

- What is a Makefile and why would we want to use one?
  it can store and complie all the command line we need to write to complie our program, and it will change the output of main file if we change some contexts of library automatically instead of typing all the command again in the command line, which is much more convenient
- What does the command `gcc src/lib.c -c` do? In particular, what is the role of the `-c` flag in this command?
  compile library file as C file
- What does the command `ar rs -o libmylib.a lib.o` do? What is the output of this command?
  archive the lib.o file created after compileing lib.c to a binary file, and the output is libmylib.a
- What does the commnad `gcc src/bin/main.c -lmylib -L. -I include` do? In particular:
  - What is the role of the `-l` flag? link the main.c with libmylib.a
  - What is the role of the `-L` flag? What does `-L.` mean? telling where to find libmylib.a file
  - What is the role of the `-I` flag? telling where to find the host file which is my_lib.h
	
	

