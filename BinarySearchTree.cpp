#include "BinarySearchTree.hpp"
#include<cstring>
#include<iostream>

using namespace std;
typedef int Datatype;
using namespace std;
BinarySearchTree::Node::Node(DataType newval)
{
	val = newval;  
	left = NULL;    
	right = NULL;   	
}

// Default constructor.
BinarySearchTree::BinarySearchTree()
{
	size_ = 0;
	root_ = NULL;
}

// Destructor.
BinarySearchTree::~BinarySearchTree()
{
	if( root_ == NULL )
	{
		return;
	}
	Node*visit = root_;
	while( visit -> right != NULL )
	{
		remove( visit -> right -> val );
	}
	while( visit -> left != NULL )
	{
		remove( visit -> left -> val );
	}
	remove( root_ -> val );
}

// Inserts value "val" into the tree. Returns false if failed (i.e., "val"
// already exists in the tree), and true otherwise.
bool BinarySearchTree::insert(DataType val)
{
	Node*tempNode = new Node( val );
	
	if( size_ == 0 )
	{
		root_ = tempNode;
		size_ ++;
		return true;
	}
	else if( exists( val ) )
	{
		return false; 
	}
	else
	{
		Node*temp = root_;
		Node*temp2 = temp;
		while( temp != NULL )
		{
			temp2 = temp;
			if( temp -> val > val )
			{
				temp = temp -> left;
			}
			else 
			{
				temp = temp -> right;
			}
		}
		if( temp2 -> val < val )
		{
			temp2 -> right = tempNode;
		}
		else 
		{
			temp2 -> left = tempNode;
		}
		size_ ++;
		return true; 
	} 
}
// Removes the node with value "val" from the tree. Returns true if successful,
// false otherwise.
bool BinarySearchTree::remove(DataType val)
{
	if( !exists( val ) )
	{
		return false;
	}
	else
	{
		Node*temp = root_;
		Node*temp2 = temp;
		if( size_ == 1 )
		{
			delete root_;
			size_ --;
			root_ = NULL;	
			return true;
		}	
		while( temp -> val != val )
		{
			temp2 = temp;
			if( temp -> val < val )
			{
				temp = temp -> right;
			}
			else
			{
				temp = temp -> left; 
			}
		}
		if( temp -> right == NULL && temp -> left == NULL )
		{
			if( temp2 -> val < temp -> val )
			{
				temp2 -> right = NULL;
			}
			
			else 
			{
				temp2 -> left = NULL;
			}
			delete temp;
			size_ --;
			return true;
		}
		else if( temp -> right != NULL && temp -> left != NULL )
		{
			Node*min = temp -> right;
			while( min -> left != NULL )
			{
				min = min -> left;
			}
			DataType var = min -> val;
			remove( min -> val );
			temp -> val = var;
			return true;
		}
		else
		{
			if( root_ == temp )
			{
				if( temp -> right == NULL )
				{
					root_ = temp -> left;
				}
				else
				{
					root_ = temp -> right;
				}
				delete temp;
				temp = NULL;
				size_ --;
				return true;
			}
			if( temp -> val > temp2 -> val )
			{
				if( temp -> left == NULL )
				{
					temp2 -> right = temp -> right;
				}
				else 
				{
					temp2 -> right = temp -> left; 
				}
			}
			else 
			{
				if( temp -> left == NULL )
				{
					temp2 -> left = temp -> right;
				}
				else 
				{
					temp2 -> left = temp -> left;
				}
			}
			delete temp;
			size_ --;
			return true;
		}
	}
}

// Returns true if a node with value "val" exists in the tree; false otherwise.
bool BinarySearchTree::exists(DataType val) const
{
	if( size_ == 0 )
	{
		return false;
	}
	else 
	{
		Node*temp = root_;
		while( temp != NULL )
		{
			if( temp -> val == val )
			{
				return true;
			}
			else 
			{
				if( temp -> val > val ) 
				{
					temp = temp -> left;
				}
				else
				{
					temp = temp -> right;
				}
			}
		}
		return false;
	}
}

// Returns the minimum value of the tree. You can assume that this function
// will never be called on an empty tree.
BinarySearchTree::DataType BinarySearchTree::min() const
{
	if( size_ == 0 )
	{
		return 0;
	}
	Node*temp = root_;
	while( temp -> left != NULL )
	{
		temp = temp -> left;
	}
	return temp -> val;
}

// Returns the maximum value of the tree. You can assume that this function
// will never be called on an empty tree.
BinarySearchTree::DataType BinarySearchTree::max() const
{	
	if( size_ == 0 )
	{
		return 0;
	}
	Node*temp = root_;
	while( temp -> right != NULL )
	{
		temp = temp -> right ;
	}
	return temp -> val;
}

// Returns the number of nodes in the tree.
unsigned int BinarySearchTree::size() const
{
	return size_;
}

// Returns the maximum depth of the tree. A tree with only the root node has a
// depth of 0. You can assume that this function will never be called on an 
// empty tree.
unsigned int BinarySearchTree::depth() const
{
	return getNodeDepth( root_ );
}

// Optional function.
// Recursively get the maximum depth from a given node. Call on root_ first.
// This might be of great value to you in depth().
int BinarySearchTree::getNodeDepth(Node* n) const
{
	Node*visit = n;
	int depthL = 0;
	int depthR = 0;
	if( visit -> right == NULL && visit -> left == NULL )
	{
		return 0;
	}
	else
	{
		if( visit -> left ) 
		{
			depthL = 1 + getNodeDepth( visit -> left );
		}
		if( visit -> right )
		{
			depthR = 1 + getNodeDepth( visit -> right );
		}
	}
	// comparing the left depth and the right depth
	if( depthR <= depthL )
	{
		return depthL;
	}
	else 
	{
		return depthR;
	}
}
  
// You can print the tree in which ever manner you like, however methods such
// as in-order, level-order, etc. might be the most useful for debugging
// purposes.
void BinarySearchTree::print() const
{
	if( size_ == 0 )
	{
		return;
	}
	Node*que[ size_ ];
	que[ 0 ] = root_;
	int index = 0;
	int temp = 0;
	int count = 1;
	while( count > 0 )
	{
		cout << que[ temp ] -> val << endl;
		if( que[ temp ] -> left != NULL )
		{
			index ++;
			que[ index ] = que[ temp ] -> left; 
			count ++;
		}
		else if( que[ temp ] -> left != NULL && que[ temp ] -> right != NULL )
		{
			index ++;
			que[ index ] = que[ temp ] -> right;
		}
		temp ++;
		count --;
	}
}
