#ifndef MARKDOWNEDITORTOOLBUTTON_H
#define MARKDOWNEDITORTOOLBUTTON_H
#include "mdeditor_global.h"

#include <QToolButton>

namespace TextEditor {
class TextEditorWidget;
}

namespace MDEditor {
class MarkdownEditorToolButtonPrivate;
class MDEDITORSHARED_EXPORT MarkdownEditorToolButton : public QToolButton
{
    Q_OBJECT
public:
    enum ButtonId
    {
        ID_Unknown = 0,
        ID_Bold,
        ID_Italic,
        ID_StrikeThrough,
        ID_H1,
        ID_H2,
        ID_H3,
        ID_H4,
        ID_H5,
        ID_H6,
        ID_HorizonalRule,
        ID_Tastlist,
        ID_Link,
        ID_Image,
        ID_Table,
        ID_MathFormula,
        ID_Code,
        ID_FlowChart,
        ID_SequenceDiagram
    };

    MarkdownEditorToolButton(ButtonId, QWidget* parent = 0);
    ~MarkdownEditorToolButton();

    ButtonId buttonId() const;
    void setButtonId(ButtonId id);

    void setEditorWidget(TextEditor::TextEditorWidget* widget);

public slots:
    void doAction();

private:
    MDEditor::MarkdownEditorToolButtonPrivate* d;
};
}

#endif // MARKDOWNEDITORTOOLBUTTON_H
