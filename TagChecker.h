#ifndef TAGCHECKER_H
#define TAGCHECKER_H
#include"Tag.h"
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