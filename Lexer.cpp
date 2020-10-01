#include "Lexer.h"
#include <string.h>
#include <string>
#include <stdlib.h>
#include "InstanceManager.h"
#include "defined.h"
Lexer::Lexer(const char* program)
{
	this->line=1;
	this->col=0;
	char* dest=(char*)malloc(sizeof(char)*strlen(program));
	strcpy(dest,program);
	this->initStart(dest);
	free(dest);
}

Lexer::~Lexer()
{
}
void Lexer::initStart(char* src){
	while (true){
		if (*src==' ' || *src == '\t' || *src=='\f' || *src == '\b' || *src == '\r'){
			this->col++;
			src++;
		}else if (*src == ' '){
			this->col++;
			src++;
		}else if(*src == '\n'){
			this->col=0;
			this->line++;
			src++;
		}else if(*src == '\0'){
			this->col++;
			this->tokens.push_back(new Token('\0',EOFS,line,col));
			break;
		}else if(*src == '#'){
		    while (*src!='\n'){ 
			if (*src=='\0')break;
			src++;
			}
		}else if(*src == ')'){
			col++;
			this->tokens.push_back(new Token(*src,RPAREN,line,col));
			src++;
		}else if(*src == '('){
			col++;
			this->tokens.push_back(new Token(*src,LPAREN,line,col));
			src++;
		}else if(*src == '+'){
			col++;
			this->tokens.push_back(new Token(*src,ADD,line,col));
			src++;
		}else if(*src == '-'){
			col++;
			this->tokens.push_back(new Token(*src,SUB,line,col));
			src++;
		}else if(*src == '/'){
			col++;
			this->tokens.push_back(new Token(*src,DIV,line,col));
			src++;
		}else if(*src == '*'){
			col++;
			this->tokens.push_back(new Token(*src,MUL,line,col));
			src++;
		}else if(*src == ';'){
			col++;
			this->tokens.push_back(new Token(*src,S_COL,line,col));
			src++;
		}else if(*src == '{'){
			col++;
			this->tokens.push_back(new Token(*src,OCURLY,line,col));
			src++;
		}else if(*src == '}'){
			col++;
			this->tokens.push_back(new Token(*src,CCURLY,line,col));
			src++;
		}else if(*src == ','){
			col++;
			this->tokens.push_back(new Token(*src,COMMA,line,col));
			src++;
		}else if(*src == '='){
			col++;
			this->tokens.push_back(new Token(*src,EQUAL,line,col));
			src++;
		}
		else{
			col++;
			if (*src == '.' || isdigit(*src)){
				int cur=col;
				std::string digit="";
				int ndot=0;
				while (isdigit(*src)||*src=='.'){
					if (*src=='.')ndot++;
					if (ndot>1){
						InstanceManager::handler->addError(ILLEGAL_NUMBER,LEXICAL_ERROR,new Token(*src,DUMMY,line,col));
						InstanceManager::handler->throwError();
					}
					digit+=*src;
					src++;
					col++;
					if (!isdigit(*src) && (*src!='.'))break;
				}
				digit+='\0';
				this->tokens.push_back(new Token(digit.c_str(),NUMBER,line,cur));
			}else if(*src == '_' || isalpha(*src)){
				int c=col;
				std::string identifier("");
				while (isalpha(*src) || *src == '_' || isdigit(*src)){
					identifier+=*src;
					src++;
					if (!isdigit(*src) && *src!='_' && isalpha(*src)==false && *src != '\0')break;
					col++;
				}
				identifier+='\0';
				if (strcmp(identifier.c_str(),"float")==0){
					this->tokens.push_back(new Token("float",KEYWORD,line,c));
				}else{
				    this->tokens.push_back(new Token(identifier.c_str(),IDENTIFIER,line,c));
				}
			}else{
				InstanceManager::handler->addError(ILLEGAL_CHAR,LEXICAL_ERROR,new Token(*src,DUMMY,line,col));
				src++;
			}
		}
	}
}
