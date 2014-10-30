#include <iostream>
#include "btree.h"
#include <vector>

using namespace std;

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

  

  for (auto iter = b.cbegin(); iter != b.cend(); ++iter) {
    cout << *iter << endl;
  }


  cout << "-------------" << endl;

  //cout << b << endl;


  /*

  for (; iter2 != b.cend(); ++iter2) {
    cout << *iter2 << endl;
  }

  */

  /*

  vector<int> v = { 1, 2, 3, 4, 5, 6, 7 };
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