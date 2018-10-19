#include "mdeditorconstants.h"
#include "markdowneditor.h"
#include "markdown2htmlconverter.h"
#include "pandocconverter.h"
#include "discontconverter.h"
#include "markdowneditorwidget.h"

#include <QAction>
#include <QWidgetAction>
#include <QApplication>

using namespace MDEditor;

MarkdownEditor::MarkdownEditor(MarkdownEditorWidget *widget)
{
    setWidget(widget);
}

MDEditorFactory::MDEditorFactory(Internal::MDEditorPlugin* owner)
    :Core::IEditorFactory(owner), m_owner(owner)
{
    setId(MDEditor::Constants::MDEditor_ID);
    setDisplayName(qApp->translate("OpenWith::Editors", MDEditor::Constants::MDEditor_DISPLAY_NAME));
    addMimeType(MDEditor::Constants::MD_SOURCE_MIMETYPE);
    addMimeType(MDEditor::Constants::MDX_SOURCE_MIMETYPE);
}

MDEditorFactory::~MDEditorFactory()
{

}

Core::IEditor *MDEditorFactory::createEditor()
{
    MarkdownEditorWidget *widget = new MarkdownEditorWidget();
    widget->setConverter(new Markdown2HtmlConverter);
    MarkdownEditor* editor = new MarkdownEditor(widget);
    widget->setRevisionsVisible(true);
    return editor;
}

void MDEditorFactory::extensionsInitialized()
{

}
