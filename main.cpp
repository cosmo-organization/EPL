#include <iostream>
#include "Lexer.h"
#include "InstanceManager.h"
#include "Parser.h"
#include <string.h>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;
int main(int argc, char** argv) {
	char* filename = "sampleprogram.txt";
	std::ifstream infile(filename);
	string tmp;
	string sourcecode("");
	while (getline(infile, tmp)) {
		sourcecode.append(tmp.c_str());
		sourcecode.append("\n");
	}
	cout << sourcecode.c_str();
	infile.close();
	Lexer* lexer=new Lexer(sourcecode.c_str());
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
	sourcecode.clear();
	return 0;
}
