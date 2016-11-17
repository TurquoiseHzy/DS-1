//
//  TagChecker.h
//
//  Created by Ziyi Huang on 2016/11/16.
//  Copyright © 2016年 Ziyi Huang. All rights reserved.
//	
//	
//	Declaration of class TagChecker
//	
//
#ifndef TAGCHECKER_H
#define TAGCHECKER_H
#include"Tag.h"

//a class to save all infomations in HTML
//and provide interface to divide & print;
class TagChecker{
protected:
	CharStringLink *article;
	CharString *content;
	std::vector<Tag *> topTag;
public:
	TagChecker():article(NULL){
	};
	~TagChecker(){
	}

public:
	void init(std::istream &inputStream);

public:
	int solve();


	void print(std::ostream &outputStream); 

	void divide(Dictionary *dictionary,std::ostream &outputStream); 

	void errorreport(std::ostream &outputStream, Index errIndex);
};


#endif