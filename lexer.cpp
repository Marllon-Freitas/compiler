#include "lexer.h"
#include <iostream>
#include <sstream>
using std::cin;
using std::cout;
using std::stringstream;

// Constructor
Lexer::Lexer()
{
	// Inserts the reserved words into the ID table
	id_table["true"] = Id{Tag::TRUE, "true"};
	id_table["false"] = Id{Tag::FALSE, "false"};
}

// Returns tokens to the parser
Token Lexer::Scan()
{
	// Skips whitespace, tabs, and newlines
	while (isspace(peek))
	{
		if (peek == '\n')
			line += 1;
		peek = cin.get();
	}

	// Returns numbers
	if (isdigit(peek))
	{
		int v = 0;

		do
		{
			// Converts character 'n' to the numeric digit n
			int n = peek - '0';
			v = 10 * v + n;
			peek = cin.get();
		} while (isdigit(peek));

		// DEBUG: Displays the recognized token
		cout << "<NUM," << v << "> ";

		// Returns the NUM token
		return Num{v};
	}

	// Returns keywords and identifiers
	if (isalpha(peek))
	{
		stringstream ss;

		do
		{
			ss << peek;
			peek = cin.get();
		} while (isalpha(peek));

		string s = ss.str();
		auto pos = id_table.find(s);

		// If the lexeme is already in the table
		if (pos != id_table.end())
		{
			// DEBUG: Displays the recognized token
			switch (pos->second.tag)
			{
			case TRUE:
				cout << "<" << "TRUE" << "," << pos->second.name << "> ";
				break;
			case FALSE:
				cout << "<" << "FALSE" << "," << pos->second.name << "> ";
				break;
			default:
				cout << "<" << "ID" << "," << pos->second.name << "> ";
				break;
			}

			// Returns the found token (could be a keyword or an existing ID)
			return pos->second;
		}

		// If the lexeme is not yet in the table, it's a new identifier
		Id new_id{Tag::ID, s};
		id_table[s] = new_id;

		// DEBUG: Displays the recognized token
		cout << "<" << "ID" << "," << new_id.name << "> ";

		// Returns the new ID token
		return new_id;
	}

	// Operators (and other isolated non-alphanumeric characters)
	Token t{peek};
	peek = ' ';

	// DEBUG: Displays the token for the character
	cout << "<" << char(t.tag) << "> ";

	// Returns the token for the isolated character
	return t;
}

void Lexer::Start()
{
	// Simulates the parser asking the lexer for tokens until the input ends
	while (peek != '\n')
		Scan();
}