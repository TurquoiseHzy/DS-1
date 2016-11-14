#ifndef TAGCHECKER_H
#define TAGCHECKER_H
class TagChecker{
protected:
	CharStringLink *article;
	CharString *content;
public:
	TagChecker():article(NULL){
	};
	~TagChecker(){
	}

public:
	void init(std::istream &inputStream);

public:
	int solve();
};


#endif