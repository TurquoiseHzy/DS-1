//
//  TagChecker.cpp
//
//  Created by Ziyi Huang on 2016/11/16.
//  Copyright © 2016年 Ziyi Huang. All rights reserved.
//	
//	
//	Definition of function in class TagChecker
//	
//
#include<iostream>

#include"Tag.h"
#include"Stack.h"
#include"CharStringLink.h"
#include"TagChecker.h"


//init: from @inputStream to input all HTML
void TagChecker::init(std::istream &inputStream){
	while(true){
	std::string line;
		if(!getline(inputStream,line)){
			break;
		};
		line = line + std::string("\n");
		if(article == NULL){
			article = new CharStringLink();
		}
		article->add(line);
	}
	CharStringNode *now = article->head;
	CharString *res = new CharString(std::string(""));
	while(now != NULL){
		res->concat(now);
		now = now -> next;
	}
	content = res;
}

int TagChecker::solve(){
	Stack <Tag> stack;
	Tag *nowFather = NULL;
	Index lastLeftBracket = -1; //last "<" used to make tag;
	Index cursor = 0; // haven't solve
	Index nextLeftBracket = 0; // next "<"
	Index nextRightBracket = 0;// next ">"
	Index nextTagEnd = 0;//next "</"
	bool lastIsLeft = false;
	bool nextIsStart = true;// next is "<" or "</"
	Index eoc = content->get_length();
	while(cursor < eoc){
		if(content->noContent(cursor,eoc - 1)){
			return 0;
		}
		nextLeftBracket = content->findNextChar(cursor,'<');
		nextRightBracket = content->findNextChar(cursor,'>');
		if(content->charOf(nextLeftBracket + 1) == '/'){
			nextTagEnd = nextLeftBracket;
			nextIsStart = false;
		}
		else{
			nextIsStart = true;
		}
		if(nextLeftBracket < nextRightBracket){ // when find "<"
			if(lastIsLeft){
				return nextLeftBracket;
			}
			if(nextIsStart){
				lastLeftBracket = nextLeftBracket;
				cursor = lastLeftBracket + 1;
				lastIsLeft = true;
			}
			else{  //when find "</"
				Index TagEnd = content->findNextChar(nextTagEnd + 1,'>');
				if(TagEnd > content->findNextChar(nextTagEnd + 1,'<')){
					return content->findNextChar(nextTagEnd + 1,'<');
				}
				if(TagEnd == Index(-1)){
					return nextTagEnd; //error;
				}
				CharString *endedTagName = content->substring(nextTagEnd + 2,TagEnd - 1);
				Tag *nowTag = stack.pop();

#ifdef CORRECT_MODE			//no tag not-closed-admiition
				if(nowTag == NULL || nowTag->tagname != *endedTagName){
					nowTag->tagname.print(std::cerr);
					std::cerr << std :: endl;
					endedTagName->print(std::cerr);
					std::cerr << std :: endl;
					return nextTagEnd; //error
				}
#else
				if(nowTag == NULL || nowTag->tagname != *endedTagName){
					while(nowTag->tagname != *endedTagName){
						nowTag = stack.pop();
						if(nowTag == NULL){
							std::cerr << "ERROR: unappeared tag" << std :: endl;
							endedTagName->print(std::cerr);
							std::cerr << std :: endl;
							return nextTagEnd;
						}
					}
				}
#endif
				nowTag->edIndex = nextTagEnd - 1;
				nowTag->extractHtml(content);
				nowTag->closed = true;
				nowFather = nowTag->father;
				cursor = TagEnd + 1;
				lastIsLeft = false;
			}
		}
		else{
			if(!lastIsLeft){
				return nextRightBracket;
			}
			if(lastLeftBracket == Index(-1)){
				return nextRightBracket;
			}

			if(content->charOf(nextRightBracket - 1) == '/'){
				CharString *x = content->substring(lastLeftBracket + 1,nextRightBracket - 2);
				Tag *newTag = new Tag(x);
				newTag->stIndex = nextRightBracket;
				newTag->edIndex = lastLeftBracket;
				newTag->closed = true;
				cursor = nextRightBracket + 1;
				lastIsLeft = false;
				if(nowFather){
					nowFather->childs.push_back(newTag);
					newTag->father = nowFather;
					if(nowFather->important){
						newTag->important = true;
					}
					if(nowFather->isContent){
						newTag->isContent = true;
					}
				}
				else{
					topTag.push_back(newTag);
				}
				continue;
			}

			CharString *x = content->substring(lastLeftBracket + 1,nextRightBracket - 1);
			Tag *newTag = new Tag(x);
			newTag->stIndex = nextRightBracket + 1;
			stack.push(newTag);
			cursor = nextRightBracket + 1;
			lastIsLeft = false;
			if(nowFather){
				nowFather->childs.push_back(newTag);
				newTag->father = nowFather;
				newTag->height = nowFather->height + 1;
				if(nowFather->important){
					newTag->important = true;
				}
				if(nowFather->isContent){
					newTag->isContent = true;
				}
			}
			else{
				topTag.push_back(newTag);
			}
			if(x->charOf(0) != '!'){
				nowFather = newTag;
			}
		}
	}
	return -1;
}

//print all tags var @outputStream(output defined in class @Tag)
void TagChecker::print(std::ostream &outputStream){
	for(Index i = 0 ; i < topTag.size() ; i ++){
		topTag[i]->print(outputStream);
	}
}

//errorreport
void TagChecker::errorreport(std::ostream &outputStream ,Index errIndex){
	if(errIndex >= 20){
		for(Index i = 20 ; i != 0 ; i --){
			outputStream << content->charOf(errIndex - i);
		}
	}
	else{
		for(Index i = 0 ; i < errIndex; i ++){
			outputStream << content->charOf(i);
		}
	}
	outputStream << " " << content->charOf(errIndex) <<" ";
	if(errIndex + 20 < content->get_length()){
		for(Index i = 1 ; i <= 20 ; i ++){
			outputStream << content->charOf(errIndex + i);
		}
	}
	else{
		for(Index i = errIndex + 1 ; i < content->get_length(); i ++){
			outputStream << content->charOf(i);
		}
	}

}

//devide(defined in class @Tag)
void TagChecker::divide(Dictionary *dictionary,std::ostream &outputStream){
	for(Index i = 0 ; i < topTag.size() ; i ++){
		topTag[i]->divide(dictionary,outputStream);
	}
}