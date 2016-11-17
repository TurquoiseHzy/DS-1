//
//  Stack.h
//
//  Created by Ziyi Huang on 2016/11/16.
//  Copyright © 2016年 Ziyi Huang. All rights reserved.
//	
//	
//	Declaration & definition of class Stack
//	
//
#ifndef STACK_H
#define STACK_H
typedef unsigned int Size;
typedef unsigned int Index;
template <class DataType>
/*
	class Stack:
		@attr:
			data:saves ptr of data
			size:size of Stack
			capacity:capacity of Stack

*/
class Stack{
protected:
	DataType **data;
	Size size;
	Size capacity;

public:
	Stack():data(NULL),
		size(0),
		capacity(1) { 
			data = new DataType* [1]; 
	}
	~Stack(){
		delete[] data;
	}
protected:
	//double capacity
	void doubleCapacity(){
		DataType **ndata = new DataType* [ capacity * 2 ];
		for(Index i = 0 ; i < capacity ; i ++){
			ndata[i] = data[i];
		}
		capacity = capacity * 2;
		delete []data;
		data = ndata;
	}

public:
	//return top
	DataType* top(){
		if(size){
			return data[size - 1];
		}
		return NULL;
	}

	//judge empty
	bool empty(){
		return (size == 0);
	}

	//return size
	Size get_size(){
		return size;
	}
	
	//pop top
	DataType* pop(){
		if(size){
			size --;
			return data[size];
		}
		return NULL;
	}

	//push @dt
	Size push(DataType* dt){
		if(size == capacity){
			doubleCapacity();
		}
		data[size] = dt;
		size ++;
		return size;
	}

	//push @dt
	Size push(DataType& dt){
		if(size == capacity){
			doubleCapacity();
		}
		data[size] = &dt;
		size ++;
		return size;
	}
};
#endif