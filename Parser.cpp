#include "Parser.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
Parser::Parser(std::vector<Token*> token_stream)
{
	this->tokens=token_stream;
	this->cc=0;
	this->ct=this->tokens[this->cc];
}

Parser::~Parser()
{
	this->tokens.clear();
	this->tokens.clear();
	this->functions.clear();
}
void Parser::parse(){
	int ctc=0;
	while (ct->t()!=EOFS)
	  FUN();
	eat(EOFS);
}
void Parser::E(){
	T();
	while (this->ct->t() == ADD || this->ct->t() == SUB){
		if (ct->t()==ADD){
			next();
			T();
		}else if(ct->t()==SUB){
			next();
			T();
		}
	}
	
}
void Parser::T(){
	F();
	while (ct->t() == DIV||ct->t()==MUL){
		if (ct->t()==DIV){
			next();
			F();
		}else if (ct->t()==MUL){
			next();
			F();
		}
	}
}
void Parser::F(){
	if (ct->t() == NUMBER){
		next();
	}else if(ct->t() == LPAREN){
		next();
		E();
		next(RPAREN);
	}else if(ct->t()==SUB){
		next();
		F();
	}else if (ct->t()==IDENTIFIER){
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
	eat(KEYWORD);
	eat(IDENTIFIER);
	previous();
	if (haveFunc(ct))
	 InstanceManager::handler->redeclared(ct,this->sameAsThisFun(ct));
	this->curfun=ct->val();
	this->functions.push_back(ct);
	eat(IDENTIFIER);
	eat(LPAREN);
	eat(RPAREN);
	eat(OCURLY);
	while (ct->t()!=CCURLY){
		A();
	}
	eat(CCURLY);
}
void Parser::S(){
	A();
}
bool Parser::haveFunc(Token* t){
	for (int i=0;i<this->functions.size();i++){
		if (strcmp(ct->val(),functions[i]->val())==0){
			return true;
		}
	}
	return false;
}
Token* Parser::sameAsThisFun(Token* fun){
	for (int i=0;i<this->functions.size();i++){
		if (strcmp(ct->val(),functions[i]->val())==0){
			return functions[i];
		}
	}
}
void Parser::A(){
	if (ct->t()==KEYWORD){
		eat(KEYWORD);
		eat(IDENTIFIER);
		previous();
		if (this->have(ct))InstanceManager::handler->redeclared(this->sameNameAs(ct),ct);
		this->varlist.push_back(ct);
		eat(IDENTIFIER);
		while (ct->t() != S_COL){
			eat(COMMA);
			eat(IDENTIFIER);
			previous();
			if (this->have(ct))InstanceManager::handler->redeclared(this->sameNameAs(ct),ct);
			this->varlist.push_back(ct);
			eat(IDENTIFIER);
		}
		eat(S_COL);
	}else{
	eat(IDENTIFIER);
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
	eat(IDENTIFIER);
	eat(EQUAL);
	E();
	eat(S_COL);
   }
}
Token* Parser::sameNameAs(Token* t){
	for (int i=0;i<this->varlist.size();i++){
		if (strcmp(ct->val(),varlist[i]->val())==0){
			return varlist[i];
		}
	}
}
bool Parser::have(Token* declvar){
	for (int i=0;i<this->varlist.size();i++){
		if (strcmp(ct->val(),varlist[i]->val())==0){
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
		case DIV:
			return "/";
		case MUL:
			return "*";
		case ADD:
			return "+";
		case SUB:
			return "-";
		case OCURLY:
			return "{";
		case CCURLY:
			return "}";
		case LPAREN:
			return "(";
		case RPAREN:
			return ")";
		case S_COL:
			return ";";
		case COMMA:
			return ",";
		case IDENTIFIER:
			return "NAME";
		case KEYWORD:
			return "KEYWORD";
		case EOFS:
			return "EOF Exception";
		case EQUAL:
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
