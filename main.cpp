#include <iostream>
#include "Lexer.h"
#include "InstanceManager.h"
#include "Parser.h"
#include <string.h>
int main(int argc, char** argv) {
	char* sourcecode=new char[2048];
	FILE* file=fopen("sample.txt","r");
	int c=0;
	while(!feof(file)){
		sourcecode[c++]=fgetc(file);
	}
	sourcecode[strlen(sourcecode)-1]='\0';
	fclose(file);
	Lexer* lexer=new Lexer(sourcecode);
	InstanceManager::handler->throwError();
	std::vector<Token*> tokens=lexer->_tokens();
//	for (int i=0;i<tokens.size();i++){
//		printf("val:%s,line:%d,column:%d\n",tokens[i]->val(),tokens[i]->l(),tokens[i]->c());
//	}
	Parser* parser=new Parser(tokens);
	parser->parse();
	printf("Successfully parsed no error-----\n");
	delete parser;
	delete lexer;
	delete sourcecode;
	return 0;
}
