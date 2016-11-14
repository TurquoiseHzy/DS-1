#include<iostream>

#include"Tag.h"
#include"Stack.h"
#include"CharStringLink.h"
#include"TagChecker.h"

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
	bool nextIsStart = true;// next is "<" or "</"
	Index eoc = content->get_length();
	while(cursor < eoc){
		nextLeftBracket = content->findNextChar(cursor,'<');
		nextRightBracket = content->findNextChar(cursor,'>');
		if(content->indexOf(nextLeftBracket + 1) == '/'){
			nextTagEnd = nextLeftBracket;
			nextIsStart = false;
		}
		else{
			nextIsStart = true;
		}
		if(nextLeftBracket < nextRightBracket){ // when find "<"
			if(nextIsStart){
				lastLeftBracket = nextLeftBracket;
				cursor = lastLeftBracket + 1;
			}
			else{  //when find "</"
				Index TagEnd = content->findNextChar(nextTagEnd,'>');
				if(TagEnd == -1){
					return nextTagEnd; //error;
				}
				CharString *endedTagName = new CharString(content->substring(nextTagEnd + 2,TagEnd));
				Tag *nowTag = stack.pop();
				if(nowTag == NULL || nowTag->tagname != *endedTagName){
					return nextTagEnd; //error
				}
				nowTag->closed = true;
				if(nowFather){
					nowFather->childs.push_back(nowTag);
				}
				cursor = TagEnd + 1;
			}
		}
		else{
		// todo : when find ">"
		}
	}
	return 0;
}
