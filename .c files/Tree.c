/* Eric Ngo
 * May 22, 2018
 * File Name: Tree.c
 * File Description: The Tree.c file implements a basic Tree data structure
 *                   in which items are stored via Nodes. The tree starts
 *                   with a root and all of the nodes extend from that root.
 *                   Items are inserted by comparing their values to the nodes
 *                   and inserting to the left if its less than the node and
 *                   to the right if its greater than the node. You can also
 *                   look up whether or not a certain node is in the tree and
 *                   remove it as well.
 */
#include <cstdlib>
#include <string>
#include "Tree.h"
using namespace std;

// messages
static const char AND[] = " and ";
static const char CHECK[] = " - Checking ";
static const char COMPARE[] = " - Comparing ";
static const char DEALLOCATE[] = " - Deallocating]\n";
static const char INSERT[] = " - Inserting ";
static const char REPLACE[] = " - Replacing ";
static const char UPDATE[] = " - Updating ";

//debug switch
template <class Whatever>
int Tree<Whatever>::debug = 0; 

#ifndef TRUE
#define TRUE 1
#endif

#ifndef FALSE
#define FALSE 0
#endif

#define THRESHOLD 2

//operator used to print out to ostream
template <class Whatever>
ostream & operator << (ostream &, const TNode<Whatever> &);

/*============================================================================
 * struct TNode
 *
 * Description: The struct TNode used to implement a Tree structure. Each 
 *			    TNode contains the fields to access the data associated with
 *			    it, along with the other Nodes to the left and right of it, 
 *			    Each TNode also takes into account its height and balance, 
 *			    alongside the occupancy in the list; it also knows the
 *			    tree_count.
 *
 * Data Fields: Whatever data - the name of the TNode
 *				TNode<Whatever> * left - the TNode to the left of the current 
 *										 TNode
 *				TNode<Whatever> * right - the TNode to the right of the current
 *										  TNode
 *				long & occupancy - the number of TNodes in the tree
 *				unsigned long hasBeenDeleted - boolean switch to turn on 
 *											   debug mode
 *				long balance - the balance of the TNode
 *				long height - the height of the TNode
 *				unsigned long & tree_count - the tree count
 *
 *	Public Functions:
 *			TNode constructor - constructor to create TNode out of a
 *			given tree
 *			TNode constructor - constructor to create TNode out of a
 *			given TNode
 *			~TNode destructor - deletes all memory tied to TNode
 *			delete_AllTNodes - deletes all the children of the current node
 *			Insert - function to insert an element into the tree
 *			ReplaceAndRemoveMax - function to "remove" an element with 2
 *			children
 *			Remove - removes a node from the tree
 *			SetHeightAndBalance - updates the height and balance of a
 *			node
 ===========================================================================*/
template <class Whatever>
struct TNode {
		
        long balance; //balance of Node in the tree
        Whatever data; //the data (name) associated with the node
        long height; //the height of the Node in the tree
        TNode<Whatever> * left; //pointer to the node to the left 
        long & occupancy; //the number of nodes in the tree
        TNode<Whatever> * right; //pointer to the node to the right
        unsigned long & tree_count; //number of trees instantiated
        
/***************************************************************************
% Routine Name : TNode  (public)
% File :         Tree.c
% 
% Description : Initializes data to the TNode through a passed in tree; 
%				initializes left and right to null, sets balance and height 
%				to 0, and increments occupancy and sets the tree_count
%
% Parameters descriptions : 
% 
% name               description
% -------------------------------------------------------------------------
% element           the name of the TNode to be inserted
% theTree           The tree used to instantiate data fields in the Node
***************************************************************************/
        TNode (const Whatever & element, Tree<Whatever> & theTree)
                : balance (0), data (element), height (0), left (0), 
                occupancy (theTree.occupancy), right (0), 
                tree_count (theTree.tree_count) {
                //update occupancy in the tree
				occupancy++;
        }
        
/***************************************************************************
% Routine Name : TNode  (public)
% File :         Tree.c
% 
% Description : Initializes data to the TNode through a passed in TNode; 
%				initializes left and right to null, sets balance and height 
%				to 0, and increments occupancy and sets the tree_count
%
% Parameters descriptions : 
% 
% name               description
% -------------------------------------------------------------------------
% element           the name of the TNode to be inserted
% parentTNode       The TNode used to instantiate data fields in the Node
***************************************************************************/
        TNode (const Whatever & element, TNode<Whatever> & parentTNode)
        : balance (0), data (element), height (0), left (0), 
                occupancy (parentTNode.occupancy), right (0), 
                tree_count (parentTNode.tree_count) {
                //update occupancy in the tree
				occupancy++;
        }
/***************************************************************************
% Routine Name : ~Tnode (public)
% File :         Tree.c
% 
% Description :  Destructor for TNode, deletes all data associated with it
***************************************************************************/
        ~TNode (void) {
			//updates occupancy after removing node
			occupancy--;
		}

/***************************************************************************
% Routine Name : delete_AllTNodes (public)
% File :         Tree.c
% 
% Description :  deletes all of the TNodes in a tree when called
***************************************************************************/
        void delete_AllTNodes (void) {
			/*go all the way left*/
			if(left)
				left->delete_AllTNodes ();

			/*go all the way right*/
			if(right)
				right->delete_AllTNodes ();

			/*deletes once at a leaf*/
			delete(this);
        }
		//function declaration for Insert
        unsigned long Insert (const Whatever & element, 
                              TNode<Whatever> *& PointerInParent);

        // OPTIONAL TNode :: Lookup => uncomment if implementing recursively
        // unsigned long Lookup(Whatever & element) const;


/***************************************************************************
% Routine Name : ReplaceAndRemoveMax  (public)
% File :         Tree.c
% 
% Description : Function used when removing a TNode with 2 children; algorithm
%				is to go in to the left branch and grab the largest TNode in 
%				there and set it to the TNode to be deleted
%
% Parameters descriptions : 
% 
% name               description
% -------------------------------------------------------------------------
% targetTNode       the TNode that will be deleted
% PointerInParent   pointer to the current TNode from the parent
***************************************************************************/
        void ReplaceAndRemoveMax (TNode<Whatever> & targetTNode, 
                TNode<Whatever> *& PointerInParent) {
			
			//recursively traverse to the right until you cant anymore
			if(right) {
				right -> ReplaceAndRemoveMax(targetTNode, right);
				
				/* increments height & balance after exiting recursive
				 * call*/
				SetHeightAndBalance(PointerInParent);
			}

			//when the largest element is found
			else {
				
				//prints debug message if switch is on
				if(Tree<Whatever> :: debug) {
					cerr << TREE << tree_count << CHECK <<
					((const char*) data) << "]\n";
				
					cerr << TREE << tree_count << REPLACE <<
					((const char*) data) << "]\n";
				}

				/*overwrites targetTNode to be the largest TNode in the
				 *left subtree*/
				targetTNode.data = data;

				//updates Pointer to the parent before deleting 
				PointerInParent = left;
				delete this;
			}
        }

/***************************************************************************
% Routine Name : Remove  (public)
% File :         Tree.c
% 
% Description : Function to remove an element from a tree. It will return 
%				false when a remove was unsuccessful or true when a remove
%				was successful
%
% Parameters descriptions : 
% 
% name               description
% -------------------------------------------------------------------------
% elementTNode      the TNode that will be deleted
% PointerInParent   pointer to the current TNode from the parent
%<Return>			true if remove is successful, false otherwise
***************************************************************************/
        unsigned long Remove (TNode<Whatever> & elementTNode, 
                TNode<Whatever> *& PointerInParent,
                long fromSHB = FALSE) {
                
			//return value of the function
			long retVal = 0;
			
			//check if element is found in the tree
			if(elementTNode.data == data) {

				//prints debug message if switch is on
				if(Tree<Whatever> :: debug)
				cerr << TREE << tree_count << COMPARE << 
				((const char*) elementTNode.data) << AND << 
				((const char*) PointerInParent->data) << "]\n";

				//saves the data of the element being deleted 
				elementTNode.data = data;
				
				//if element is a leaf
				if(!left && !right) {
					//properly removes element and returns true
					delete this;
					PointerInParent = NULL;
					return 1;
				}

				//if only child is a right pointer
				else if(!left) {
					//temp TNode to store current TNode
					TNode<Whatever>* temp = PointerInParent;

					//updates PointerInParent to the next TNode
					PointerInParent = right;

					//properly removes element and returns true
					delete temp;
					temp = NULL;
					return 1;
				}

				//if only child is a left pointer
				else if(!right) {
					//temp TNode to store current TNode
					TNode<Whatever>* temp1 = PointerInParent;

					//updates PointerInParent to the next TNode
					PointerInParent = left;

					//properly removes element and returns true
					delete temp1;
					temp1 = NULL;
					return 1;
				}
				
				//case of 2 children
				else {
					/*calls ReplaceAndRemoveMax to get rid of Node with 2
					 *children and returns true*/
					left->
					ReplaceAndRemoveMax(*this, left);
					return 1;
				}
			}

			//returns false if element doesnt exist in tree
			else if(!right && !left)
				return 0;

			//continue traversing until element is found/or not in list
			else {
				//print debug message if switch is on
				if(Tree<Whatever> :: debug)
				cerr << TREE << tree_count << COMPARE << 
				((const char*) elementTNode.data) << AND << 
				((const char*) data) << "]\n";

				//continue traversing right
				if(elementTNode.data > data) {
					retVal = right -> Remove(elementTNode, right);

				}
			
				//continue traversing left
				else {
					retVal = left -> Remove(elementTNode, left);
				}

				/*updates height and balance after every recursive call
				 * only if this function isn't called from
				 * SetHeightAndBalance */
				if(!fromSHB)
					SetHeightAndBalance(PointerInParent);
			}

			return retVal;
        }

/***************************************************************************
% Routine Name : SetHeightAndBalance  (public)
% File :         Tree.c
% 
% Description : Function to upate the height and balance of a TNode
%
% Parameters descriptions : 
% 
% name               description
% -------------------------------------------------------------------------
% PointerInParent   pointer to the current TNode from the parent
***************************************************************************/
        void SetHeightAndBalance (TNode<Whatever> *& PointerInParent) {

			//calculation if Node has a left child
			if(!right && left) {
				height = left->height + 1;

				//-1 represents null TNode
				balance = left->height - (-1);
			}

			//calculation if Node has a right child
			else if(!left && right) {
				height = right->height + 1;

				//-1 represents null TNode
				balance = (-1) - right->height;
			}

			//calculation if Node has 2 children
			else if(right && left) { 

				//uses height of biggest child
				if(right->height > left->height) {
					height = right->height + 1;
					balance = left->height - right->height;
				}

				else {
					height = left->height + 1;
					balance = left->height - right->height;
				}
			}

			//treshold of balance 2 check
			if(abs(balance) > THRESHOLD) {
				//temp TNode created to call remove function
				TNode<Whatever> elementTNode = 
				TNode<Whatever>(data, *PointerInParent);
				 
				//removes current TNode if its balance is off
				Remove(elementTNode, PointerInParent, true);
				
				//re inserts the element that is removed 
				PointerInParent -> Insert(elementTNode.data, PointerInParent);
			}

		}

        ostream & Write_AllTNodes (ostream & stream) const {
                if (left)
                        left->Write_AllTNodes (stream);
                stream << *this;
                if (right)
                        right->Write_AllTNodes (stream);

                return stream;
        }
};

/* YOUR DEBUG SETTERS GO HERE */


/***************************************************************************
% Routine Name : Tree :: Set_Debug_On	(public)
% File :         Tree.c
% 
% Description :  turns on debug mode to print out debug messages
***************************************************************************/
template <class Whatever>
void Tree<Whatever> :: Set_Debug_On(void) {
	debug = 1;
}

/***************************************************************************
% Routine Name : Tree :: Set_Debug_Off	(public)
% File :         Tree.c
% 
% Description :  turns off debug mode 
***************************************************************************/
template <class Whatever>
void Tree<Whatever> :: Set_Debug_Off(void) {
	debug = 0;
}


/***************************************************************************
% Routine Name : Tree :: Insert
% File :         Tree.c
% 
% Description :  inserts a new node into the tree struct
% Parameters descriptions :
% 
% name               description
% --------------------------------------------------------------------------
% element			the element to be inserted into the tree
% PointerInParent	pointer to the current TNode from the parent
% <return>			true when the element is inserted
***************************************************************************/
template <class Whatever>
unsigned long TNode<Whatever> :: Insert (const Whatever & element, 
                                         TNode<Whatever> *& PointerInParent) {

    //overwrites already existing node in tree
	if(element == data) {
		data = element;	
	}

	//checks if item being inserted is bigger than the current element
	else if(element > data) {

		//print debug if switch is on
		if(Tree<Whatever> :: debug)
			cerr << TREE << tree_count << COMPARE << ((const char*) element)
			<< AND << ((const char*) data) << "]\n";
		
		//if right child is null, insert into tree
		if(!right) { 
			right = new TNode<Whatever>(element, *this);
			
			//print debug message 
			if(Tree<Whatever> :: debug)
				cerr << TREE << tree_count << INSERT << 
				((const char*) element) << "]\n";
		}
	
		//otherwise continue traversing
		else {
			right -> Insert(element, right);
		}

		//print debug message
		if(Tree<Whatever> :: debug)
			cerr << TREE << tree_count << UPDATE << ((const char*) data)
			<< "]\n";
		//updates height and balance after returning from recursive call
		SetHeightAndBalance(PointerInParent);
	}

	//if item is smaller than the current element
	else {

		//print debug message
		if(Tree<Whatever> :: debug)
			cerr << TREE << tree_count << COMPARE << ((const char*) element)
			<< AND << ((const char*) data) << "]\n";

		//insert into tree if left child is null
		if(!left) { 
			left = new TNode<Whatever>(element, *this);
			
			//print debug message
			if(Tree<Whatever> :: debug)
				cerr << TREE << tree_count << INSERT <<
				((const char*) element) << "]\n";
		}

		//traverse otherwise
		else {
			left -> Insert(element, left);
		}
		
		//print debug
		if(Tree<Whatever> :: debug)
			cerr << TREE << tree_count << UPDATE << ((const char*) data)
			<< "]\n";

		//updates height and balance after returning from recursive call
		SetHeightAndBalance(PointerInParent);
	}


	return 1;
}

template <class Whatever>
ostream & operator << (ostream & stream, const TNode<Whatever> & nnn) {
        stream << "at height:  :" << nnn.height << " with balance:  "
                << nnn.balance << "  ";
        return stream << nnn.data << "\n";
}


/***************************************************************************
% Routine Name : Tree :: IsEmpty
% File :         Tree.c
% 
% Description :  checks if the tree is empty
%
% -------------------------------------------------------------------------
% <return>			true if tree is empty, false otherwise
***************************************************************************/
template <class Whatever>
unsigned long Tree<Whatever> :: IsEmpty () const {

	//null root or 0 occupancy denotes empty tree
	if(!root || occupancy == 0)
		return 1;
	
	return 0;
}


/***************************************************************************
% Routine Name : Tree<Whatever> :: Insert
% File :         Tree.c
% 
% Description :  inserts a new node into the tree struct
% Parameters descriptions :
% 
% name               description
% --------------------------------------------------------------------------
% element			the element to be inserted into the tree
% <return>			true when the element is inserted
***************************************************************************/
template <class Whatever>
unsigned long Tree<Whatever> :: Insert (const Whatever & element) {

    //creates a new root if tree is empty
	if(IsEmpty()) {
		root = new TNode<Whatever>(element, *this);
		
		//print debug message if switch is on
		if(debug)
			cerr << TREE << tree_count<< INSERT << 
			((const char*) element) << "]\n";
	}

	//delegate to TNode's insert for any other case
	else
		root -> Insert(element, root);
	
	
	return 1;
}


/***************************************************************************
% Routine Name : Tree<Whatever> :: Lookup
% File :         Tree.c
% 
% Description :  looks up a TNode in the tree struct
% Parameters descriptions :
% 
% name               description
% --------------------------------------------------------------------------
% element			the element being searched for in the tree
% <return>			null if the item being searched for isnt in the tree
% <return>			true of element is found
***************************************************************************/
template <class Whatever>
unsigned long Tree<Whatever> :: Lookup (Whatever & element) const {
	/*initialize local current TNode*/
	TNode<Whatever> * current = root;

	/*empty tree check*/
	if(IsEmpty())
		return 0;

	/*loop to iterate through tree*/
	else while(true){

		/*print debug message if debug switch is on*/
		if(debug)
			cerr << TREE << tree_count << 
			COMPARE << ((const char *) element) << AND 
			<< ((const char *) current->data) << "]" << "\n";

		/*returns true and the data of the TNode if found*/
		if(*element == *(current->data)) {
			element = current->data;
			return 1;
		}	

		/*search if element is on the right*/
		else if(*element > *(current->data)) {

			/*return null if reached the end of tree*/
			if(current->right == NULL) {
				break;
			}

			/*continue traversing through tree*/
			current = current->right;
		}

		/*search if element is on the left*/
		else {

			/*return null if reached end of tree*/
			if(current->left == NULL) {
				break;
			}

			/*continue traversing through tree*/
			current = current->left;
		}
	}
	return 0;    // not there
}



/***************************************************************************
% Routine Name : Tree<Whatever> :: Remove
% File :         Tree.c
% 
% Description :  removes a TNode from the tree struct
% Parameters descriptions :
% 
% name               description
% --------------------------------------------------------------------------
% element			the element to be removed in the tree
% <return>			null if the item being searched for isnt in the tree
% <return>			true if the element is found
***************************************************************************/
template <class Whatever>
unsigned long Tree<Whatever> :: Remove (Whatever & element) {
	
	//false if tree doesn't exist
	if(!root)
		return 0;

	//delegates to TNode's remove otherwise
	else {
		//temp TNode created to call TNode remove
		TNode<Whatever> elemTNode(element, *root);
		long retVal = root -> Remove(elemTNode, root);

		//stores the value of the removed element to print to the stream
		element = elemTNode.data;
		return retVal;
	}

	return 0;
}

/***************************************************************************
% Routine Name : Tree<Whatever> :: Tree  (public)
% File :         Tree.c
% 
% Description :  Guarantee initialization of occupancy and root. It also 
%                initializes the tree_count using a static counter.
***************************************************************************/
template <class Whatever>
Tree<Whatever> :: Tree (void): occupancy (0), root (NULL) 

{       
		//initializes tree_count
		tree_count = 1;

		//print debug message if switch is on
		if(debug)
			cerr << TREE << tree_count << ALLOCATE;
}

template <class Whatever>
Tree<Whatever> :: ~Tree (void)
/***************************************************************************
% Routine Name : Tree<Whatever> :: ~Tree  (public)
% File :         Tree.c
% 
% Description :  deallocates memory associated with the Tree.  It
%                will also delete all the memory of the elements within
%                the table.
***************************************************************************/

{
	//print debug message if switch is on
	if(debug)
		cerr << TREE << tree_count << DEALLOCATE;

	//deletes all TNodes in the tree
	if(root)
		root -> delete_AllTNodes();
}



template <class Whatever>
ostream & Tree<Whatever> :: Write (ostream & stream) const
/***************************************************************************
% Routine Name : Tree<Whatever> :: Write (public)
% File :         Tree.c
% 
% Description : This function will output the contents of the Tree table
%               to the stream specificed by the caller.  The stream could be
%               cerr, cout, or any other valid stream.
%
% Parameters descriptions :
% 
% name               description
% ------------------ ------------------------------------------------------
% stream             A reference to the output stream.
% <return>           A reference to the output stream.
***************************************************************************/

{
        stream << "Tree " << tree_count << ":\n"
                << "occupancy is " << occupancy << " elements.\n";

        return (root) ? root->Write_AllTNodes (stream) : stream;
}
