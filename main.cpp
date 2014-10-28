#include <iostream>
#include "btree.h"

using namespace std;

int main() {
  btree<int> b(4);
  b.insert(37);
  b.insert(20);
  b.insert(105);
  b.insert(1);

  b.insert(12);
  
  for (auto it = b.root.elements.begin(); it != b.root.elements.end(); ++it) {
    cout << it->first << endl;
  }


  //end
  cin.ignore(2);
  cin.get();
  return 0;
}