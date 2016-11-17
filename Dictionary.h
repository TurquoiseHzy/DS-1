#ifndef DICTIONARY_H
#define DICTIONARY_H
#include<hash_map>
#include"CharString.h"
typedef std::hash_map<std::string,int> HashTable;
inline size_t __stl_hash_string(const char* __s);
struct charstring_hash{
	size_t operator ()(const std::string &x) const{
		return __stl_hash_string(x.c_str());
	}
};
class Dictionary{
public:
	HashTable data;
	Size max_len;

public:
	Dictionary(std::istream &inputStream);

public:
	bool exist(CharString *key);

};



#endif