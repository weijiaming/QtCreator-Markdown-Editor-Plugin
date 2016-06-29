#ifndef MARKDOWNEDITORWIDGET_H
#define MARKDOWNEDITORWIDGET_H
#include "mdeditorplugin.h"

#include <texteditor/texteditor.h>
#include <texteditor/textdocument.h>

#include <QSharedPointer>

class QWebView;
using namespace TextEditor;
namespace MDEditor {
class MarkdownConverterInterface;

class MDEDITORSHARED_EXPORT MarkdownEditorWidget : public TextEditor::TextEditorWidget
{
    Q_OBJECT
public:
    MarkdownEditorWidget(QWidget *parent = 0);
    ~MarkdownEditorWidget();

    void setConverter(MarkdownConverterInterface*);

private slots:
    void onWebReload();
    void syncScroll();

protected:
    void showEvent(QShowEvent *) override;
    void hideEvent(QHideEvent *) override;
    bool event(QEvent *e) override;

protected:
    void addToolBar();

    QToolBar* m_toolbar;
    QWebView* m_webview;
    MarkdownConverterInterface* m_converter = nullptr;
};
}

#endif // MARKDOWNEDITORWIDGET_H
