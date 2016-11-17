#include"SentenceSeparator.h"
CharStringLink * SentenceSeparator::separate(){
	if(result == NULL){
		result = new CharStringLink;
		Index cursor = 0;
		int len = dictionary->max_len;
		while(cursor < sentence->get_length()){
			CharString *word = sentence->substring(cursor,cursor + len - 1);
			if(word->get_length() <= 3 || dictionary->exist(word)){
				result->add(word);
				cursor = cursor + len;
				if((sentence->charOf(cursor) >= 0&&cursor < sentence->get_length())){
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
				/*while((int(sentence->charOf(cursor + 1)) ==  -68 || int(sentence->charOf(cursor + 1))  == - 128) && cursor < sentence->get_length()){
					cursor = cursor + 3;
				}*/
				len =  dictionary->max_len;
			}
			else{
				len = len - 1;
			}
		}
	}
	return result;
}