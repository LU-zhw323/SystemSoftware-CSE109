/* Modify this prehash function to work with a template type T instead of a char*
unsigned long prehash(unsigned char *str) {
    unsigned long h = 5381;
    int c;
    while (c = *str++) { 
	    h = ((h << 5) + h) + c;
    }
    return h;
}*/

#include"linkedlist.h"
#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<math.h>

template <class T>
class HashSet {
  private:
    // The backbone of the hash set. This is an array of Linked List pointers.
    LinkedList<T>** array;
    

    // The number of buckets in the array
    size_t size; 
    size_t loadfactor;

    // Generate a prehash for an item with a given size
    unsigned long prehash(T item){
        unsigned long h = 5381;
        int c;
        while (c = item++) { 
            h = ((h << 5) + h) + c;
        }
        return h;
    }

  public:
    // Initialize an empty hash set, where size is the number of buckets in the array
    HashSet(size_t size){
        this->size = size;///////////////////////////////
        this->loadfactor = 0;
        this->array = (LinkedList<T>** )malloc (this->size * sizeof(LinkedList<T>*));
        for(int i = 0; i < this->size; i++){
            *(this->array+i)= (LinkedList<T>* )malloc(sizeof(LinkedList<T>));
            *(this->array+i) = new LinkedList<T>();
        }
    }

    HashSet(){
        this->size = 10;
        this->loadfactor = 0;
        this->array = (LinkedList<T>** )malloc (this->size * sizeof(LinkedList<T>*));
        for(int i = 0; i < this->size; i++){
           *(this->array+i)= (LinkedList<T>* )malloc(sizeof(LinkedList<T>));
            *(this->array+i) = new LinkedList<T>();
        }
    }

    // Free all memory allocated by the hash set
    ~HashSet(){
        free(this->array);
    }

    // Hash an unsigned long into an index that fits into a hash set
    unsigned long hash(T item){
        unsigned long Pre = prehash(item);
        unsigned long HA = Pre % this->size;
        return HA;
    }
    // Resize the underlying table to the given size. Recalculate the load factor after resize
    void resize(size_t new_size){
        size_t copySize = this->size;
        this->size = new_size;
        LinkedList<T>** copy = (LinkedList<T>** )malloc (copySize * sizeof(LinkedList<T>*));
        for(int i = 0; i < copySize; i++){
           *(copy+i)= (LinkedList<T>* )malloc(sizeof(LinkedList<T>));
            *(copy+i) = new LinkedList<T>();
        }
        for(int i = 0; i < copySize; i++){
            *(copy+i) = *(this->array+i);
        }
        free(this->array);
        this->array = (LinkedList<T>** )malloc (new_size * sizeof(LinkedList<T>*));
        for(int i = 0; i < new_size; i++){
            *(this->array+i)= (LinkedList<T>* )malloc(sizeof(LinkedList<T>));
            *(this->array+i) = new LinkedList<T>();
        }
        for(int i = 0; i < copySize; i++){
            LinkedList<T>* L = *(copy+i);
            Node<T>* node = L->head;
            while(node != NULL){
                T item = node->item;
                unsigned long Load = hash(item);
                LinkedList<T>* R = *(this->array+Load);
                R->insertAtHead(R,item);
                node = node->next;
            }
        }
        free(copy);
        //this->size = new_size;

        /*
        this->array = (LinkedList<T>** )malloc(new_size * sizeof(LinkedList<T>*));
        for(int i = this->size; i < new_size; i++){
            *(this->array+i)= (LinkedList<T>* )malloc(sizeof(LinkedList<T>));
            *(this->array+i) = new LinkedList<T>();
        }
        this->size = new_size;
        */
    }


    // Insert item in the set. Return true if the item was inserted, false if it wasn't (i.e. it was already in the set)
    // Recalculate the load factor after each successful insert (round to nearest whole number).
    // If the load factor exceeds 70 after insert, resize the table to hold twice the number of buckets.
    bool insert(T item){
        unsigned long Load = hash(item);
        
        LinkedList<T>* L = *(this->array+Load);
        size_t result = L->find(L,item);
        
        if(result != 100){
            return false;
        }//check duplicate insert
        else{
            if(this->loadfactor >= (this->size * 0.7)){
                resize((this->size*2));
            }
            L->insertAtHead(L,item);
            this->loadfactor++;
            return true;
        }
        /*
        this->size++;
        size_t loadFactor = 0.7*this->size;
        if(Load >= loadFactor){

        }
        else{
            return true;
        }
        */
    }

    // Remove an item from the set. Return true if it was removed, false if it wasn't (i.e. it wasn't in the set to begin with)
    bool remove(T item){
        unsigned long target=hash(item);
        LinkedList<T>* L = *(this->array+target);
        size_t result = L->find(L,item);
        if(result==100){
            return false;
        }//case for not found
        else{
           T Rresult = L->removeAtIndex(L,result);
           if(Rresult != NULL){
               return true;
           }
           else{
               return false;
           }
        }
    }

    // Return true if the item exists in the set, false otherwise
    bool contains(T item){
        
        unsigned long Load = hash(item);
        
        LinkedList<T>* L = *(array+Load);
        size_t result = L->find(L,item);
        
        if(result == 100){
           
            return false;
        }
        else{
            return true;
        }
    }

    

    // Returns the number of items in the hash set
    size_t len(){
        
        int result=0;
        LinkedList<T>* L = *(this->array);
        for(int i = 0; i < this->size; i++){
            L = *(this->array+i);
            
            result += L->length;
            
        }
        return result;
    }

    // Returns the number of items the hash set can hold before reallocating
    size_t capacity(){
        size_t CA = (0.7 * this->size)-1;
        return CA;
    }

    // Print Table. You can do this in a way that helps you implement your hash set.
    void print(){
        int i = 0;
        LinkedList<T>* L = *(this->array+i);
        
        while(L != NULL){
            printf("bucket: %d\t",i);
            L->printList(L);
            i++;
            L = *(this->array+i);
        }
    }

};