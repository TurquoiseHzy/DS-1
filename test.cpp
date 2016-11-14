#include<iostream>
#include"Stack.h"
#include"CharStringLink.h"
#include"Tag.h" 
#include"TagChecker.h"
int main(){
	
	TagChecker *appInstance = new TagChecker();
	appInstance->init(std::cin);
	appInstance->solve();
	return 0;
}