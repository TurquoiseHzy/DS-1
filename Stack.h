#ifndef STACK_H
#define STACK_H
#include"Error.h"
typedef unsigned int Size;
template <class DataType>
class Stack{
protected:
	DataType *data;
	Size size;
	Size capacity;

public:
	Stack():data(NULL),
		size(0),
		capacity(1) { 
			data = new DataType [1]; 
	}
	~Stack(){
		delete[] data;
	}
protected:
	void doubleSize(){
		DataType *ndata = new DataType [ capacity * 2 ];
		memcpy(ndata, data, capacity);
		capacity << 1;
		delete []data;
		data = ndata;
	}

public:
	DataType top(){
		try{
			if(size){
				return data[size - 1];
			}
			throw EmptyStackError;
		}
	}

	bool empty(){
		return (size == 0);
	}

	Size get_size(){
		return size;
	}
	
	DataType pop(){
		try{
			if(size){
				size --;
				return data[size];
			}
			throw EmptyStackError;
		}
	}

	Size push(DataType dt){
		if(size == capacity){
			doubleSize();
		}
		data[size] = dt;
		return size;
	}
};
#endif