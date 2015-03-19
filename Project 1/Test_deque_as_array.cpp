#include "Deque_as_array_tester.h"
#include "Deque_as_array.h"
#include <iostream>
//#include <algorithm>
using namespace std;

int main() {

	Deque_as_array d1(4);
	cout << "The capacity of the deque is " << d1.capacity();
	d1.print ();

	try
	{
		cout << "Trying to remove element from the array.\n";
		d1.dequeue_head();
	} 
	catch (underflow)
	{
		cout <<"This array is empty,so removal of the head cannot occur.\n\n";
	}

	
	d1.enqueue_head(50);
	d1.enqueue_tail(60);
	d1.enqueue_head(70);

	
	cout << "After adding three elements to the dequeue's head.Staus of deque is:\n\n";
	d1.print ();

	cout <<"\n";
	cout << "Removing the head of the deque\n\n";
	d1.dequeue_head();
	d1.print ();
	
	cout <<"\n";
	cout << "Removing the tail of the deque\n";
	d1.dequeue_tail();
	d1.print ();
	
	cout << "\n";
	cout << "Removing another element, should leave the array empty...\n";
	d1.dequeue_tail();
	d1.print ();

	try
	{
		cout <<"\n";
		cout <<"Attempting to remove another element should throw an exception.\n";
		d1.dequeue_tail();
		d1.print();
	}
	catch (underflow)
	{
		cout <<"\n";
		cout << "UNDERFLOW HAS OCCURRED! Since the array is empty, more elements cannot be removed.\n";
	}

	cout << "Exhausting the array...";
	d1.enqueue_head (60);
	d1.enqueue_tail (70);
	d1.enqueue_head (80);
	d1.enqueue_tail (90);
	d1.print ();

	cout <<"\n";
	cout << "Checking if the deque is empty by calling the empty() function....\n";
	if (d1.empty())
	{
		cout << "The array is empty\n\n";
	}
	
	else
	{
		cout << "The array has elements in it and is not empty.\n\n";
	}
	
	
	try
	{
		cout <<"\n";
		cout <<"Attempting to add another element. This should throw an exception...\n";
		d1.enqueue_head(100);
	}
	catch (overflow)
	{
		cout <<"OVERFLOW HAS OCCURRED !Will be unable to add another element since the deque is full";
	}

	
	cout <<"\n";
	cout <<"Calling the clear() function to remove all the elements from the array.";
	d1.clear();
	d1.print();



	
	getchar();
	
	return 0;
	
}

