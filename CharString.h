#ifndef CHARSTRING_H
#define CHARSTRING_H
#include<string>
typedef unsigned int Size;
typedef unsigned int Index;
class CharString{
protected:
	char *data;
	Size length;

public:
	CharString(const char *src,const Size& l):length(l){
		data = new char [ l ];
		memcpy(data,src,l);
	}
	CharString(std::string& str):length(str.length()){
		data = new char [length];
		memcpy(data,str.data(),length);
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
		if( index < length )
			return data[index];
		else
			return '\0';
	}

	Size get_length(){
		return length;
	}

	CharString substring(Index st_index,Index ed_index){
		return CharString(data + st_index , ed_index - st_index + 1);
	}

	CharString concat( CharString *src){
		Size l = src->get_length();
		char *ndata = new char[length + l];
		memcpy(ndata, data,length);
		memcpy(ndata + length , src->get_data(), l);
		delete[] data;
		data = ndata;
		length += l;
		return *this;
	}

	CharString concat(const char *src, const Size &l){
		char *ndata = new char[length + l];
		memcpy(ndata, data, length);
		memcpy(ndata + length , src, l );
		delete[] data;
		data = ndata;
		length += l;
		return *this;
	}

	CharString* assgin(CharString *Dest,const char *src , const Size &length){
		return assign(Dest,new CharString(src,length));
	}
	CharString* assign(CharString *Dest,CharString *src){
		delete Dest;
		Dest = new CharString(*src);
		return Dest;
	}

	CharString* operator = (CharString &src){
		assign(this,&src);
		return this;
	}

	CharString* operator = (CharString *src){
		assign(this,src);
		return this;
	}

	bool operator ==(CharString& src){
		if(length != src.length){
			return false;
		}
		for(Size i = 0;  i < length ; i ++){
			if(data[i] != src.data[i]){
				return false;
			}
		}
		return true;
	}

	bool operator !=(CharString& src){
		return !this->operator==(src);
	}

	void print(std::ostream &outputStream){
		for(Index i = 0 ; i < length ; i ++){
			outputStream << data[i];
		}
	}

	Index findNextChar(const Index& stIndex,const char &key){
		for(Index i = stIndex ; i < length ; i ++){
			if(key == data[i]){
				return i;
			}
		}
		return -1;
	}
};

#endif