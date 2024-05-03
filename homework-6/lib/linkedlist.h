#include <stdlib.h>
#include<stdio.h>
#include<stdbool.h>
#include"llnode.h"
#include<iostream>
//#ifndef _LLNODE_H_
//#define _LLNODE_H_
//include "llnode.h"
//#endif



template <class T>
class LinkedList {
//private:
    //Node<T>* head;
   // Node<T>* tail;
public:
	  Node<T>* head;
    Node<T>* tail;
    size_t length;////////////////size_t
    LinkedList();
    ~LinkedList();
    size_t insertAtTail(LinkedList* list_pointer, T item);
    size_t insertAtHead(LinkedList* list_pointer, T item);
    size_t insertAtIndex(LinkedList* list_pointer, size_t index, T item);
    T removeTail(LinkedList* list_pointer);
    T removeHead(LinkedList* list_pointer);
    T removeAtIndex(LinkedList* list_pointer, size_t index);
		size_t find(LinkedList* list_pointer, T item);
		void printList(LinkedList* list_pointer);

};

template<class T>
LinkedList<T>::LinkedList(){
  this->head = NULL;
  this->tail = NULL;
  this->length = 0;
}

template <class T>
LinkedList<T>::~LinkedList(){
  free(this->head);
  free(this->tail);
}

template<class T>
size_t LinkedList<T>::insertAtTail(LinkedList* list_pointer, T item){
  Node<T>* newNode = new Node<T>(item);
  list_pointer->tail->next = newNode;
  list_pointer->tail = newNode;
  list_pointer->length ++;
  return 0;
}

template <class T>
size_t LinkedList<T>::insertAtHead(LinkedList* list_pointer, T item){
  Node<T>* position = new Node<T>(item);
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

template <class T>
size_t LinkedList<T>::insertAtIndex(LinkedList* list_pointer, size_t index, T item){
  if(index > list_pointer->length){
		exit(1);
	}
  Node<T>* position = new Node<T>(item);
  if(index == 0){
		return insertAtHead(list_pointer, item);
	}
  else if(index == list_pointer->length){
		return insertAtTail(list_pointer,item);
	}
  else{
		Node<T>* current_Node = (Node<T>* )malloc(sizeof(list_pointer->head));
		if(current_Node == NULL){
			exit(1);
		}
		current_Node = list_pointer->head;
		int i = 0;
		while(current_Node != NULL){
			if(i == index - 1){
				Node<T>* next_Node = (Node<T>* )malloc(sizeof(current_Node->next));
				if(next_Node == NULL){
					exit(1);
				}
				next_Node = current_Node->next;
				current_Node->next = position;
				position->next = next_Node;
				list_pointer->length++;
			}
			current_Node = current_Node->next;
			i++;
		}
		return 0;
	}
}

template <class T>
T LinkedList<T> :: removeTail(LinkedList* list_pointer){
	printf("Jb\n");
	Node<T>* current_Node = (Node<T>* )malloc(sizeof(list_pointer->head));
	if(current_Node == NULL){
		exit(1);
	}
	current_Node = list_pointer->head;
	/*
	T item = (T ) malloc(sizeof(list_pointer->tail->item));
	if(item == NULL){
		exit(1);
	}
	*/
	T item = current_Node->item;
	int index = 0;
	while(current_Node != NULL){
		if(index == list_pointer->length - 2){
			item = current_Node->next->item;
			//list_pointer->tail = NULL;
			current_Node->next = NULL;
			list_pointer->tail = current_Node;
			//list_pointer->tail->next = NULL;
			//free(current_Node);
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

template <class T>
T LinkedList<T>::removeHead(LinkedList* list_pointer){
	/*
	T item = (T )malloc(sizeof(list_pointer->head->item));
	if(item == NULL){
		exit(1);
	}
	*/
	T item = list_pointer->head->item;
	Node<T>* head = list_pointer->head;
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

template <class T>
T LinkedList<T>::removeAtIndex(LinkedList* list_pointer, size_t index){
	int i = 0;
	Node<T>* current_Node = (Node<T>* )malloc(sizeof(list_pointer->head));
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
		T item;
		while(current_Node != NULL){
			if(i == index - 1){
				Node<T>* target = (Node<T>* )malloc(sizeof(current_Node->next));
				if(target == NULL){
					exit(1);
				}
				target = current_Node->next;
				Node<T>* next_Node = (Node<T>* )malloc(sizeof(target->next));
				if(next_Node == NULL){
					exit(1);
				}
				next_Node = target->next;
				/*
				item = (T ) malloc(sizeof(target->item));
				if(item == NULL){
					exit(1);
				}
				*/
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

template<class T>
void LinkedList<T>::printList(LinkedList* list_pointer){
	
	Node<T>* current_Node = list_pointer->head;
	
	while(current_Node != NULL){
		printf("%d\t", current_Node->item);
		current_Node = current_Node->next;
	}
	printf("\n");
}

template<class T>
size_t LinkedList<T>::find(LinkedList* list_pointer, T item){
	size_t i = 0;
	Node<T>* current_Node = list_pointer->head;
	
	while(current_Node != NULL){
		if(current_Node->item == item){
			return i;
		}
		current_Node = current_Node->next;
		i++;
		
	}
	return 100;//case for not found
}