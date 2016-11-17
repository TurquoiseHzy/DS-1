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
class App{
public:
	Dictionary *dictionary;
	TagChecker* tagchecker;
public:
	App():dictionary(NULL){
	}

public:
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
	Dictionary* initDictionary(std::istream& inputStream){
		if(dictionary == NULL){
			dictionary = new Dictionary(inputStream);
		}
		return dictionary;
	}

	CharStringLink* divideWords(CharString sentence){
		SentenceSeparator *ssor = new SentenceSeparator(dictionary,&sentence);
		return ssor->separate();
	}

	void doDivideWords(std::ostream& outputStream){
		tagchecker->divide(dictionary,outputStream);
	}
};


#endif