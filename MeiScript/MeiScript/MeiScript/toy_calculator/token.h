#pragma once
#include <string>
using namespace std;

enum class TokenKind : int{
	BAD_TOKEN,
	LP_TOKEN,  //(
	RP_TOKEN,  // )
	NUMBER_TOKEN,
	ADD_OPERATOR_TOKEN,
	SUN_OPERATOR_TOKEN,
	MUL_OPERATOR_TOKEN,
	DIV_OPERATOR_TOKEN,
	END_OF_LINE_TOKEN,
};

struct Token {
	TokenKind kind;
	double value;
	string str;
};

void set_line(const string& line);
void get_token(Token *token);

