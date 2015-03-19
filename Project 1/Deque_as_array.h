#ifndef DEQUE_AS_ARRAY_H
#define DEQUE_AS_ARRAY_H

/*****************************************
 * UW User ID:  ssabhlok
 * Submitted for ECE 250
 * Semester of Submission:  (Fall) 2014
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided  code.
 *****************************************/

#include "Exception.h"
#include <iostream>
using namespace std;


class Deque_as_array {
	private:
		int array_size; // Holds the size of the deque
		int *array;		// Creates a pointer to an array called array.
		int ihead;		// A variable that points to the head of the deque.
		int itail;		// A variable that points to the end of the deque.
		int count;      // Counts the number of elements in the deque.

	public:
		Deque_as_array( int = 10 );
		~Deque_as_array();

		int head() const;		// Accessor returns the integer at the head of the deque.
		int tail() const;		// Accessor returns the integer at the tail of the deque.
		int size() const;		// Accessor returns the number of elements in the deque.
		bool empty() const;		// Accessor returns true if array is empty and false if the array has elements. 
		int capacity() const;   // Accessor returns the size of the deque. Depends on the size set by the user.

		void enqueue_head( int const & ); //Mutator manupilates the ihead variable so that it points to the appropriate element.
		void enqueue_tail( int const & ); //Mutator manupilates the itail variable so that it points to the appropriate element.
		int dequeue_head();				  //Mutator removes the element at the head and accordingly manupilates the ihead variable.
		int dequeue_tail();				  //Mutator removes the element at the tail and accordingly manupilates the itail variable.
		void clear();					  // Clears all the elements of the deque.
		void print();					  // Prints all the elemnents of the deque.

	
};

Deque_as_array::Deque_as_array( int n ): 
array_size( max( 1, n ) ), 
array( new int[array_size] ), 
count( 0 ) {
	// Initializing the head to 0, so that it points to the first element of the deque.
	ihead = 0;
	// Initializing the tail to 0, so that it points to the first element of the deque.
	itail = 0;

}

Deque_as_array::~Deque_as_array() { 
	delete [] array ;
}

int Deque_as_array::size() const {
	
	return count;
}

 
int Deque_as_array::capacity() const {
	return array_size;
}

 
bool Deque_as_array::empty() const {
	
// If Statement to check if the deque is empty	
	if (count  == 0) 
	{
		return true;
	}

	else 
	{
		return false;
	}

}

 
int Deque_as_array::head() const {
	// If the deque is empty, the function throws an underflow exception.
	if (size() == 0)
	{
	   throw underflow();
	}
	else 
	{ // Else returns the value at the head of the deque. 
		return array[ihead];

	}
}

 
int Deque_as_array::tail() const {
		//If the deque is empty, the function throws an underflow exception.
	if (size() == 0)
	{
	   throw underflow();
	}
	else 
	{   // Else returns the value at the tail of the deque.   
		return array[itail];

	}
}


void Deque_as_array::enqueue_head( int const &obj ) {
	if (empty())
	{
		// Setting the head and tail to 0, so that they point to the first element of the deque.
		ihead = itail = 0;
		// Storing an object to the current address of head.
		array[ihead] = obj;
		// Incrementing the element count of the deque.
		count ++;
	}
	else if (size() == capacity())
	{	//If the number of elements in the array exceed the capacaity, an exception is thrown.
		throw overflow();
	}
	else
	{	// Decrementing the head, so that it points to a new address for storing an object.
		ihead = (ihead - 1);
		if( ihead < 0)
		{   // Adding the array size to the head, to ensure circular insertion.
			ihead = (ihead) + (array_size);
		}
		// Storing an object to the current address of head.
		array[ihead] = obj;
		// Incrementing the element count of the deque.
		count++;
	}

}


void Deque_as_array::enqueue_tail( int const &obj ) {
	if (empty())
	{
		// Setting the head and tail to 0, so that they point to the first element of the deque.
		itail = ihead = 0;
		// Storing an object to the current address of tail.
		array[itail] = obj;
		// Incrementing the element count of the deque.
		count = count + 1;
	}

	else if (size() == capacity())
	{	//If the number of elements in the array exceed the capacaity, an exception is thrown.
		throw overflow();
	}

	else {
	
		if(itail == (array_size -1) )
		{
		// If the tail is pointing to the last element,redirect it to the 0th element for circulat insertion
			itail = 0;
		// Storing an object to the current address of tail.
			array[itail] = obj;
		// Incrementing the element count of the deque.
			count++;
		}
		else
		{
			// Incrementing the head, so that it points to a new address for storing an object.
			itail = (itail + 1);
			// Storing an object to the current address of tail.
			array[itail] = obj;
			// Incrementing the element count of the deque.
			count ++;
		}
}
}

 
int Deque_as_array::dequeue_head() {
	// Initialising a new variable for return the object removed.
	int temp = 0; 
	if (empty ())
	{	// If the deque is already empty, throw an underflow exception.
		throw underflow();
	}
	else
	{   // Assigning the value of the current head, to the variable.
		temp =  array[ihead];
		//Incrementing the head, in order to move its address.
		ihead = (ihead +1) % (array_size);
		if (ihead<0)
		{
		// Ensuring that the head remains positive and circular deletion occurs.
		ihead = (ihead)+(array_size);
		
		}
		// Since an element is being removed, count is decremented
		count = count -1;
		
	}
		// This returns the value of the deleted element.
		return temp;    
}

 
int Deque_as_array::dequeue_tail() {
	// Initialising a new variable for return the object removed.
	int temp = 0;	
	if (empty ())
	{
		// If the deque is already empty, throw an underflow exception.
		throw underflow();
	}
	else
	{	// Assigning the value of the current head, to the variable.
		temp = array[itail];
		itail = itail-1;
		if (itail < 0)
		{	// Ensuring that the tail always remains positive and points to the last element if it becomes negative.
			itail =(array_size - 1);
		}
		if (size() == 1)
		{	//If there is one element left, then dequeing it should leave the deque empty.
			size () == 0;
		}
		// Since an element is being removed, count is decremented
		count = count-1;
		
		// This returns the value of the deleted element.
		return temp;     
}
}


// Clears the array by setting the head,tail and count variables to 0.
void Deque_as_array::clear() {
	ihead = 0;
	itail = 0;
	count = 0;
	
}

// prints the array
void Deque_as_array::print() 
{
	//Checks if the deque is empty.
	if (empty()) {
		cout << "The array is empty! " << endl;
		return;
	}
	//Else prints the elements, clearly indicating the head, tail and size.
	else{
	cout<< "The elements of the array are : \n";

	{
	int n = this->array_size;
	
	for(int i = 0; i < n ; i++)
	{
		cout <<"\n";
		cout<<" i: " << i << "    " << array[i]<< endl;
	}
	cout<<endl;
	cout<< "\nThe head of the deque is : "<< array[ihead];
	cout<< "\nThe tail of the deque is : " <<array[itail];
	cout <<"\nYou array has "<<count<<" elements.\n";
	}
}
}




// Is an error showing up in ece250.h or elsewhere?
// Did you forget a closing '}' ?

#endif