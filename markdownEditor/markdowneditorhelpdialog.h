#ifndef MARKDOWNEDITORHELPDIALOG_H
#define MARKDOWNEDITORHELPDIALOG_H

#include <QDialog>

namespace Ui {
class MarkdownEditorHelpDialog;
}

class MarkdownEditorHelpDialog : public QDialog
{
    Q_OBJECT

public:
    explicit MarkdownEditorHelpDialog(QWidget *parent = 0);
    ~MarkdownEditorHelpDialog();

private:
    Ui::MarkdownEditorHelpDialog *ui;
};

#endif // MARKDOWNEDITORHELPDIALOG_H
