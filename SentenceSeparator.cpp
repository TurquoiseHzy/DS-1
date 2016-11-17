#include"SentenceSeparator.h"
CharStringLink * SentenceSeparator::separate(){
	if(result == NULL){
		result = new CharStringLink;
		Index cursor = 0;
		int len = dictionary->max_len;
		while(cursor < sentence->get_length()){
			CharString *word = sentence->substring(cursor,cursor + len - 1);
			if(len <= 3 || dictionary->exist(word)){
				result->add(word);
				cursor = cursor + len;
				while(sentence->charOf(cursor) >= 0){
					cursor ++;
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