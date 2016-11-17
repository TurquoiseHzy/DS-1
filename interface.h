//
//  interface.h
//
//  Created by Ziyi Huang on 2016/11/16.
//  Copyright © 2016年 Ziyi Huang. All rights reserved.
//	
//	
//	Declaration & definition of class App
//	
//
#ifndef INTERFACE_H
#define INTERFACE_H
#include"Stack.h"
#include"CharStringLink.h"
#include"Tag.h" 
#include"TagChecker.h"
#include"Dictionary.h"
#include"SentenceSeparator.h"
#include<iostream>
#include<fstream>

//afford interface
class App{
public:
	Dictionary *dictionary;	//dictionary
	TagChecker* tagchecker;	//@tagchecker: to extractinfo
public:
	App():dictionary(NULL){
	}

public:

	/*
		@param:
			inputStream:	html input stream
			outputStream:	outputs
		@return:
			a TagChecker, saves all info of HTML include tag-tree and original content
	*/
	TagChecker* extractInfo(std::istream& inputStream,std::ostream& outputStream){
		TagChecker *tagCheckerInstance = new TagChecker();
		tagCheckerInstance->init(inputStream);
		int result = tagCheckerInstance->solve();
		if(!result){
			tagCheckerInstance->print(outputStream);
		}
		else{
			std::cerr << "ERROR"<<std::endl;
		}
		tagchecker = tagCheckerInstance;
		return tagCheckerInstance;
	}

	/*
		@param:
			inputStream:	dic input stream
		@return:
			A Dictionary: 	saves dictionary and more info
	*/
	Dictionary* initDictionary(std::istream& inputStream){
		if(dictionary == NULL){
			dictionary = new Dictionary(inputStream);
		}
		return dictionary;
	}

	/*
		@param:
			sentence: sentence to devide
		@return:
			A linklist,saves devide-result
	*/
	CharStringLink* divideWords(CharString sentence){
		SentenceSeparator *ssor = new SentenceSeparator(dictionary,&sentence);
		return ssor->separate();
	}

	//only use in this project,divide all tag-sentence in @tagchecker and output in @outputStream
	void doDivideWords(std::ostream& outputStream){
		tagchecker->divide(dictionary,outputStream);
	}
};


#endif