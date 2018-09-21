#Binary Tree

This program is an implementation of a self-balancing binary search tree written in C++ in a Data Structures class at UC San Diego. 
The tree can perform all basic functions such as inserting, deleting, and searching items. The implementation of the tree is done using a 
*Tree* class that calls on a *TNode* struct to perform the functions. The *Tree* class records the data such as the occupancy, root, and 
the number of TNodes in the tree. Each *Tnode* is responsible for recording its height, balance, value, occupancy in the tree, and pointers
to *Tnodes* to the left and right of it. Every *Tree* function has a matching *Tnode* function which it delegates to, in most cases the 
calls were recursive. The functions were written so that each recursive call was called on a pointer relative to the calling TNode in order
to traverse the tree. When the program ends, all Tnodes are deleted in post order to prevent memory leaks. The code above was tested 
extensively using Valgrind.

##Calculator

There is also an implementation of a calculator written in C++ using two stacks. Input from the user is recorded in intopost format into a
stack, with one stack that holds the values and another stack that holds the operands used. A function called *Eval* then evaluates the 
intpost expression and provides an answer to the user.
