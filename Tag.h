#ifndef TAG_H
#define TAG_H
typedef unsigned int Size;
#include"CharString.h"
#include<vector>
class Tag{
public:
	CharString tagname;
	CharString *attr;
	Size attrNum;
	CharString innerHtml;
	Size *innerHtmlLength;
	std::vector<Tag*> childs;
	bool closed;
public:
};


#endif