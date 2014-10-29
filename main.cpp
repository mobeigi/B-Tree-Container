#include <iostream>
#include "btree.h"
#include <vector>

using namespace std;

int main() {
  btree<int> b(4);
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

  /*
  for (auto it = b.root.elements.begin(); it != b.root.elements.end(); ++it) {
    cout << it->first << endl;
  }
  */

  btree<int>::iterator iter = b.begin();

  for (; iter != b.end(); ++iter) {
    std::cout << *iter << std::endl;
  }
 

  //end
  cin.ignore(2);
  cin.get();
  return 0;
}