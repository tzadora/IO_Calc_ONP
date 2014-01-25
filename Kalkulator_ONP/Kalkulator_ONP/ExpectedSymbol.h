#pragma once

//oczekiwany symbol, ANY - cokolwiek
enum tokenType { ANY, 
				 NUMBER, 
				 OPERATOR, 
				 FUNCTION, 
				 DOT, 
				 PLUSMINUS, 
				 WHITE_SPACE, 
				 BRACKET_BEGIN,
				 BRACKET_END,
				 LETTER
};

class ExpectedSymbol
{
protected:
	bool isNumber(const std::string & num);
	bool isOperator(const std::string & op);
	bool isFunction(const std::string & fun);
	bool isDot(const std::string & dot);
	bool isPlusMinus(const std::string & pm);
	bool isWhiteSpace(const std::string & ws);
	bool isBracketBegin(const std::string & bb);
	bool isBracketEnd(const std::string & be);
	bool isLetter(const std::string & let);

public:
	bool check(std::string c, tokenType expected = ANY);
	
};
