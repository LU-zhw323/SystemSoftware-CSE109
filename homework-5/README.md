# CSE 109 - Homework 5

**Due Date: 3/12/2021 EOD**

## Instructions 

**Read thoroughly before starting your project:**

1. Fork this repository into your CSE109 project namespace. [Instructions](https://docs.gitlab.com/ee/workflow/forking_workflow.html#creating-a-fork)
2. Clone your newly forked repository onto your development machine. [Instructions](https://docs.gitlab.com/ee/gitlab-basics/start-using-git.html#clone-a-repository) 
3. As you are writing code you should commit patches along the way. *i.e.* don't just submit all your code in one big commit when you're all done. Commit your progress as you work. **You should make at least one commit per question.**
4. When you've committed all of your work, there's nothing left to do to submit the assignment.

## Assignment

In this assignment we will explore the C GCC compilation pipeline. I've defined a simple C program in the project directory. Take a moment before starting to familiarize yourself with the files in the `src` and `include` directories. We are going to compile `main.c` into an executable `main`, and `lib1.c`/`lib2.c` into a library `libmylib.a`. The executable `main` will link to `libmylib.a`. You've done this several times already with the gcc command, but as we've learned in class, gcc is really a series of programs that are interconnected. In this assignment we will decompose the process into a number of different steps. Those steps are:

1. The C preprocessor - cpp
2. The C frontend - cc
3. The assembler - as
4. The linker - ld

As you go through this assignment you will generate a number of intermediate files. Usually I implore you not to commit compiler artifacts to your git repositories, but for this assignment the whole point is to generate and analyze these artifacts, so do commit them this time. They will have the extensions `.i`, `.s`, `.o`, and `.a`. In Part 1 will ask you to generate some files of the form `main.i.NNNt.*`. Save these to your repository as well. You should keep them all in the project root.

Here is a short reference of what the various file types mean:

- `.h` - C Header file
- `.c` - C Source
- `.i` - C preprocesor output
- `.s` - Assembly
- `.o` - Object Code
- `.a` - Object Archive

For this assignment, I ask you to make a number of observations about things we haven't covered in detail, and to form an inference from what you observe. Your objective for these questions is not to get the right answer (although it's fine if you do), but to form a well-reasoned response based on what we have studied. Getting the question wrong is fine as long as you do so thoughtfully. You will be graded on the clarity of your reasoning, and your ability to pull in knowledge from what we have studied in class.

### Part 1 - Exploring The C Preprocessor

The C preprocessor can be called directly by invoking the command `cpp` from the command line with a target input file. For example:

```bash
$ cpp main.c
```

Use the `cpp` command to preprocess `/src/bin/main.c`. You will have to use the `-I` flag in the usual way to tell the preprocessor where to find `mylib.h`. Save the result to a file in the project root directory called `main.i` (you can use the [`>` bash operator](https://www.linux.com/topic/desktop/understanding-angle-brackets-bash/) in the terminal to do this).

**Question 1:** How many bytes are in the source file?
134 bytes
**Question 2:** How many bytes are in `main.i`? What happened in `cpp` to cause this difference?
264 bytes, as the cpp would find both two header files,mylib.h and otherheader.h, and combine them with source file.
**Question 3:** List all the differences you see between `main.c` and `main.i`.
  main.i includes some steps of preprocessing at the begining of the file, like "include/mylib.h"
  main.i also includes the functions in the headerfiles at the begining of the file.
  they both include the main function
### Part 2 - Exploring The C Frontend

We can call the C frontend directly by invoking the command `cc` from the command line, with the target input file being the output we got from `main.i`. When you invoke `cc`, it transforms the input program into a number of internal states. We can take a look at some of these states with a collection of flags named `-fdump-*`.

The `cc` command will automatically invoke the assembler, which we can short-circuit with the `-S` flag to see the assembly output.

(you can do Questions 4-7 in one command)

**Question 4:** Use the `cc` command to compile `main.i`, into `main.s`, the contents of which is `main.c` represented in human-readable assembly language.

**Question 5:** Use the `-fdump-tree-gimple` flag to output the Gimple intermediate representation.

**Question 6:** Use the `-fdump-tree-ssa` flag to output the SSA intermediate representation.

**Question 7:** Use the `-fdump-rtl-expand` flag to output the first RTL intermediate representation.

**Question 8:** Use the `-fdump-rtl-dfinish` flag to output the final RTL intermediate representation.

**Question 9:** On my machine, the files generated are:

- main.i.004t.gimple
- main.i.018t.ssa
- main.i.192t.expand
- main.i.270t.dfinish

What do you think the number in the file names might indicate?
The sequence of intermediate representation
**Question 10:** Consider `main.i` and the Gimple intermediate representation. What has changed between these two files?
Two functions in the main.i disappeared. In Gimple, there is an integer variable D.1809 which is used to represent the result of x + y
**Question 11:** Consider the Gimple and SSA intermediate representations. What has changed between these two files?
In SSA, it includes different symbol for the copies of x and y, which reassigns the value of x and y for multiple times.
**Question 12:** Consider the SSA and RTL-expand intermediate representations. Why do you think the RTL representation is so much larger than the SSA representation?
RTL is the object code with infinite register. Thus, it will be big enough to have a lot amount of registers to hold all the variables in the file.
**Question 13:** Now take a look at the assembly code in the `main.s` file. It's okay that you don't know what this does, that's a topic for CSE202. But as you look at this file, remember the [Rosetta Stone](https://en.wikipedia.org/wiki/Rosetta_Stone). The people who studied this stone were able to use their knowledge of Greek to decode the meaning behind the hieroglyphics by making connections between the two languages. Try to use your knowledge of C to decode the meaning behind some of the assembly in `main.s`. There are wrong answers here (this question will be graded on your reasoning, not on accuracy).
From line 1 to line 4, it is just setting the file and functions. pushq %rbp is to push a quad word into register rbp. movq %rsp %rbp is to move a quad word from register rsp to rbp. subq $4 %rsp is to subtract 4 from register rsp. movl	$0, -4(%rbp) is to move 0 into the memory of (%rbp - 4). movl	$1, %edi is to move 1 into the least significan byte of register rdi, same as other move instructions. callq	_add is to call the function add, and callq _sub is to call the function subtract. addl	-12(%rbp), %eax is to add the content in memory of (rbp - 12) to the register rax and store the result in rax. popq	%rbp is to pop the value stored in register rbq out from stack. retq is the return.

### Part 3 - Exploring the Assembler

The assembler can be called directly using the command `as`. The input to the assembler will be the assembly file from Part 2. The assembler will convert this assembly code into platform specific object code. Normally, `as` will call the linker `ld` after this step to generate an executable, but we can prevent that using the `-c` flag.

**Question 14:** Use `as` to turn `main.s` into `main.o`.

**Question 15:** A `.o` file is known as an object file because it contains platform-specific object code. We can take a look at this code using the `hexdump` command with the `-C` flag. Do this in your console and reproduce the results below:

**main.o:**
```
Paste hexdump of main.o here
00000000  cf fa ed fe 07 00 00 01  03 00 00 00 01 00 00 00  |................|
00000010  04 00 00 00 b8 01 00 00  00 20 00 00 00 00 00 00  |......... ......|
00000020  19 00 00 00 38 01 00 00  00 00 00 00 00 00 00 00  |....8...........|
00000030  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
00000040  a8 00 00 00 00 00 00 00  d8 01 00 00 00 00 00 00  |................|
00000050  a8 00 00 00 00 00 00 00  07 00 00 00 07 00 00 00  |................|
00000060  03 00 00 00 00 00 00 00  5f 5f 74 65 78 74 00 00  |........__text..|
00000070  00 00 00 00 00 00 00 00  5f 5f 54 45 58 54 00 00  |........__TEXT..|
00000080  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
00000090  45 00 00 00 00 00 00 00  d8 01 00 00 04 00 00 00  |E...............|
000000a0  80 02 00 00 02 00 00 00  00 04 00 80 00 00 00 00  |................|
000000b0  00 00 00 00 00 00 00 00  5f 5f 63 6f 6d 70 61 63  |........__compac|
000000c0  74 5f 75 6e 77 69 6e 64  5f 5f 4c 44 00 00 00 00  |t_unwind__LD....|
000000d0  00 00 00 00 00 00 00 00  48 00 00 00 00 00 00 00  |........H.......|
000000e0  20 00 00 00 00 00 00 00  20 02 00 00 03 00 00 00  | ....... .......|
000000f0  90 02 00 00 01 00 00 00  00 00 00 02 00 00 00 00  |................|
00000100  00 00 00 00 00 00 00 00  5f 5f 65 68 5f 66 72 61  |........__eh_fra|
00000110  6d 65 00 00 00 00 00 00  5f 5f 54 45 58 54 00 00  |me......__TEXT..|
00000120  00 00 00 00 00 00 00 00  68 00 00 00 00 00 00 00  |........h.......|
00000130  40 00 00 00 00 00 00 00  40 02 00 00 03 00 00 00  |@.......@.......|
00000140  00 00 00 00 00 00 00 00  0b 00 00 68 00 00 00 00  |...........h....|
00000150  00 00 00 00 00 00 00 00  32 00 00 00 18 00 00 00  |........2.......|
00000160  01 00 00 00 00 00 0b 00  00 01 0b 00 00 00 00 00  |................|
00000170  02 00 00 00 18 00 00 00  98 02 00 00 03 00 00 00  |................|
00000180  c8 02 00 00 14 00 00 00  0b 00 00 00 50 00 00 00  |............P...|
00000190  00 00 00 00 00 00 00 00  00 00 00 00 01 00 00 00  |................|
000001a0  01 00 00 00 02 00 00 00  00 00 00 00 00 00 00 00  |................|
000001b0  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
*
000001d0  00 00 00 00 00 00 00 00  55 48 89 e5 48 83 ec 10  |........UH..H...|
000001e0  c7 45 fc 00 00 00 00 bf  01 00 00 00 be 02 00 00  |.E..............|
000001f0  00 e8 00 00 00 00 89 45  f8 bf 03 00 00 00 be 04  |.......E........|
00000200  00 00 00 e8 00 00 00 00  89 45 f4 8b 45 f8 03 45  |.........E..E..E|
00000210  f4 89 45 f8 8b 45 f8 48  83 c4 10 5d c3 00 00 00  |..E..E.H...]....|
00000220  00 00 00 00 00 00 00 00  45 00 00 00 00 00 00 01  |........E.......|
00000230  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
00000240  14 00 00 00 00 00 00 00  01 7a 52 00 01 78 10 01  |.........zR..x..|
00000250  10 0c 07 08 90 01 00 00  24 00 00 00 1c 00 00 00  |........$.......|
00000260  78 ff ff ff ff ff ff ff  45 00 00 00 00 00 00 00  |x.......E.......|
00000270  00 41 0e 10 86 02 43 0d  06 00 00 00 00 00 00 00  |.A....C.........|
00000280  2c 00 00 00 02 00 00 2d  1a 00 00 00 01 00 00 2d  |,......-.......-|
00000290  00 00 00 00 01 00 00 06  01 00 00 00 0f 01 00 00  |................|
000002a0  00 00 00 00 00 00 00 00  07 00 00 00 01 00 00 00  |................|
000002b0  00 00 00 00 00 00 00 00  0c 00 00 00 01 00 00 00  |................|
000002c0  00 00 00 00 00 00 00 00  00 5f 6d 61 69 6e 00 5f  |........._main._|
000002d0  61 64 64 00 5f 73 75 62  00 00 00 00              |add._sub....|
000002dc
```

We'll learn more about this later in the course. For now, just looking at it, what observations do you make? Are you able to draw any connections between the hexdump and the C and assembly code?

### Part 4 - Building a Library

Now that we've gone through the process of turning a source file into an object file, we need to link to the library code on which it depends. To do that, we need to repeat the build process for `mylib1.c` and `mylib2.c`.

**Question 16:** Go through the process of turning `mylib1.c` into `mylib2.o` by following the steps in parts 1 through 3. You'll need to build the following files (you can skip the Gimple/SSA/RTL intermediate representations):

- mylib1.i
- mylib1.s
- mylib1.o
- mylib2.i
- mylib2.s
- mylib2.o

**Question 17:** Use `hexdump -C` to take a look at the object code within `mylib1.o` and `mylib2.o`. Paste the output of each below:

**mylib1.o:**
```
Paste hexdump of mylib1.o here
00000000  cf fa ed fe 07 00 00 01  03 00 00 00 01 00 00 00  |................|
00000010  04 00 00 00 b8 01 00 00  00 20 00 00 00 00 00 00  |......... ......|
00000020  19 00 00 00 38 01 00 00  00 00 00 00 00 00 00 00  |....8...........|
00000030  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
00000040  78 00 00 00 00 00 00 00  d8 01 00 00 00 00 00 00  |x...............|
00000050  78 00 00 00 00 00 00 00  07 00 00 00 07 00 00 00  |x...............|
00000060  03 00 00 00 00 00 00 00  5f 5f 74 65 78 74 00 00  |........__text..|
00000070  00 00 00 00 00 00 00 00  5f 5f 54 45 58 54 00 00  |........__TEXT..|
00000080  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
00000090  12 00 00 00 00 00 00 00  d8 01 00 00 04 00 00 00  |................|
000000a0  00 00 00 00 00 00 00 00  00 04 00 80 00 00 00 00  |................|
000000b0  00 00 00 00 00 00 00 00  5f 5f 63 6f 6d 70 61 63  |........__compac|
000000c0  74 5f 75 6e 77 69 6e 64  5f 5f 4c 44 00 00 00 00  |t_unwind__LD....|
000000d0  00 00 00 00 00 00 00 00  18 00 00 00 00 00 00 00  |................|
000000e0  20 00 00 00 00 00 00 00  f0 01 00 00 03 00 00 00  | ...............|
000000f0  50 02 00 00 01 00 00 00  00 00 00 02 00 00 00 00  |P...............|
00000100  00 00 00 00 00 00 00 00  5f 5f 65 68 5f 66 72 61  |........__eh_fra|
00000110  6d 65 00 00 00 00 00 00  5f 5f 54 45 58 54 00 00  |me......__TEXT..|
00000120  00 00 00 00 00 00 00 00  38 00 00 00 00 00 00 00  |........8.......|
00000130  40 00 00 00 00 00 00 00  10 02 00 00 03 00 00 00  |@...............|
00000140  00 00 00 00 00 00 00 00  0b 00 00 68 00 00 00 00  |...........h....|
00000150  00 00 00 00 00 00 00 00  32 00 00 00 18 00 00 00  |........2.......|
00000160  01 00 00 00 00 00 0b 00  00 01 0b 00 00 00 00 00  |................|
00000170  02 00 00 00 18 00 00 00  58 02 00 00 01 00 00 00  |........X.......|
00000180  68 02 00 00 08 00 00 00  0b 00 00 00 50 00 00 00  |h...........P...|
00000190  00 00 00 00 00 00 00 00  00 00 00 00 01 00 00 00  |................|
000001a0  01 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
000001b0  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
*
000001d0  00 00 00 00 00 00 00 00  55 48 89 e5 89 7d fc 89  |........UH...}..|
000001e0  75 f8 8b 45 fc 03 45 f8  5d c3 00 00 00 00 00 00  |u..E..E.].......|
000001f0  00 00 00 00 00 00 00 00  12 00 00 00 00 00 00 01  |................|
00000200  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
00000210  14 00 00 00 00 00 00 00  01 7a 52 00 01 78 10 01  |.........zR..x..|
00000220  10 0c 07 08 90 01 00 00  24 00 00 00 1c 00 00 00  |........$.......|
00000230  a8 ff ff ff ff ff ff ff  12 00 00 00 00 00 00 00  |................|
00000240  00 41 0e 10 86 02 43 0d  06 00 00 00 00 00 00 00  |.A....C.........|
00000250  00 00 00 00 01 00 00 06  01 00 00 00 0f 01 00 00  |................|
00000260  00 00 00 00 00 00 00 00  00 5f 61 64 64 00 00 00  |........._add...|
00000270
```
**mylib2.o:**
```
Paste hexdump of mylib2.o here
00000000  cf fa ed fe 07 00 00 01  03 00 00 00 01 00 00 00  |................|
00000010  04 00 00 00 b8 01 00 00  00 20 00 00 00 00 00 00  |......... ......|
00000020  19 00 00 00 38 01 00 00  00 00 00 00 00 00 00 00  |....8...........|
00000030  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
00000040  78 00 00 00 00 00 00 00  d8 01 00 00 00 00 00 00  |x...............|
00000050  78 00 00 00 00 00 00 00  07 00 00 00 07 00 00 00  |x...............|
00000060  03 00 00 00 00 00 00 00  5f 5f 74 65 78 74 00 00  |........__text..|
00000070  00 00 00 00 00 00 00 00  5f 5f 54 45 58 54 00 00  |........__TEXT..|
00000080  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
00000090  12 00 00 00 00 00 00 00  d8 01 00 00 04 00 00 00  |................|
000000a0  00 00 00 00 00 00 00 00  00 04 00 80 00 00 00 00  |................|
000000b0  00 00 00 00 00 00 00 00  5f 5f 63 6f 6d 70 61 63  |........__compac|
000000c0  74 5f 75 6e 77 69 6e 64  5f 5f 4c 44 00 00 00 00  |t_unwind__LD....|
000000d0  00 00 00 00 00 00 00 00  18 00 00 00 00 00 00 00  |................|
000000e0  20 00 00 00 00 00 00 00  f0 01 00 00 03 00 00 00  | ...............|
000000f0  50 02 00 00 01 00 00 00  00 00 00 02 00 00 00 00  |P...............|
00000100  00 00 00 00 00 00 00 00  5f 5f 65 68 5f 66 72 61  |........__eh_fra|
00000110  6d 65 00 00 00 00 00 00  5f 5f 54 45 58 54 00 00  |me......__TEXT..|
00000120  00 00 00 00 00 00 00 00  38 00 00 00 00 00 00 00  |........8.......|
00000130  40 00 00 00 00 00 00 00  10 02 00 00 03 00 00 00  |@...............|
00000140  00 00 00 00 00 00 00 00  0b 00 00 68 00 00 00 00  |...........h....|
00000150  00 00 00 00 00 00 00 00  32 00 00 00 18 00 00 00  |........2.......|
00000160  01 00 00 00 00 00 0b 00  00 01 0b 00 00 00 00 00  |................|
00000170  02 00 00 00 18 00 00 00  58 02 00 00 01 00 00 00  |........X.......|
00000180  68 02 00 00 08 00 00 00  0b 00 00 00 50 00 00 00  |h...........P...|
00000190  00 00 00 00 00 00 00 00  00 00 00 00 01 00 00 00  |................|
000001a0  01 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
000001b0  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
*
000001d0  00 00 00 00 00 00 00 00  55 48 89 e5 89 7d fc 89  |........UH...}..|
000001e0  75 f8 8b 45 fc 2b 45 f8  5d c3 00 00 00 00 00 00  |u..E.+E.].......|
000001f0  00 00 00 00 00 00 00 00  12 00 00 00 00 00 00 01  |................|
00000200  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
00000210  14 00 00 00 00 00 00 00  01 7a 52 00 01 78 10 01  |.........zR..x..|
00000220  10 0c 07 08 90 01 00 00  24 00 00 00 1c 00 00 00  |........$.......|
00000230  a8 ff ff ff ff ff ff ff  12 00 00 00 00 00 00 00  |................|
00000240  00 41 0e 10 86 02 43 0d  06 00 00 00 00 00 00 00  |.A....C.........|
00000250  00 00 00 00 01 00 00 06  01 00 00 00 0f 01 00 00  |................|
00000260  00 00 00 00 00 00 00 00  00 5f 73 75 62 00 00 00  |........._sub...|
00000270
```

**Question 18:** Using `ar`, package `mylib1.o` and `mylib2.o` into a static library called `libmylib.a`.

**Question 19:** Now use `hexdump -C` to inspect the contents of `libmylib.a`. Paste the output in the space below.

**libmylib.a:**
```
Paste hexdump of libmylib.a here
00000000  21 3c 61 72 63 68 3e 0a  23 31 2f 32 30 20 20 20  |!<arch>.#1/20   |
00000010  20 20 20 20 20 20 20 20  31 36 31 35 31 33 37 31  |        16151371|
00000020  31 31 20 20 35 30 31 20  20 20 32 30 20 20 20 20  |11  501   20    |
00000030  31 30 30 36 34 34 20 20  36 30 20 20 20 20 20 20  |100644  60      |
00000040  20 20 60 0a 5f 5f 2e 53  59 4d 44 45 46 20 53 4f  |  `.__.SYMDEF SO|
00000050  52 54 45 44 00 00 00 00  10 00 00 00 00 00 00 00  |RTED............|
00000060  80 00 00 00 05 00 00 00  38 03 00 00 10 00 00 00  |........8.......|
00000070  5f 61 64 64 00 5f 73 75  62 00 00 00 00 00 00 00  |_add._sub.......|
00000080  23 31 2f 31 32 20 20 20  20 20 20 20 20 20 20 20  |#1/12           |
00000090  31 36 31 35 31 33 34 31  32 39 20 20 35 30 31 20  |1615134129  501 |
000000a0  20 20 32 30 20 20 20 20  31 30 30 36 34 34 20 20  |  20    100644  |
000000b0  36 33 36 20 20 20 20 20  20 20 60 0a 6d 79 6c 69  |636       `.myli|
000000c0  62 31 2e 6f 00 00 00 00  cf fa ed fe 07 00 00 01  |b1.o............|
000000d0  03 00 00 00 01 00 00 00  04 00 00 00 b8 01 00 00  |................|
000000e0  00 20 00 00 00 00 00 00  19 00 00 00 38 01 00 00  |. ..........8...|
000000f0  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
00000100  00 00 00 00 00 00 00 00  78 00 00 00 00 00 00 00  |........x.......|
00000110  d8 01 00 00 00 00 00 00  78 00 00 00 00 00 00 00  |........x.......|
00000120  07 00 00 00 07 00 00 00  03 00 00 00 00 00 00 00  |................|
00000130  5f 5f 74 65 78 74 00 00  00 00 00 00 00 00 00 00  |__text..........|
00000140  5f 5f 54 45 58 54 00 00  00 00 00 00 00 00 00 00  |__TEXT..........|
00000150  00 00 00 00 00 00 00 00  12 00 00 00 00 00 00 00  |................|
00000160  d8 01 00 00 04 00 00 00  00 00 00 00 00 00 00 00  |................|
00000170  00 04 00 80 00 00 00 00  00 00 00 00 00 00 00 00  |................|
00000180  5f 5f 63 6f 6d 70 61 63  74 5f 75 6e 77 69 6e 64  |__compact_unwind|
00000190  5f 5f 4c 44 00 00 00 00  00 00 00 00 00 00 00 00  |__LD............|
000001a0  18 00 00 00 00 00 00 00  20 00 00 00 00 00 00 00  |........ .......|
000001b0  f0 01 00 00 03 00 00 00  50 02 00 00 01 00 00 00  |........P.......|
000001c0  00 00 00 02 00 00 00 00  00 00 00 00 00 00 00 00  |................|
000001d0  5f 5f 65 68 5f 66 72 61  6d 65 00 00 00 00 00 00  |__eh_frame......|
000001e0  5f 5f 54 45 58 54 00 00  00 00 00 00 00 00 00 00  |__TEXT..........|
000001f0  38 00 00 00 00 00 00 00  40 00 00 00 00 00 00 00  |8.......@.......|
00000200  10 02 00 00 03 00 00 00  00 00 00 00 00 00 00 00  |................|
00000210  0b 00 00 68 00 00 00 00  00 00 00 00 00 00 00 00  |...h............|
00000220  32 00 00 00 18 00 00 00  01 00 00 00 00 00 0b 00  |2...............|
00000230  00 01 0b 00 00 00 00 00  02 00 00 00 18 00 00 00  |................|
00000240  58 02 00 00 01 00 00 00  68 02 00 00 08 00 00 00  |X.......h.......|
00000250  0b 00 00 00 50 00 00 00  00 00 00 00 00 00 00 00  |....P...........|
00000260  00 00 00 00 01 00 00 00  01 00 00 00 00 00 00 00  |................|
00000270  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
*
000002a0  55 48 89 e5 89 7d fc 89  75 f8 8b 45 fc 03 45 f8  |UH...}..u..E..E.|
000002b0  5d c3 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |]...............|
000002c0  12 00 00 00 00 00 00 01  00 00 00 00 00 00 00 00  |................|
000002d0  00 00 00 00 00 00 00 00  14 00 00 00 00 00 00 00  |................|
000002e0  01 7a 52 00 01 78 10 01  10 0c 07 08 90 01 00 00  |.zR..x..........|
000002f0  24 00 00 00 1c 00 00 00  a8 ff ff ff ff ff ff ff  |$...............|
00000300  12 00 00 00 00 00 00 00  00 41 0e 10 86 02 43 0d  |.........A....C.|
00000310  06 00 00 00 00 00 00 00  00 00 00 00 01 00 00 06  |................|
00000320  01 00 00 00 0f 01 00 00  00 00 00 00 00 00 00 00  |................|
00000330  00 5f 61 64 64 00 00 00  23 31 2f 31 32 20 20 20  |._add...#1/12   |
00000340  20 20 20 20 20 20 20 20  31 36 31 35 31 33 34 31  |        16151341|
00000350  38 32 20 20 35 30 31 20  20 20 32 30 20 20 20 20  |82  501   20    |
00000360  31 30 30 36 34 34 20 20  36 33 36 20 20 20 20 20  |100644  636     |
00000370  20 20 60 0a 6d 79 6c 69  62 32 2e 6f 00 00 00 00  |  `.mylib2.o....|
00000380  cf fa ed fe 07 00 00 01  03 00 00 00 01 00 00 00  |................|
00000390  04 00 00 00 b8 01 00 00  00 20 00 00 00 00 00 00  |......... ......|
000003a0  19 00 00 00 38 01 00 00  00 00 00 00 00 00 00 00  |....8...........|
000003b0  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
000003c0  78 00 00 00 00 00 00 00  d8 01 00 00 00 00 00 00  |x...............|
000003d0  78 00 00 00 00 00 00 00  07 00 00 00 07 00 00 00  |x...............|
000003e0  03 00 00 00 00 00 00 00  5f 5f 74 65 78 74 00 00  |........__text..|
000003f0  00 00 00 00 00 00 00 00  5f 5f 54 45 58 54 00 00  |........__TEXT..|
00000400  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
00000410  12 00 00 00 00 00 00 00  d8 01 00 00 04 00 00 00  |................|
00000420  00 00 00 00 00 00 00 00  00 04 00 80 00 00 00 00  |................|
00000430  00 00 00 00 00 00 00 00  5f 5f 63 6f 6d 70 61 63  |........__compac|
00000440  74 5f 75 6e 77 69 6e 64  5f 5f 4c 44 00 00 00 00  |t_unwind__LD....|
00000450  00 00 00 00 00 00 00 00  18 00 00 00 00 00 00 00  |................|
00000460  20 00 00 00 00 00 00 00  f0 01 00 00 03 00 00 00  | ...............|
00000470  50 02 00 00 01 00 00 00  00 00 00 02 00 00 00 00  |P...............|
00000480  00 00 00 00 00 00 00 00  5f 5f 65 68 5f 66 72 61  |........__eh_fra|
00000490  6d 65 00 00 00 00 00 00  5f 5f 54 45 58 54 00 00  |me......__TEXT..|
000004a0  00 00 00 00 00 00 00 00  38 00 00 00 00 00 00 00  |........8.......|
000004b0  40 00 00 00 00 00 00 00  10 02 00 00 03 00 00 00  |@...............|
000004c0  00 00 00 00 00 00 00 00  0b 00 00 68 00 00 00 00  |...........h....|
000004d0  00 00 00 00 00 00 00 00  32 00 00 00 18 00 00 00  |........2.......|
000004e0  01 00 00 00 00 00 0b 00  00 01 0b 00 00 00 00 00  |................|
000004f0  02 00 00 00 18 00 00 00  58 02 00 00 01 00 00 00  |........X.......|
00000500  68 02 00 00 08 00 00 00  0b 00 00 00 50 00 00 00  |h...........P...|
00000510  00 00 00 00 00 00 00 00  00 00 00 00 01 00 00 00  |................|
00000520  01 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
00000530  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
*
00000550  00 00 00 00 00 00 00 00  55 48 89 e5 89 7d fc 89  |........UH...}..|
00000560  75 f8 8b 45 fc 2b 45 f8  5d c3 00 00 00 00 00 00  |u..E.+E.].......|
00000570  00 00 00 00 00 00 00 00  12 00 00 00 00 00 00 01  |................|
00000580  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
00000590  14 00 00 00 00 00 00 00  01 7a 52 00 01 78 10 01  |.........zR..x..|
000005a0  10 0c 07 08 90 01 00 00  24 00 00 00 1c 00 00 00  |........$.......|
000005b0  a8 ff ff ff ff ff ff ff  12 00 00 00 00 00 00 00  |................|
000005c0  00 41 0e 10 86 02 43 0d  06 00 00 00 00 00 00 00  |.A....C.........|
000005d0  00 00 00 00 01 00 00 06  01 00 00 00 0f 01 00 00  |................|
000005e0  00 00 00 00 00 00 00 00  00 5f 73 75 62 00 00 00  |........._sub...|
000005f0
```

**Question 20:** Compare the hexdumps of `mylib1.o`, `mylib2.o`, and `libmylib.a`. What do you notice? How many bytes are in `mylib1.o`? How many are in `mylib2.o`? How many are in `libmylib.a`? Based on your comparison, what do you think the extra bytes are doing in `libmylib.a`?
The hexdump of libmylib.a is quite likely to be the hexdump of mylib1.o + hexdump of mylib2.o.  mylib2.o is 624 bytes, mylib1.o is 624 bytes as well, and 1520 bytes. Since libmylib.a is an executable file including both two object files, I assume that it should not only include two object files, but it will also use some extra bytes to include something that make it executable.

### Part 5 - Building an Executable

We now have everything we need to build our executable. The `gcc` linker is a program called `ld`, and you can invoke the linker manually with the `ld` command in the terminal. But we won't use this command directly to build our executable, because doing so requires a number of arguments that are specific to the way your machine is configured. Therefore it's hard for me to provide generic instructions to do this as it might be different depending on your operating system and environment. Instead, we will invoke `gcc` which will call `ld` with the appropriate configuration options.

**Question 21:** Use `gcc` to combine `main.o` with `libmylib.a` to generate an executable named `main`.

**Question 22:** Use `hexdump -C` to take a look at hte object code within `main` and paste the output below:

```
Paste hexdump of main here
00000000  21 3c 61 72 63 68 3e 0a  23 31 2f 32 30 20 20 20  |!<arch>.#1/20   |
00000010  20 20 20 20 20 20 20 20  31 36 31 35 31 33 37 31  |        16151371|
00000020  31 31 20 20 35 30 31 20  20 20 32 30 20 20 20 20  |11  501   20    |
00000030  31 30 30 36 34 34 20 20  36 30 20 20 20 20 20 20  |100644  60      |
00000040  20 20 60 0a 5f 5f 2e 53  59 4d 44 45 46 20 53 4f  |  `.__.SYMDEF SO|
00000050  52 54 45 44 00 00 00 00  10 00 00 00 00 00 00 00  |RTED............|
00000060  80 00 00 00 05 00 00 00  38 03 00 00 10 00 00 00  |........8.......|
00000070  5f 61 64 64 00 5f 73 75  62 00 00 00 00 00 00 00  |_add._sub.......|
00000080  23 31 2f 31 32 20 20 20  20 20 20 20 20 20 20 20  |#1/12           |
00000090  31 36 31 35 31 33 34 31  32 39 20 20 35 30 31 20  |1615134129  501 |
000000a0  20 20 32 30 20 20 20 20  31 30 30 36 34 34 20 20  |  20    100644  |
000000b0  36 33 36 20 20 20 20 20  20 20 60 0a 6d 79 6c 69  |636       `.myli|
000000c0  62 31 2e 6f 00 00 00 00  cf fa ed fe 07 00 00 01  |b1.o............|
000000d0  03 00 00 00 01 00 00 00  04 00 00 00 b8 01 00 00  |................|
000000e0  00 20 00 00 00 00 00 00  19 00 00 00 38 01 00 00  |. ..........8...|
000000f0  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
00000100  00 00 00 00 00 00 00 00  78 00 00 00 00 00 00 00  |........x.......|
00000110  d8 01 00 00 00 00 00 00  78 00 00 00 00 00 00 00  |........x.......|
00000120  07 00 00 00 07 00 00 00  03 00 00 00 00 00 00 00  |................|
00000130  5f 5f 74 65 78 74 00 00  00 00 00 00 00 00 00 00  |__text..........|
00000140  5f 5f 54 45 58 54 00 00  00 00 00 00 00 00 00 00  |__TEXT..........|
00000150  00 00 00 00 00 00 00 00  12 00 00 00 00 00 00 00  |................|
00000160  d8 01 00 00 04 00 00 00  00 00 00 00 00 00 00 00  |................|
00000170  00 04 00 80 00 00 00 00  00 00 00 00 00 00 00 00  |................|
00000180  5f 5f 63 6f 6d 70 61 63  74 5f 75 6e 77 69 6e 64  |__compact_unwind|
00000190  5f 5f 4c 44 00 00 00 00  00 00 00 00 00 00 00 00  |__LD............|
000001a0  18 00 00 00 00 00 00 00  20 00 00 00 00 00 00 00  |........ .......|
000001b0  f0 01 00 00 03 00 00 00  50 02 00 00 01 00 00 00  |........P.......|
000001c0  00 00 00 02 00 00 00 00  00 00 00 00 00 00 00 00  |................|
000001d0  5f 5f 65 68 5f 66 72 61  6d 65 00 00 00 00 00 00  |__eh_frame......|
000001e0  5f 5f 54 45 58 54 00 00  00 00 00 00 00 00 00 00  |__TEXT..........|
000001f0  38 00 00 00 00 00 00 00  40 00 00 00 00 00 00 00  |8.......@.......|
00000200  10 02 00 00 03 00 00 00  00 00 00 00 00 00 00 00  |................|
00000210  0b 00 00 68 00 00 00 00  00 00 00 00 00 00 00 00  |...h............|
00000220  32 00 00 00 18 00 00 00  01 00 00 00 00 00 0b 00  |2...............|
00000230  00 01 0b 00 00 00 00 00  02 00 00 00 18 00 00 00  |................|
00000240  58 02 00 00 01 00 00 00  68 02 00 00 08 00 00 00  |X.......h.......|
00000250  0b 00 00 00 50 00 00 00  00 00 00 00 00 00 00 00  |....P...........|
00000260  00 00 00 00 01 00 00 00  01 00 00 00 00 00 00 00  |................|
00000270  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
*
000002a0  55 48 89 e5 89 7d fc 89  75 f8 8b 45 fc 03 45 f8  |UH...}..u..E..E.|
000002b0  5d c3 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |]...............|
000002c0  12 00 00 00 00 00 00 01  00 00 00 00 00 00 00 00  |................|
000002d0  00 00 00 00 00 00 00 00  14 00 00 00 00 00 00 00  |................|
000002e0  01 7a 52 00 01 78 10 01  10 0c 07 08 90 01 00 00  |.zR..x..........|
000002f0  24 00 00 00 1c 00 00 00  a8 ff ff ff ff ff ff ff  |$...............|
00000300  12 00 00 00 00 00 00 00  00 41 0e 10 86 02 43 0d  |.........A....C.|
00000310  06 00 00 00 00 00 00 00  00 00 00 00 01 00 00 06  |................|
00000320  01 00 00 00 0f 01 00 00  00 00 00 00 00 00 00 00  |................|
00000330  00 5f 61 64 64 00 00 00  23 31 2f 31 32 20 20 20  |._add...#1/12   |
00000340  20 20 20 20 20 20 20 20  31 36 31 35 31 33 34 31  |        16151341|
00000350  38 32 20 20 35 30 31 20  20 20 32 30 20 20 20 20  |82  501   20    |
00000360  31 30 30 36 34 34 20 20  36 33 36 20 20 20 20 20  |100644  636     |
00000370  20 20 60 0a 6d 79 6c 69  62 32 2e 6f 00 00 00 00  |  `.mylib2.o....|
00000380  cf fa ed fe 07 00 00 01  03 00 00 00 01 00 00 00  |................|
00000390  04 00 00 00 b8 01 00 00  00 20 00 00 00 00 00 00  |......... ......|
000003a0  19 00 00 00 38 01 00 00  00 00 00 00 00 00 00 00  |....8...........|
000003b0  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
000003c0  78 00 00 00 00 00 00 00  d8 01 00 00 00 00 00 00  |x...............|
000003d0  78 00 00 00 00 00 00 00  07 00 00 00 07 00 00 00  |x...............|
000003e0  03 00 00 00 00 00 00 00  5f 5f 74 65 78 74 00 00  |........__text..|
000003f0  00 00 00 00 00 00 00 00  5f 5f 54 45 58 54 00 00  |........__TEXT..|
00000400  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
00000410  12 00 00 00 00 00 00 00  d8 01 00 00 04 00 00 00  |................|
00000420  00 00 00 00 00 00 00 00  00 04 00 80 00 00 00 00  |................|
00000430  00 00 00 00 00 00 00 00  5f 5f 63 6f 6d 70 61 63  |........__compac|
00000440  74 5f 75 6e 77 69 6e 64  5f 5f 4c 44 00 00 00 00  |t_unwind__LD....|
00000450  00 00 00 00 00 00 00 00  18 00 00 00 00 00 00 00  |................|
00000460  20 00 00 00 00 00 00 00  f0 01 00 00 03 00 00 00  | ...............|
00000470  50 02 00 00 01 00 00 00  00 00 00 02 00 00 00 00  |P...............|
00000480  00 00 00 00 00 00 00 00  5f 5f 65 68 5f 66 72 61  |........__eh_fra|
00000490  6d 65 00 00 00 00 00 00  5f 5f 54 45 58 54 00 00  |me......__TEXT..|
000004a0  00 00 00 00 00 00 00 00  38 00 00 00 00 00 00 00  |........8.......|
000004b0  40 00 00 00 00 00 00 00  10 02 00 00 03 00 00 00  |@...............|
000004c0  00 00 00 00 00 00 00 00  0b 00 00 68 00 00 00 00  |...........h....|
000004d0  00 00 00 00 00 00 00 00  32 00 00 00 18 00 00 00  |........2.......|
000004e0  01 00 00 00 00 00 0b 00  00 01 0b 00 00 00 00 00  |................|
000004f0  02 00 00 00 18 00 00 00  58 02 00 00 01 00 00 00  |........X.......|
00000500  68 02 00 00 08 00 00 00  0b 00 00 00 50 00 00 00  |h...........P...|
00000510  00 00 00 00 00 00 00 00  00 00 00 00 01 00 00 00  |................|
00000520  01 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
00000530  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
*
00000550  00 00 00 00 00 00 00 00  55 48 89 e5 89 7d fc 89  |........UH...}..|
00000560  75 f8 8b 45 fc 2b 45 f8  5d c3 00 00 00 00 00 00  |u..E.+E.].......|
00000570  00 00 00 00 00 00 00 00  12 00 00 00 00 00 00 01  |................|
00000580  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
00000590  14 00 00 00 00 00 00 00  01 7a 52 00 01 78 10 01  |.........zR..x..|
000005a0  10 0c 07 08 90 01 00 00  24 00 00 00 1c 00 00 00  |........$.......|
000005b0  a8 ff ff ff ff ff ff ff  12 00 00 00 00 00 00 00  |................|
000005c0  00 41 0e 10 86 02 43 0d  06 00 00 00 00 00 00 00  |.A....C.........|
000005d0  00 00 00 00 01 00 00 06  01 00 00 00 0f 01 00 00  |................|
000005e0  00 00 00 00 00 00 00 00  00 5f 73 75 62 00 00 00  |........._sub...|
000005f0
AppledeMacBook-Pro:homework-5 apple$ gcc main.i -lmylib -L./ -Iinclude
AppledeMacBook-Pro:homework-5 apple$ gcc main.i -lmylib -L./ -Iinclude -o main
AppledeMacBook-Pro:homework-5 apple$ hexdump -C main
00000000  cf fa ed fe 07 00 00 01  03 00 00 00 02 00 00 00  |................|
00000010  0e 00 00 00 e8 02 00 00  85 00 20 00 00 00 00 00  |.......... .....|
00000020  19 00 00 00 48 00 00 00  5f 5f 50 41 47 45 5a 45  |....H...__PAGEZE|
00000030  52 4f 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |RO..............|
00000040  00 00 00 00 01 00 00 00  00 00 00 00 00 00 00 00  |................|
00000050  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
00000060  00 00 00 00 00 00 00 00  19 00 00 00 e8 00 00 00  |................|
00000070  5f 5f 54 45 58 54 00 00  00 00 00 00 00 00 00 00  |__TEXT..........|
00000080  00 00 00 00 01 00 00 00  00 40 00 00 00 00 00 00  |.........@......|
00000090  00 00 00 00 00 00 00 00  00 40 00 00 00 00 00 00  |.........@......|
000000a0  05 00 00 00 05 00 00 00  02 00 00 00 00 00 00 00  |................|
000000b0  5f 5f 74 65 78 74 00 00  00 00 00 00 00 00 00 00  |__text..........|
000000c0  5f 5f 54 45 58 54 00 00  00 00 00 00 00 00 00 00  |__TEXT..........|
000000d0  30 3f 00 00 01 00 00 00  82 00 00 00 00 00 00 00  |0?..............|
000000e0  30 3f 00 00 04 00 00 00  00 00 00 00 00 00 00 00  |0?..............|
000000f0  00 04 00 80 00 00 00 00  00 00 00 00 00 00 00 00  |................|
00000100  5f 5f 75 6e 77 69 6e 64  5f 69 6e 66 6f 00 00 00  |__unwind_info...|
00000110  5f 5f 54 45 58 54 00 00  00 00 00 00 00 00 00 00  |__TEXT..........|
00000120  b4 3f 00 00 01 00 00 00  48 00 00 00 00 00 00 00  |.?......H.......|
00000130  b4 3f 00 00 02 00 00 00  00 00 00 00 00 00 00 00  |.?..............|
00000140  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
00000150  19 00 00 00 48 00 00 00  5f 5f 4c 49 4e 4b 45 44  |....H...__LINKED|
00000160  49 54 00 00 00 00 00 00  00 40 00 00 01 00 00 00  |IT.......@......|
00000170  00 40 00 00 00 00 00 00  00 40 00 00 00 00 00 00  |.@.......@......|
00000180  d0 00 00 00 00 00 00 00  01 00 00 00 01 00 00 00  |................|
00000190  00 00 00 00 00 00 00 00  22 00 00 80 30 00 00 00  |........"...0...|
000001a0  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
*
000001c0  00 40 00 00 40 00 00 00  02 00 00 00 18 00 00 00  |.@..@...........|
000001d0  48 40 00 00 05 00 00 00  98 40 00 00 38 00 00 00  |H@.......@..8...|
000001e0  0b 00 00 00 50 00 00 00  00 00 00 00 00 00 00 00  |....P...........|
000001f0  00 00 00 00 04 00 00 00  04 00 00 00 01 00 00 00  |................|
00000200  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
*
00000230  0e 00 00 00 20 00 00 00  0c 00 00 00 2f 75 73 72  |.... ......./usr|
00000240  2f 6c 69 62 2f 64 79 6c  64 00 00 00 00 00 00 00  |/lib/dyld.......|
00000250  1b 00 00 00 18 00 00 00  b5 ec fc b8 9c 16 31 b8  |..............1.|
00000260  8e f3 60 ec 83 e6 ad e7  32 00 00 00 20 00 00 00  |..`.....2... ...|
00000270  01 00 00 00 00 00 0b 00  00 01 0b 00 01 00 00 00  |................|
00000280  03 00 00 00 00 08 61 02  2a 00 00 00 10 00 00 00  |......a.*.......|
00000290  00 00 00 00 00 00 00 00  28 00 00 80 18 00 00 00  |........(.......|
000002a0  30 3f 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |0?..............|
000002b0  0c 00 00 00 38 00 00 00  18 00 00 00 02 00 00 00  |....8...........|
000002c0  01 3c 0c 05 00 00 01 00  2f 75 73 72 2f 6c 69 62  |.<....../usr/lib|
000002d0  2f 6c 69 62 53 79 73 74  65 6d 2e 42 2e 64 79 6c  |/libSystem.B.dyl|
000002e0  69 62 00 00 00 00 00 00  26 00 00 00 10 00 00 00  |ib......&.......|
000002f0  40 40 00 00 08 00 00 00  29 00 00 00 10 00 00 00  |@@......).......|
00000300  48 40 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |H@..............|
00000310  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
*
00003f30  55 48 89 e5 48 83 ec 10  c7 45 fc 00 00 00 00 bf  |UH..H....E......|
00003f40  01 00 00 00 be 02 00 00  00 e8 32 00 00 00 89 45  |..........2....E|
00003f50  f8 bf 03 00 00 00 be 04  00 00 00 e8 40 00 00 00  |............@...|
00003f60  89 45 f4 8b 45 f8 03 45  f4 89 45 f8 8b 45 f8 48  |.E..E..E..E..E.H|
00003f70  83 c4 10 5d c3 90 90 90  90 90 90 90 90 90 90 90  |...]............|
00003f80  55 48 89 e5 89 7d fc 89  75 f8 8b 45 fc 03 45 f8  |UH...}..u..E..E.|
00003f90  5d c3 90 90 90 90 90 90  90 90 90 90 90 90 90 90  |]...............|
00003fa0  55 48 89 e5 89 7d fc 89  75 f8 8b 45 fc 2b 45 f8  |UH...}..u..E.+E.|
00003fb0  5d c3 90 90 01 00 00 00  1c 00 00 00 00 00 00 00  |]...............|
00003fc0  1c 00 00 00 00 00 00 00  1c 00 00 00 02 00 00 00  |................|
00003fd0  30 3f 00 00 34 00 00 00  34 00 00 00 b3 3f 00 00  |0?..4...4....?..|
00003fe0  00 00 00 00 34 00 00 00  03 00 00 00 0c 00 01 00  |....4...........|
00003ff0  10 00 01 00 00 00 00 00  00 00 00 01 00 00 00 00  |................|
00004000  00 01 5f 00 05 00 04 5f  6d 68 5f 65 78 65 63 75  |.._...._mh_execu|
00004010  74 65 5f 68 65 61 64 65  72 00 2b 6d 61 69 6e 00  |te_header.+main.|
00004020  2f 61 64 64 00 34 73 75  62 00 39 02 00 00 00 03  |/add.4sub.9.....|
00004030  00 b0 7e 00 03 00 80 7f  00 03 00 a0 7f 00 00 00  |..~.............|
00004040  b0 7e 50 20 00 00 00 00  02 00 00 00 0f 01 10 00  |.~P ............|
00004050  00 00 00 00 01 00 00 00  16 00 00 00 0f 01 00 00  |................|
00004060  80 3f 00 00 01 00 00 00  1b 00 00 00 0f 01 00 00  |.?..............|
00004070  30 3f 00 00 01 00 00 00  21 00 00 00 0f 01 00 00  |0?......!.......|
00004080  a0 3f 00 00 01 00 00 00  26 00 00 00 01 00 00 01  |.?......&.......|
00004090  00 00 00 00 00 00 00 00  20 00 5f 5f 6d 68 5f 65  |........ .__mh_e|
000040a0  78 65 63 75 74 65 5f 68  65 61 64 65 72 00 5f 61  |xecute_header._a|
000040b0  64 64 00 5f 6d 61 69 6e  00 5f 73 75 62 00 64 79  |dd._main._sub.dy|
000040c0  6c 64 5f 73 74 75 62 5f  62 69 6e 64 65 72 00 00  |ld_stub_binder..|
000040d0
AppledeMacBook-Pro:homework-5 apple$ gcc main.o -lmylib -L./ -Iinclude -o main
AppledeMacBook-Pro:homework-5 apple$ hexdump -C main
00000000  cf fa ed fe 07 00 00 01  03 00 00 00 02 00 00 00  |................|
00000010  0e 00 00 00 e8 02 00 00  85 00 20 00 00 00 00 00  |.......... .....|
00000020  19 00 00 00 48 00 00 00  5f 5f 50 41 47 45 5a 45  |....H...__PAGEZE|
00000030  52 4f 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |RO..............|
00000040  00 00 00 00 01 00 00 00  00 00 00 00 00 00 00 00  |................|
00000050  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
00000060  00 00 00 00 00 00 00 00  19 00 00 00 e8 00 00 00  |................|
00000070  5f 5f 54 45 58 54 00 00  00 00 00 00 00 00 00 00  |__TEXT..........|
00000080  00 00 00 00 01 00 00 00  00 40 00 00 00 00 00 00  |.........@......|
00000090  00 00 00 00 00 00 00 00  00 40 00 00 00 00 00 00  |.........@......|
000000a0  05 00 00 00 05 00 00 00  02 00 00 00 00 00 00 00  |................|
000000b0  5f 5f 74 65 78 74 00 00  00 00 00 00 00 00 00 00  |__text..........|
000000c0  5f 5f 54 45 58 54 00 00  00 00 00 00 00 00 00 00  |__TEXT..........|
000000d0  30 3f 00 00 01 00 00 00  82 00 00 00 00 00 00 00  |0?..............|
000000e0  30 3f 00 00 04 00 00 00  00 00 00 00 00 00 00 00  |0?..............|
000000f0  00 04 00 80 00 00 00 00  00 00 00 00 00 00 00 00  |................|
00000100  5f 5f 75 6e 77 69 6e 64  5f 69 6e 66 6f 00 00 00  |__unwind_info...|
00000110  5f 5f 54 45 58 54 00 00  00 00 00 00 00 00 00 00  |__TEXT..........|
00000120  b4 3f 00 00 01 00 00 00  48 00 00 00 00 00 00 00  |.?......H.......|
00000130  b4 3f 00 00 02 00 00 00  00 00 00 00 00 00 00 00  |.?..............|
00000140  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
00000150  19 00 00 00 48 00 00 00  5f 5f 4c 49 4e 4b 45 44  |....H...__LINKED|
00000160  49 54 00 00 00 00 00 00  00 40 00 00 01 00 00 00  |IT.......@......|
00000170  00 40 00 00 00 00 00 00  00 40 00 00 00 00 00 00  |.@.......@......|
00000180  d0 00 00 00 00 00 00 00  01 00 00 00 01 00 00 00  |................|
00000190  00 00 00 00 00 00 00 00  22 00 00 80 30 00 00 00  |........"...0...|
000001a0  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
*
000001c0  00 40 00 00 40 00 00 00  02 00 00 00 18 00 00 00  |.@..@...........|
000001d0  48 40 00 00 05 00 00 00  98 40 00 00 38 00 00 00  |H@.......@..8...|
000001e0  0b 00 00 00 50 00 00 00  00 00 00 00 00 00 00 00  |....P...........|
000001f0  00 00 00 00 04 00 00 00  04 00 00 00 01 00 00 00  |................|
00000200  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
*
00000230  0e 00 00 00 20 00 00 00  0c 00 00 00 2f 75 73 72  |.... ......./usr|
00000240  2f 6c 69 62 2f 64 79 6c  64 00 00 00 00 00 00 00  |/lib/dyld.......|
00000250  1b 00 00 00 18 00 00 00  b5 ec fc b8 9c 16 31 b8  |..............1.|
00000260  8e f3 60 ec 83 e6 ad e7  32 00 00 00 20 00 00 00  |..`.....2... ...|
00000270  01 00 00 00 00 00 0b 00  00 01 0b 00 01 00 00 00  |................|
00000280  03 00 00 00 00 08 61 02  2a 00 00 00 10 00 00 00  |......a.*.......|
00000290  00 00 00 00 00 00 00 00  28 00 00 80 18 00 00 00  |........(.......|
000002a0  30 3f 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |0?..............|
000002b0  0c 00 00 00 38 00 00 00  18 00 00 00 02 00 00 00  |....8...........|
000002c0  01 3c 0c 05 00 00 01 00  2f 75 73 72 2f 6c 69 62  |.<....../usr/lib|
000002d0  2f 6c 69 62 53 79 73 74  65 6d 2e 42 2e 64 79 6c  |/libSystem.B.dyl|
000002e0  69 62 00 00 00 00 00 00  26 00 00 00 10 00 00 00  |ib......&.......|
000002f0  40 40 00 00 08 00 00 00  29 00 00 00 10 00 00 00  |@@......).......|
00000300  48 40 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |H@..............|
00000310  00 00 00 00 00 00 00 00  00 00 00 00 00 00 00 00  |................|
*
00003f30  55 48 89 e5 48 83 ec 10  c7 45 fc 00 00 00 00 bf  |UH..H....E......|
00003f40  01 00 00 00 be 02 00 00  00 e8 32 00 00 00 89 45  |..........2....E|
00003f50  f8 bf 03 00 00 00 be 04  00 00 00 e8 40 00 00 00  |............@...|
00003f60  89 45 f4 8b 45 f8 03 45  f4 89 45 f8 8b 45 f8 48  |.E..E..E..E..E.H|
00003f70  83 c4 10 5d c3 90 90 90  90 90 90 90 90 90 90 90  |...]............|
00003f80  55 48 89 e5 89 7d fc 89  75 f8 8b 45 fc 03 45 f8  |UH...}..u..E..E.|
00003f90  5d c3 90 90 90 90 90 90  90 90 90 90 90 90 90 90  |]...............|
00003fa0  55 48 89 e5 89 7d fc 89  75 f8 8b 45 fc 2b 45 f8  |UH...}..u..E.+E.|
00003fb0  5d c3 90 90 01 00 00 00  1c 00 00 00 00 00 00 00  |]...............|
00003fc0  1c 00 00 00 00 00 00 00  1c 00 00 00 02 00 00 00  |................|
00003fd0  30 3f 00 00 34 00 00 00  34 00 00 00 b3 3f 00 00  |0?..4...4....?..|
00003fe0  00 00 00 00 34 00 00 00  03 00 00 00 0c 00 01 00  |....4...........|
00003ff0  10 00 01 00 00 00 00 00  00 00 00 01 00 00 00 00  |................|
00004000  00 01 5f 00 05 00 04 5f  6d 68 5f 65 78 65 63 75  |.._...._mh_execu|
00004010  74 65 5f 68 65 61 64 65  72 00 2b 6d 61 69 6e 00  |te_header.+main.|
00004020  2f 61 64 64 00 34 73 75  62 00 39 02 00 00 00 03  |/add.4sub.9.....|
00004030  00 b0 7e 00 03 00 80 7f  00 03 00 a0 7f 00 00 00  |..~.............|
00004040  b0 7e 50 20 00 00 00 00  02 00 00 00 0f 01 10 00  |.~P ............|
00004050  00 00 00 00 01 00 00 00  16 00 00 00 0f 01 00 00  |................|
00004060  80 3f 00 00 01 00 00 00  1b 00 00 00 0f 01 00 00  |.?..............|
00004070  30 3f 00 00 01 00 00 00  21 00 00 00 0f 01 00 00  |0?......!.......|
00004080  a0 3f 00 00 01 00 00 00  26 00 00 00 01 00 00 01  |.?......&.......|
00004090  00 00 00 00 00 00 00 00  20 00 5f 5f 6d 68 5f 65  |........ .__mh_e|
000040a0  78 65 63 75 74 65 5f 68  65 61 64 65 72 00 5f 61  |xecute_header._a|
000040b0  64 64 00 5f 6d 61 69 6e  00 5f 73 75 62 00 64 79  |dd._main._sub.dy|
000040c0  6c 64 5f 73 74 75 62 5f  62 69 6e 64 65 72 00 00  |ld_stub_binder..|
000040d0
```

**Question 23:** Compare the output of `hexdump` for `main`, `main.o`, and `libmylib.a`. What do you notice? How many bytes are in `main.o`? How many are in `libmylib.a`? How many are in `main`? Based on your comparison, what do you think the extra bytes are doing in `main`?
main is seemed to include the context of main.o and some of the context of libmylib.a, and main.o's content is at the lower part of the main, and libmylib.a's content is at the upper part of the main. libmylib.a is 1520 bytes, main.o is 732 bytes, and main is 16592 bytes. Since main is an Unix executable file, and it is seemed to include main.o and libmylib.a, it is likely to use some sxtra bytes to include something that makes it executable.
**Question 24:** Write a `Makefile` that automates the build process without using `gcc` (except to invoke the linker in the last step). Your `Makefile` should have the following directives:

- all - build the executable from `main.o` and `libmylib.a`
- main.o - build `main.o` from `main.c`
- libmylib.a - build `libmylib.a` from `mylib1.o` and `mylib2.o`
- clean - remove all `*.i`, `*.s`, `*.a`, `*.o`, `main`, and intermediate representation files.
