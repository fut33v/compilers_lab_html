#include <iostream>
#include "Code.h"
#include "ConstRecognizer.h"
#include "WordRecognizer.h"

#define DIGIT_ASCII_LOWER_LIMIT 48
#define DIGIT_ASCII_UPPER_LIMIT 57
#define LETTER_UPPERCASE_ASCII_LOWER_LIMIT 65
#define LETTER_UPPERCASE_ASCII_UPPER_LIMIT 90
#define LETTER_LOWERCASE_ASCII_LOWER_LIMIT 97
#define LETTER_LOWERCASE_ASCII_UPPER_LIMIT 122

#define CLASS_OPERATION_SIGN 4
#define CLASS_BRACKET 3
#define CLASS_ERROR 0

int main (){
	Code code("test.html");
	ConstRecognizer Const(&code);
	WordRecognizer Word("reserved.words", &code);
	std::string Token;
	while(!code.IsEnd()){
		char ch = code.ShowCh();
		if(((int)ch >= DIGIT_ASCII_LOWER_LIMIT && (int)ch <= DIGIT_ASCII_UPPER_LIMIT) || (ch == '\'') || (ch == '#')){
			int Class = Const.getClass();
			Token = Const.getToken();
			std::cout<<code.getStrNum()+1<<" "<<Class<<" "<<Token<<std::endl;			
		} else if(((int)ch >= LETTER_LOWERCASE_ASCII_LOWER_LIMIT && (int)ch <= LETTER_LOWERCASE_ASCII_UPPER_LIMIT) ||
		((int)ch >= LETTER_UPPERCASE_ASCII_LOWER_LIMIT && (int)ch <= LETTER_UPPERCASE_ASCII_UPPER_LIMIT) || (ch == '_') || (ch == '<')){
			std::list<std::pair<std::pair<int,int>, std::string> > classAndToken;
			Word.getClass(&classAndToken);
			for (auto it : classAndToken){
				std::cout<<code.getStrNum()+1<<" "<<it.first.first<<" "<<it.first.second<<" "<<it.second<<std::endl;
			}
			while (!classAndToken.empty()){
				classAndToken.pop_back();
			}			
		} else if(ch == ' ' || ch == '\n' || ch == '\t'){
			code.GiveCh();
		}
		else if(ch == '>' || ch == '=' || ch == '/'){
			code.GiveCh();
			switch (ch){
				case '=': {				
					Token = "=";
					std::cout<<code.getStrNum()+1<<" "<<CLASS_OPERATION_SIGN<<" "<<Token<<std::endl;
					break;
				} 
				case '>': {
					Token = ">";
					std::cout<<code.getStrNum()+1<<" "<<CLASS_BRACKET<<" "<<Token<<std::endl;
					break;
				}
				case '/': {
					Token = "/";
					std::cout<<code.getStrNum()+1<<" "<<CLASS_ERROR<<" "<<Token<<std::endl;
					break;
				}	
			}		
		}
	}
}
