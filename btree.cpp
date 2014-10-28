/*
 *  B-Tree implementation
 *
 * Author: Mohammad Ghasembeigi
*/

//TEMP!!!!! remove after
#include "btree.h"
#include <map>

//Constructor
template <typename T>
btree<T>::btree(size_t maxNodeElems = 40) {
  maxElements = maxNodeElems;
}

//Copy semantics
template <typename T>
btree<T>::btree(const btree<T>& original) {
  maxElements = original.maxElements;
  root = original.root;

  //Recursively copy binary tree
  copyBTree(original.root, root);
}

//Helper Function: Copy nodes in btree recursively
template <typename T>
void btree<T>::copyBTree(Node *source, Node *dest) {
  //Iterate over node
  for(std::map<T, Element>::iterator it = source.elements.begin(); it != source.elements.end(); ++it) {
    //Copy values from this node

  }
}

/*

//Move semantics
template <typename T>
btree<T>::btree(btree<T>&& original) {

}

template <typename T>
btree<T>& btree<T>::operator=(const btree<T>& rhs) {
 
}

template <typename T>
btree<T>& btree<T>::operator=(btree<T>&& rhs) {

}

template <typename T>
std::ostream& operator<<(std::ostream& os, const btree<T>& tree) {

}

template <typename T>
typename btree<T>::iterator btree<T>::find(const T& elem) {
  
}

template <typename T>
typename btree<T>::const_iterator btree<T>::find(const T& elem) const {
  
}

template <typename T>
std::pair<typename btree<T>::iterator, bool> btree<T>::insert(const T& elem) {
  
}

template <typename T>
btree<T>::~btree() {

}

*/
