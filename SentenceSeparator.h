//
//  SentenceSeparator.h
//
//  Created by Ziyi Huang on 2016/11/16.
//  Copyright © 2016年 Ziyi Huang. All rights reserved.
//	
//	
//	Declaration of class SentenceSeparator
//	
//
#ifndef SENTENCESEPARATOR_H
#define SENTENCESEPARATOR_H
#include<hash_map>
#include"CharString.h"
#include"CharStringLink.h"
#include"Dictionary.h"

/*
	class Declaration:
		@attr:	
			sentence: sentence to divide
			result: divide result
			dictionary: dictionary
		@func:
			seperate():seperate @sentence
*/
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