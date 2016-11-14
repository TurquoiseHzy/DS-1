#ifndef CHARSTRING_H
#define CHARSTRING_H
#include<string>
typedef unsigned int Size;
typedef unsigned int& Index;
class CharString{
protected:
	char *data;
	Size length;

public:
	CharString(const char *src,const Size& l):length(l){
		data = new char [ l ];
		memcpy(data,src,l);
	}
	CharString():length(0){
		data = new char [ 1 ];
	}
	CharString( CharString &src){
		length= src.get_length();
		data = new char [length];
		memcpy(data, src.get_data(), length);
	}
	~CharString(){
		delete[] data;
	}

public:
	(char *)get_data(){
		return data;
	}

	char indexOf(Index index){
		return data[index];
	}

	Size get_length(){
		return length;
	}

	CharString substring(Index st_index,Index ed_index){
		return CharString(data + st_index , ed_index - st_index + 1);
	}

	CharString concat( CharString *src){
		Size l = src.get_length();
		char *ndata = new char[length + l];
		memcpy(ndata, data,length);
		memcpy(ndata + length + 1, src.get_data(), l);
		delete[] data;
		data = ndata;
		return *this;
	}

	CharString concat(const char *src, const Size &l){
		char *ndata = new char[length + l];
		memcpy(ndata, data, length);
		memcpy(ndata + length + 1, src, l );
		delete[] data;
		data = ndata;
		return *this;
	}

	CharString assign(CharString *Dest,CharString *src){
		Dest
	}
};

#endif