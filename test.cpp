#include<iostream>
#include<fstream>
#include"Stack.h"
#include"CharStringLink.h"
#include"Tag.h" 
#include"TagChecker.h"
int main(){
	for(int i = 1 ; i <= 10; i ++){
		TagChecker *appInstance = new TagChecker();
		std::string name ;
		if( i < 10){
			char *ch = new char [1];
			ch[0] = '0' + i;
			name = std::string("input/") + std::string("000")+std::string(ch,1);
		}
		else{
			name = "input/0010";
		}
		std::ifstream filein(name+std::string(".html"));
		std::ofstream fileout(name+std::string(".info"));
		appInstance->init(filein);
		int result = appInstance->solve();
		if(!result){
			appInstance->print(fileout);
		}
		else{
			if(result == -1){
				std::cerr << "ERROR in " + name + "\n code = -1"<<std::endl;
			}
			else{
				std::cerr << "ERROR in " + name + "\n code = " <<result<<std::endl;
				appInstance->errorreport(std::cerr,result);
			}
		}
		filein.close();
		fileout.close();
	}

	
	return 0;
}