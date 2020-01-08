#include "Entry.h"
#include "ConsoleWindow.h"
#include <QTimer>


void Entry::setupToolBar() {
	paintTool = new PaintToolBar();
	connect(paintTool->palletAction, &QAction::triggered, this, &Entry::pick_color);
	
	scriptTool = new ScriptToolBar();
	connect(scriptTool->runAction, &QAction::triggered, this, &Entry::run_script);
	connect(scriptTool->stopAction, &QAction::triggered, this, &Entry::stop_script);
	connect(scriptTool->decFontAction, &QAction::triggered, this, &Entry::editorZoomOut);
	connect(scriptTool->incFontAction, &QAction::triggered, this, &Entry::editorZoomIn);
	connect(scriptTool->commentAction, &QAction::triggered, this, &Entry::comment_line);

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
	action = menu->addAction(QString::fromLocal8Bit("&保存布局"), this, &Entry::saveLayout);
	action = menu->addAction(QString::fromLocal8Bit("&载入布局"), this, &Entry::loadLayout);
	action = menu->addAction(QString::fromLocal8Bit("&保存默认设置"), this, &Entry::wirteSettings_slot);
	action = menu->addAction(QString::fromLocal8Bit("&载入默认设置"), this, &Entry::readSettings_slot);
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

	connect(run_thread, &Lua::LuaScript::sig_took_time, this, &Entry::update_statusbar_msg);
	connect(run_thread, &Lua::LuaScript::sig_script_stop, this, &Entry::set_btn_stopstatu);

	//for good look
	QFont font("YaHei Consolas Hybrid", 11);
	activeEditor->setStyleSheet("background-color: #cfd9e8");
	activeEditor->setFont(font);
	console->setStyleSheet("background-color: #cfd9e8");
	console->setFont(font);

}

void Entry::setupCenterWidget() {
	//设置中心界面
	QScrollArea* scrollArea = new QScrollArea();
	center = new ShowWidget(this);
	scrollArea->setBackgroundRole(QPalette::Dark);
	scrollArea->setWidget(center);

	center->resize(400, 300);
	setCentralWidget(scrollArea);


	QTimer* timer = new QTimer(this);
	connect(timer, &QTimer::timeout, center, &ShowWidget::animate);
	timer->start(1000 / 100); //40 pic per second
	center->setMng(mng);
	connect(mng, &SourceMnger::sig_show_msg, center, &ShowWidget::setId);
	//connect(center, &ShowWidget::sig_resize, this, &Entry::resize_toolBar);
	//for update pixel msg with current position
}

void Entry::setupStatusBar() {
	//pixelMsg = new QLabel("" , this);
	//pixelMsg->setFrameStyle();
	//statusBar()->setSizeGripEnabled(false);
	//statusBar()->addWidget(pixelMsg, 1);
	//center->setPixelShowLabel(pixelMsg);
}

void Entry::setupUI() {
	this->resize(1250, 840);	
	setupMenuBar();
	setupToolBar();
	setupDockWidget();
	setupCenterWidget();
	setupStatusBar();
	readSettings_slot();
	//setCenterSize
}

Entry::Entry(QWidget *parent)
	: QMainWindow(parent)
{
	mng = new SourceMnger(this);
	run_thread = new Lua::LuaScript(mng);
	setupUI();
}

void Entry::createStatusBar() {
	statusBar()->showMessage(tr("Ready"));
}

void Entry::writeSettings(QString key) {
	QSettings settings("MeiSoftWare", "MeiVision");
	settings.beginGroup(key + "MainWindow");
	settings.setValue("geometry", saveGeometry());
	settings.setValue("windowState", saveState());
	settings.endGroup();
}

void Entry::readSettings(QString key) {
	QSettings settings("MeiSoftWare", "MeiVision");
	settings.beginGroup(key + "MainWindow");
	restoreGeometry(settings.value("geometry").toByteArray());
	restoreState(settings.value("windowState").toByteArray());
	settings.endGroup();
}

//slots
void Entry::run_script() {
	console->clear();
	console->show();
	console->insert_text("script starting...\n");
	set_btn_runstatu();
	QString text = activeEditor->text();
	if (!run_thread->isFinished()) run_thread->quit();
	run_thread->set_script_run(text.toStdString());
}

void Entry::stop_script() {
	run_thread->stop_script();
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

bool Entry::save() {
	return   activeEditor->save();
}

void Entry::create_script() {
	DockEditor* newEditor = new DockEditor(QString("new " + QString::number(DockEditor::new_count ++)), this);
	editors << newEditor;
	tabifyDockWidget(activeEditor, newEditor);  //在脚本界面新建一个标签；
	newEditor->show();
	newEditor->raise();
	activeEditor = newEditor;
	activeEditor->raise();

	//for good look 
	QFont font("YaHei Consolas Hybrid", 11);
	activeEditor->setFont(font);
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
	center->setId(id);
}

void Entry::update_statusbar_msg(const QString& msg, int time) {
	statusBar()->showMessage(msg, time);
}



void Entry::saveLayout()
{
	QString fileName
		= QFileDialog::getSaveFileName(this, tr("Save layout"));
	if (fileName.isEmpty())
		return;
	QFile file(fileName);
	if (!file.open(QFile::WriteOnly)) {
		QString msg = tr("Failed to open %1\n%2")
			.arg(QDir::toNativeSeparators(fileName), file.errorString());
		QMessageBox::warning(this, tr("Error"), msg);
		return;
	}

	QByteArray geo_data = saveGeometry();
	QByteArray layout_data = saveState();

	bool ok = file.putChar((uchar)geo_data.size());
	if (ok)
		ok = file.write(geo_data) == geo_data.size();
	if (ok)
		ok = file.write(layout_data) == layout_data.size();

	if (!ok) {
		QString msg = tr("Error writing to %1\n%2")
			.arg(QDir::toNativeSeparators(fileName), file.errorString());
		QMessageBox::warning(this, tr("Error"), msg);
		return;
	}
}

void Entry::loadLayout()
{
	QString fileName
		= QFileDialog::getOpenFileName(this, tr("Load layout"));
	if (fileName.isEmpty())
		return;
	QFile file(fileName);
	if (!file.open(QFile::ReadOnly)) {
		QString msg = tr("Failed to open %1\n%2")
			.arg(QDir::toNativeSeparators(fileName), file.errorString());
		QMessageBox::warning(this, tr("Error"), msg);
		return;
	}

	uchar geo_size;
	QByteArray geo_data;
	QByteArray layout_data;

	bool ok = file.getChar((char*)&geo_size);
	if (ok) {
		geo_data = file.read(geo_size);
		ok = geo_data.size() == geo_size;
	}
	if (ok) {
		layout_data = file.readAll();
		ok = layout_data.size() > 0;
	}

	if (ok)
		ok = restoreGeometry(geo_data);
	if (ok)
		ok = restoreState(layout_data);

	if (!ok) {
		QString msg = tr("Error reading %1").arg(QDir::toNativeSeparators(fileName));
		QMessageBox::warning(this, tr("Error"), msg);
		return;
	}
}

void Entry::resize_toolBar(QSize size) {
	//int h = paintTool->height();
	//paintTool->resize(size.width(), h);
	//scriptTool->resize(this->width() - size.width(), h);
	////removeToolBar(scriptTool);
	////insertToolBar(paintTool, scriptTool);
	//update();
}

void Entry::set_btn_runstatu() {
	scriptTool->runAction->setDisabled(true); // cannot run two script in the same time
	scriptTool->stopAction->setDisabled(false);
}

void Entry::set_btn_stopstatu() {
	scriptTool->runAction->setDisabled(false); // cannot run two script in the same time
	scriptTool->stopAction->setDisabled(true);
}

void Entry::closeEvent(QCloseEvent* event)
{
	QMainWindow::closeEvent(event);
}
