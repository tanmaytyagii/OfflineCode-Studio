#pragma once

#include <QMainWindow>

class QsciScintilla;
class QTextEdit;

namespace offlinecode::presentation {

class MainWindow final : public QMainWindow {
public:
    explicit MainWindow(QWidget* parent = nullptr);

private:
    void createActions();
    void createWorkspace();
    void configureEditor(QsciScintilla& editor);

    QsciScintilla* editor_{nullptr};
    QTextEdit* output_{nullptr};
};

} // namespace offlinecode::presentation
