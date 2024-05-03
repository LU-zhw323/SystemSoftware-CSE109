# CSE 109 - Homework 6

**Due Date: 3/30/2021 EOD**

## Instructions 

**Read thoroughly before starting your project:**

1. Fork this repository into your CSE109 project namespace. [Instructions](https://docs.gitlab.com/ee/workflow/forking_workflow.html#creating-a-fork)
2. Clone your newly forked repository onto your development machine. [Instructions](https://docs.gitlab.com/ee/gitlab-basics/start-using-git.html#clone-a-repository) 
3. As you are writing code you should commit patches along the way. *i.e.* don't just submit all your code in one big commit when you're all done. Commit your progress as you work. **You should make at least one commit per function.**
4. When you've committed all of your work, there's nothing left to do to submit the assignment.

## Assignment

There are two parts to this assignment. In Part 1, you will convert you linked list data structure that you implemented in Homework 4 from C to C++. In Part 2, you will implement a hash set in C++.

## Part 1 - Linked List Conversion

Convert your linked list data structure from Homework 4 to a C++ class. If you didn't successfully complete Homework 4, you can use the [posted solution](https://gitlab.com/lehigh-cse-109/spring-2021/assignments/homework-4/-/tree/solutions) as the basis for this part of the assignment. Your linked list class should be a template class so that it can hold items of any type. You should also convert your Node struct to a Node template class.

The Node class should have the following methods:

```c++
template <class T>
class Node {
  public:
    T item
    size_t length;
    LinkedList::Node* next;
    Node();
    ~Node();
};
```

You can add any other methods and fields necessary to make your Node work. You can implement these functions in a header file called `llnode.h` inside of the `lib` directory. Make sure they exist wihtin the `LinkedList` namespace though.

The Linked List class should have the following methods:

```c++
template <class T>
class LinkedList {
  private:
    LinkedList::Node<T>* head;
    LinkedList::Node<T>* tail;
  public:
    size_t length;
    LinkedList();
    ~LinkedList();
    size_t insertAtTail(List* list_pointer, T item);
    size_t insertAtHead(List* list_pointer, T item);
    size_t insertAtIndex(size_t index, T item);
    T removeTail();
    T removeHead();
    T removeAtIndex(size_t index);
};
```

You can add any other methods and fields necessary to make your LinkedList work. You can write all of this code in a header file called `linkedlist.h` inside of the lib directory. You should add some template implementations for common types, like `int`, `char`, etc. Write a Makefile inside of this directory that has the following directives:

- static - build a static library `liblinkedlist.a`, put it in `lib/build/lib/release`. Put object files in `lib/build/objects`
- shared - build a shared library `liblinkedlist.so`, put it in `lib/build/lib/release`. Put object files in `lib/build/objects`
- debug - build a shared library with debug symbols, put it in `lib/build/lib/debug`. Put object files in `lib/build/objects`
- clean - remove all build artifacts.

## Part 2 - Hash Set

In this part you will implement a hash set data structure in C++. The core of the hashset is an array of linked list pointers. The type of the table is a `LinkedList<T>**`. The first star indicates it's a pointer to an array, the second star indicates each array element holds a List pointer. The Hashset also holds its size, and the current load factor. The load factor will be recalculated on each insert, and if the value exceeds a threshold (70% filled buckets) then the underlying table array will be resized. This will involve allocating a new, larger array, rehashing all of the elements into this new array, then freeing the old array and its constituent linked lists.

The Hashset struct is declared in `hashset.h`, along with a number of functions you will need to implement.

```c++

template <class T>
class HashSet {
  private:
    // The backbone of the hash set. This is an array of Linked List pointers.
    LinkedList<T>** array;

    // The number of buckets in the array
    size_t size; 

    // Generate a prehash for an item with a given size
    unsigned long prehash(T item);

  public:
    // Initialize an empty hash set, where size is the number of buckets in the array
    HashSet(size_t size);

    // Free all memory allocated by the hash set
    ~HashSet();

    // Hash an unsigned long into an index that fits into a hash set
    unsigned long hash(T item);

    // Insert item in the set. Return true if the item was inserted, false if it wasn't (i.e. it was already in the set)
    // Recalculate the load factor after each successful insert (round to nearest whole number).
    // If the load factor exceeds 70 after insert, resize the table to hold twice the number of buckets.
    bool insert(T item);

    // Remove an item from the set. Return true if it was removed, false if it wasn't (i.e. it wasn't in the set to begin with)
    bool remove(T item);

    // Return true if the item exists in the set, false otherwise
    bool contains(T item);

    // Resize the underlying table to the given size. Recalculate the load factor after resize
    void resize(size_t new_size);

    // Returns the number of items in the hash set
    size_t len();

    // Returns the number of items the hash set can hold before reallocating
    size_t capacity();

    // Print Table. You can do this in a way that helps you implement your hash set.
    void print();

};
```

You should add some template implementations for common types, like `int`, `char`, etc. Write a Makefile inside of the project root that has the following directives:

- static - build a static library `libhashset.a`, put it in `build/lib/release`. Put object files in `build/objects`
- shared - build a shared library `libhashset.so`, put it in `build/lib/release`. Put object files in `build/objects`
- debug - build a shared library with debug symbols, put it in `build/lib/debug`. Put object files in `build/objects`
- clean - remove all build artifacts.
- install - move the shared library to `/usr/lib`

## Build Instructions

Write build instructions here. Explain to the user all the steps necessary to build this project including:

- What software (including versions) are needed?
GCC complier(version: latest version), VScode with C/C++ extension(lateset version)
- What system architectures and operating systems are supported?
Linux , MacOS
- What commands need to be entered to build the project?
g++ src/bin/main.cpp -Iinclude -Ilib
## Usage

Write usage instructions here. Explain to the user how they can integrate your library into their project. Usage instructions might include:

- What the user should #include into their project and where.
#include "hashset.h"
#include<stdio.h>
#include<stdlib.h>
$include<stdbool.h>
- An example command of how the user might build their project to link to your library.
go to the lib folder:

make shared
export LD_LIBRARY_PATH=/homedirectory/lib:$LD_LIBRARY_PATH
g++ src/bin/main -lliblinkedlist -Llib/build/lib/release -I./

- How to create a linked list using your library.
using LinkedList<T> list();
- How to use the linked list.
by putting "." to access memebers and methods in LinkedList
eg. list.insertAtHead(list, item);
- How to clean up the linked list to avoid leaking memory.
by using deconstructor
eg. list.~LinkedList();
## Examples

Write two examples demonstrating how to use your linked list library. These example should be complete in the sense that the user can just copy and paste them into their code and everything should work as long as they follow the build and usage instructions you gave them.
Command:
(go to the lib folder:)
make shared
export LD_LIBRARY_PATH=/homedirectory/lib:$LD_LIBRARY_PATH
g++ src/bin/main.cpp -lliblinkedlist -Llib/build/lib/release -I./
./a.out

In main.cpp:
LinkedList<T> list();
int a = 1;
int b = 2;
int c = 3;
list.insertAtHead(a);
list.insertAtTail(b);
list.insertAtIndex(c,1);
list.removeHead();
list.printList();
