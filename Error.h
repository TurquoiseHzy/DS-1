#ifndef ERROR_H
#define ERROR_H
class BaseError{
	/*
protected:
	BaseError* instance;*/
protected:
	BaseError(){}/*
public:
	virtual BaseError* getInstance(){};*/
};

class EmptyStackError:BaseError{/*
public:
	EmptyStackError* getInstance(){
		if(instance == 0){
			instance = new EmptyStackError();
		}
		return dynamic_cast<EmptyStackError*>(instance);
	}*/
};
#endif