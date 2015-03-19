#ifndef SINGLE_NODE_H
#define SINGLE_NODE_H

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

template <typename T>
class Quadtree;
using namespace std;

template <typename T>
class Quadtree_node {
	private:
		T       x_value;
		T       y_value;

		Quadtree_node *north_west;
		Quadtree_node *north_east;
		Quadtree_node *south_west;
		Quadtree_node *south_east;

	public:
		Quadtree_node( T const & = T(), T const & = T() );

		T retrieve_x() const;
		T retrieve_y() const;

		Quadtree_node *nw() const;
		Quadtree_node *ne() const;
		Quadtree_node *sw() const;
		Quadtree_node *se() const;

		T min_x() const;
		T min_y() const;

		T max_x() const;
		T max_y() const;

		T sum_x() const;
		T sum_y() const;

		bool member( T const &, T const & ) const;

		bool insert( T const &, T const & );
		void clear();

	friend class Quadtree<T>;
};

template <typename T>
Quadtree_node<T>::Quadtree_node( T const &x, T const &y ):
x_value( x ), 
y_value( y ), 
north_west( 0 ),
north_east( 0 ),
south_west( 0 ),
south_east( 0 ) {
	// empty constructor
}

template <typename T>
T Quadtree_node<T>::retrieve_x() const {
	return x_value;
	// returns the value of x at the root
}

template <typename T>
T Quadtree_node<T>::retrieve_y() const {
	return y_value;
	// returns the value of y at the root
}

template <typename T>
Quadtree_node<T> *Quadtree_node<T>::nw() const {
	return north_west;
	// returns the nw node.
}

template <typename T>
Quadtree_node<T> *Quadtree_node<T>::ne() const {
	return north_east;
	// returns the ne node.
}

template <typename T>
Quadtree_node<T> *Quadtree_node<T>::sw() const {
	return south_west;
	// returns the sw node.
}

template <typename T>
Quadtree_node<T> *Quadtree_node<T>::se() const {
	return south_east;
	// returns the se node.
}

template <typename T>
T Quadtree_node<T>::min_x() const {
	// Checks if the node has any more children
	if(sw() == 0  && nw()==0)
	{
		return retrieve_x();
	// Then retrieves the value of the nodes.
	}

	//Otherwise checks if one of the nodes is set to zero
	//and recursively calls min_x() to traverse the remaining node similarly.
	if (sw() == 0 )
	{	
		return nw() -> min_x();
	// recursively calls min_x() via the nw pointer to traverse the subtree
	// and find the minimum value.
	}
	
	if (nw() == 0 )
	{
		return sw() -> min_x();
	// recursively calls min_x() via the nw pointer to traverse the subtree
	// and find the minimum value.
	}
	
	//returns the minumum value between the two leaves.
	return min (nw() -> min_x(), sw() -> min_x());
}

template <typename T>
// Similar  to min_x but instead uses sw and se as one of them
//	will be the smallest 'y values'.
T Quadtree_node<T>::min_y() const {
	if(sw () == 0  && se()==0)
		{
		return retrieve_y();
		}
	if ( sw () == 0)
		{	
			return se() -> min_y();
		}
	if (se () == 0)
		{
			return sw ()-> min_y();
		}

	return min (se () -> min_y(), sw () -> min_y());
}

template <typename T>
T Quadtree_node<T>::max_x() const {
	if(se ()== 0  && ne()==0)
	{
		return retrieve_x();
	}
	if ( se () == 0)
	{	
		return ne () -> max_x();
	}
	if (ne () == 0)
		{
			return se () -> max_x();
		// recursively calls mi_x() via the nw pointer to traverse the subtree
		// and find the minimum value.
		}

	//returns the maximum value between the two leaves.
	return max (ne () -> max_x(), se () -> max_x());
}

template <typename T>
T Quadtree_node<T>::max_y() const {
		if(nw () == 0  && ne () == 0)
		{
		return retrieve_y();
		}
	if ( nw ()== 0)
		{	
			return ne() -> max_y();
		}
	if (ne() == 0)
		{
			return nw() -> max_y();
		}

	return max (nw() -> max_y(), ne() -> max_y());
}

template <typename T>
//calculates the sum in the x direction
T Quadtree_node<T>::sum_x() const {
	if ( this == 0 ) {
// returns 0 if the tree just contains the root.
		return 0;
	} else {
	
	//retrieves the vakue of the parent node and then each of the child pointers, recursively call sum_x to span the
	// tree and hence obtain 'x values' for all 4 directions.
		return retrieve_x() + (nw()->sum_x())+ sw()->sum_x() + se()->sum_x()+ne()->sum_x();
	
	}
}

template <typename T>
// Calculates the sum in the y direction
T Quadtree_node<T>::sum_y() const {
	if ( this == 0 ) {
		return 0;
	} else {
	//retrieves the value of the parent node and then each of the child pointers, recursively call sum_y to span the
	// tree and hence obtain 'y values' for all 4 directions.
		return retrieve_y() + nw()->sum_y()+ sw()->sum_y() + se()->sum_y()+ne()->sum_y();
	}
}

template <typename T>
// Member checks if the x & y values passed, are present as nodes in the tree. 
	bool Quadtree_node<T>::member( T const &x, T const &y ) const {
	if ( this == 0 ) 
	{ // Returns false if the tree is empty.
		return false;
	}

	if (x == x_value && y==y_value)
	{	// Returns true if the x and y values are found.
		return true;
	}

	if(x >= x_value)
	{	
		if(y >= y_value)
		{	// recursively calls member with the ne() pointer to find the node
			// if the x and y values are greater than the nodes'.
			return ne()->member(x,y);
		}
		else
		{	// recursively calls member with the se() pointer to find the node
			// if the x value is greater but y value is less than the nodes'.
			return se()->member(x,y);
		}
	}
	else
	{	
		if(y >= y_value)
		{	
			// recursively calls member with the nw() pointer to find the node
			// if the x value is lesser but y value is greater than the nodes'.
			return nw()->member(x,y);
		}
		else
		{	// recursively calls member with the sw() pointer to find the node
			// if the x and y values are lesser than the nodes'.
			return sw()->member(x,y);
		}
	}

}



template <typename T>
// Inserts a new node into the tree.
bool Quadtree_node<T>::insert( T const &x, T const &y ) {
	
 if (x_value == x && y_value == y)
{	//Checks if the values passed are already present as a node.
	return false;
}
	
 if (x < x_value  && y <y_value)
{	
	if(sw() == 0)
	{// If sw node is empty, nd x & y are less than root's x & y, create new node for sw direction.
		south_west =  new  Quadtree_node (x,y);
		return true;
	}
	// If x & y are less than root's x & y, inserts a node in sw direction.
	return sw() -> insert(x,y);
}
 if (x >= x_value  && y >= y_value)
{
	if(ne () == 0)
	{// If ne node is empty,and x & y are greater than root's x & y, create new node for ne direction.
		north_east =  new Quadtree_node (x,y);
		return true;
	}
	// If x & y are greater than root's x & y, inserts a node for ne direction.
	return ne() -> insert(x,y);
}
 if (x >= x_value && y< y_value)
{
	if(se() == 0)
	{ //If se node is empty,and x > root x & y < root y,then create new node for se direction.
		south_east =  new Quadtree_node (x,y);
		return true;
	}
	//If x > root x & y < root y, insert a new node for se direction.
	return se() -> insert(x,y);
}
 if (x < x_value && y >= y_value)
{
	if(nw() == 0)
	{//If nw node is empty,and x < root x & y > root y,then create new node for nw direction.
		north_west =  new Quadtree_node (x,y);
		return true;
	}
	//If x < root x & y > root y, insert a new node for nw direction.
	return nw()->insert(x,y);
}

}

template <typename T>
// Clears the tree by recursively calling itself.
void Quadtree_node<T>::clear() {
	if (sw() != 0)
	{//If sw is not equal to 0.
		//Calls clear with the accessor.
		sw() -> clear(); 
		// Deletes the node
		delete south_west;
		// Sets south_west to 0 as a sanity check.
		south_west = 0;

	}
	if (ne() != 0)
	{
		//Calls clear with the accessor.
		ne() -> clear();
		// Deletes the node
		delete north_east;
		// Sets north_east to 0 as a sanity check.
		north_east = 0;

	}
	if (se() != 0)
	{
		 //Calls clear with the accessor.
		 se() -> clear();
		 // Deletes the node
		 delete south_east;
		 // Sets south_east to 0 as a sanity check.
		 south_east = 0;

	}
	if (nw() != 0)
	{
		//Calls clear with the accessor.
		 nw()-> clear(); 
		 // Deletes the node
		 delete north_west;
		 // Sets south_east to 0 as a sanity check.
		 north_west = 0;
	}

}

// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif