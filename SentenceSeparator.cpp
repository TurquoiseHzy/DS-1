//
//  SentenceSeparator.cpp
//
//  Created by Ziyi Huang on 2016/11/16.
//  Copyright © 2016年 Ziyi Huang. All rights reserved.
//	
//	
//	Definition of fun separate()
//	
//
#include"SentenceSeparator.h"

/*
	seperate():
		@param:
		@return: divide result
*/
CharStringLink * SentenceSeparator::separate(){
	if(result == NULL){
		result = new CharStringLink;
		Index cursor = 0;
		int len = dictionary->max_len;

		while(cursor < sentence->get_length()){
			CharString *word = sentence->substring(cursor,cursor + len - 1);

			if(word->get_length() <= 3 || dictionary->exist(word)){	//find-succeed or word less than one chs-characters
				result->add(word);
				cursor = cursor + len;

				if((sentence->charOf(cursor) >= 0&&cursor < sentence->get_length())){	//to check out English-letters/ numbers
					while(( sentence->charOf(cursor) == '\0'
							|| sentence->charOf(cursor) == '\n'
							|| sentence->charOf(cursor) == ' ')
							&&  cursor < sentence -> get_length()){
								cursor ++;
					}
					Index mark = cursor;
					while(sentence->charOf(cursor) >= 0
						&& cursor < sentence->get_length()){
							if(!( sentence->charOf(cursor) != '\0'
							&& sentence->charOf(cursor) != '\n'
							&& sentence->charOf(cursor) != ' ')){
								if(cursor > mark){
									result->add(sentence->substring(mark,cursor - 1));
									mark = cursor + 1;
								}
							}
							cursor ++;
					}
					if(cursor > mark){
						result->add(sentence->substring(mark,cursor - 1));
					}
				}
				len =  dictionary->max_len;
			}
			
			else{
				len = len - 1;
			}
		}
	}
	return result;
}