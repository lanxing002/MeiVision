#include "Entry.h"
#include "ConsoleWindow.h"
#include <QTimer>


void Entry::setupToolBar() {
	paintTool = new PaintToolBar(this);
	connect(paintTool->palletAction, &QAction::triggered, this, &Entry::pick_color);
	
	scriptTool = new ScriptToolBar(this);
	connect(scriptTool->runAction, &QAction::triggered, this, &Entry::run_script);
	connect(scriptTool->runAction, &QAction::triggered, this, &Entry::stop_script);

	addToolBar(paintTool);
	addToolBar(scriptTool);
}

void Entry::setupMenuBar() {
	QMenu* menu = menuBar()->addMenu(QString::fromLocal8Bit("&文件"));
	QAction* action = menu->addAction(QString::fromLocal8Bit("新建"), this, &Entry::create_script);
	action->setShortcut(tr("Ctrl+N"));
	action = menu->addAction(QString::fromLocal8Bit("打开"), this, &Entry::open);
	action->setShortcut(tr("Ctrl+O"));
	action = menu->addAction(QString::fromLocal8Bit("保存"), this, &Entry::save);
	action->setShortcut(tr("Ctrl+S"));
	menu->addSeparator();
	action = menu->addAction(QString::fromLocal8Bit("&退出"), this, &QWidget::close);
	action->setShortcut(tr("Ctrl+Q"));

	menu = menuBar()->addMenu(QString::fromLocal8Bit("&设置"));
}

void Entry::setupDockWidget() {

	//connect(console_sender, &ConsoleSender::sig_stdout, ui.console_text, &ConsoleWindow::update_log, Qt::QueuedConnection);

	DockEditor* editor = new DockEditor("new", this);
	addDockWidget(Qt::RightDockWidgetArea, editor);
	editors << editor;
	activeEditor = editor;
	connect(this, &QMainWindow::tabifiedDockWidgetActivated, this, &Entry::set_active_editor);

	console = new DockConsole("console", this);
	addDockWidget(Qt::BottomDockWidgetArea, console);
	console->close();
	connect(run_thread, &Lua::LuaScript::sig_stdoutmsg, console, &DockConsole::update_log);
	connect(run_thread, &Lua::LuaScript::sig_erroutmsg, console, &DockConsole::update_error_log);

	
	//for good look
	activeEditor->setStyleSheet("background-color: #cfd9e8");
	console->setStyleSheet("background-color: #cfd9e8");
}

void Entry::setupCenterWidget() {
	//设置中心界面
	center = new ShowWidget(this);
	center->setMinimumSize(400, 300);
	setCentralWidget(center);

	QTimer* timer = new QTimer(this);
	connect(timer, &QTimer::timeout, center, &ShowWidget::animate);
	timer->start(1000);
	center->setMng(mng);
	connect(mng, &SourceMnger::sig_show_msg, center, &ShowWidget::setId);
}

void Entry::setupUI() {
	this->resize(1250, 840);	
	setupMenuBar();
	setupToolBar();
	setupDockWidget();
	setupCenterWidget();
}

Entry::Entry(QWidget *parent)
	: QMainWindow(parent), isUntitled(false)
{
	mng = new SourceMnger(this);
	run_thread = new Lua::LuaScript(mng);
	setupUI();
}

void Entry::createStatusBar() {
	statusBar()->showMessage(tr("Ready"));
}

//slots
void Entry::run_script() {
	console->clear();
	console->show();
	console->insert_text("script starting...\n");
	QString text = activeEditor->text();
	if (!run_thread->isFinished()) run_thread->quit();
	run_thread->set_script_run(text.toStdString());
}

void Entry::stop_script() {
	//ui.console_text->clear();
	//ui.console_text->insertPlainText("script starting...\n");
	//QString text = ui.script_text->toPlainText();
	//if (!run_thread->isFinished()) run_thread->quit();
	//run_thread->set_script_run(text.toStdString());
	//Lua::Lua_script::run_script(text.toStdString(), outbuffer);
	//ui.console_text->clear_text_buffer();
}


void Entry::pick_color()
{
	QColorDialog* dig = new QColorDialog(this);
	dig->open(this, "id");
}

void Entry::open() {
	const QString file_path_name = QFileDialog::getOpenFileName(this);
	if (file_path_name.isEmpty()) return;

	//has opened
	if (DockEditor::openedFile.contains(file_path_name)) {
		QMessageBox::warning(this, tr("SDI"),
			tr("file %1 has opended.")
			.arg(QDir::toNativeSeparators(file_path_name)));
		return;
	}

	QFileInfo fileInfo(file_path_name);
	QString filename(fileInfo.fileName());

	DockEditor* newEditor = new DockEditor(filename, this, file_path_name);
	editors << newEditor;
	tabifyDockWidget(activeEditor, newEditor);  //在脚本界面新建一个标签；
	newEditor->show();
	newEditor->raise();
	activeEditor = newEditor;
	activeEditor->raise();
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
	//QApplication::setOverrideCursor(Qt::WaitCursor);
	//ui.script_text->setPlainText(in.readAll());
	statusBar()->showMessage(tr("File loaded"), 5000);
	//QGuiApplication::restoreOverrideCursor();
	this->cur_file = file_name;
	this->isUntitled = true; // has read some file
}

bool Entry::save() {
	return   activeEditor->save();
}

//bool Entry::saveAs() {
//	QString fileName = QFileDialog::getSaveFileName(this, tr("Save As"),
//		cur_file);
//	if (fileName.isEmpty())
//		return false;
//
//	return save_file(fileName);
//}
//
//bool Entry::save_file(const QString& file_name) {
//	QFile file(file_name);
//	if (!file.open(QFile::WriteOnly | QFile::Text)) {
//		QMessageBox::warning(this, tr("SDI"),
//			tr("Cannot write file %1:\n%2.")
//			.arg(QDir::toNativeSeparators(file_name), file.errorString()));
//		return false;
//	}
//
//	QTextStream out(&file);
//	QApplication::setOverrideCursor(Qt::WaitCursor);
//	//out << ui.script_text->toPlainText();
//	statusBar()->showMessage(tr("File saved"), 5000);
//	QGuiApplication::restoreOverrideCursor();
//	return true;
//}

void Entry::create_script() {
	DockEditor* newEditor = new DockEditor(QString("new " + QString::number(DockEditor::new_count ++)), this);
	editors << newEditor;
	tabifyDockWidget(activeEditor, newEditor);  //在脚本界面新建一个标签；
	newEditor->show();
	newEditor->raise();
	activeEditor = newEditor;
	activeEditor->raise();
}

void Entry::set_active_editor(QDockWidget* dockWidget) {
	activeEditor = static_cast<DockEditor*>(dockWidget);
}

void Entry::dockWidget_topLevelChanged(bool b) {
	QDockWidget* dw = static_cast<QDockWidget*>(QObject::sender());
	if (dw->isFloating())
	{
		dw->setWindowFlags(Qt::CustomizeWindowHint |
			Qt::Window | Qt::WindowMinimizeButtonHint |
			Qt::WindowMaximizeButtonHint |
			Qt::WindowCloseButtonHint);
		dw->show();
	}
}

void Entry::reset_show_img(size_t id) {
	//ui.openGLWidget->setId(id);
}

void Entry::receive_test(const string& str) {
	qDebug() << QString::fromStdString(str) << "----------------------------rrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrrr";
}

void Entry::update_statusbar_msg(const QString& msg, int time) {
	statusBar()->showMessage(msg, time);
}
