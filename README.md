# Cpp-Exercises
Various C++ Exercises

Custom templated unordered Set class is an exercise I did some time ago to learn more C++ 
while trying to use a bit less of the STL automatized utilities to force myself to implement a 
lot of features on my own, for learning purposes.

Implementation:

  1. The Set class implements the default constructor, parametrized constructor, copy 
constructor, iterators constructor, destructor, some operator overloads, and some 
manipulation methods like add, remove, swap, resize, clear, and other getters 
utilities like find_element, get_elements, and get_size.

  2. There is also a templated global function that accepts a predicate like filter_out and 
returns the elements that satisfy the given predicate and a couple of global 
operators like operator- and operator+. 
All methods are documented in the code link.
There is also a main file that tests a lot of functionalities of the Set with different data types
