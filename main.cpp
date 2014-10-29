#include <iostream>
#include "btree.h"
#include <vector>

using namespace std;

int main() {
  btree<int> b(4);
  std::pair<btree<int>::iterator, bool> a1 = b.insert(37);
  std::pair<btree<int>::iterator, bool> a2 = b.insert(20);
  std::pair<btree<int>::iterator, bool> a3 = b.insert(105);
  std::pair<btree<int>::iterator, bool> a4 = b.insert(1);

  std::pair<btree<int>::iterator, bool> b1 = b.insert(12);

  /*
  for (auto it = b.root.elements.begin(); it != b.root.elements.end(); ++it) {
    cout << it->first << endl;
  }
  */

  /*
  for (btree<int>::iterator iter = b.begin(); iter != b.end(); ++iter)
    std::cout << *iter << std::endl;
 */

  btree<int>::iterator bit = b.begin();
  cout << *bit << endl;
  ++bit;
  cout << *bit << endl;
  ++bit;
  cout << *bit << endl;
  ++bit;
  cout << *bit << endl;
  ++bit;
  cout << *bit << endl;

  //end
  cin.ignore(2);
  cin.get();
  return 0;
}