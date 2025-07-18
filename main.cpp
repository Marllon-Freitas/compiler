#include <iostream>
#include "parser.h"
#include "lexer.h"
using namespace std;

int main()
{
	Parser translator;
	Lexer scanner;
	scanner.Start();

	// temp:
	// try
	// {
	// 	translator.Start();
	// }
	// catch (SyntaxError)
	// {
	// 	cout << "^\n";
	// 	cout << "Syntax error";
	// }
	cout << endl;
}
