#ifndef hashTable_h
#define hashTable_h

#include <iostream>
#include <stdexcept>
#include <string>

#include "node.h"

using namespace std;

template <typename T>
class HashTable{
    
    public:
    
        HashTable();
        HashTable( const unsigned );
    
        bool empty() const;
        unsigned getSize() const;
        unsigned getCollisionNum() const;
    
        unsigned getHash( const string & ) const;
        void insert( const string & );
    
        bool search(const string &);
    
        void print();
    
        ~HashTable();
    
    private:
    
        Node<T> ** contents;
        unsigned sz;
        unsigned collisions;
    
};


template <typename T>
HashTable<T>::HashTable(){
    sz = 1000;
    contents = new Node<T> * [1000];
    collisions = 0;
    
    for(unsigned i = 0; i < sz; i++){
        contents[i] = NULL;
    }
    
}


template <typename T>
HashTable<T>::HashTable( const unsigned size ){
    
    sz = size;
    contents = new Node<T> * [size];
    collisions = 0;
    
    for(unsigned i = 0; i < sz; i++){
        contents[i] = NULL;
    }
    
}

template <typename T>
bool HashTable<T>::empty() const{
    return (sz == 0);
}

template <typename T>
unsigned HashTable<T>::getSize() const{
    return sz;
}

template <typename T>
unsigned HashTable<T>::getCollisionNum() const{
    return collisions;
}

template <typename T>
unsigned HashTable<T>::getHash( const string & key ) const{
    
    unsigned hashVal = 0;
    
    for( unsigned i = 0; i < key.length(); i++ ){
        hashVal = 37 * hashVal + key.at(i);
    }
    
    return (hashVal % sz);
    
}


template <typename T>
void HashTable<T>::insert( const string & key ) {

    unsigned index = getHash(key);
    
    if( contents[index] == NULL ){
        contents[index] = new Node<T>(key);
    }
    else{
        collisions++;
        Node<T> * temp = new Node<T> (key);
        temp->setNextPtr(contents[index]);
        contents[index] = temp;
    }

}

template <typename T>
bool HashTable<T>::search(const string & key) {
    
    
    unsigned index = getHash(key);
    
    if(contents[index] == NULL){
        return false;
    }
    else{
        Node<T> * temp = contents[index];
        while(temp != NULL){
            if(temp->getObject() == key){
                return true;
            }
            temp = temp->getNextPtr();
        }
    }
    
    return false;
    
    
    /*
    unsigned index = getHash(key);
    
    if(contents[index] == NULL){
        cout << "Not found" << endl;
        return false;
    }
    else if(contents[index]->getObject() == key){
        cout << "Found" << endl;
        return true;
    }
    else{
        Node<T> * ptr = contents[index];
        
        while(ptr->getObject() != key){
            ptr = ptr->getNextPtr();
            if(ptr == NULL){
                cout << "Not found"<< endl;
                return false;
            }
        }
        cout << "Found" << endl;
        return true;
    }
    cout << "Not found" << endl;
    return false;
    */
    
}

template <typename T>
void HashTable<T>::print(){
    
    
    for(unsigned i = 0; i < sz; i++){
        if(contents[i] != NULL){
            Node<T> * temp = contents[i];
            while(temp != NULL){
                cout << "Index: " << i << endl;
                cout << "Key: " << temp->getObject() << endl;
                cout << "Address: " << temp << endl;
                
                temp = temp->getNextPtr();
                
                cout << endl;
            }
        }
    }
}

template <typename T>
HashTable<T>::~HashTable(){
    
    for (unsigned i = 0; i < sz; i++){
        if (contents[i] != NULL) {
            Node<T> * prev = NULL;
            Node<T> * entry = contents[i];
            while (entry != NULL) {
                prev = entry;
                entry = entry->getNextPtr();
                delete prev;
            }
        }
    }
    delete [] contents;
    
}

    
#endif /* hashTable_h */
