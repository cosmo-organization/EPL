#include "Parser.h"
#include <stdio.h>
#include <string.h>
#include <string>
#include <stdlib.h>
Parser::Parser(std::vector<Token*> token_stream)
{
	this->tokens=token_stream;
	this->cc=0;
	this->ct=this->tokens[this->cc];
}
bool isequal(const char* s1, const char* s2) {
	std::string s1c(s1);
	std::string s2c(s2);
	return s1c.compare(s2c);
}
Parser::~Parser()
{
	this->tokens.clear();
	this->tokens.clear();
	this->functions.clear();
}
void Parser::parse(){
	int ctc=0;
	while (ct->t() != TT::EOFS) {
		FUN();
	}
	eat(TT::EOFS);
}
void Parser::E(){
	T();
	while (this->ct->t() == TT::ADD || this->ct->t() == TT::SUB){
		if (ct->t()== TT::ADD){
			next();
			T();
		}else if(ct->t()== TT::SUB){
			next();
			T();
		}
	}
	
}
void Parser::T(){
	F();
	while (ct->t() == TT::DIV||ct->t()== TT::MUL){
		if (ct->t()== TT::DIV){
			next();
			F();
		}else if (ct->t()== TT::MUL){
			next();
			F();
		}
	}
}
void Parser::F(){
	if (ct->t() == TT::NUMBER){
		next();
	}else if(ct->t() == TT::LPAREN){
		next();
		E();
		eat(TT::RPAREN);
	}else if(ct->t()== TT::SUB){
		next();
		F();
	}else if (ct->t()== TT::IDENTIFIER){
		if (strcmp(ct->val(),curfun)==0){
		char* err=new char[100];
		sprintf(err,"function name:'%s' not used as variable at line:%d,col:%d\n",
		  ct->val(),
		  ct->l(),
		  ct->c()
		);
		InstanceManager::handler->throwHazardas(err);
	    }
	    if (!have(ct))
	     InstanceManager::handler->undefinedIdentifier(ct);
		next();
	}
}
void Parser::FUN(){
	this->varlist.clear();
	eat(TT::KEYWORD);
	eat(TT::IDENTIFIER);
	previous();
	if (haveFunc(ct))
	 InstanceManager::handler->redeclared(this->sameAsThisFun(ct),ct);
	this->curfun=ct->val();
	this->functions.push_back(ct);
	eat(TT::IDENTIFIER);
	eat(TT::LPAREN);
	eat(TT::RPAREN);
	eat(TT::OCURLY);
	while (ct->t()!= TT::CCURLY){
		A();
	}
	eat(TT::CCURLY);
}
void Parser::S(){
	A();
}
bool Parser::haveFunc(Token* t){
	for (int i=0;i<this->functions.size();i++){
		if (isequal(ct->val(),functions[i]->val())==0){
			return true;
		}
	}
	return false;
}
Token* Parser::sameAsThisFun(Token* fun){
	for (int i=0;i<this->functions.size();i++){
		if (isequal(ct->val(),functions[i]->val())==0){
			return functions[i];
		}
	}
}
void Parser::A(){
	if (ct->t()== TT::KEYWORD){
		eat(TT::KEYWORD);
		eat(TT::IDENTIFIER);
		previous();
		if (this->have(ct))InstanceManager::handler->redeclared(this->sameNameAs(ct),ct);
		this->varlist.push_back(ct);
		eat(TT::IDENTIFIER);
		while (ct->t() != TT::S_COL){
			eat(TT::COMMA);
			eat(TT::IDENTIFIER);
			previous();
			if (this->have(ct))InstanceManager::handler->redeclared(this->sameNameAs(ct),ct);
			this->varlist.push_back(ct);
			eat(TT::IDENTIFIER);
		}
		eat(TT::S_COL);
	}else{
	eat(TT::IDENTIFIER);
	previous();
	if (strcmp(ct->val(),curfun)==0){
		char* err=new char[100];
		sprintf(err,"function name:'%s' not used as variable at line:%d,col:%d\n",
		  ct->val(),
		  ct->l(),
		  ct->c()
		);
		InstanceManager::handler->throwHazardas(err);
	}
	if (!have(ct))
	  InstanceManager::handler->undefinedIdentifier(ct);
	eat(TT::IDENTIFIER);
	eat(TT::EQUAL);
	E();
	eat(TT::S_COL);
   }
}
Token* Parser::sameNameAs(Token* t){
	for (int i=0;i<this->varlist.size();i++){
		if (isequal(ct->val(),varlist[i]->val())==0){
			return varlist[i];
		}
	}
	return NULL;
}
bool Parser::have(Token* declvar){
	for (int i=0;i<this->varlist.size();i++){
		if (isequal(ct->val(),varlist[i]->val())==0){
			return true;
		}
	}
	return false;
}
void Parser::next(){
	if (cc == tokens.size()){
		printf("EOF Exception\n");
		exit(-2);
	}
	this->cc++;
	this->ct=this->tokens[cc];
}
const char* Parser::getTypeVal(TT type){
	switch(type){
		case TT::DIV:
			return "/";
		case TT::MUL:
			return "*";
		case TT::ADD:
			return "+";
		case TT::SUB:
			return "-";
		case TT::OCURLY:
			return "{";
		case TT::CCURLY:
			return "}";
		case TT::LPAREN:
			return "(";
		case TT::RPAREN:
			return ")";
		case TT::S_COL:
			return ";";
		case TT::COMMA:
			return ",";
		case TT::IDENTIFIER:
			return "NAME";
		case TT::KEYWORD:
			return "KEYWORD";
		case TT::EOFS:
			return "EOF Exception";
		case TT::EQUAL:
			return "=";
		default:
			return "";
	}
}
void Parser::next(TT type){
	next();
	char* err=new char[100];
	if (this->tokens[this->cc]->t() == type){
		
	}else{
	    sprintf(err,"Expected:'%s' but found:'%s' at line:%d on col:%d\n",
		this->getTypeVal(type),
		this->ct->val(),
		this->ct->l(),
		this->ct->c()
		);
		InstanceManager::handler->throwHazardas(err);
	}
}
void Parser::eat(TT type){
	char* err=new char[100];
	if (ct->t()==type){
		next();
	}else{
	    sprintf(err,"Expected:'%s' but found:'%s' at line:%d on col:%d\n",
		this->getTypeVal(type),
		this->ct->val(),
		this->ct->l(),
		this->ct->c()
		);
		InstanceManager::handler->throwHazardas(err);
	}
}
void Parser::previous(){
	this->cc-=1;
	this->ct=this->tokens[this->cc];
}
