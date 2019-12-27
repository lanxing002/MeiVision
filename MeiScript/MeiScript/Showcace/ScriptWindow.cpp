#include "ScriptWindow.h"

ScriptEditor::ScriptEditor(QWidget* parent)
	: QPlainTextEdit(parent)
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

int DockEditor::new_count = 1;
QSet<QString> DockEditor::openedFile;

DockEditor::DockEditor(const QString& title, QMainWindow* parent, QString file_path_name)
:QDockWidget(title, (QWidget*)parent), edit_title(title), file_path_name(file_path_name) {
	this->editor = new ScriptEditor(this);
	connect(editor, &QPlainTextEdit::textChanged, this, &DockEditor::setChanged);
	HighLighter* highLighter = new HighLighter(editor->document());
	setWidget(editor);

	if (file_path_name.size() > 0) {
		assert(openedFile.contains(file_path_name) == false); 
		openedFile.insert(file_path_name);
		openFile();
	}
}

DockEditor::~DockEditor() {}

void DockEditor::openFile() {
	QFile file(file_path_name);
	if (!file.open(QFile::ReadWrite | QFile::Text)) {
		QMessageBox::warning(this, tr("SDI"),
			tr("Cannot read file %1:\n%2.")
			.arg(QDir::toNativeSeparators(file_path_name), file.errorString()));
		return;
	}
	QTextStream in(&file);
	editor->setPlainText(in.readAll());
}

bool DockEditor::saveAs() {
	const QString tmp_name = QFileDialog::getSaveFileName(this, tr("Save As"));
	if (tmp_name.isEmpty())
		return false;

	if (DockEditor::openedFile.contains(tmp_name)) {
		QMessageBox::warning(this, tr("SDI"),
			tr("file %1 has opended.")
			.arg(QDir::toNativeSeparators(file_path_name)));
		return false;
	}

	bool result =  saveFile(tmp_name);
	if (!result) return false;

	QFileInfo fileInfo(tmp_name);
	QString str(fileInfo.fileName());
	setWindowTitle(str);
	this->file_path_name = tmp_name;
	this->edit_title = str;
	openedFile.insert(tmp_name);
	return true;
}

bool DockEditor::saveFile(const QString& tmp_name) {
	QFile file(tmp_name);
	if (!file.open(QFile::WriteOnly | QFile::Text)) {
		QMessageBox::warning(this, tr("SDI"),
			tr("Cannot write file %1:\n%2.")
			.arg(QDir::toNativeSeparators(tmp_name), file.errorString()));
		return false;
	}

	QTextStream out(&file);
	//QApplication::setOverrideCursor(Qt::WaitCursor);
	out << editor->toPlainText();
	return true;
}

bool DockEditor::save() {
	bool result =  file_path_name.size() > 0 ? saveFile(file_path_name) : saveAs();
	setSaved();
	return result;
}

const QString& DockEditor::text() const {
	return editor->toPlainText();
}

void DockEditor::setChanged() {
	setWindowTitle(edit_title + " *");
}
void DockEditor::setSaved() {
	setWindowTitle(edit_title);
}