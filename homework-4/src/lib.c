#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

void printList(List* list) {
	Node* node;

  	// Handle an empty node. Just print a message.
	if(list->head == NULL) {
		printf("\nEmpty List");
		return;
	}
	
  	// Start with the head.
	node = (Node*) list->head;

	printf("\nList: \n\n\t"); 
	while(node != NULL) {
		printf("[ %x ]", node->item);

		// Move to the next node
		node = (Node*) node->next;

		if(node !=NULL) {
			printf("-->");
		}
	}
	printf("\n\n");
}

// Initialize an empty list
void initList(List* list_pointer){
	list_pointer->head = NULL;
	list_pointer->tail = NULL;
	list_pointer->length = 0;
}

// Create node containing item, return reference of it.
Node* createNode(void* item){
	Node* new_Node;
	new_Node = (Node* ) malloc(sizeof(item));
	if(new_Node == NULL){
		exit(1);
	}
	new_Node->item = item;
	new_Node->next = NULL;
	return new_Node;
}

// Insert new item at the end of list.
int insertAtTail(List* list_pointer, void* item){
	Node* position = (Node* )createNode(item);
	if(position == NULL){
		return 1;
	}
	list_pointer->tail->next = position;
	list_pointer->tail = position;
	list_pointer->length ++;
	return 0;
}

// Insert item at start of the list.
int insertAtHead(List* list_pointer, void* item){
	Node* position = (Node* )createNode(item);
	if(position == NULL){
		return 1;
	}
	if(list_pointer->length == 0){
		list_pointer->head = position;
		list_pointer->tail = position;
		list_pointer->length++;
	}
	else{
		position->next = list_pointer->head;
		list_pointer->head = position;
		list_pointer->length ++;
	}
	return 0;
}

// Insert item at a specified index.
int insertAtIndex(List* list_pointer, int index, void* item){
	if(index > list_pointer->length){
		exit(1);
	}
	Node* position = (Node* )createNode(item);
	if(position == NULL){
		return 1;
	}
	if(index == 0){
		int result = insertAtHead(list_pointer, item);
		return result;
	}
	else if(index == list_pointer->length){
		int result = insertAtTail(list_pointer,item);
		return result;
	}
	else{
		Node* current_Node = (Node* )malloc(sizeof(list_pointer->head));
		if(current_Node == NULL){
			exit(1);
		}
		current_Node = list_pointer->head;
		int i = 0;
		while(current_Node != NULL){
			if(i == index - 1){
				Node* next_Node = (Node* )malloc(sizeof(current_Node->next));
				if(next_Node == NULL){
					exit(1);
				}
				next_Node = current_Node->next;
				current_Node->next = position;
				//curent_Node->next->next = position;
				position->next = next_Node;
				list_pointer->length++;
			}
			current_Node = current_Node->next;
			i++;
		}
		return 0;
	}
}

// Remove item from the end of list and return a reference to it
void* removeTail(List* list_pointer){
	Node* current_Node = (Node* )malloc(sizeof(list_pointer->head));
	if(current_Node == NULL){
		exit(1);
	}
	current_Node = list_pointer->head;
	
	void* item = (void* ) malloc(sizeof(list_pointer->tail->item));
	if(item == NULL){
		exit(1);
	}
	
	int index = 0;
	while(current_Node != NULL){
		if(index == list_pointer->length - 1){
			item = current_Node->item;
			list_pointer->tail = NULL;
			list_pointer->tail = current_Node;
			list_pointer->tail->next = NULL;
			free(current_Node);
			list_pointer->length --;
		}
		current_Node = current_Node->next;
		index++;
	}
	if(item == NULL){
		return NULL;
	}
	else{
		return item;
	}
}

// Remove item from start of list and return a reference to it
void* removeHead(List* list_pointer){
	void* item = (void* )malloc(sizeof(list_pointer->head->item));
	if(item == NULL){
		exit(1);
	}
	item = list_pointer->head->item;
	Node* head = list_pointer->head;
	list_pointer->head = NULL;
	list_pointer->head = head->next;
	free(head);
	list_pointer->length --;
	if(item == NULL){
		return NULL;
	}
	else{
		return item;
	}
}

// remove item at a specified index and return a reference to it
void* removeAtIndex(List* list_pointer, int index){
	int i = 0;
	Node* current_Node = (Node* )malloc(sizeof(list_pointer->head));
	if(current_Node == NULL){
		exit(1);
	}
	current_Node = list_pointer->head;
	if(index > list_pointer->length){
		exit(1);
	}
	else if(index == 0){
		return removeHead(list_pointer);
	}
	else if(index == list_pointer->length){
		return removeTail(list_pointer);
	}
	else{
		void* item;
		while(current_Node != NULL){
			if(i == index - 1){
				Node* target = (Node* )malloc(sizeof(current_Node->next));
				if(target == NULL){
					exit(1);
				}
				target = current_Node->next;
				Node* next_Node = (Node* )malloc(sizeof(target->next));
				if(next_Node == NULL){
					exit(1);
				}
				next_Node = target->next;
				item = (void* ) malloc(sizeof(target->item));
				if(item == NULL){
					exit(1);
				}
				item = target->item;
				target = NULL;
				current_Node->next = next_Node;
				free(target);
				return item;
			}
			current_Node = current_Node->next;
			i++;
		}
		if(item == NULL){
			return NULL;
		}
	}
}

// Return item at index
void* itemAtIndex(List* list_pointer, int index){
	int i = 0;
	Node* current_Node = NULL;
	if(list_pointer == NULL){
		return NULL;
	}
	current_Node = list_pointer->head;
	while(current_Node != NULL){
		if(i == index){
			return current_Node->item;
		}
		current_Node = current_Node->next;
		i++;
	}
	return NULL;
	/*
	Node* current_Node = (Node *)malloc(sizeof(list_pointer->head));
	if(current_Node == NULL){
		exit(1);
	}
	current_Node = list_pointer->head;
	int i = 0;
	if(index > list_pointer->length){
		exit(1);
	}
	void* item;
	while(current_Node != NULL){
		if(i == index){
			item = (void* )malloc(sizeof(current_Node->item));
			if(item == NULL){
				exit(1);
			}
			item = current_Node->item;
			return item;
		}
		current_Node = current_Node->next;
		i++;
	}
	if(item == NULL){
		return NULL;
	}
	*/
}







