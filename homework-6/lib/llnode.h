#include<stdlib.h>
#include<stdio.h>
#include<iostream>


template <class T>
class Node {
  public:
    T item;
    size_t length;
    Node<T>* next;
    Node(T item);
    ~Node();
};


template <class T>
Node<T>::Node(T item){
  /*
  this->item = (T)malloc(sizeof(item));
  if(this->item == NULL){
    exit(1);
  }
  */
  this->item = item;
  this->length = sizeof(item);
  this->next = NULL;
}

template <class T>
Node<T>::~Node(){
  free(this->item);
}



