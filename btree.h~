/**
 * The btree is a linked structure which operates much like
 * a binary search tree, save the fact that multiple client
 * elements are stored in a single node.  Whereas a single element
 * would partition the tree into two ordered subtrees, a node 
 * that stores m client elements partition the tree 
 * into m + 1 sorted subtrees.
 *
 * Author: Mohammad Ghasembeigi (implementing for provided public interface)
 */

#ifndef BTREE_H
#define BTREE_H

#include <iostream>
#include <cstddef>
#include <utility>
#include <map>
#include <queue>

//Include our btree iterator
#include "btree_iterator.h"

//Use standard namespace
using namespace std;

//Add declarations for non-template friends
template <typename T> class btree;
template <typename T> std::ostream& operator<<(std::ostream& os, const btree<T>& tree);

template <typename T> 
class btree {
 public:
  /**
   * Constructs an empty btree.  Note that
   * the elements stored in your btree must
   * have a well-defined zero-arg constructor,
   * copy constructor, operator=, and destructor.
   * The elements must also know how to order themselves
   * relative to each other by implementing operator<
   * and operator==. (These are already implemented on
   * behalf of all built-ins: ints, doubles, strings, etc.)
   * 
   * @param maxNodeElems the maximum number of elements
   *        that can be stored in each B-Tree node
   */
   btree(size_t maxNodeElems = 40) : maxElements(maxNodeElems) {};

  /**
   * The copy constructor and  assignment operator.
   * They allow us to pass around B-Trees by value.
   * Although these operations are likely to be expensive
   * they make for an interesting programming exercise.
   * Implement these operations using value semantics and 
   * make sure they do not leak memory.
   */

  /** 
   * Copy constructor
   * Creates a new B-Tree as a copy of original.
   *
   * @param original a const lvalue reference to a B-Tree object
   */
  btree(const btree<T>& original);

  /** 
   * Move constructor
   * Creates a new B-Tree by "stealing" from original.
   *
   * @param original an rvalue reference to a B-Tree object
   */
  btree(btree<T>&& original);
  
  
  /** 
   * Copy assignment
   * Replaces the contents of this object with a copy of rhs.
   *
   * @param rhs a const lvalue reference to a B-Tree object
   */
  btree<T>& operator=(const btree<T>& rhs);

  /** 
   * Move assignment
   * Replaces the contents of this object with the "stolen"
   * contents of original.
   *
   * @param rhs a const reference to a B-Tree object
   */
  btree<T>& operator=(btree<T>&& rhs);

  /**
   * Puts a breadth-first traversal of the B-Tree onto the output
   * stream os. Elements must, in turn, support the output operator.
   * Elements are separated by space. Should not output any newlines.
   *
   * @param os a reference to a C++ output stream
   * @param tree a const reference to a B-Tree object
   * @return a reference to os
   */
  friend std::ostream& operator<< <T> (std::ostream& os, const btree<T>& tree);

  /** Iterator type definitions **/

  //Give friendship to iterator classes
  friend class btree_iterator<T>;
  friend class const_btree_iterator<T>;

  typedef btree_iterator<T> iterator;
  typedef const_btree_iterator<T> const_iterator;
  typedef std::reverse_iterator<iterator> reverse_iterator;
  typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

  //non-const and const iterators for begin() and end()
  iterator begin();
  iterator end();

  const_iterator begin() const; //const begin()
  const_iterator end() const; //const end()
  const_iterator cbegin() const { return begin(); };  //cbegin()
  const_iterator cend() const { return end(); };    //cend()

  //We can also provide reverse iteration operations using rever_iterator adaptors
  reverse_iterator rbegin() { return reverse_iterator(end()); } //rbegin
  const_reverse_iterator rbegin() const { return const_reverse_iterator(end()); } //const rbegin
  const_reverse_iterator crbegin() const { return rbegin(); }  //crbegin()
  
  reverse_iterator rend() { return reverse_iterator(begin()); } //rend
  const_reverse_iterator rend() const { return const_reverse_iterator(begin()); } //const rend
  const_reverse_iterator crend() const { return rend(); }  //crend()


  /**
    * Returns an iterator to the matching element, or whatever 
    * the non-const end() returns if the element could 
    * not be found.  
    *
    * @param elem the client element we are trying to match.  The elem,
    *        if an instance of a true class, relies on the operator< and
    *        and operator== methods to compare elem to elements already 
    *        in the btree.  You must ensure that your class implements
    *        these things, else code making use of btree<T>::find will
    *        not compile.
    * @return an iterator to the matching element, or whatever the
    *         non-const end() returns if no such match was ever found.
    */
  iterator find(const T& elem);
    
  /**
    * Identical in functionality to the non-const version of find, 
    * save the fact that what's pointed to by the returned iterator
    * is deemed as const and immutable.
    *
    * @param elem the client element we are trying to match.
    * @return an iterator to the matching element, or whatever the
    *         const end() returns if no such match was ever found.
    */
  const_iterator find(const T& elem) const;
      
  /**
    * Operation which inserts the specified element
    * into the btree if a matching element isn't already
    * present.  In the event where the element truly needs
    * to be inserted, the size of the btree is effectively
    * increases by one, and the pair that gets returned contains
    * an iterator to the inserted element and true in its first and
    * second fields.  
    *
    * If a matching element already exists in the btree, nothing
    * is added at all, and the size of the btree stays the same.  The 
    * returned pair still returns an iterator to the matching element, but
    * the second field of the returned pair will store false.  This
    * second value can be checked to after an insertion to decide whether
    * or not the btree got bigger.
    *
    * The insert method makes use of T's zero-arg constructor and 
    * operator= method, and if these things aren't available, 
    * then the call to btree<T>::insert will not compile.  The implementation
    * also makes use of the class's operator== and operator< as well.
    *
    * @param elem the element to be inserted.
    * @return a pair whose first field is an iterator positioned at
    *         the matching element in the btree, and whose second field 
    *         stores true if and only if the element needed to be added 
    *         because no matching element was there prior to the insert call.
    */
  std::pair<iterator, bool> insert(const T& elem);

  /**
    * Disposes of all internal resources, which includes
    * the disposal of any client objects previously
    * inserted using the insert operation. 
    * Check that your implementation does not leak memory!
    */
  ~btree();

  
private:

  struct Element;

  /*
  * A node consists of a mapping of values to Elements.
  * A map is ideal due to its weak ordering on inserted values of type T.
  * Each node is aware of its parent node to simplify later traversal algorithms.
  */
  struct Node {
    //Node constructor
    Node(Node* p = nullptr) : parent(p), elements(std::map<T, Element>()) {}

    //Structures
    Node* parent;
    std::map<T, Element> elements;
  };

  /*
  * Each node has up to 'maxNodeElems' elements. Each element has a value T.
  * Each element also has a left and right child node which have value 'nullptr' to indicate no child.
  */
  struct Element {
    //Element constructor
    Element(T value = T(), Node *left = nullptr, Node *right = nullptr) : value(value), leftChild(left), rightChild(right) {}
    
    //Structures
    T value;
    Node *leftChild;
    Node *rightChild;

  };

  size_t maxElements;  //stores the max number of elements each node may contain
  Node root;  //store the root node as all other nodes will be linked to it


  //Helper functions

  //Recursive node copy function to copy a btree
  void copyBTree(const Node *source, Node *parent, Node *dest);

  //Recursive print node function to print an entire tree in breadth first order
  static void printBTree(std::ostream& os, const Node *node, std::queue<Node*>& childs, const T &lastValue); //declare static so nonmember << operator may use it

  //Recursive insertion function to find and insert an elem (if it is unique)
  std::pair<typename btree<T>::iterator, bool> recursiveInsert(Node *node, const T& elem);

  //Recursive find functions, non-const and const versions provided to cater for non-const and const BTree's
  iterator recursiveFind(Node* node, const T& elem);
  const_iterator recursiveFind(const Node* node, const T& elem) const;

  //Recursively element delete function that deletes an element and all of its linked childs
  void deleteElement(Element& e);

};


/**
 * The template implementation needs to be visible to whatever
 * translation unit makes use of templatized btree methods.
 * The unconventional practice is to #include the implementation
 * file just before the end of the interface (sort of like
 * sneaking it in and hoping it isn't noticed).  Because the
 * .tem file is included here, the .h file is NOT #included in 
 * the .tem file.  We'd otherwise have circular inclusions
 * and the compiler would be peeved.
 */

#include "btree.tem"

#endif
