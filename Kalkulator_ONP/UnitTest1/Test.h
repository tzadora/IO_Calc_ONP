#pragma once

// Klasa zawierajaca powtarzajace sie metody testow
class Test
{
private:
	
	static void parse(std::string expression);
public:
	static std::list<Symbol> listOfSymbols;

	static void testExpectedSymbolIsFalse(std::string expression, tokenType);
	static void testExpectedSymbolIsTrue(std::string expression, tokenType);
	static void testSingleExpression(std::string expression);
	static void testOperation(Symbol* s1, Symbol* s2, Symbol* op, double result);
	static void testFunction(Symbol* s1, Symbol* fun, double result);
	static void testSingleExpressionType(std::string expression, tokenType type);
	static void testExpression(std::string expression, std::list<tokenType> listOfTokens);
	static void testCalculateMethod(std::string expression, double result);
};

