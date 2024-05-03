# CSE 109 - Homework 4

**Due Date: 3/3/2021 EOD**

## Instructions 

**Read thoroughly before starting your project:**

1. Fork this repository into your CSE109 project namespace. [Instructions](https://docs.gitlab.com/ee/workflow/forking_workflow.html#creating-a-fork)
2. Clone your newly forked repository onto your development machine. [Instructions](https://docs.gitlab.com/ee/gitlab-basics/start-using-git.html#clone-a-repository) 
3. As you are writing code you should commit patches along the way. *i.e.* don't just submit all your code in one big commit when you're all done. Commit your progress as you work. **You should make at least one commit per function.**
4. When you've committed all of your work, there's nothing left to do to submit the assignment.

## Assignment

You will implement a linked list data structure in this assignment. The linked list will consist of a `head` pointer and a tail pointer. The head pointer will point to a `Node` struct, which will hold a data void pointer as well as a pointer to the next node in the list. The `tail` pointer will point to the final node in the linked list. The `next` pointer on the tail will point to `NULL`.


```
  ┌─────────┐    ┌─────────┐   ┌─────────┐    ┌─────────┐
  │     head│--->│  void*  │-->│  void*  │--->│  void*  │---> NULL
  │         │    └─────────┘   └─────────┘    └─────────┘
  │     tail│--------------------------------------^
  └─────────┘
```


The `List` and `Node` structs are declared in `linkedlist.h`, along with a number of functions you will need to implement.

```c
// Initialize an empty list. The head and tail pointers should point to NULL.
void initList(List* list_pointer);

// Create Node struct containing a void pointer to an item, return pointer to the newly created Node struct
Node* createNode(void* item);

// Insert new Node at the end of the list, containing a void pointer to item. The next pointer on this Node
// points to NULL. On success return 0. On failure, return 1.
int insertAtTail(List* list_pointer, void* item);

// Insert a Node at the head of the list, containing a void pointer to item. The next pointer on the
// newly created node points to the previous head of hte list. On success return 0. On failure, return 1.
int insertAtHead(List* list_pointer, void* item);

// Insert a Node at the specified index, containing a void pointer to item. If the index is greater than
// the length of the list, the program should crash. On success return 0. On failure, return 1.
int insertAtIndex(List* list_pointer, int index, void* item);

// Remove Node from the end of list and return the void pointer it contains. The preceeding Node should
// point to NULL after this operation. On failure return a NULL pointer.
void* removeTail(List* list_pointer);

// Remove Node from start of list and return return the void pointer it contains. The following Node should 
// be the new head of the list. On failure return a NULL pointer.
void* removeHead(List* list_pointer);

// Insert Node item at a specified index and return return the void pointer it contains. The Node at the specified
// index before this function is called should be the next Node following the newly inserted Node.
// On failure return a NULL pointer.
void* removeAtIndex(List* list_pointer, int index);

// Return the pointer stored in the Node at the specified index. On failure return a NULL pointer. 
void* itemAtIndex(List* list_pointer, int index);
```

There is a print function that is already implemented for you. This will help you inspect the list as you write the above functions.

## Build Instructions

To build this program, user needs a gcc as C compiler to compile the program. For the files in the program folder, users need to build C library files to include the functions of Linked List(linkedlist.h and lib.c), and then include them to the main.c to use them. Before compileing main.c, users also need to link those two library files to the main.Also, users need to include stdlib.h and stdio.h in the files as well.

## Usage
The command to link and compile main.c is below: 
main: main.o liblinkedlist.a
	gcc main.o -o main -llinkedlist -L.

main.o: src/bin/main.c
	gcc src/bin/main.c -c -I include

liblinkedlist.a: src/lib.c
	gcc src/lib.c -c -I include
	ar rs liblinkedlist.a lib.o
The usage of the functions and structs in the library is below:
In the library, we have decleared two structs for the linked list: Node and List. Node contains two pointers, item(pointing the contains of this Node) and next(pointing to the next node of this node). List contains two pointers as well, head(pointing the first node of the list) and tail(pointing to the last node of the list). In order to use the functions, users need to first declare a pointer of List in the main and initilize it by initList function, which would assign the head and tail of that pointer of List to NULL.However, before initialize, users need to assign the memory space for the list. Using insertAtHead,insertAtTail, and insertAtIndex can insert a Node with given contains into the List in different position. Using removeHead,removeTail,removeAtIndex can remove a specifc node in the List and return back the contains of this removed node, and user need to use deference operator(*) to see the contains because it will return the address of contains. itemAtIndex can be used to check any node's contains, and it also requires users to use deference operator(*) to see the contains.


## Examples

 
 List* Linked_list = (List* )malloc(sizeof(List));
 if(Linked_list == NULL){
   exit(1)
 }
 initList(Linked_list);
 //so far the initialization is done
 //eg1.
 int x = 12;
 int y = 22;
 int z = 30;
 insertAtHead(Linked_List,&x);
 insertAtTail(Linked_List,&z);
 insertAtIndex(Linked_List,1,&y);
 printList(Linked_List);
 //eg2.
 int x = 12;
 int y = 22;
 int z = 30;
 insertAtHead(Linked_List,&x);
 insertAtTail(Linked_List,&z);
 insertAtIndex(Linked_List,1,&y);
 printList(Linked_List);
 printf("%d\n", *itemAtIndex(Linked_List,0));
 removeHead(Linked_List);
 removeAtIndex(Linked_List,0);
 printList(Linked_List);
  
