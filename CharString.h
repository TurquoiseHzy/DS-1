#ifndef CHARSTRING_H
#define CHARSTRING_H
#include<string>
#include<iostream>
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
	(char *)get_data() const{
		return data;
	}

	char charOf(Index index){
		if( index < length )
			return data[index];
		else
			return '\0';
	}

	Size get_length() const{
		return length;
	}

	CharString *substring(Index st_index,Index ed_index){
		if(st_index <= ed_index){
			return new CharString(data + st_index , ed_index - st_index + 1);
		}
		return new CharString(std::string(""));
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
		delete Dest->data;
		Dest->data = new char [src->length];
		Dest->length = src ->length;
		memcpy(Dest->data,src->data,src->length);
		return Dest;
	}

	CharString* operator = (CharString &src){
		return assign(this,&src);
	}

	CharString* operator = (CharString *src){
		return assign(this,src);
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
		bool longspace = false;
		bool bracketover = true;
		for(Index i = 0 ; i < length ; i ++){
			if(data[i] == '<'){
				bracketover = false;
			}
			if(data[i] == '>'){
				bracketover = true;
			}
			else if(bracketover){
				if(data[i] != '\n' && data[i] != ' '){
					outputStream << data[i];
				}
				else if(data[i] != '\n' && !longspace){
					outputStream << data[i];
				}
				if(data[i] == ' '){
					longspace = true;
				}
				else{
					longspace = false;
				}
			}
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

	bool noContent(const Index& stIndex, const Index& edIndex){
		for(Index i = stIndex ; i <= edIndex ; i ++){
			if(data[i] != '\n' && data[i] != '\0' && data[i] != ' '){
				return false;
			}
		}
		return true;
	}

	Index findNextNotChar(const Index&stIndex, const char *redundantChar,const Size &redundantSize){
		for(Index i = stIndex ; i < length ; i ++){
			bool flag = true;
			for(Size j = 0 ; j < redundantSize ; j ++){
				if(data[i] == redundantChar[j]){
					flag = false;
					break;
				}
			}
			if(flag){
				return i;
			}
		}
		return (Index)-1;
	}

	std::string get_string() const{
		return std::string(data,length);
	}


	Index indexOf(CharString& key){
		if(	length < key.length ){
			return -1;
		}
		for(Index i = 0 ; i < length - key.length + 1; i ++){
			bool flag = true;
			for(Index j = 0 ; j < key.length ; j ++){
				if(data[i + j] != key.charOf(j)){
					flag = false;
					break;
				}
			}
			if(flag){
				return i;
			}
		}
		return -1;
	}
};

#endif