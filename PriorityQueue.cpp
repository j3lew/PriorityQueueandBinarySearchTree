#include "PriorityQueue.hpp"
#include <iostream>
#include <cstdlib>
using namespace std;
typedef int DataType;

// Implement the functions here.
PriorityQueue::PriorityQueue(unsigned int capacity){
	capacity_ = capacity;
	size_ = 0;
	heap_ = new DataType( capacity );
}

PriorityQueue::~PriorityQueue(){
	delete[ ] heap_;
}

bool PriorityQueue::enqueue(DataType val){
	if( full( ) )
	{
		return false;
	}
	else if( empty( ) )
	{
		heap_[ 1 ] = val;
		size_ ++;
		return true;	
	}
	else  
	{
		int count = size_ + 1;
		heap_[ count ] = val;
		int temp;
		while( heap_[ count / 2 ] < heap_[ count ] && count > 1 )
		{
			temp = heap_[ count ];
			heap_[ count ] = heap_[ count / 2 ];
			heap_[ count / 2 ] = temp;
			count = count / 2;
		}
		size_ ++;
		return true;
	}
}
	
bool PriorityQueue::dequeue(){
	if( empty() )
	{
		return false;
	}
	else
	{
		int count = 1;
		heap_[ 1 ] = heap_[ size_ ];
		while( ( heap_[ count * 2 ] > heap_[ count ] || heap_[ count * 2 + 1 ] > heap_[ count ] ) && count * 2 < size_  )
		{
			if( heap_[ count * 2 ] > heap_[ count * 2  + 1 ] )
			{
				count *= 2;
			}
			else 
			{
				count = count * 2  + 1;
			}
			DataType temp = heap_[ count ];
			heap_[ count ] = heap_[ count / 2 ];
			heap_[ count / 2 ] = temp;
		}
		size_--;
		return true;
	}
}
		
DataType PriorityQueue::max() const{
	if( empty( ) )
	{
		return NULL;
	}
	else
	{
		return heap_[ 1 ];
	}
}
			
bool PriorityQueue::empty() const{
	if ( size_ == 0 )
	{
		return true;
	}
	else 
	{
		return false;
	}
}
				
bool PriorityQueue::full() const{
	if (size_ == capacity_)
	{
		return true;
	}
	else 
	{
		return false;
	}
}
					
unsigned int PriorityQueue::size() const{
	return size_;
}
						
void PriorityQueue::print() const{
	for( int i = 1; i <= size_; i++ )
	{
		cout << heap_[ i ] << endl;
	}
}

