#ifndef DOUBLE_HASH_TABLE_H
#define DOUBLE_HASH_TABLE_H

/*****************************************
 * UW User ID:  ssabhlok
 * Submitted for ECE 250
 * Semester of Submission:  (Fall) 2014
 *
 * By submitting this file, I affirm that
 * I am the author of all modifications to
 * the provided code.
 *****************************************/

#include "Exception.h"
#include "ece250.h"
#include <iostream>
using namespace std;

enum state { EMPTY, OCCUPIED, DELETED };

template<typename T>
class DoubleHashTable {
private:
int count;
int power;
int array_size;
T *array;
state *occupied;

int h1( T const & ) const; // first hash function
int h2( T const & ) const; // second hash function

public:
DoubleHashTable( int = 5 );
~DoubleHashTable();
int size() const;
int capacity() const;	
bool empty() const;
bool member( T const & ) const;
T bin( int ) const;

void print() const;
void occupy() const;

void insert( T const & );
bool remove( T const & );
void clear();
};

template<typename T >
DoubleHashTable<T >::DoubleHashTable( int m ):
count( 0 ), power( m ),
array_size( 1 << power ),
array( new T [array_size] ),
occupied( new state[array_size] ) {

for ( int i = 0; i < array_size; ++i ) {
occupied[i] = EMPTY;
}
}

template<typename T >
DoubleHashTable<T >::~DoubleHashTable() {
delete[] array;
delete[] occupied;
}

template<typename T >
int DoubleHashTable<T>::size() const {
    // enter your implemetation here 
return count;
}

template<typename T >
int DoubleHashTable<T >::capacity() const {
    // enter your implemetation here 
return array_size;
}



template<typename T >
bool DoubleHashTable<T >::empty() const  {
    // enter your implemetation here 
if(count == 0)
return true;
else
return false;
}

template<typename T >
int DoubleHashTable<T >::h1( T const &obj ) const {
int value = static_cast <int> (obj) % (array_size);
if (value < 0)
{
value = value + array_size;
}
return value;
}

template<typename T >
int DoubleHashTable<T >::h2( T const &obj ) const {
int value1 = (static_cast <int> (obj) / (array_size)) % (array_size);
if ( value1 < 0 )
{
value1 = value1 + array_size;
}
if ( value1%2 ==0)
{
value1 = value1 +1;
}
return value1;
}

template<typename T >
bool DoubleHashTable<T >::member( T const &obj ) const {
bool isThere = false;
int position;
int f1 = h1(obj);
int f2 = h2(obj);
for (int i =0; i <array_size; i ++)
{
position = ((f1+(i*f2)) % (array_size));
if (array[position]==(obj) && occupied[position]==OCCUPIED)
{
isThere = true;
break;
}
}
return isThere;
}

template<typename T >
T DoubleHashTable<T >::bin( int n ) const {
    return array[n];	     
                    
//return T();
}

template<typename T >
void DoubleHashTable<T >::insert( T const &obj ) {
int position;
int f1 = h1(obj);
int f2 = h2(obj);
if (count == array_size)
{
throw overflow ();
}

for ( int i = 0; i < array_size; i++)
{
position = ((f1+(i*f2)) % (array_size));

if (occupied[position]==DELETED || occupied[position]==EMPTY)
{
array[position] =  (obj);
occupied[position] = OCCUPIED;
count ++;
break;
}
}
 
return ; 
}

template<typename T >
bool DoubleHashTable<T >::remove( T const &obj ) {
// enter your implemetation here 
	int position;
	int f1 = h1(obj);
	int f2 = h2(obj);
	bool flagValue = false;
	if(count ==0)
	{
		return false;
	}
	for (int i = 0; i< array_size; i++)
	{
		position = ((f1+(i*f2)) % (array_size));
		if(array[position] ==  (obj))
		{
			array[position] = NULL;
			occupied [position] = EMPTY;
			count = count - 1;
			flagValue = true;
			break;
		}
	}
return flagValue;
}

template<typename T >
void DoubleHashTable<T >::clear() {
// enter your implemetation here
for ( int i =0; i < array_size; i++)
{
occupied[i] = EMPTY;
}
return;
}

template<typename T >
void DoubleHashTable<T >::print() const {
     
cout <<"The elements in the bins are:\n ";
for ( int i = 0; i < array_size; i++)
{
cout<<i<<" : "<< array[i]<<endl;
//cout<<occupied[i]<<endl;
}
cout <<"The number of elements in the hash table are: "<<count;
cout <<"The array size is: "<< array_size;

return;
}

template<typename T >
void DoubleHashTable<T >::occupy() const {
     
cout <<"The positions occupied in the hash table are:\n ";
for ( int i = 0; i < array_size; i++)
{
cout<<"OCCUPIED"<<endl;
}

return;
}

#endif