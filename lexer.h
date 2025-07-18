#include <unordered_map>
#include <string>
using std::string;
using std::unordered_map;

// Each token must have a tag (a number starting from 256).
// The tag for individual characters is their ASCII code.
enum Tag
{
	NUM = 256,
	ID,
	TRUE,
	FALSE
};

// Classes to represent tokens
struct Token
{
	int tag;
	Token(int t) : tag(t) {}
};

struct Num : public Token
{
	int value;
	Num(int v) : Token(Tag::NUM), value(v) {}
};

struct Id : public Token
{
	string name;
	Id() : Token(0) {}
	Id(int t, string s) : Token(t), name(s) {}
};

// Lexical analyzer
class Lexer
{
private:
	int line = 1;
	char peek = ' ';
	unordered_map<string, Id> id_table;

public:
	Lexer();

	Token Scan();
	void Start();
};