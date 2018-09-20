/* Eric Ngo
 * May 27, 2018
 * File Name: Tree.h
 * File Description: The Tree.h file holds all the public information of
 *					 the Tree.c file. It declares all the functions and
 *					 data fields of the Tree class and declares the struct
 *					 TNode as a friend.
 */
#ifndef TREE_H
#define TREE_H

#include <iostream>
using namespace std;

// debug message
static const char ALLOCATE[] = " - Allocating]\n";
static const char TREE[] = "[Tree ";

template <class Whatever>
struct TNode;


/*============================================================================
 * class Tree
 *
 * Description: The class Tree is the base of the tree data structure
 *			    implementation. It delegates most of the basic functions
 *			    of the tree, such as inserting and deleting nodes, to the 
 *			    struct TNode, where a recursive function is called. The
 *			    tree only has 1 pointer to the root TNode, but it also
 *			    keeps track of the occupancy and the count of the tree. 
 *
 * Data Fields: friend struct TNode <Whatever> - shares data with TNode
 *				TNode<Whatever> root - pointer to the root TNode in tree
 *				long occupancy - the number of TNodes in the tree
 *				unsigned long tree_count - the number of trees
 *				instantiated
 *				static int debug - debug switch 
 *
 *	Public Functions:
 *			Tree constructor - constructor to create a new tree
 *			Tree Destructor - destructor to clear memory tied to the tree
 *			Set_Debug_on - function to turn on debug mode
 *			Set_Debug_off - function to turn off debug mode
 *			IsEmpty - function to determine if tree is empty or not
 *			Insert - function to insert an element into the tree
 *			Lookup - function to search for an element in the tree
 *			Remove - function to remove an element in the tree
 ===========================================================================*/
template <class Whatever>
class Tree {
        friend struct TNode<Whatever>;
        long occupancy;
        TNode<Whatever> * root;
        unsigned long tree_count;
        static int debug;
public:
        
        Tree (void);
        ~Tree (void);
        
        static void Set_Debug_On (void);
        static void Set_Debug_Off (void);
        unsigned long IsEmpty (void) const;
        unsigned long Insert (const Whatever &);
        unsigned long Lookup (Whatever &) const;
        unsigned long Remove (Whatever &);
        ostream & Write (ostream &) const;
};

#include "Tree.c"

#endif
