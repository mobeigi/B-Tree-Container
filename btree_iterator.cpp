/*
* btree_iterator and const_btree_iterator implementations
*
* Each operation implementation is directly followed by the const equivalent implementation.
*/

//Operator*
template <typename T>
T& btree_iterator<T>::operator*() const {
  //Dereferencing returns element value iterator points to
  return it->second.value;
}

template <typename T>
const T& const_btree_iterator<T>::operator*() const {
  //Dereferencing returns element value iterator points to
  return it->second.value;
}

//Operator++
template <typename T>
btree_iterator<T>& btree_iterator<T>::operator++() {
  //LEFT
  if (it->second.leftChild != nullptr && !didTraverse) {

    //If so, update current node
    node = it->second.leftChild;
    
    //expand it and traverse downwards (left)
    forward_traverse_down(node, it);
  }

  //EXIT
  else if (it == node->elements.end() && node->parent == nullptr && didTraverse) {
    it = node->elements.end();

  }

  //FORWARD
  else {
    didTraverse = false; //reset didTraverse

    //inc
    ++it;

    if (it == node->elements.end() ) {

      --it;

      //Check right if exists
      if (it->second.rightChild != nullptr) {
        node = it->second.rightChild;
        forward_traverse_down(node, it);
      }
      else {
        forward_traverse_up(node, ++it);
      }
    }
    //Otherwise, expand any left elements this node has (we work from bottom to top)
    else if (it->second.leftChild != nullptr) {
      node = it->second.leftChild;
      forward_traverse_down(node, it);
    }

  }
  return *this;
}

template <typename T>
const_btree_iterator<T>& const_btree_iterator<T>::operator++() {
  //Check if left child exists
  if (it->second.leftChild != nullptr && !didTraverse) {
    //If so, update current node
    node = it->second.leftChild;

    //expand it and traverse downwards (left)
    forward_traverse_down(node, it);
  }
  //Otherwise we will traverse along current node
  else {
    didTraverse = false; //reset didTraverse

    ++it; //Point iterator to next element in node

    //If we have reached the end of the node and this is not the root node
    if (it == node->elements.end() && node->parent != nullptr) {
      //Traverse up to parent node
      forward_traverse_up(node, it);
    }
    //Otherwise, expand any left elements this node has (we work from bottom to top)
    else if (it->second.leftChild != nullptr) {
      node = it->second.leftChild;
      forward_traverse_down(node, it);
    }
  }

  return *this;
}

//Operator==
template <typename T>
bool btree_iterator<T>::operator==(const btree_iterator& other) const {
  return (node == other.node && it == other.it);
}

template <typename T>
bool const_btree_iterator<T>::operator==(const const_btree_iterator& other) const {
  return (node == other.node && it == other.it);
}


/*
 * Helper functions used for repetitive operations as we move between levels in the BTree.
 * Again, operations are directly followed by their const equivalent implementation.
*/

/*
 * forward_traverse_down moves down recursively to the lowest node with a left child link.
 * This ensures you are at the node with the next (lowest) value.
*/
template <typename T>
void btree_iterator<T>::forward_traverse_down(typename btree<T>::Node *n,
  typename std::map<T, typename btree<T>::Element>::iterator& it) {

  //Set iterator to provided nodes starting element
  it = n->elements.begin();

  //While a left child exists, expand it
  if (it->second.leftChild != nullptr) {
    node = it->second.leftChild;  //Set current node
    forward_traverse_down(node, it);  //keep traversing down recursively to get lowest node
  }

}

//Const implementation of above
template <typename T>
void const_btree_iterator<T>::forward_traverse_down(const typename btree<T>::Node *n,
  typename std::map<T, typename btree<T>::Element>::const_iterator& it) {

  //Set iterator to provided nodes starting element
  it = n->elements.begin();

  //While a left child exists, expand it
  if (it->second.leftChild != nullptr) {
    node = it->second.leftChild;  //Set current node
    forward_traverse_down(node, it);  //keep traversing down recursively to get lowest node
  }

}

/*
* forward_traverse_up moves up recursively to the next element in parent nodes.
* This ensures you are at the the next node with the next value as all left links/childs have been exhausted.
*/

template <typename T>
void btree_iterator<T>::forward_traverse_up(typename btree<T>::Node *n,
  typename std::map<T, typename btree<T>::Element>::iterator& it) {

  //Decrement iterator so we have valid (last) location
  --it;

  //Set didTraverse to true so parent node knows we have already searched left child of next element
  didTraverse = true;

  //Get value at this location
  T value = it->first;

  //Set current node to parent of provided node and set iterator to the 'next value' after stored value
  node = n->parent;
  it = node->elements.upper_bound(value);

  //If we reached the end of this node and parents exist, continue traversing up recursively
  if (it == node->elements.end() && node->parent != nullptr) {
    forward_traverse_up(node, it);
  }

}

template <typename T>
void const_btree_iterator<T>::forward_traverse_up(const typename btree<T>::Node *n,
  typename std::map<T, typename btree<T>::Element>::const_iterator& it) {

  //Decrement iterator so we have valid (last) location
  --it;

  //Set didTraverse to true so parent node knows we have already searched left child of next element
  didTraverse = true;

  //Get value at this location
  T value = it->first;

  //Set current node to parent of provided node and set iterator to the 'next value' after stored value
  node = n->parent;
  it = node->elements.upper_bound(value);

  //If we reached the end of this node and parents exist, continue traversing up recursively
  if (it == node->elements.end() && node->parent != nullptr) {
    forward_traverse_up(node, it);
  }

}

/*
* reverse_traverse_down moves down recursively to the highest node with a right child link.
* This ensures you are at the node with the next (highest) value.
*/
template <typename T>
void btree_iterator<T>::reverse_traverse_down(typename btree<T>::Node *n,
  typename std::map<T, typename btree<T>::Element>::iterator& it) {


}

template <typename T>
void const_btree_iterator<T>::reverse_traverse_down(const typename btree<T>::Node *n,
  typename std::map<T, typename btree<T>::Element>::const_iterator& it) {


}

/*
* reverse_traverse_up moves up recursively to the previous element in parent nodes.
* This ensures you are at the the previous node with the next lowest value as all right links/childs have been exhausted.
*/
template <typename T>
void btree_iterator<T>::reverse_traverse_up(typename btree<T>::Node *n,
  typename std::map<T, typename btree<T>::Element>::iterator& it) {


}

template <typename T>
void const_btree_iterator<T>::reverse_traverse_up(const typename btree<T>::Node *n,
  typename std::map<T, typename btree<T>::Element>::const_iterator& it) {


}