#ifndef MDEDITOR_H
#define MDEDITOR_H

#include "mdeditorplugin.h"
#include "mdeditor_global.h"
#include <texteditor/textdocument.h>
#include <texteditor/texteditorconstants.h>
#include <texteditor/texteditor.h>

namespace MDEditor {
class MarkdownEditorWidget;
class MarkdownEditor : public TextEditor::BaseTextEditor
{
    Q_OBJECT
public:
    MarkdownEditor(MarkdownEditorWidget *);
};

class MDEditorFactory : public Core::IEditorFactory
{
    Q_OBJECT
public:
    MDEditorFactory(Internal::MDEditorPlugin* owner);
    ~MDEditorFactory();
    Core::IEditor *createEditor();

    void extensionsInitialized();
private:
    Internal::MDEditorPlugin* m_owner;
};

} // MDEditor

#endif // MDEDITOR_H
