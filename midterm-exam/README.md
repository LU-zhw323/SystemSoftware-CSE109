# CSE 109 - Systems Software - Midterm

Due by: 3/17/2020 by EOD

## Ethics Contract

**FIRST**: Please read the following carefully:

- I have not received, I have not given, nor will I give or receive, any assistance to another student taking this exam, including discussing the exam with students in another section of the course. Do not discuss the exam after you are finished until final grades are submitted.
- If I use any resources (including text books and online references and websites), I will cite them in my assignment.
- I will not ask question about how to debug my exam code on Piazza or any other platform.
- I will not plagiarize someone else's work and turn it in as my own. If I use someone else's work in this exam, I will cite that work. Failure to cite work I used is plagiarism.
- I understand that acts of academic dishonesty may be penalized to the full extent allowed by the [Lehigh University Code of Conduct][0], including receiving a failing grade for the course. I recognize that I am responsible for understanding the provisions of the Lehigh University Code of Conduct as they relate to this academic exercise.

If you agree with the above, type your full name in the following space along with the date. Your exam **will not be graded** without this assent. When you are done, **make your first commit with the commit message: `I, <your full name here>, agree to the ethics contract`.**

Write your name and date below between the lines below

---------------------------------------------
Zhenyu Wu 15th March 2021
---------------------------------------------

## Instructions 

**Read thoroughly before starting your exam:**

1. Fork this repository into your CSE109 project namespace. [Instructions](https://docs.gitlab.com/ee/workflow/forking_workflow.html#creating-a-fork)
2. Clone your newly forked repository onto your development machine. [Instructions](https://docs.gitlab.com/ee/gitlab-basics/start-using-git.html#clone-a-repository) 
3. As you are writing code you should commit patches along the way. *i.e.* don't just submit all your code in one big commit when you're all done. Commit your progress as you work. **You should make at least one commit per question.**
4. When you've committed all of your work, there's nothing left to do to submit the assignment.

## Exam Prelude

There are 15 questions in this exam divided into two parts. Each question is weighted equally. This exam will test your ability to independently:

- Organize a programming project
- Use the basics of the C progamming language including structs and pointers
- Allocate memory on the heap and use it in a way that does not cause memory leaks
- Implement a data structure as a library and use that library in an executable
- Write and use Makefiles to automate the build process

In Part 1 you're going to implement a binary search tree (BST) data structure as a C library. If you need a refresher on binary search trees [here's a good one](https://en.wikipedia.org/wiki/Binary_search_tree) that has implementations on the general algorithms. There's also literally a million videos online about binary search trees. Here are a couple of okay ones:

- https://youtu.be/4WXbZFtaPrA
- https://youtu.be/VSTi4qegmZg

This repository is blank except for this README file. It's your job to create this library from scratch. You are going to lay out the directory structure, create a Makefile, create a header file, create library source files, implement your BST datastructure, and then finally provide tests to verify the tree works. You can use any libraries and functions you like to accomplish this (except one that would provide a BST that you then wrap).

Part 2 is the oral portion of the exam. I will ask you to pick a couple functions in your BST and to record an explanation of your work along with your screen. For more info, see Part 2.

### Commit Policy

I'm going to divide the project into discrete "questions", and you must make at least one commit per question. This is how I will know you are not just copying and pasting an entire solution from the internet. I will be able to see how much time you spend on each question based on your commit times. Red flags are raised when certain patterns of behavior indicating cheating are exhibited by your commit activity. 

You can do the questions in any order, and you can go back to questions for which you have already made a commit, but I want you to have at least one commit per question. The commit message for each question should be "QUESTION N" where N is the number of the question.

### Resource Usage Policy

You are free to use any resource for this exam. This includes books, notes, lecture videos, documentation, the internet, Stack Overflow, etc. The only course resources off limits are me and your TAs. I am free to answer clarifying questions, but that's it. I can't help you debug or provide any technical support (this includes support with git. Knowing how to use git is part of this exam.)

If you use any resources from the internet or anywhere else, **YOU HAVE TO CITE THEM** in your exam. Failure to cite resources you used may lead to failure of the exam. This includes the wiki article and videos I posted above. If you use them, cite them every time you use them. See the Works Cited section at the bottom for more deails on how to cite your work in this document using Markdown.

## Part 1

### Question 1

Lay out your directory structure. Create a `src` directory, an `include` directory, and a blank `Makefile` in the project root. 

- Inside the `src` directory create a `bin` directory. 
- Inside the `src/bin` directory create `main.c`
- Inside the `src` directory create `lib.c`, `insert.c`, `find.c`, `remove.c`, and `rebalance.c`.
- Inside the `include` directory, create `bst.h`

### Question 2

Implement the Makefile to build your project. It will be a little different than the homework so pay attention to these instructions. Your Makefile should have at least the following directives:

- `static` will generate a static library (libbst.a) and put it in `build/lib`.
- `shared` will generate a shared library (libbst.so) and put it in `build/lib` (Remember this [reading][2]).
- `bin` will generate an executable from `main.c` called `main`, which statically links to `libbst.a` (it should make that as well if it doesn't exist). Put the executable in `build/bin` and the library in `build/lib`. Put object files in `build/objects`.
- `all` will build the static and shared libraries as well as `main`.
- `clean` will clean the project of all build directories and artifacts (*.so *.a *.o main)
- `install` will move the shared library to `/usr/lib`.
[For shared libaray][2]
### Question 3

In `bst.h`, write a `Node` struct to represent the nodes of the BST. Each `Node` should have at least the following fields:

- `void* item` a pointer to an item held on the `Node`.
- `Node** nodes` An array of pointers to `Node` pointers. For a BST, you will have two pointers to `Node` pointers.

You can include any other fields you see fit to make this work.

### Question 4

In `bst.h`, write a `BST` struct to represent the BST. The `BST` should have at least the following fields:

- `Node* tree_root` a pointer to the root node of the BST.
- `int depth` a character to hold the depth of the tree.
- `int item_size` the size of each item stored in the BST in bytes.

You can include any other fields you see fit to make this work.

### Question 5

Stub out the relevant function signatures for your BST in `bst.h`

The functions you will implement are:

- `initBinaryTree()` takes a `BST*` and an `int item_size`. Initializes the fields on the BST. Returns nothing.
- `insertItem()` takes a `BST*` and a `void* item`. Inserts the item at the appropriate place in the tree. Returns `0` on success and `1` on failure. Updates the depth on the tree after each insert.
- `findItem()` takes a `BST*` and a `void* query`. Searches the BST for a node with an `item` equivalent to `query`. Returns a pointer to the `item` if it is found in the tree, `NULL` if it's not.
- `removeItem()` takes a `BST*` and a `void* query`. Searches the BST for a node with an `item` equivalent to `query`, and removes that node from the tree. Returns a pointer to the `item` if it is found in the tree, `NULL` if it's not. Updates the depth of the BST after each remove.
- `freeNodes()`takes a ``BST*` and frees all the nodes and their items. It should not free the BST itself.
- `rebalanceTree()`takes a ``BST*` and rebalances it. Returns nothing.
- `printTree()` takes a `BST*` and prints the entire tree. This can be in any format that helps you visualize the tree.

You can add any other function arguments you see fit to make your functions work.

### Question 6

Implement `initBinaryTree()` in `lib.c`

### Question 7

Implement `insertItem()` in `insert.c`

### Question 8

Implement `printTree()` in `lib.c`
[traversal][6]

### Question 9

Implement `findItem()` in `find.c`

### Question 10

Implement `removeItem()` in `remove.c`

### Question 11

Implement `freeNodes()` in `lib.c`
[Free][5]

### Question 12

Implement `rebalanceTree()` in `rebalance.c`

[Rebalance][4]
[Put BST into array][7]

### Question 13

Write at least 5 tests in `main.c` to demonstrate your code works. See the Linked List homework for a way you might do this.

### Bonus

Set up a test runner on gitlab so that your tests runs automatically and passes with a green checkmark. This extra credit will be +10% toward a previous homework assignment (Maximum 100% though. Not payable forward to future assignments).

## Part 2

### Questions 14 and 15

This is the oral portion of the exam. You will record an explanation for two functions that you implemented in Part 1.

- For the first explanation, choose one of Questions 6, 8, or 11.
- For the second explanation, choose one of Questions 7, 9, or 10.

If you didn't get one of these questions, explain how you attempted to solve it and where you got stuck. This will get you at least some points. You ca record both of these questions in a single recording, or do two recordings.

You can use Zoom to do this, [here is a link][3] to some instructions. You don't have to record your face, only your voice and the screen. Go through the answer and explain how you arrived there. Your goal with this question is to convince me you know what you are talking about, so I want you to do this without reading a script or written answer. Just go through line by line and explain what the program does. When you are done, upload your recording to your Lehigh Drive and add a link below. **IMPORTANT: Make sure you give me permission to view the file**.

Recording Link(s): https://drive.google.com/file/d/1VYOYj1xH1FyRyrd1XJF9UJZQf7GNWTvr/view?usp=sharing

## Works Cited

Include a list of websites and resources you used to complete this exam. Make a numbered list, and at the place where you used this resource cite it using [reference style links in Markdown][1] (See this Readme's source for an example. It's invisible in the rendered document, but there are a number of links below this paragraph).

[0]: https://studentaffairs.lehigh.edu/content/code-conduct
[1]: https://www.markdownguide.org/basic-syntax#reference-style-links
[2]: http://crasseux.com/books/ctutorial/Building-a-library.html#Building%20a%20library
[3]: https://support.zoom.us/hc/en-us/articles/201362473-Local-recording
[4]: https://www.geeksforgeeks.org/convert-normal-bst-balanced-bst/
[5]: https://stackoverflow.com/questions/9181146/freeing-memory-of-a-binary-tree-c
[6]: https://en.wikipedia.org/wiki/Binary_search_tree
[7]: https://stackoverflow.com/questions/29582431/convert-binary-tree-to-array-in-c