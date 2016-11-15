#ifndef TAG_H
#define TAG_H
typedef unsigned int Size;
#include"CharString.h"
#include<vector>
class Tag{
public:
	CharString tagname;
	CharString attrs;
	Index stIndex,edIndex;
	CharString innerHtml;
	std::vector<Tag*> childs;
	unsigned int height;
	Tag * father;
	bool closed;

public:
	Tag(CharString *src):closed(false),
		father(NULL),
		stIndex(-1),
		edIndex(-1),
		height(0)
	{
		Index NameEnd = src->findNextChar(0,' ');
		NameEnd = NameEnd == Index(-1) ? src->get_length() : NameEnd;
		tagname = src->substring(0,NameEnd - 1);
		attrs = src->substring(NameEnd,src->get_length() - 1);
		innerHtml = CharString(std::string("EMPTY TAG"));
	}

public:
	void extractHtml(CharString *src){
		innerHtml = src->substring(stIndex,edIndex);
	}

	void print(std::ostream &outputStream){
		/*
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
	}
};


#endif