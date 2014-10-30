/*
 *  B-Tree implementation
 *
 * Author: Mohammad Ghasembeigi
*/

//TEMP!!!!! remove after
#include <queue>
#include <utility>

/*
* Copy Semantics
*/
template <typename T>
btree<T>::btree(const btree<T>& original) {
  maxElements = original.maxElements;
  root = original.root;

  //Recursively copy binary tree using helper function
  copyBTree(&original.root, nullptr, &root);
}

/*
 * Helper Function : Copy nodes in btree recursively.
*/
template <typename T>
void btree<T>::copyBTree(const Node *source, Node *parent, Node *dest) {
  queue<Node*> sourceChilds;
  queue<Node*> destChilds;

  //Copy map from source to dest
  dest->elements = source->elements;

  //Copy parent
  dest->parent = parent;

  //For each node
  auto dit = dest->elements.begin();

  for (auto sit = source->elements.begin(); sit != source->elements.end(); ++sit, ++dit) {
    //Check left child for a valid node to copy
    if (sit->second.leftChild != nullptr) {
      //Make new node with this node as its parent
      Node *newNode = new Node(dest);

      sourceChilds.push(sit->second.leftChild);
      destChilds.push(newNode);
      dit->second.leftChild = newNode;
    }

    //Check right child for a valid node to copy
    if (sit->second.rightChild != nullptr) {
      //Make new node with this node as its parent
      Node *newNode = new Node(dest);

      sourceChilds.push(sit->second.rightChild);
      destChilds.push(newNode);
      dit->second.rightChild = newNode;
    }
  }

  //For each children
  while (!sourceChilds.empty()) {
    //Get front node
    Node *nextSource = sourceChilds.front();
    Node *nextDest = destChilds.front();

    //Pop it off queue
    sourceChilds.pop();
    destChilds.pop();

    //Recursively copy child nodes with this node as the parent
    copyBTree(nextSource, dest, nextDest);
  }
}

/*
* Move Semantics
*
* Move over root node and update all child nodes parents to point to new moved root.
* Leave moved from object in valid state by nullifing all left and right child links.
*/
template <typename T>
btree<T>::btree(btree<T>&& original) {
  maxElements = original.maxElements;
  root = std::move(original.root);

  //Iterate through root elements
  for (auto it = root.elements.begin(); it != root.elements.end(); ++it) {
    //For each valid child, update the parent node to newely moved node
    if (it->second.leftChild != nullptr) {
      it->second.leftChild->parent = &root;
    }

    if (it->second.rightChild != nullptr) {
      it->second.rightChild->parent = &root;
    }
  }

  //We have to leave original in a valid state
  //We must nullify its child links so that it can destruct correctly
  for (auto it = original.root.elements.begin(); it != original.root.elements.end(); ++it) {
    it->second.leftChild = it->second.rightChild = nullptr;
  }
}

/*
 * Operater= Copy Semantics 
 *
 * TODO: Fix semantics, should this or copy constructor be using each other?
*/
template <typename T>
btree<T>& btree<T>::operator=(const btree<T>& rhs) {
  maxElements = rhs.maxElements;
  root = rhs.root;
  
  //Recursively copy binary tree using helper function
  copyBTree(&rhs.root, nullptr, &root);

  //Return this pointer
  return *this;
}

/*
* Operater= Move Semantics
*/
template <typename T>
btree<T>& btree<T>::operator=(btree<T>&& rhs) {
  maxElements = rhs.maxElements;
  root = std::move(rhs.root);

  //Iterate through root elements
  for (auto it = root.elements.begin(); it != root.elements.end(); ++it) {
    //For each valid child, update the parent node to newely moved node
    if (it->second.leftChild != nullptr) {
      it->second.leftChild->parent = &root;
    }

    if (it->second.rightChild != nullptr) {
      it->second.rightChild->parent = &root;
    }
  }

  //We have to leave original in a valid state
  //We must nullify its child links so that it can destruct correctly
  for (auto it = rhs.root.elements.begin(); it != rhs.root.elements.end(); ++it) {
    it->second.leftChild = it->second.rightChild = nullptr;
  }

  return *this;
}

/*
* Print out tree values in breadth-first (level) order.
* Assumes << operator is implemented on type T
*
* Complexity: O(log n) to find last element in BTree and O(n) to print out each value
* TODO: Improve complexity by implementing proper end()
*/
template <typename T>
std::ostream& operator<<(std::ostream& os, const btree<T>& tree) {

  //Determine value of last element in this BTree
  typename std::map<T, typename btree<T>::Element>::const_iterator it = tree.root.elements.end();

  //Get last element in root
  --it;

  //Get lowest rightmost value, this will be last element in BTree
  while (it->second.rightChild != nullptr) {
    it = it->second.rightChild->elements.end();
    --it;
  }

  //Delegate printing to recursive helper function
  btree<T>::printBTree(os, &tree.root, it->first);

  return os;
}

/*
 * Helper Function: Print out node contents recursively with a single space between each element
 * A final space is not printed for the final value. This required the passing of the value by reference and works as this value will be unique.
*/
template <typename T>
void btree<T>::printBTree(std::ostream& os, const Node *node, const T &lastValue) {
  queue<Node*> childs;

  //Print out elements in this node
  for (auto it = node->elements.cbegin(); it != node->elements.cend(); ++it) {
    //Print out value
    os << it->first;

    //Print space for all but last element
    if (it->first != lastValue)
      os << " ";

    if (it->second.leftChild != nullptr)
      childs.push(it->second.leftChild);

    if (it->second.rightChild != nullptr)
      childs.push(it->second.rightChild);
  }

  //For each children
  while (!childs.empty()) {
    //Get front node
    Node *n = childs.front();

    //Pop it off queue
    childs.pop();

    //Recursively print its contents
    printBTree(os, n, lastValue);
  }

}

/*
 * Returns: an iterator positioned at the element found in the B-Tree. If the element being searched is not 
 * found in the B-Tree, an iterator that is equal to the return value of end() is returned.
*/
template <typename T>
typename btree<T>::iterator btree<T>::find(const T& elem) {
  //Delegate work to recursive helper function
  return recursiveFind(&root, elem);
}

template <typename T>
typename btree<T>::const_iterator btree<T>::find(const T& elem) const {
  //Delegate work to recursive helper function
  return recursiveFind(&root, elem);
}

/*
 * Helper function: Recursively search for an element in a node.
 *
 * Complexity: O(log n) to find location of element using left and right child links
*/
template <typename T>
typename btree<T>::iterator btree<T>::recursiveFind(const Node* node, const T& elem) {
  //Make iterator and set it to lower bound for this node
  typename std::map<T, typename btree<T>::Element>::iterator it = node->elements.lower_bound(elem);
  
  //Check if elem is bigger than all values in this node
  if (it == node->elements.end()) {

    //Get last element
    --it;

    //If last element has a right child, search for elem there
    if (it->second.rightChild != nullptr)
      return recursiveFind(it->second.rightChild, elem);
    //Otherwise, element is not in Btree
    else
      return end();
  }
  //Otherwise see if this is value we are searching for
  else if (it->first == elem) {
    //If so return iterator to this element
    return btree_iterator<T>(node, it);
  }
  //Otherwise value must be located in left child
  else {
    //If last element has a left child, search for elem there
    if (it->second.leftChild != nullptr)
      return recursiveFind(it->second.leftChild, elem);
    //Otherwise, element is not in Btree
    else
      return end();
  }

}

template <typename T>
typename btree<T>::const_iterator btree<T>::recursiveFind(const Node* node, const T& elem) const {
  //Make iterator and set it to lower bound for this node
  typename std::map<T, typename btree<T>::Element>::const_iterator it = node->elements.lower_bound(elem);

  //Check if elem is bigger than all values in this node
  if (it == node->elements.end()) {

    //Get last element
    --it;

    //If last element has a right child, search for elem there
    if (it->second.rightChild != nullptr)
      return recursiveFind(it->second.rightChild, elem);
    //Otherwise, element is not in Btree
    else
      return end();
  }
  //Otherwise see if this is value we are searching for
  else if (it->first == elem) {
    //If so return iterator to this element
    return const_btree_iterator<T>(node, it);
  }
  //Otherwise value must be located in left child
  else {
    //If last element has a left child, search for elem there
    if (it->second.leftChild != nullptr)
      return recursiveFind(it->second.leftChild, elem);
    //Otherwise, element is not in Btree
    else
      return end();
  }
}

/*
* Insert elements into the BTree
*
* Returns: A pair consisting of an iterator positioned at the element inserted and a boolean indicating the 
* success of insertion.
*
* TODO: Ensure proper iterations are returned in pairs
*/
template <typename T>
std::pair<typename btree<T>::iterator, bool> btree<T>::insert(const T& elem) {
  //Delegate work to recursive helper function
  return recursiveInsert(&root, elem);
}

template <typename T>
std::pair<typename btree<T>::iterator, bool> btree<T>::recursiveInsert(Node *node, const T& elem) {

  //Iterate over node elements
  for (auto it = node->elements.begin(); it != node->elements.end(); ++it) {
    //Create boolean for final iteration special case
    bool finalIteration = false;

    if (it == --node->elements.end())
      finalIteration = true;

    //Keep traversing while elem < it's element and not equal to it
    if (elem == it->first) {
      //Exact match found, return pair
      typename std::map<T, typename btree<T>::Element>::iterator itt(it); //create typenamed iterator from it
      return pair<typename btree<T>::iterator, bool>(btree_iterator<T>(node, itt), false);
    }
    //If elem is less than element or this is the last element, we must insert or expand here
    else if (elem < it->first || finalIteration) {

      //We can insert the element at this location in this node if there is space
      if (node->elements.size() < maxElements) {
        //Create new element
        Element e(elem);
        node->elements.insert(pair<T, Element>(elem, e));

        typename std::map<T, typename btree<T>::Element>::iterator itt(it); //create typenamed iterator from it
        return pair<typename btree<T>::iterator, bool>(btree_iterator<T>(node, itt), true);
      }
      //Otherwise, recursively analyse the left or right child
      else {
        Node *child = it->second.leftChild;
        
        //Select right child for the last element if elem is bigger
        if (finalIteration && elem > it->first)
          child = it->second.rightChild;

        //If child is empty node
        if (child == nullptr) {
          //Create new node
          child = new Node(node);

          //Set pointers to child node
          if (finalIteration && elem > it->first)
            it->second.rightChild = child;
          else
            it->second.leftChild = child;
        }

        //We recursively insert searching the child and assigning the parent child to any newely created nodes
        return recursiveInsert(child, elem);
      }
    }
  }

  //No elements in the node, we must add the new element
  //Create new element
  Element e(elem);
  node->elements.insert(pair<T, Element>(elem, e));

  return pair<typename btree<T>::iterator, bool>(btree<T>::iterator(), true);

}

/*
 * begin() 
*/
template <typename T>
typename btree<T>::iterator btree<T>::begin() {

  //Set iterator to roots first element
  typename std::map<T, typename btree<T>::Element>::iterator it = root.elements.begin();

  //If empty root node or first element has no left child
  if (it == root.elements.end() || it->second.leftChild == nullptr) {

    //Return iterator pointing to root node
    return btree_iterator<T> (&root, it);
  }
  //Otherwise, a left child exists
  else {
    Node *p = it->second.leftChild;

    //Find the left most whild
    while (it->second.leftChild != nullptr) {
      p = it->second.leftChild;
      it = p->elements.begin();
    }

    //Return iterator to lowest value element
    return btree_iterator<T>(p, it);
  }
}

/*
* cbegin()
*/
template <typename T>
typename btree<T>::const_iterator btree<T>::begin() const {

  //Set iterator to roots first element
  typename std::map<T, typename btree<T>::Element>::const_iterator it = root.elements.begin();

  //If empty root node or first element has no left child
  if (it == root.elements.end() || it->second.leftChild == nullptr) {

    //Return iterator pointing to root node
    return const_btree_iterator<T>(&root, it);
  }
  //Otherwise, a left child exists
  else {
    Node *p = it->second.leftChild;

    //Find the left most whild
    while (it->second.leftChild != nullptr) {
      p = it->second.leftChild;
      it = p->elements.begin();
    }

    //Return iterator to lowest value element
    return const_btree_iterator<T>(p, it);;
  }
}

/*
* end()
*/

template <typename T>
typename btree<T>::iterator btree<T>::end() {
  typename std::map<T, typename btree<T>::Element>::iterator it = root.elements.end();
  return btree_iterator<T>(&root, it);
}

/*
* cend()
*/
template <typename T>
typename btree<T>::const_iterator btree<T>::end() const {
  typename std::map<T, typename btree<T>::Element>::const_iterator it = root.elements.end();
  return const_btree_iterator<T>(&root, it);
}

/*
 *  Destructor 
*/
template <typename T>
btree<T>::~btree() {

}

