#ifndef TOKEN_H
#define TOKEN_H
enum class TT{
	IDENTIFIER,
	NUMBER,
	DIV,
	MUL,
	SUB,
	ADD,
	DUMMY,
	FLOAT,
	LPAREN,
	RPAREN,
	OCURLY,
	CCURLY,
	S_COL,
	COMMA,
	EOFS,
	KEYWORD,
	EQUAL,
};
class Token
{
	public:
		Token(const char* value,TT type,int line,int column);
		Token(const char value,TT type,int line,int column);
		Token(Token*);
		~Token();
		char* val(){return this->value;}
		int l(){return this->line;}
		int c(){return this->column;}
		TT t(){return this->type;}
	protected:
		char* value;
		int line;
		int column;
		TT type;
};

#endif
