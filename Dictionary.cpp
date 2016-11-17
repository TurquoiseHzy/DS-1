#include"Dictionary.h"
#include<string>
#include<fstream>
#include<iostream>
inline size_t __stl_hash_string(const char* __s)
{
  unsigned long __h = 0; 
  for ( ; *__s; ++__s)
    __h = 5*__h + *__s;
  
  return size_t(__h);
}


Dictionary::Dictionary(std::istream &inputStream):max_len(0){
	std::string line;
	while(true){
		if(!getline(inputStream,line)){
			break;
		}
		if(line.length() > max_len){
			max_len = line.length();
		}
		data[CharString(line).get_string()] = 10;
	}
}

bool Dictionary::exist(CharString *key){/*
	if(key->get_length() % 3 == 0 && key->get_length() >=6 ){
		data[key->get_string()] ++ ;
	}*/
	if(data[key->get_string()] >= 10){
		return true;
	}
	return false;
}