#ifndef CHARSTRINGLINK_H
#define CHARSTRINGLINK_H
#include"CharString.h"
class CharStringNode : public CharString{
public:
	CharStringNode *next,*pre;
public:
	CharStringNode(const char *src,const Size& l):CharString(src, l),next(NULL),pre(NULL){
	}
	CharStringNode():CharString(),next(NULL),pre(NULL){
	}
	CharStringNode(CharStringNode &src):next(NULL),pre(NULL){
		length= src.get_length();
		data = new char [length];
		memcpy(data, src.get_data(), length);
	}
	CharStringNode(CharString &src):CharString(src),next(NULL),pre(NULL){
	}
	CharStringNode(CharString *src):CharString(*src),next(NULL),pre(NULL){
	}
	CharStringNode(std::string& src):CharString(src),next(NULL),pre(NULL){
	}
	~CharStringNode(){ 
	}
};


class CharStringLink{
public:
	CharStringNode *head,*tail;
protected:
	Size size;

public:
	CharStringLink():head(NULL),tail(NULL),size(0){
	}
	~CharStringLink(){
		CharStringNode *now = head;
		while(now != NULL){
			now = now->next;
			delete head;
			head = now;
		}
	}
public:
	Size get_size(){
		return size;
	}

	bool empty(){
		return (size == 0);
	}

	CharStringNode *search(const char*key, const Size&length){
		CharStringNode *now = head;
		while(now != NULL){
			if(*now == CharString(key,length)){
				return now;
			}
			now = now -> next;
		}
		return NULL;
	}
	
	CharStringNode *search(CharString* key){
		CharStringNode *now = head;
		while(now != NULL){
			if(*now == *key){
				return now;
			}
			now = now -> next;
		}
		return NULL;
	}

	CharStringNode *search(CharString &key){
		CharStringNode *now = head;
		while(now != NULL){
			if(*now == key){
				return now;
			}
			now = now -> next;
		}
		return NULL;
	}

	CharStringNode *search(std::string& src){
		CharStringNode *now = head;
		while(now != NULL){
			if(*now == CharString(src)){
				return now;
			}
			now = now->next;
		}
		return NULL;
	}
	CharStringNode *add(const char *src,const Size &l){
		CharStringNode *newNode = new CharStringNode (src,l);
		return add(newNode);
	}

	CharStringNode *add(CharString &src){
		CharStringNode *newNode = new CharStringNode(src);
		return add(newNode);
	}

	CharStringNode *add(CharString *src){
		CharStringNode *newNode = new CharStringNode(src);
		return add(newNode);
	}

	CharStringNode *add(std::string& src){
		CharStringNode *newNode = new CharStringNode(src);
		return add(newNode);
	}
	CharStringNode *add(CharStringNode *src){
		if(size == 0){
			head = src ;
			tail = src ;
		}
		else{ 
			src -> pre = tail;
			tail -> next = src;
			tail = src;
		}
		size ++;
		return src;
	}

	void remove(std::string& key){
		remove(search(key));
	}
	void remove(const char*key, const Size&length){
		remove(search(key,length));
	}

	void remove(CharString* key){
		remove(search(key));
	}

	void remove(CharString &key){
		remove(search(key));
	}

	void remove(CharStringNode *dest){
		if(dest == NULL){
			return ;
		}
		if(dest ->next != NULL){
			dest -> next -> pre = dest -> pre;
		}
		if(dest -> pre != NULL){
			dest -> pre -> next = dest -> next;
		}
		delete dest;
		size --;
	}
};


#endif