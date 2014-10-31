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

//Operator=
template <typename T>
btree_iterator<T>& btree_iterator<T>::operator=(const btree_iterator<T>& other) {
  //Set iterator fields
  node = other.node;
  it = other.it;
  didTraverse = other.didTraverse;

  return *this;
}

template <typename T>
const_btree_iterator<T>& const_btree_iterator<T>::operator=(const const_btree_iterator<T>& other) {
  //Set iterator fields
  node = other.node;
  it = other.it;
  didTraverse = other.didTraverse;

  return *this;
}

//Operator++
template <typename T>
btree_iterator<T>& btree_iterator<T>::operator++() {
  //If we there are lower values, explore them first
  if (it->second.leftChild != nullptr && !didTraverse) {

    //Update current node
    node = it->second.leftChild;
    
    //expand it and traverse downwards (left)
    forward_traverse_down(node, it);
  }
  //Otherwise, go forward to next element in node
  else {
    didTraverse = false; //reset didTraverse

    //Increment iterator to next element
    ++it;

    //If this element is end(),
    if (it == node->elements.end() ) {

      //Take iterator of last element
      --it;

      //Check if a right child exists
      if (it->second.rightChild != nullptr) {
        //If so explore the left most element in right child
        node = it->second.rightChild;
        forward_traverse_down(node, it);
      }
      //Otherwise, go to parent node if it exists
      else if (node->parent != nullptr) {
        forward_traverse_up(node, ++it);
      }
      //Otherwise this is root node (no parent) and we've exhausted the btree, set iterator to end()
      else {
        it = node->elements.end();
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
  //If we there are lower values, explore them first
  if (it->second.leftChild != nullptr && !didTraverse) {

    //Update current node
    node = it->second.leftChild;

    //expand it and traverse downwards (left)
    forward_traverse_down(node, it);
  }
  //Otherwise, go forward to next element in node
  else {
    didTraverse = false; //reset didTraverse

    //Increment iterator to next element
    ++it;

    //If this element is end(),
    if (it == node->elements.end()) {

      //Take iterator of last element
      --it;

      //Check if a right child exists
      if (it->second.rightChild != nullptr) {
        //If so explore the left most element in right child
        node = it->second.rightChild;
        forward_traverse_down(node, it);
      }
      //Otherwise, go to parent node if it exists
      else if (node->parent != nullptr) {
        forward_traverse_up(node, ++it);
      }
      //Otherwise this is root node (no parent) and we've exhausted the btree, set iterator to end()
      else {
        it = node->elements.end();
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


//Operator++ post increment
template <typename T>
btree_iterator<T>& btree_iterator<T>::operator++(int) {
  btree_iterator<T> *copy = new btree_iterator<T>(node, it);
  ++(*this);
  return *copy;
}

template <typename T>
const_btree_iterator<T>& const_btree_iterator<T>::operator++(int) {
  const_btree_iterator<T> *copy = new const_btree_iterator<T>(node, it);
  ++(*this);
  return *copy;
}

//Operator--
template <typename T>
btree_iterator<T>& btree_iterator<T>::operator--() {

  //Special Case: For very first element, set iterator to correct location, either 1 left of rbegin
  //Or the lowest and right-most element via right child links
  if (it == node->elements.end() && node->parent == nullptr) {
    --it;

    //If no links exist, the first element is the beginning
    if (it->second.rightChild == nullptr) {
      return *this;
    }
  }

  //Expand the right child if it exists
  if (it->second.rightChild != nullptr && !didTraverse) {
    //Update current node
    node = it->second.rightChild;

    //expand it and traverse downwards (right)
    reverse_traverse_down(node, it);
  }
  //Otherwise, go to previous element in node
  else {
    didTraverse = false; //reset didTraverse

    //If this element is begin(),
    if (it == node->elements.begin()) {

      //Check if a left child exists
      if (it->second.leftChild != nullptr) {
        //If so explore the right most element in left child
        node = it->second.leftChild;
        reverse_traverse_down(node, it);
      }
      //Otherwise, go to parent node if it exists
      else if (node->parent != nullptr) {
        reverse_traverse_up(node, it);
      }
      //Otherwise this is root node (no parent) and we've exhausted the btree, set iterator to rend()
      else {
        it = node->elements.begin();
      }
    }
    //If left child exists, expand it as it will always contain next value
    else if (it->second.leftChild != nullptr) {
      node = it->second.leftChild;
      reverse_traverse_down(node, it);
    }
    //Simply go to previous element
    else {
      --it;
    }
  }

  return *this;
}

template <typename T>
const_btree_iterator<T>& const_btree_iterator<T>::operator--() {
  //Special Case: For very first element, set iterator to correct location, either 1 left of rbegin
  //Or the lowest and right-most element via right child links
  if (it == node->elements.end() && node->parent == nullptr) {
    --it;

    //If no links exist, the first element is the beginning
    if (it->second.rightChild == nullptr) {
      return *this;
    }
  }

  //Expand the right child if it exists
  if (it->second.rightChild != nullptr && !didTraverse) {
    //Update current node
    node = it->second.rightChild;

    //expand it and traverse downwards (right)
    reverse_traverse_down(node, it);
  }
  //Otherwise, go to previous element in node
  else {
    didTraverse = false; //reset didTraverse

    //If this element is begin(),
    if (it == node->elements.begin()) {

      //Check if a left child exists
      if (it->second.leftChild != nullptr) {
        //If so explore the right most element in left child
        node = it->second.leftChild;
        reverse_traverse_down(node, it);
      }
      //Otherwise, go to parent node if it exists
      else if (node->parent != nullptr) {
        reverse_traverse_up(node, it);
      }
      //Otherwise this is root node (no parent) and we've exhausted the btree, set iterator to rend()
      else {
        it = node->elements.begin();
      }
    }
    //If left child exists, expand it as it will always contain next value
    else if (it->second.leftChild != nullptr) {
      node = it->second.leftChild;
      reverse_traverse_down(node, it);
    }
    //Simply go to previous element
    else {
      --it;
    }
  }

  return *this;
}

//Operator-- post decrement
template <typename T>
btree_iterator<T>& btree_iterator<T>::operator--(int) {
  btree_iterator<T> *copy = new btree_iterator<T>(node, it);
  --(*this);
  return *copy;
}

template <typename T>
const_btree_iterator<T>& const_btree_iterator<T>::operator--(int) {
  const_btree_iterator<T> *copy = new const_btree_iterator<T>(node, it);
  --(*this);
  return *copy;
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

template <typename T>
bool const_btree_iterator<T>::operator==(const btree_iterator<T>& other) const {
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

  //Set iterator to provided nodes last element
  it = n->elements.end();
  --it; //set to element before end (last element)

  //While a right child exists, expand it
  if (it->second.rightChild != nullptr) {
    node = it->second.rightChild;  //Set current node
    reverse_traverse_down(node, it);  //keep traversing down recursively to get lowest node
  }

}

template <typename T>
void const_btree_iterator<T>::reverse_traverse_down(const typename btree<T>::Node *n,
  typename std::map<T, typename btree<T>::Element>::const_iterator& it) {
  //Set iterator to provided nodes last element
  it = n->elements.end();
  --it; //set to element before end (last element)

  //While a right child exists, expand it
  if (it->second.rightChild != nullptr) {
    node = it->second.rightChild;  //Set current node
    reverse_traverse_down(node, it);  //keep traversing down recursively to get lowest node
  }
}

/*
* reverse_traverse_up moves up recursively to the previous element in parent nodes.
* This ensures you are at the the previous node with the next lowest value as all right links/childs have been exhausted.
*/
template <typename T>
void btree_iterator<T>::reverse_traverse_up(typename btree<T>::Node *n,
  typename std::map<T, typename btree<T>::Element>::iterator& it) {

  //Set didTraverse to true so parent node knows we have already searched left/right child of next element
  didTraverse = true;

  //Get value at this location
  T value = it->first;

  //Set current node to parent of provided node and set iterator to the 'next value' after stored value
  node = n->parent;
  it = node->elements.upper_bound(value);

  //If we reached the end of this node and parents exist, continue traversing up recursively
  if (it == node->elements.begin() && node->parent != nullptr) {
    reverse_traverse_up(node, it);
  }
  //Otherwise decrement to set correct position
  else {
    --it;
  }

}

template <typename T>
void const_btree_iterator<T>::reverse_traverse_up(const typename btree<T>::Node *n,
  typename std::map<T, typename btree<T>::Element>::const_iterator& it) {
  //Set didTraverse to true so parent node knows we have already searched left/right child of next element
  didTraverse = true;

  //Get value at this location
  T value = it->first;

  //Set current node to parent of provided node and set iterator to the 'next value' after stored value
  node = n->parent;
  it = node->elements.upper_bound(value);

  //If we reached the end of this node and parents exist, continue traversing up recursively
  if (it == node->elements.begin() && node->parent != nullptr) {
    reverse_traverse_up(node, it);
  }
  //Otherwise decrement to set correct position
  else {
    --it;
  }
}
