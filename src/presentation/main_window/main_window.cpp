#include "presentation/main_window/main_window.h"

#include <Qsci/qscilexercpp.h>
#include <Qsci/qsciscintilla.h>

#include <QAction>
#include <QApplication>
#include <QFileSystemModel>
#include <QFontDatabase>
#include <QHeaderView>
#include <QMenu>
#include <QMenuBar>
#include <QPlainTextEdit>
#include <QSplitter>
#include <QStatusBar>
#include <QTabWidget>
#include <QTextEdit>
#include <QToolBar>
#include <QTreeView>

namespace offlinecode::presentation {

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
    setWindowTitle(tr("OfflineCode Studio"));
    resize(1200, 760);
    createActions();
    createWorkspace();
    statusBar()->showMessage(tr("Ready | C++17 | No toolchain configured"));
}

void MainWindow::createActions() {
    auto* fileMenu = menuBar()->addMenu(tr("&File"));
    auto* buildMenu = menuBar()->addMenu(tr("&Build"));
    auto* runMenu = menuBar()->addMenu(tr("&Run"));
    menuBar()->addMenu(tr("&Help"));

    auto* toolbar = addToolBar(tr("Main"));
    toolbar->setObjectName(QStringLiteral("mainToolBar"));

    auto* openAction = fileMenu->addAction(tr("&Open Project..."));
    openAction->setShortcut(QKeySequence::Open);
    toolbar->addAction(openAction);

    auto* saveAction = fileMenu->addAction(tr("&Save"));
    saveAction->setShortcut(QKeySequence::Save);
    toolbar->addAction(saveAction);

    toolbar->addSeparator();
    auto* buildAction = buildMenu->addAction(tr("&Build"));
    buildAction->setShortcut(Qt::Key_F6);
    toolbar->addAction(buildAction);

    auto* runAction = runMenu->addAction(tr("&Run"));
    runAction->setShortcut(Qt::Key_F5);
    toolbar->addAction(runAction);

    auto* stopAction = runMenu->addAction(tr("&Stop"));
    stopAction->setShortcut(QKeySequence(Qt::SHIFT | Qt::Key_F5));
    stopAction->setEnabled(false);
    toolbar->addAction(stopAction);

    connect(buildAction, &QAction::triggered, this, [this] {
        output_->append(tr("Build requested. Connect BuildCoordinator in the next milestone."));
    });
    connect(runAction, &QAction::triggered, this, [this] {
        output_->append(tr("Run requested. No successful artifact is available yet."));
    });
}

void MainWindow::createWorkspace() {
    auto* projectModel = new QFileSystemModel(this);
    projectModel->setRootPath(QString());

    auto* projectTree = new QTreeView(this);
    projectTree->setModel(projectModel);
    projectTree->setHeaderHidden(false);
    projectTree->setMinimumWidth(220);
    for (int column = 1; column < projectModel->columnCount(); ++column) {
        projectTree->hideColumn(column);
    }

    auto* tabs = new QTabWidget(this);
    tabs->setTabsClosable(true);
    tabs->setMovable(true);

    editor_ = new QsciScintilla(tabs);
    configureEditor(*editor_);
    editor_->setText(QStringLiteral("#include <iostream>\n\nint main() {\n"
                                    "    std::cout << \"Hello, OfflineCode!\\n\";\n"
                                    "    return 0;\n}\n"));
    tabs->addTab(editor_, tr("main.cpp"));

    auto* horizontal = new QSplitter(Qt::Horizontal, this);
    horizontal->setObjectName(QStringLiteral("workspaceSplitter"));
    horizontal->addWidget(projectTree);
    horizontal->addWidget(tabs);
    horizontal->setStretchFactor(1, 1);

    output_ = new QTextEdit(this);
    output_->setReadOnly(true);
    output_->setPlaceholderText(tr("Build, run, and test output will appear here."));
    output_->setAccessibleName(tr("Build and run output"));

    auto* vertical = new QSplitter(Qt::Vertical, this);
    vertical->setObjectName(QStringLiteral("mainSplitter"));
    vertical->addWidget(horizontal);
    vertical->addWidget(output_);
    vertical->setStretchFactor(0, 4);
    vertical->setStretchFactor(1, 1);
    setCentralWidget(vertical);
}

void MainWindow::configureEditor(QsciScintilla& editor) {
    const auto font = QFontDatabase::systemFont(QFontDatabase::FixedFont);
    editor.setFont(font);
    editor.setMarginsFont(font);
    editor.setMarginType(0, QsciScintilla::NumberMargin);
    editor.setMarginLineNumbers(0, true);
    editor.setMarginWidth(0, QStringLiteral("00000"));
    editor.setBraceMatching(QsciScintilla::SloppyBraceMatch);
    editor.setAutoIndent(true);
    editor.setIndentationsUseTabs(false);
    editor.setIndentationWidth(4);
    editor.setTabWidth(4);
    editor.setFolding(QsciScintilla::BoxedTreeFoldStyle);
    editor.setUtf8(true);
    editor.setAccessibleName(tr("C++ source editor"));

    auto* lexer = new QsciLexerCPP(&editor);
    lexer->setDefaultFont(font);
    editor.setLexer(lexer);
}

} // namespace offlinecode::presentation
