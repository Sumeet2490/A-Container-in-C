# Container-in-C

Implement a container class template named Map similar to the std::map class from the C++ Standard Library. Such containers implement key-value pairs, where key and value may be any types, including class types. (In the following, the value will be referred to as the mapped type or mapped object, and the term value will used to designate the entire pair. This is so as to be consistent with the terminology in the standard library.) Note that C++ terminology uses object even for fundamental types such as ints. Your Map class template will have two type parameters, Key_T and Mapped_T, denoting the key type and the mapped type, respectively. As in std::map, the mapped type values themselves must be in your map, not pointers to the values.

The specification given below is intended to be a proper subset of the functionality of std::map. This means that if you don't fully understand something, you can check the documentation for std::map, or even write a small test using std::map. If you find any discrepancies between what is described below and std::map, please let me know.

You may assume that the Key_T and Mapped_T are copy constructible and destructible. You may assume that Key_T has a less-than operator (<), and an equality operator (==), as free-standing functions (not member functions). You may also assume that Mapped_T has an equality comparison (==). If operator< is invoked on Map objects, you may also assume that Mapped_T has operator<. You may not assume that either class has a default constructor or an assignment operator. You may only assume that a Mapped_T that is used with operator[] may be default initialized. You may not make any other assumptions. (Check with us if there is any doubt.)

Your Map class must expose three nested classes: Iterator, ConstIterator, and ReverseIterator. None of these classes should permit default construction.

An iterator is an object that points to an element in a sequence. The iterators must traverse the Map by walking through the keys in sorted order. Iterators must remain valid as long as the element they are pointing to has not been erased. Any function that results in the removal of an element from a map, such as erase, will invalidate any iterator that points to that element, but not any other iterator.

Your map implementation must be completely contained in your Map.hpp file. I do not believe that you will need a Map.cpp file, but you may have one if you wish.

Additionally, your class must meet the following time complexity requirements: O(lg(N)) for key lookup, insertion, and deletion; and O(1) for all iterator increments and decrements. These time complexities are the worst-case, expected time complexities. In other words, for the worst-case possible input, your submission must, when averaged over many runs, have the given time complexity. If you use amortization to achieve the above bounds, that is fine, but contact me.

To achieve the performance requirements, two data structures that will work are balanced binary trees or skip lists. Note that the former is much easier to implement. Hash tables will not work.

All classes should be in the cs540 namespace. Your code must work with test classes that are not in the cs540 namespace, however. Your code should not have any memory errors or leaks as reported by valgrind. Your code should compile and run on the remote.cs.binghamton.edu cluster. Your code should not have any hard-coded, arbitrary limits or assumptions about maximum number of elements, maximum sizes, etc.
