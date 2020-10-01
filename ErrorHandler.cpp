#include "ErrorHandler.h"
#include <stdio.h>
#include <stdlib.h>
void ErrorHandler::addError(ET et,PE pe,Token* t){
	char* err=new char[100];
	switch(pe){
		case LEXICAL_ERROR:{
			switch(et){
				case ILLEGAL_NUMBER:
					sprintf(err,"Illegal Number:{'%s',at line:%d, of col:%d}\n",t->val(),t->l(),t->c());
					errors.push_back(err);
					break;
				case ILLEGAL_CHAR:
					sprintf(err,"Illegal Char at:{'%s' at line:%d, of col:%d}\n",t->val(),t->l(),t->c());
					errors.push_back(err);
					break;
			}
			break;
		}
		case PARSER_ERROR:{
			switch(et){
				case SYNTAX_ERROR:
					sprintf(err,"Syntax Error '%s' line:%d col:%d\n",t->val(),t->l(),t->c());
					errors.push_back(err);
					break;
				case EXCEPTED_CURLY:
					sprintf(err,"Expected } after '%s' at line:%d on column:%d\n",t->val(),t->l(),t->c());
					errors.push_back(err);
					break;
				case EXCEPTED_PAREN:
					sprintf(err,"Expected ) after '%s' at line:%d on column:%d\n",t->val(),t->l(),t->c());
					errors.push_back(err);
					break;
				case EXCEPTED_SEMICOLON:
					sprintf(err,"Expected ; after '%s' at line:%d on column:%d\n",t->val(),t->l(),t->c());
					errors.push_back(err);
					break;
			}
			break;
		}
	}
//	delete err;
}
void ErrorHandler::undefinedIdentifier(Token* t){
	char* err=new char[100];
	sprintf(err,"Undefined identifier '%s' at line:%d on column:%d\n",t->val(),t->l(),t->c());
	errors.push_back(err);
	this->throwError();
}
void ErrorHandler::redeclared(Token* previous,Token* now){
	char* err=new char[100];
	sprintf(err,"Redeclare ['%s',line:%d,col:%d] Previousely Declared at:['%s',line:%d,col:%d]\n",
	  now->val(),
	  now->l(),
	  now->c(),
	  previous->val(),
	  previous->l(),
	  previous->c()
	);
	errors.push_back(err);
	this->throwError();
}
void ErrorHandler::throwError(){
	if (!this->errors.empty()){
		for (int i=0;i<this->errors.size();i++){
			printf("%d: Error:%s",i+1,this->errors[i]);
		}
	    printf("Error in Parsing and exited with return code:-1");
//	    errors.clear();
		exit(-1);
	}
}
void ErrorHandler::throwHazardas(const char* msg){
	errors.push_back(msg);
	this->throwError();
}
