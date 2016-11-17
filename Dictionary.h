//
//  Dictionary.h
//
//  Created by Ziyi Huang on 2016/11/15.
//  Copyright © 2016年 Ziyi Huang. All rights reserved.
//	
//	
//	Declaration of class CharStringNode & CharStringLink
//	
//
#ifndef DICTIONARY_H
#define DICTIONARY_H
#include<hash_map>
#include"CharString.h"

typedef std::hash_map<std::string,int> HashTable;

//hash_function
inline size_t __stl_hash_string(const char* __s);
struct charstring_hash{
	size_t operator ()(const std::string &x) const{
		return __stl_hash_string(x.c_str());
	}
};

class Dictionary{
public:
	HashTable data;	//data
	Size max_len;	//max_len of words in data

public:
	Dictionary(std::istream &inputStream);

public:
	bool exist(CharString *key);

};



#endif