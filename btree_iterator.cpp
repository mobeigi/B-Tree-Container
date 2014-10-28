/*
* btree_iterator and const_btree_iterator implementations
*
* Each operation implementation is directly followed by the const equivalent implementation.
*/

//Operator*
template <typename T>
T& btree_iterator<T>::operator*() const {
  return it->second.value;
}

template <typename T>
const T& const_btree_iterator<T>::operator*() const {
  return it->second.value;
}

//Operator++



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


}

//Const implementation of above
template <typename T>
void const_btree_iterator<T>::forward_traverse_down(const typename btree<T>::Node *n,
  typename std::map<T, typename btree<T>::Element>::const_iterator& it) {


}

/*
* forward_traverse_up moves up recursively to the next element in parent nodes.
* This ensures you are at the the next node with the next value as all left links/childs have been exhausted.
*/

template <typename T>
void btree_iterator<T>::forward_traverse_up(typename btree<T>::Node *n,
  typename std::map<T, typename btree<T>::Element>::iterator& it) {


}

template <typename T>
void const_btree_iterator<T>::forward_traverse_up(const typename btree<T>::Node *n,
  typename std::map<T, typename btree<T>::Element>::const_iterator& it) {


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