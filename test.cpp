#include<iostream>
#include<fstream>
#include <locale.h>
#include"interface.h"
int main(){
	App *appInstance = new App; 
	std::ifstream dicin("´Ê¿â.dic");
	std::cout.imbue(std::locale("chs"));
	dicin.imbue(std::locale("chs"));
	appInstance->initDictionary(dicin);
	dicin.close();
	for(int i = 1 ; i <= 10; i ++){
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
		filein.imbue(std::locale("chs"));
		std::ofstream fileout(name+std::string(".info"));
		std::ofstream filetxt(name+std::string(".txt"));
		fileout.imbue(std::locale("chs"));
		filetxt.imbue(std::locale("chs"));
		appInstance->extractInfo(filein,fileout);
		filein.close();
		fileout.close();
		appInstance->doDivideWords(filetxt);
	}
	return 0;
}
