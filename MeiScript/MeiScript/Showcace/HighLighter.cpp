#include "HighLighter.h"

HighLighter::HighLighter(QTextDocument*parent)
	: QSyntaxHighlighter(parent)
{
	LuaHighLightRule rule;

	keyword_format.setForeground(Qt::darkGreen);
	//keyword_format.setFontWeight(QFont::);
	QStringList keyword_patterns;
	keyword_patterns << "\\band\\b" << "\\bbreak\\b" << "\\bdo\\b"
		<< "\\belse\\b" << "\\belseif\\b" << "\\bend\\b"
		<< "\\bfalse\\b" << "\\bfor\\b" << "\\bfunction\\b"
		<< "\\bif\\b" << "\\bin\\b" << "\\blocal\\b"
		<< "\\bnil\\b" << "\\bnot\\b" << "\\bor\\b"
		<< "\\brepeat\\b" << "\\breturn\\b" << "\\bthen\\b"
		<< "\\btrue\\b" << "\\butil\\b" << "\\bwhile\\b"
		<< "\\bgoto\\b" ;

	foreach(const QString & pattern, keyword_patterns) {
		rule.pattern = QRegExp(pattern);
		rule.format = keyword_format;
		rules.append(rule);
	}


	singleLineCommentFormat.setForeground(Qt::gray);
	rule.pattern = QRegExp("--[^\n]*");
	rule.format = singleLineCommentFormat;
	rules.append(rule);

	//multiLineCommentFormat.setForeground(Qt::gray);
	//rule.pattern = QRegExp("--\[\[.*\]\]--");
	//rule.format = multiLineCommentFormat;
	//rules.append(rule);

	function_format.setFontWeight(QFont::Bold);
	function_format.setForeground(Qt::blue);
	rule.pattern = QRegExp("\\b[A-Za-z0-9_]+(?=\\()");
	rule.format = function_format;
	rules.append(rule);
}

HighLighter::~HighLighter()
{
}


void HighLighter::highlightBlock(const QString& text){
	
	//set format for matched sunstring
	foreach(const LuaHighLightRule & rule, rules) {
		QRegExp exp(rule.pattern);
		int index = exp.indexIn(text);
		while (index >= 0) {
			int length = exp.matchedLength();
			setFormat(index, length, rule.format);
			index = exp.indexIn(text, index + length);
		}
	}
}