#ifndef QUADTREE_H
#define QUADTREE_H

/*****************************************
 * UW User ID:  ssabhlok
 * Submitted for ECE 250
 * Department of Electrical and Computer Engineering
 * University of Waterloo
 * Calender Term of Submission:  (Winter|Spring|Fall) 20NN
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *****************************************/

#include "ece250.h"
#include "Quadtree_node.h"
#include "Exception.h"
#include <iostream>
using namespace std;
template <typename T>
class Quadtree {
	private:
		Quadtree_node<T> *tree_root;
		int count;

	public:
		Quadtree();
		~Quadtree();

		// Accessors

		int size() const;
		bool empty() const;

		T min_x() const;
		T min_y() const;

		T max_x() const;
		T max_y() const;

		T sum_x() const;
		T sum_y() const;

		Quadtree_node<T> *root() const;
		bool member( T const &, T const & ) const;

		// Mutators

		void insert( T const &, T const & );
		void clear();

	
};

template <typename T>
Quadtree<T>::Quadtree():
tree_root( 0 ), 
count( 0 ) {
	//sets tree_root and count values to 0 by default
	//empty constructor.
	
}

template <typename T>
Quadtree<T>::~Quadtree() {
	//calls the clear function to destroy the object.
	clear();
}

template <typename T>
int Quadtree<T>::size() const {
	return count; // returns the number of elements in the tree
}

template <typename T>
bool Quadtree<T>::empty() const {
// Runs an if-condition to check if the tree is empty (count = 0)
	if (count == 0)
		return true;
	else
		return false;
}

template <typename T>
//returns the minimum x_value in the tree.
T Quadtree<T>::min_x() const {
	if (count == 0)
	{
		throw underflow();
		// If the tree is empty thrown an underflow exception
	}
	else
	{
		return tree_root->min_x();
		// otherwise call the corresponding min function in QuadTree_node.h
	}
}

template <typename T>
// returns the minimum y value in the tree.
T Quadtree<T>::min_y() const {
	if (count == 0)
		// If the tree is empty
	{
		throw underflow();
		// thrown an underflow exception
	}
	else
	{
		return tree_root->min_y();
		// otherwise call the corresponding min function in QuadTree_node.h
	}
}

template <typename T>
// returns the maximum x value in the tree.
T Quadtree<T>::max_x() const {
	if (count == 0)
		//If the tree is empty
	{
		throw underflow();
		//throw an underflow exception
	}
	else
	{
		return tree_root->max_x();
		//otherwise call the corresponding max function in QuadtTree_node.h
	}
}

template <typename T>
// returns the maximum y value in the tree.
T Quadtree<T>::max_y() const {
		if (count == 0)
		//If the tree is empty
	{
		throw underflow();
		//throw an underflow exception

	}
	else
	{
		return tree_root->max_y();
		//otherwise call the corresponding max function in QuadtTree_node.h
	}
}

template <typename T>
// returns the sum in the x direction
T Quadtree<T>::sum_x() const {
		if (count == 0)
	{
		return 0;
		// If the tree is empty the function returns 0
	}
	else
	{
		return tree_root->sum_x();
		// Otherwise it branches recursively to the sum_x() 

	}
}

template <typename T>
T Quadtree<T>::sum_y() const {
		if (count == 0)
	{// If the tree is empty the function returns 0
		return 0;
	}
	else
	{ // Otherwise it branches recursively to the sum_y() 
		return tree_root->sum_y();
	}
}

template <typename T>
Quadtree_node<T> *Quadtree<T>::root() const {
	return tree_root; // returns the tree_root object.
}

template <typename T>
//Checks if values passed are assiged a node in the tree.
bool Quadtree<T>::member( T const &x, T const &y ) const {
	
	if ( tree_root != 0)
	{   // redirects pointer to member in Quadtree_node to check if node exists
		return tree_root->member(x,y);
	}
		return false;
}

template <typename T>
// Inserts a new Quadtree_node object in the tree.
void Quadtree<T>::insert( T const &x, T const &y ) {
	if (count == 0)
	{
		//Creates a new Quadtree_node object if tree is empty
			tree_root = new Quadtree_node<T>(x,y);
		// Increments counter.
			count++; 

	}
	else
	{
		// If tree has objects, simply inserts a new node.
		if (tree_root -> insert(x,y))
		// Increments counter.
			count++;
	     
	}
	
}

template <typename T>
//Clears the tree by deleting the tree_root object
void Quadtree<T>::clear() {

	if ( tree_root != 0)
	{	
		tree_root->clear(); //pointer redirected to Quadtree_node.h class.
		delete tree_root; // deletes the tree root object.
		tree_root = 0;	// sets tree_root to 0 as a sanity check.
		count = 0;  // sets count to 0.
	}
}



// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif