#ifndef STACK_H
#define STACK_H
typedef unsigned int Size;
template <class DataType>
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
	void doubleCapacity(){
		DataType **ndata = new DataType* [ capacity * 2 ];
		memcpy(ndata, data, capacity);
		capacity = capacity * 2;
		delete []data;
		data = ndata;
	}

public:
	DataType* top(){
		if(size){
			return data[size - 1];
		}
		return NULL;
	}

	bool empty(){
		return (size == 0);
	}

	Size get_size(){
		return size;
	}
	
	DataType* pop(){
		if(size){
			size --;
			return data[size];
		}
		return NULL;
	}

	Size push(DataType* dt){
		if(size == capacity){
			doubleCapacity();
		}
		data[size] = dt;
		size ++;
		return size;
	}

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