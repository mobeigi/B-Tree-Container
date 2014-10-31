B-Tree-Container
=========
C++ implementation of a multiple B-Tree container

The btree is a linked structure which operates much like a binary search tree, save the fact that multiple client elements are stored in a single node.  Whereas a single element would partition the tree into two ordered subtrees, a node that stores m client elements partition the tree into m + 1 sorted subtrees.

This task required knowledge of templates and custom iterators (const and non-const iterators). The purpose of this task was to learn about iterators in C++ and how they behave. It shows how valuable and powerful iterators are in accessing information from a container. operator overloading, constructors, destructors and iterator adaptors were also used.

Operations provided included:
* custom iterator (const and non-const versions, including reverse_iterators)
* find - search for an element in the btree and get an iterator to the element
* insert - insert an element into the btree if element is unique and return pair<iterator, bool>, similar to map::insert
* output operator<< for printing btree in breadth first order

License
----
Free to use.