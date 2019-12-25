#include "ScriptWindow.h"

ScriptEditor::ScriptEditor(QWidget* parent)
	: QPlainTextEdit(parent), ctrl_press(false)
{
	cnt_area = new LineNumberArea(this);
	connect(this, &QPlainTextEdit::blockCountChanged, this, &ScriptEditor::update_cnt_area_width);
	connect(this, &QPlainTextEdit::updateRequest, this, &ScriptEditor::update_cnt_area);
	connect(this, &QPlainTextEdit::cursorPositionChanged, this, &ScriptEditor::highlight_current_line);
	update_cnt_area_width(0);

	QAction* copyLineAction = new QAction(this);
	copyLineAction->setShortcut(tr("ctrl+d"));
	connect(copyLineAction, &QAction::triggered, this, &ScriptEditor::copy_line);
	this->addAction(copyLineAction);
}

ScriptEditor::~ScriptEditor()
{
}

void ScriptEditor::resizeEvent(QResizeEvent* event) {
	QPlainTextEdit::resizeEvent(event);
	
	QRect cr = contentsRect();
	cnt_area->setGeometry(QRect(cr.left(), cr.top(), cnt_area_width(), cr.height()));
}

void ScriptEditor::copy_line() {
	this->moveCursor(QTextCursor::StartOfLine);
	this->moveCursor(QTextCursor::EndOfLine, QTextCursor::KeepAnchor);
	
	QString line = this->textCursor().selectedText();
	this->moveCursor(QTextCursor::EndOfLine, QTextCursor::MoveAnchor);
	this->insertPlainText("\n" + line);
}

int ScriptEditor::cnt_area_width() {
	int digits = 1;
	int max = qMax(1, blockCount());
	while (max >= 10) {
		max /= 10;
		++digits;
	}

	int space = 3 + fontMetrics().width(QLatin1Char('9')) * digits;

	return space;
}

void ScriptEditor::update_cnt_area(const QRect& rect, int dy) {
	if (dy)
		cnt_area->scroll(0, dy);
	else
		cnt_area->update(0, rect.y(), cnt_area->width(), rect.height());
	
	if (rect.contains(viewport()->rect()))
		update_cnt_area_width(0);
}

void ScriptEditor::update_cnt_area_width(int width) {
	setViewportMargins(cnt_area_width(), 0, 0, 0);
}


void ScriptEditor::highlight_current_line() {
	QList<QTextEdit::ExtraSelection> extra_selections;

	QTextEdit::ExtraSelection selection;
	QColor line_color = QColor(Qt::yellow).lighter(160);

	selection.format.setBackground(line_color);
	selection.format.setProperty(QTextFormat::FullWidthSelection, true);

	extra_selections.append(selection);

	setExtraSelections(extra_selections);
}


void ScriptEditor::cnt_area_paint_event(QPaintEvent* event) {
	QPainter painter(cnt_area);
	painter.fillRect(event->rect(), Qt::gray);

	QTextBlock block = firstVisibleBlock();
	int blockNumber = block.blockNumber();
	int top = (int)blockBoundingGeometry(block).translated(contentOffset()).top();
	int bottom = top + (int)blockBoundingRect(block).height();

	while (block.isValid() && top <= event->rect().bottom()) {
		if (block.isVisible() && bottom >= event->rect().top()) {
			QString number = QString::number(blockNumber + 1);
			painter.setPen(Qt::black);
			painter.drawText(-2, top, cnt_area->width(), fontMetrics().height(),
				Qt::AlignRight, number);
		}

		block = block.next();
		top = bottom;
		bottom = top + (int)blockBoundingRect(block).height();
		++blockNumber;
	}

}
