#include "markdowneditorwidget.h"
#include "markdowneditortoolbutton.h"
#include "mdeditorconstants.h"
#include "markdownconverterinterface.h"
#include <coreplugin/rightpane.h>
#include <coreplugin/icore.h>
#include <utils/fileutils.h>

#include <QWebView>
#include <QFileInfo>
#include <QProcess>
#include <QDebug>
#include <QFile>
#include <QDir>
#include <QToolBar>
#include <QWebFrame>

using namespace TextEditor;
using namespace MDEditor;
using namespace MDEditor::Internal;

MarkdownEditorWidget::MarkdownEditorWidget(QWidget *parent)
    : TextEditor::TextEditorWidget(parent), m_toolbar(new QToolBar(this)),
      m_webview(new QWebView(this))
{

    QSharedPointer<TextEditor::TextDocument> pDocument (new TextDocument);
    pDocument.data()->setId(MDEditor::Constants::MDDocument_ID);
    setTextDocument(pDocument);

    addToolBar();
    m_webview->show();

    connect(this,SIGNAL(textChanged()),this,SLOT(onWebReload()));
    connect(this,SIGNAL(cursorPositionChanged()),this,SLOT(syncScroll()));
    connect(pDocument.data(),SIGNAL(changed()),this,SLOT(onWebReload()));
}

MarkdownEditorWidget::~MarkdownEditorWidget()
{
    if(m_converter)
    {
        delete m_converter;
        m_converter = nullptr;
    }
}

void MarkdownEditorWidget::setConverter(MarkdownConverterInterface*pConverter)
{
    if(m_converter)
    {
        delete m_converter;
    }
    m_converter = pConverter;
}

void MarkdownEditorWidget::addToolBar()
{
    QList<MarkdownEditorToolButton::ButtonId> ids;
    ids<<MarkdownEditorToolButton::ID_Bold
       <<MarkdownEditorToolButton::ID_Italic
       <<MarkdownEditorToolButton::ID_StrikeThrough
//       <<MarkdownEditorToolButton::ID_H1
//       <<MarkdownEditorToolButton::ID_H2
//       <<MarkdownEditorToolButton::ID_H3
//       <<MarkdownEditorToolButton::ID_H4
//       <<MarkdownEditorToolButton::ID_H5
//       <<MarkdownEditorToolButton::ID_H6
       <<MarkdownEditorToolButton::ID_HorizonalRule
       <<MarkdownEditorToolButton::ID_Link
       <<MarkdownEditorToolButton::ID_Image
       <<MarkdownEditorToolButton::ID_Table
       <<MarkdownEditorToolButton::ID_Tastlist
       <<MarkdownEditorToolButton::ID_Code
       <<MarkdownEditorToolButton::ID_MathFormula
       <<MarkdownEditorToolButton::ID_FlowChart
       <<MarkdownEditorToolButton::ID_SequenceDiagram;

    foreach (const MarkdownEditorToolButton::ButtonId id, ids) {
        MarkdownEditorToolButton* but = new MarkdownEditorToolButton(id, this);
        but->setEditorWidget(this);
        connect(but,SIGNAL(pressed()),but,SLOT(doAction()));
        m_toolbar->addWidget(but);
    }
    insertExtraToolBarWidget(Left, m_toolbar);
}

void MarkdownEditorWidget::onWebReload()
{
    QUrl url = m_converter->convert(textDocument()->filePath(), toPlainText());
    if(m_webview->url() == url)
        m_webview->reload();
    else
        m_webview->setUrl(url);
    syncScroll();
}

void MarkdownEditorWidget::syncScroll()
{
    int currentline, endline;
    int column;
    convertPosition(position(CurrentPosition), &currentline, &column);
    convertPosition(position(EndOfDocPosition), &endline, &column);

    int maxVertical = m_webview->page()->mainFrame()->scrollBarMaximum(Qt::Vertical);
    m_webview->page()->mainFrame()->setScrollPosition(QPoint(0,0));
    if(endline != 0)
        m_webview->page()->mainFrame()->scroll(0, (currentline-1) * maxVertical/ endline);
}

void MarkdownEditorWidget::showEvent(QShowEvent* e)
{
    Core::RightPaneWidget::instance()->setWidget(m_webview);
    Core::RightPaneWidget::instance()->setShown(true);
    TextEditorWidget::showEvent(e);
}

void MarkdownEditorWidget::hideEvent(QHideEvent* e)
{
    Core::RightPaneWidget::instance()->setWidget(nullptr);
    Core::RightPaneWidget::instance()->setShown(false);
    TextEditorWidget::hideEvent(e);
}

bool MarkdownEditorWidget::event(QEvent *e)
{
    switch (e->type()) {
    case QEvent::ShortcutOverride:
        if (static_cast<QKeyEvent*>(e)->key() == Qt::Key_Escape) {
            e->accept();
            return true;
        }
        break;
    default:
        break;
    }
    return TextEditorWidget::event(e);
}
