#include <cstdio>
#include <iostream>
#include <ctype.h>
#include "token.h"

static string st_line;
static int st_line_pos;

enum class LexerStatus {
	INITIAL_STATUS,
	IN_INT_PART_STATUS,
	DOT_STATUS,
	IN_FRAC_PART_STATUS,
};

void get_token(Token* token) {
	int out_pos = 0;
	LexerStatus status = LexerStatus::INITIAL_STATUS;
	char current_char;

	token->kind = TokenKind::BAD_TOKEN;
	while (st_line[st_line_pos] != '\0') {
		current_char = st_line[st_line_pos];
		if ((status == LexerStatus::IN_INT_PART_STATUS || status == LexerStatus::IN_FRAC_PART_STATUS)
			&& !isdigit(current_char) && current_char != '.') {
			token->kind = TokenKind::NUMBER_TOKEN;
			//sscanf(st_line.c_str(), "%1f", &(token->value));
			token->value = stod(token->str, nullptr);
			return;
		}
		if (isspace(current_char)) {
			if (current_char == '\n') {
				token->kind = TokenKind::END_OF_LINE_TOKEN;
				return;
			}
			else {
				st_line_pos++;
				continue;
			}
		}

		//token->str[out_pos] = st_line[st_line_pos];
		token->str.append(1, st_line[st_line_pos]);
		st_line_pos++;
		out_pos++;

		if (current_char == '+') {
			token->kind = TokenKind::ADD_OPERATOR_TOKEN;
			return;
		}
		else if (current_char == '-') {
			token->kind = TokenKind::SUN_OPERATOR_TOKEN;
			return;
		}
		else if (current_char == '*') {
			token->kind = TokenKind::MUL_OPERATOR_TOKEN;
			return;
		}
		else if (current_char == '/') {
			token->kind = TokenKind::DIV_OPERATOR_TOKEN;
			return;
		}
		else if (current_char == '(') {
			token->kind = TokenKind::LP_TOKEN;
			return;
		}
		else if (current_char == ')') {
			token->kind = TokenKind::RP_TOKEN;
			return;
		}
		else if(isdigit(current_char)) {
			if (status == LexerStatus::INITIAL_STATUS) {
				status = LexerStatus::IN_INT_PART_STATUS;
			}
			else if (status == LexerStatus::DOT_STATUS) {
				status = LexerStatus::IN_FRAC_PART_STATUS;
			}
		}
		else if (current_char == '.') {
			if (status == LexerStatus::IN_INT_PART_STATUS) {
				status = LexerStatus::DOT_STATUS;
			}
			else {
				std::cerr << " syntax error " << endl;
				exit(1);
			}

		}
		else {
			cerr << "bad character '" << current_char << "' " << endl;
			exit(1);
		}

	}
}

void set_line(const string& line) {
	st_line = line;
	st_line_pos = 0;
}

//²âÊÔÇý¶¯´úÂë
void parse_line(string line) {
	Token token;
	set_line(line);
	for (;;) {
		get_token(&token);
		if (token.kind == TokenKind::END_OF_LINE_TOKEN) {
			break;
		}
		else {
			cout << "kind..." << static_cast<int>(token.kind) << ", str..." << token.str << std::endl;
		}
	}
}

int main_toy() {
	char buf[1024];
	while(cin.getline(buf, 1024)){
		string test_str(buf);
		test_str.append(1, '\n');
		parse_line(test_str);
	}

	return 0;
}