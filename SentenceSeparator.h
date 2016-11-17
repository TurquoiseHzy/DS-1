#ifndef SENTENCESEPARATOR_H
#define SENTENCESEPARATOR_H
#include<hash_map>
#include"CharString.h"
#include"CharStringLink.h"
#include"Dictionary.h"
class SentenceSeparator{
private:
	CharString *sentence;
	CharStringLink *result;
	Dictionary* dictionary;
public:
	SentenceSeparator(Dictionary *dic,CharString* sent):
		dictionary(dic),
		sentence(sent),
		result(NULL){
	}

public:
	CharStringLink * separate();
};



#endif