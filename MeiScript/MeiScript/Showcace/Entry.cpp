#include "Entry.h"

Entry::Entry(QWidget *parent)
	: QMainWindow(parent)
{
	mng = new SourceMnger(this);
	run_thread = new Lua::LuaScript(this, mng);

	ui.setupUi(this);
	connect(mng, &SourceMnger::sig_show_msg, this, &Entry::draw_img);
	connect(ui.run_btn, &QPushButton::clicked, this, &Entry::run_script);

	//init stdout
	StaticSender::init_sender(this);
	const ConsoleSender* console_sender = StaticSender::get_sender();
	//connect(console_sender, &ConsoleSender::sig_stdout, ui.console_text, &ConsoleWindow::update_log, Qt::QueuedConnection);
	connect(console_sender, &ConsoleSender::sig_stdout, ui.console_text, &ConsoleWindow::update_log);
	connect(run_thread, &Lua::LuaScript::sig_outmsg, ui.console_text, &ConsoleWindow::update_error_log);
	connect(ui.actionopen, &QAction::triggered, this, &Entry::open);
	connect(ui.actionsave, &QAction::triggered, this, &Entry::save);
	
	QAction* runAction = new QAction(this);
	runAction->setShortcut(tr("f5"));
	connect(runAction, &QAction::triggered, this, &Entry::run_script);
	this->addAction(runAction);

	//set short cut
	ui.actionopen->setShortcut(tr("Ctrl+O"));
	ui.actionsave->setShortcut(tr("Ctrl+S"));

	//StaticSender::destroy_sender();
	ui.script_text->setStyleSheet("background-color: #cfd9e8");
	ui.console_text->setStyleSheet("background-color: #cfd9e8");

	HighLighter* highLighter = new HighLighter(ui.script_text->document());
}

void Entry::createStatusBar() {
	statusBar()->showMessage(tr("Ready"));
}

//slots
void Entry::run_script() {
	ui.console_text->clear();
	ui.console_text->insertPlainText("script starting...\n");
	QString text = ui.script_text->toPlainText();
	run_thread->run_script(text.toStdString());
	
	mng->clear(); // 每一次脚本运行之后清理脚本所不能释放的资源， 例如图片
	//Lua::Lua_script::run_script(text.toStdString(), outbuffer);
	//ui.console_text->clear_text_buffer();
}


void Entry::open() {
	const QString file_name = QFileDialog::getOpenFileName(this);
	if (!file_name.isEmpty())
		open_file(file_name);
}
void Entry::open_file(const QString& file_name) {
	if (file_name == cur_file)
		return;
	
	QFile file(file_name);
	if (!file.open(QFile::ReadWrite | QFile::Text)) {
		QMessageBox::warning(this, tr("SDI"),
			tr("Cannot read file %1:\n%2.")
			.arg(QDir::toNativeSeparators(file_name), file.errorString()));
		return;
	}
	QTextStream in(&file);
	QApplication::setOverrideCursor(Qt::WaitCursor);
	ui.script_text->setPlainText(in.readAll());
	statusBar()->showMessage(tr("File loaded"), 5000);
	QGuiApplication::restoreOverrideCursor();
	this->cur_file = file_name;
	this->isUntitled = true; // has read some file
}

bool Entry::save() {
	return   isUntitled ? saveAs() : save_file(cur_file);
}

bool Entry::saveAs() {
	QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
		cur_file);
	if (fileName.isEmpty())
		return false;

	return save_file(fileName);
}

bool Entry::save_file(const QString& file_name) {
	QFile file(file_name);
	if (!file.open(QFile::WriteOnly | QFile::Text)) {
		QMessageBox::warning(this, tr("SDI"),
			tr("Cannot write file %1:\n%2.")
			.arg(QDir::toNativeSeparators(file_name), file.errorString()));
		return false;
	}

	QTextStream out(&file);
	QApplication::setOverrideCursor(Qt::WaitCursor);
	out << ui.script_text->toPlainText();
	statusBar()->showMessage(tr("File saved"), 5000);
	QGuiApplication::restoreOverrideCursor();
	return true;
}


void Entry::draw_img(const QImage& img) {
	//ui.openGLWidget->
}

