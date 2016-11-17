//
//  Tag.h
//
//  Created by Ziyi Huang on 2016/11/16.
//  Copyright © 2016年 Ziyi Huang. All rights reserved.
//	
//	
//	Declaration & definition of class Tag
//	
//
#ifndef TAG_H
#define TAG_H
typedef unsigned int Size;
#include"CharString.h"
#include"SentenceSeparator.h"
#include<vector>

/*
	class Tag:
		@attr:
			tagname
			attrs:
			classname:
			innerHtml:
			stIndex & edIndex: start & end index in whole html
			height: height in tag tree
			father: father in tag tree
			closed: is well-closed? to report error
			important & isContent : only use in this project to judge output or not
*/
class Tag{
public:
	CharString tagname;
	CharString attrs;
	Index stIndex,edIndex;
	CharString innerHtml;
	CharString classname;
	std::vector<Tag*> childs;
	unsigned int height;
	Tag * father;
	bool closed;
	bool important;
	bool isContent;

public:
	Tag(CharString *src):closed(false),
		father(NULL),
		stIndex(-1),
		edIndex(-1),
		height(0),
		important(false),
		isContent(false)
	{
		Index NameEnd = src->findNextChar(0,' ');
		NameEnd = NameEnd == Index(-1) ? src->get_length() : NameEnd;
		tagname = src->substring(0,NameEnd - 1);
		attrs = src->substring(NameEnd,src->get_length() - 1);
		Index now = attrs.indexOf(CharString("class",5));
		Index classnameStart,classnameEnd;
		if( now < attrs.get_length() ){
			classnameStart = attrs.findNextChar(now,'\"');
			classnameEnd = attrs.findNextChar(classnameStart + 1,'\"');
			classname = attrs.substring(classnameStart + 1,classnameEnd - 1);
			if(classname.indexOf( CharString("question",8) ) != Index(-1)
				|| classname.indexOf( CharString("answer",6) ) != Index(-1)
				|| classname.indexOf( CharString("content",7) ) != Index(-1)
				|| classname.indexOf( CharString("author",6) ) != Index(-1)){
					important = true;
			}
			if(classname == CharString("content",7)){
				isContent = true;
			}
		}
		else{
			classname = CharString();
		}
		innerHtml = CharString(std::string("EMPTY TAG"));
	}

public:
	void extractHtml(CharString *src){
		innerHtml = src->substring(stIndex,edIndex);
	}

	void print(std::ostream &outputStream){
		/*
		@show all info in HTML

		tagname.print(outputStream);
		outputStream<< ":attr = ";
		attrs.print(outputStream);
		if(childs.size() == 0){
			outputStream<<" innerHTML = ";
			innerHtml.print(outputStream);
			if(innerHtml.get_length() == 0){
				outputStream<<"EMPTY TAG";
			}
		}
		outputStream<<"\n";
		for(Index i = 0 ; i < childs.size() ; i ++){
			for(unsigned int j = 0 ; j < height ; j ++){
				outputStream <<"  ";
			}
			childs[i] -> print(outputStream);
		}*/

		//find out tag is important ?
		if(important){
			if(innerHtml.indexOf(CharString("<p",2)) != Index(-1)
				|| innerHtml.indexOf(CharString("<div",4)) != Index(-1)
				|| innerHtml.indexOf(CharString("<li",3)) != Index(-1)
				|| innerHtml.indexOf(CharString("<span",5)) != Index(-1)
				|| innerHtml.indexOf(CharString("href",4)) != Index(-1)
				|| innerHtml.indexOf(CharString("EMPTY TAG",9)) != Index(-1)
				|| classname.indexOf(CharString("header",6)) != Index(-1)
				|| classname.indexOf(CharString("heading",7)) != Index(-1)
				|| tagname == CharString("a",1)
				|| innerHtml.indexOf(CharString("img",3)) != Index(-1)){
			}
			else{
				innerHtml.print(outputStream);
				if(innerHtml.get_length() > 0){
					outputStream << std::endl;
				}
			}
		}
		for(Index i = 0 ; i < childs.size() ; i ++){
			childs[i] -> print(outputStream);
		}
	}

	void divide(Dictionary *dictionary ,std::ostream &outputStream){

		//find out tag is content ?
		if(isContent){
			if(innerHtml.indexOf(CharString("<p",2)) != Index(-1)
				|| innerHtml.indexOf(CharString("<div",4)) != Index(-1)
				|| innerHtml.indexOf(CharString("<li",3)) != Index(-1)
				|| innerHtml.indexOf(CharString("<span",5)) != Index(-1)
				|| innerHtml.indexOf(CharString("href",4)) != Index(-1)
				|| innerHtml.indexOf(CharString("EMPTY TAG",9)) != Index(-1)
				|| classname.indexOf(CharString("header",6)) != Index(-1)
				|| classname.indexOf(CharString("heading",7)) != Index(-1)
				|| tagname == CharString("a",1)
				|| innerHtml.indexOf(CharString("img",3)) != Index(-1)){
			}
			else{
				SentenceSeparator *ssor = new SentenceSeparator(dictionary,&innerHtml);
				ssor->separate()->print(outputStream);
				if(innerHtml.get_length() > 0){
					outputStream << std::endl;
				}
			}
		}
		for(Index i = 0 ; i < childs.size() ; i ++){
			childs[i] -> divide(dictionary,outputStream);
		}
	}
};


#endif