//
//  CharStringLink.h
//
//  Created by Ziyi Huang on 2016/11/15.
//  Copyright © 2016年 Ziyi Huang. All rights reserved.
//	
//	
//	Declaration & definition of class CharStringNode & CharStringLink
//	
//
#ifndef CHARSTRINGLINK_H
#define CHARSTRINGLINK_H
#include"CharString.h"


/*
	class CharStringNode
	extends from CharString
		@attribute: 
			next:	next_node_ptr
			pre:	pre_node_ptr
		@func:
			Constructor:
				allow (const char *,unsigned int )  &  (CHarStringNode &)  &  (CharString &)  &  (CharString *)  &  (string)
*/
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


/*
	class CharStringList
		@attribute: 
			head:	head_node_ptr
			tail:	tail_node_ptr
			size: 	node_num
*/
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

	//search @key(with length @length)
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

	CharStringNode *search(std::string& key){
		CharStringNode *now = head;
		while(now != NULL){
			if(*now == CharString(key)){
				return now;
			}
			now = now->next;
		}
		return NULL;
	}

	//add node @src (with length @l)
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

	//search & remove @key(with length @length)
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

	//remove @dest (dest node)
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

	/*	output link in @outputStream
		only use in this project
		ignore  ， 。 and many chs punctuation
	*/
	void print(std::ostream &outputStream){
		CharStringNode* now = head;
		while(now != NULL){
			if(now->get_length() > 0){
				if(now->get_length() == 3){
					if(int(now->get_data()[1]) == -68 
						|| int(now->get_data()[1]) == - 128){
						now = now -> next;
						continue;
					}
				}
				now->print(outputStream);
				outputStream << std::endl;
			}
			now  = now ->next;
		}
	}
};


#endif