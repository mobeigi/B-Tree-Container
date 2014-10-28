#include <iostream>
#include "btree.h"

using namespace std;

int main() {
  btree<int> b;
  b.insert(37);

  //end
  cin.ignore(2);
  cin.get();
  return 0;
}