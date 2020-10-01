#include "Token.h"
#include <string.h>
#include <stdlib.h>
Token::Token(const char* value,TT type,int line,int column)
{
	this->value=(char*)malloc(sizeof(char)*strlen(value));
	this->line=line;
	this->column=column;
	strcpy(this->value,value);
	this->type=type;
}
Token::Token(const char value,TT type,int line,int column)
{
	this->line=line;
	this->column=column;
	this->value=(char*)malloc(sizeof(char)*2);
	this->value[0]=value;
	this->value[1]='\0';
	this->type=type;
}
Token::Token(Token* t){
	this->value=(char*)malloc(sizeof(char)*strlen(t->val()));
	this->line=t->l();
	this->column=t->c();
	strcpy(this->value,t->val());
	this->type=t->t();
}

Token::~Token()
{
	delete this->value;
}
