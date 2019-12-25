#pragma once

#include <QSyntaxHighlighter>
#include <QVector>

class HighLighter : public QSyntaxHighlighter
{
	Q_OBJECT

public:
	HighLighter(QTextDocument*parent);
	~HighLighter();

protected:
	void highlightBlock(const QString& text) override;

private:
	class LuaHighLightRule {
	public:
		QRegExp pattern;
		QTextCharFormat format;
	};

	QVector<LuaHighLightRule> rules;

	QRegExp comment_start_exp;
	QRegExp comment_end_exp;

	QTextCharFormat keyword_format;
	QTextCharFormat table_format;
	QTextCharFormat single_line_key;
	QTextCharFormat single_line_value;
	QTextCharFormat singleLineCommentFormat;
	QTextCharFormat multiLineCommentFormat;
	QTextCharFormat quotation_format;
	QTextCharFormat function_format;
};
