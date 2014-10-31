/*
* BTree Container Test File
* Will test various functions outlined in spec using casserts
*
*/

#include "btree.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <cassert>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

//Main
int main() {

  //Setup
  size_t testNum = 0;

  /*
  * Test 1 - Default construction of Btree with different parameter types and inputs
  * Testing: No errors, various sizes
  *
  */
  {
    try {
      cout << "Test " << ++testNum << ": ";
      btree<int> a;
      btree<long> b(32);
      btree<double> c;
      btree<string> d(150);
      btree<short> e(1);

      cout << "Passed!" << endl;
    }
    catch (exception&) {
      cout << "FAILED!";
      exit(1);
    }
  }
  /*
  * Test 2 - Inserting into btree of ints and checking using begin() and end()
  * Testing: Valid insertion, begin(), end()
  *
  */
  {
    try {
      cout << "Test " << ++testNum << ": ";
      btree<int> a(2);
      a.insert(100);
      assert(*a.begin() == 100);
      a.insert(105);
      auto it = a.end();
      --it; //point to last element
      assert(*it == 105);

      cout << "Passed!" << endl;
    }
    catch (exception&) {
      cout << "FAILED!";
      exit(1);
    }
  }

  /*
  * Test 3 - Same as test 2 but test now using: cbegin(), cend(), rbegin(), rend(), crbegin(), crend()
  * Testing: Valid insertion, cbegin(), cend(), rbegin(), rend(), crbegin(), crend()
  *
  */
  {
    try {
      cout << "Test " << ++testNum << ": ";
      btree<int> a(2);
      a.insert(100);

      //Check all elements that should point to 100
      assert(*a.cbegin() == 100);
      auto it = a.rend();
      --it;
      assert(*it == 100);
      auto it2 = a.crend();
      --it2;
      assert(*it2 == 100);

      a.insert(105);

      //Repeat checks for elements pointing to 105
      auto it3 = a.cend();
      --it3;
      assert(*it3 == 105);
      assert(*a.rbegin() == 105);
      assert(*a.crbegin() == 105);

      cout << "Passed!" << endl;
    }
    catch (exception&) {
      cout << "FAILED!";
      exit(1);
    }
  }

  /*
  * Test 4 - Create tree of size 1, should behave like a regular binary tree
  * Testing: Valid insertion, Size 1 BTree, Iteration over this tree, Test output of BTree using operator<<
  *
  */
  {
    try {
      cout << "Test " << ++testNum << ": ";

      btree<double> a(1); //binary tree

      /*
      * Tree:                  10.5
      *                      3.6    11.2
      *                   -20            13.6
      *                               12.5   100
      */
      a.insert(10.5);
      a.insert(3.6);
      a.insert(11.2);
      a.insert(13.6);
      a.insert(100);
      a.insert(12.5);
      a.insert(-20);

      //Test output operator <<
      stringstream ss;
      ss << a;
      
      //If this fails, perhaps you have a final space after last element!
      assert(ss.str() == "10.5 3.6 11.2 -20 13.6 12.5 100");

      //Now lets test iteration!
      vector<double> sol = { -20, 3.6, 10.5, 11.2, 12.5, 13.6, 100 };
      vector<double> solRev = sol;
      std::reverse(solRev.begin(), solRev.end());

      size_t count = 0;

      //We should get increasing order iteration
      for (auto it = a.begin(); it != a.end(); ++it, ++count) {
        assert(*it == sol[count]);
      }

      count = 0;

      //Test const version
      for (auto it = a.cbegin(); it != a.cend(); ++it, ++count)
        assert(*it == sol[count]);

      count = 0;

      //Now check reverse order
      for (auto it = a.rbegin(); it != a.rend(); ++it, ++count)
        assert(*it == solRev[count]);

      count = 0;

      //Test const version
      for (auto it = a.crbegin(); it != a.crend(); ++it, ++count)
        assert(*it == solRev[count]);

      cout << "Passed!" << endl;
    }
    catch (exception&) {
      cout << "FAILED!";
      exit(1);
    }
  }


  /*
  * Test 5 - Extending on from test 4, this is the main test. We will use a 3 level deep tree of ints with a size of 4 elements per node, duplicates also tested in addition to finding elements in tree
  * Testing: Valid insertion, Iteration over this tree, Test output of BTree using operator<<, duplicates, finding, copy constructors, move constructors, iterator const correctness
  *
  */
  {
    try {
      cout << "Test " << ++testNum << ": ";

      btree<int> a(4); //btree of size 4

      /*
      * Tree:                  1    20   37                  105
      *                      0   12            72 80 95 100     200 201 202          250
      *                                    50                                 210 217      251
      *                                  
      *                                     
      *                              
      */
      a.insert(1);
      a.insert(105);
      a.insert(37); 
      a.insert(20);

      a.insert(12);
      a.insert(0);

      a.insert(100);

      a.insert(200);
      a.insert(201);
      a.insert(202);
      a.insert(250);

      a.insert(210);
      a.insert(217);

      a.insert(251);

      auto ret1 = a.insert(95);
      auto ret2 = a.insert(72);
      auto ret3 =  a.insert(80);

      auto ret4 = a.insert(50);

      //Test that ret1-ret4 return correct pairs iterator and status is true (as they've been inserted)
	  assert((ret1.second == true) && (ret2.second == true) && (ret3.second == true) && (ret4.second == true));
      assert(*ret1.first == 95 && *ret2.first == 72 && *ret3.first == 80 && *ret4.first == 50);

      //Test duplicate insertions
      auto ret5 = a.insert(200);
      auto ret6 = a.insert(0);
      auto ret7 = a.insert(105);
      auto ret8 = a.insert(251);
      auto ret9 = a.insert(100);

      //Test that ret5-ret9 return correct pairs iterator and status is false (as they're duplicates)
      assert((ret5.second == false) && (ret6.second == false) && (ret7.second == false) && (ret8.second == false) && (ret9.second == false));

      assert(*ret5.first == 200 && *ret6.first == 0 && *ret7.first == 105 && *ret8.first == 251 && *ret9.first == 100);

      //Test output operator <<
      stringstream ss;
      ss << a;

      //If this fails, perhaps you have a final space after last element!
      assert(ss.str() == "1 20 37 105 0 12 72 80 95 100 200 201 202 250 50 210 217 251");

      //Test same thing using copy constructor/move constructor
      btree<int> b = a; //copy
      stringstream ss2;
      ss2 << b;
      assert(ss2.str() == "1 20 37 105 0 12 72 80 95 100 200 201 202 250 50 210 217 251");

      btree<int> c = std::move(b); //move (from b, leaving b in valid state)
      stringstream ss3;
      ss3 << c;
      assert(ss3.str() == "1 20 37 105 0 12 72 80 95 100 200 201 202 250 50 210 217 251");
      

      //Now test this using operator =
      btree<int> d, e;
      d = a;
      stringstream ss4;
      ss4 << d;
      assert(ss4.str() == "1 20 37 105 0 12 72 80 95 100 200 201 202 250 50 210 217 251");

      e = std::move(d);
      stringstream ss5;
      ss5 << e;
      assert(ss5.str() == "1 20 37 105 0 12 72 80 95 100 200 201 202 250 50 210 217 251");


      //Now lets test iteration on tree A
      vector<double> sol = { 0, 1, 12, 20, 37, 50, 72, 80, 95, 100, 105, 200, 201, 202, 210, 217, 250, 251 };
      vector<double> solRev = sol;
      std::reverse(solRev.begin(), solRev.end());

      size_t count = 0;

      //We should get increasing order iteration
      for (auto it = a.begin(); it != a.end(); ++it, ++count) {
        assert(*it == sol[count]);
      }

      count = 0;

      //Test const version
      for (auto it = a.cbegin(); it != a.cend(); ++it, ++count)
        assert(*it == sol[count]);

      count = 0;

      //Now check reverse order
      for (auto it = a.rbegin(); it != a.rend(); ++it, ++count)
        assert(*it == solRev[count]);

      count = 0;

      //Test const version
      for (auto it = a.crbegin(); it != a.crend(); ++it, ++count)
        assert(*it == solRev[count]);


      //Now lets try to find some elements on tree A
      const btree<int> &f = e; //f is a const reference to e

      auto fit1 = f.find(100);
      assert(*fit1 == 100);

      auto fit2 = f.find(94);
      assert(fit2 == f.end());

      auto fit3 = f.find(7);
      assert(fit3 == f.end());

      //Check non-const find (e is not const)
      auto eit1 = e.find(50);
      assert(*eit1 == 50);

      auto eit2 = e.find(77);
      assert(eit2 == e.end());

      auto eit3 = e.find(199);
      assert(eit3 == e.end());

      //We've finished with test 5
      //Note that after each test, each tree should be explicitly destructed
      //However, lets make a node on the heap to test manual deletion
      btree<int> *heap = new btree<int>(4);
      *heap = a;  //copy assignment, copy from a to heap btree

      //We must delete this manually to avoid memory leaks
	  delete heap;

      cout << "Passed!" << endl;
    }
    catch (exception&) {
      cout << "FAILED!";
      exit(1);
    }
  }


  /*
  * Test 6 - Simple iteration test with strings
  * Testing: Valid insertion, Iteration over this tree, Test output of BTree using operator<<
  *
  */
  {
    try {
      cout << "Test " << ++testNum << ": ";

      btree<string> a(3); //string tree with size 3

      /*
      * Tree:                   baby      hey       zed
      *             aaaFirst ant     cat        tool    zzzLast
      *
      *
      *
      */
      a.insert("baby");
      a.insert("zed");
      a.insert("hey");

      a.insert("aaaFirst");
      a.insert("ant");
      a.insert("cat");

      a.insert("tool");
      a.insert("zzzLast");

      //Some duplicates, shouldn't change tree
      auto sit1 = a.insert("ant");
      auto sit2 = a.insert("zzzLast");
      auto sit3 = a.insert("hey");

      //Test that sit1-sit3 return correct pairs iterator and status is false (as they're duplicates)
      assert((sit1.second == false) && (sit2.second == false) && (sit3.second == false));
      assert(*sit1.first == "ant" && *sit2.first == "zzzLast" && *sit3.first == "hey");

      //Test output operator <<
      stringstream ss;
      ss << a;

      //If this fails, perhaps you have a final space after last element!
      assert(ss.str() == "baby hey zed aaaFirst ant cat tool zzzLast");
      
      //Now lets test iteration!
      vector<string> sol = { "aaaFirst", "ant", "baby", "cat", "hey", "tool", "zed", "zzzLast" };
      vector<string> solRev = sol;
      std::reverse(solRev.begin(), solRev.end());

      size_t count = 0;

      //We should get increasing order iteration
      for (auto it = a.begin(); it != a.end(); ++it, ++count) {
        assert(*it == sol[count]);
      }

      count = 0;

      //Test const version
      for (auto it = a.cbegin(); it != a.cend(); ++it, ++count)
        assert(*it == sol[count]);

      count = 0;

      //Now check reverse order
      for (auto it = a.rbegin(); it != a.rend(); ++it, ++count)
        assert(*it == solRev[count]);

      count = 0;

      //Test const version
      for (auto it = a.crbegin(); it != a.crend(); ++it, ++count)
        assert(*it == solRev[count]);

      cout << "Passed!" << endl;
    }
    catch (exception&) {
      cout << "FAILED!";
      exit(1);
    }
  }
  
  //End, capture input
  cin.ignore(2);
  cin.get();

  return 0;
}
