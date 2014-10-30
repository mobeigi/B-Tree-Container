#include "btree.h"

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

template <typename T>
void find_in_tree(const btree<T> &b, T val) {
  auto iter = std::find(b.begin(), b.end(), val);
  if (iter == b.end())
    std::cout << val << " not found" << std::endl;
  else
    std::cout << val << " found" << std::endl;
}


int main() {
  btree<int> b(4);
  btree<int> c(4);


  b.insert(37);
  b.insert(20);
  b.insert(105);
  b.insert(1);

  b.insert(12);

  b.insert(100);

  b.insert(200);
  b.insert(201);
  b.insert(202);
  b.insert(250);
  b.insert(251);

  b.insert(217);
  b.insert(210);


  c.insert(1);
  c.insert(10);
  c.insert(3);
  c.insert(4);


  /*
   btree<int> &bRef = b;

  for (auto iter = bRef.begin(); iter != bRef.end(); ++iter) {
    ++*iter;
    cout << *iter << endl;
  }

  */


  /*
  for (auto iter = b.begin(); iter != b.end(); ++iter) {
    cout << *iter << endl;
  }

  for (auto iter2 = other.begin(); iter2 != other.end(); ++iter2) {
    cout << *iter2 << endl;
  }
  */

  
  cout << "-------------" << endl;

  btree<int> other;
  other = b;

  b.~btree();

  for (auto it = other.begin(); it != other.end(); ++it) {
    cout << *it << endl;
  }

  /*
  const btree<int> &bRef = b;
  auto iter = std::find(bRef.cbegin(), bRef.cend(), 37);
  */

  /*
  if (iter == bRef.cend())
    std::cout << " not found" << std::endl;
  else
    std::cout << *iter << " found" << std::endl;
  */

  /*

  for (; iter2 != b.cend(); ++iter2) {
    cout << *iter2 << endl;
  }

  */

  
  /*
  map<int, string> m;
  m.insert(pair<int, string>(1, "LOL1"));
  m.insert(pair<int, string>(2, "LOL2"));
  m.insert(pair<int, string>(3, "LOL3"));

  // Prints 7,6,5,4,3,2,1 (reverse order)
  // Error on --it
  for (auto it = m.cbegin(); it != m.cend(); ++it) {
    ;
  }

  */

  
  
 
  
  //end
  cin.ignore(2);
  cin.get();
  return 0;
}