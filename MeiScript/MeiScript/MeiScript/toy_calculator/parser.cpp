#include <iostream>
#include "token.h"
using namespace std;

static Token st_look_ahead_token;
static int st_look_ahead_token_exists;

static void my_get_token(Token *token) {
	if (st_look_ahead_token_exists == 1) {
		*token = st_look_ahead_token;
		st_look_ahead_token_exists = 0;
	}
	else {
		get_token(token);
	}
}

static void unget_token(Token* token) {
	st_look_ahead_token = *token;
	st_look_ahead_token_exists = 1;
}

double parse_expression();

static double parse_primary_expression() {
	Token token;
	double value;

	my_get_token(&token);
	if (token.kind == TokenKind::NUMBER_TOKEN) {
		return token.value;
	}
	else if (token.kind == TokenKind::LP_TOKEN) {
		value = parse_expression();
		my_get_token(&token);
		if (token.kind == TokenKind::RP_TOKEN) {
			return value;
		}
		else {
			cerr << "miss ')'" << endl;
			exit(1);
		}
	}
	else {
		unget_token(&token);
		return 0.0;
	}
	cerr << "syntax error" << endl;
	exit(1);
	return 0.0;
}

static double parse_term() {
	double v1, v2;
	Token token;
	v1 = parse_primary_expression();
	for (;;) {
		my_get_token(&token);
		if (token.kind != TokenKind::MUL_OPERATOR_TOKEN
			&& token.kind != TokenKind::DIV_OPERATOR_TOKEN) {
			unget_token(&token); //已经读入一个符号了，因此需要将该符号退回
			break;
		}
		v2 = parse_primary_expression();
		if (token.kind == TokenKind::MUL_OPERATOR_TOKEN) {
			v1 *= v2;
		}
		else if (token.kind == TokenKind::DIV_OPERATOR_TOKEN) {
			v1 /= v2;
		}
		else {
			unget_token(&token);
		}
	}
	return v1;
}

double parse_expression() {
	double v1, v2;
	Token token;
	v1 = parse_term();
	for (;;) {
		my_get_token(&token);
		if (token.kind != TokenKind::ADD_OPERATOR_TOKEN
			&& token.kind != TokenKind::SUN_OPERATOR_TOKEN) {
			unget_token(&token);
			break;
		}
		v2 = parse_term();
		if (token.kind == TokenKind::ADD_OPERATOR_TOKEN) {
			v1 += v2;
		}
		else if(token.kind == TokenKind::SUN_OPERATOR_TOKEN){
			v1 -= v2;
		}
		else {
			unget_token(&token);
		}
	}
	return v1;
}

double parse_line(void) {
	double value;
	st_look_ahead_token_exists = 0;
	value = parse_expression();

	return value;
}

int main_calculator(void) {
	char line[1024];
	double value;
	while (cin.getline(line, 1024)) {
		set_line(string(line).append(1, '\n'));
		value = parse_line();
		cout << ">>" << value << endl;
	}
	return 0;
}