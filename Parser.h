#ifndef PARSER_H
#define PARSER_H
#include "Token.h"
#include "defined.h"
#include "InstanceManager.h"
class Parser
{
	public:
		Parser(std::vector<Token*> token_stream);
		~Parser();
		void parse();
	protected:
		char* curfun;
		std::vector<Token*> varlist;
		std::vector<Token*> tokens;
		std::vector<Token*> functions;
		Token* ct;
		int cc;
		void next();
		void next(TT type);
		void previous();
		const char* getTypeVal(TT type);
		bool have(Token*);
		Token* sameNameAs(Token*);
		void eat(TT type);
		bool haveFunc(Token* fun);
		Token* sameAsThisFun(Token* fun);
		void E();//expression parser
		void F();//Factor parser
		void T();//Term parser
		void S();//Statement parser
		void FUN();//function parser
		void A();//assignment parser
};

#endif
