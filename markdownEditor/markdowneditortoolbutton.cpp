#include "markdowneditortoolbutton.h"
#include "markdowneditorhelpdialog.h"
#include "texteditor/texteditor.h"
#include <QDebug>

namespace MDEditor{
class MarkdownEditorToolButtonPrivate
{
public:

    MarkdownEditorToolButtonPrivate() {}
    ~MarkdownEditorToolButtonPrivate()
    {
        if(helpDlg)
        {
            delete helpDlg;
            helpDlg = nullptr;
        }
    }
    MarkdownEditorToolButton::ButtonId m_ButtonId = MarkdownEditorToolButton::ID_Unknown;
    TextEditor::TextEditorWidget* m_editorWidget = nullptr;
    MarkdownEditorHelpDialog* helpDlg = nullptr;

    void apply();
};

void MarkdownEditorToolButtonPrivate::apply()
{
    if(!m_editorWidget)
        return;

    switch (m_ButtonId) {
    case MarkdownEditorToolButton::ID_Bold:
    case MarkdownEditorToolButton::ID_Italic:
    case MarkdownEditorToolButton::ID_StrikeThrough:
    case MarkdownEditorToolButton::ID_Code:
    {
        QString markerStr;
        if(m_ButtonId == MarkdownEditorToolButton::ID_Bold)
            markerStr = QString::fromUtf8("**");
        else if(m_ButtonId == MarkdownEditorToolButton::ID_Italic)
            markerStr = QString::fromUtf8("*");
        else if(m_ButtonId == MarkdownEditorToolButton::ID_StrikeThrough)
            markerStr = QString::fromUtf8("~~");
        else if(m_ButtonId ==MarkdownEditorToolButton::ID_Code )
            markerStr = QString::fromUtf8("\n```\n");

        int markerStrLength = markerStr.length();
        QString targetStr = m_editorWidget->selectedText();

        if(targetStr.startsWith(markerStr) && targetStr.endsWith(markerStr))
        {
            targetStr.remove(0, markerStrLength);
            targetStr.remove(targetStr.length() - markerStrLength,markerStrLength);
        }
        else
        {
            targetStr.prepend(markerStr);
            targetStr.append(markerStr);
        }
        m_editorWidget->insertPlainText(targetStr);
        QTextCursor tc = m_editorWidget->textCursor();
        tc.movePosition(QTextCursor::Left, QTextCursor::MoveAnchor, markerStrLength);
        m_editorWidget->setTextCursor(tc);

        break;
    }
    case MarkdownEditorToolButton::ID_H1:
    case MarkdownEditorToolButton::ID_H2:
    case MarkdownEditorToolButton::ID_H3:
    case MarkdownEditorToolButton::ID_H4:
    case MarkdownEditorToolButton::ID_H5:
    case MarkdownEditorToolButton::ID_H6:
    {
        QString str;
        if(m_ButtonId == MarkdownEditorToolButton::ID_H1)
            str = QString::fromUtf8("#");
        else if(m_ButtonId == MarkdownEditorToolButton::ID_H2)
            str = QString::fromUtf8("##");
        else if(m_ButtonId == MarkdownEditorToolButton::ID_H3)
            str = QString::fromUtf8("###");
        else if(m_ButtonId == MarkdownEditorToolButton::ID_H4)
            str = QString::fromUtf8("####");
        else if(m_ButtonId == MarkdownEditorToolButton::ID_H5)
            str = QString::fromUtf8("#####");
        else if(m_ButtonId == MarkdownEditorToolButton::ID_H6)
            str = QString::fromUtf8("######");

        m_editorWidget->gotoLineEnd();
        m_editorWidget->insertLineBelow();
        m_editorWidget->insertPlainText(str);
        break;
    }

    case MarkdownEditorToolButton::ID_HorizonalRule:
    case MarkdownEditorToolButton::ID_Tastlist:
    case MarkdownEditorToolButton::ID_Link:
    case MarkdownEditorToolButton::ID_MathFormula:
    case MarkdownEditorToolButton::ID_Image:
    case MarkdownEditorToolButton::ID_Table:
    case MarkdownEditorToolButton::ID_FlowChart:
    case MarkdownEditorToolButton::ID_SequenceDiagram:
    {
        QString str;
        if(m_ButtonId == MarkdownEditorToolButton::ID_HorizonalRule)
            str = QString::fromUtf8("---");
        else if(m_ButtonId == MarkdownEditorToolButton::ID_Tastlist)
            str = QString::fromUtf8("\n- [ ] Incomplete Task\n- [x] Complete Tast");
        else if(m_ButtonId == MarkdownEditorToolButton::ID_Link)
            str = QString::fromUtf8("[Google](http://www.google.com/)");
        else if(m_ButtonId == MarkdownEditorToolButton::ID_MathFormula)
            str = QString::fromUtf8("$$E=mc^2$$");
        else if(m_ButtonId == MarkdownEditorToolButton::ID_Image)
            str = QString::fromUtf8("![image](/path/to/img.jpg \"Optional title\")");
        else if(m_ButtonId == MarkdownEditorToolButton::ID_Table)
            str.append(QString::fromUtf8("header 1 | header 2\n---|---\nrow 1 col 1 | row 1 col 2\n\
row 2 col 1 | row 2 col 2"));
        else if(m_ButtonId == MarkdownEditorToolButton::ID_FlowChart)
            str.append(QString::fromUtf8("```flow\nst=>start: Start:>http://www.google.com[blank]\n\
e=>end:>http://www.google.com\n\op1=>operation: My Operation\nsub1=>subroutine: My Subroutine\n\
cond=>condition: Yes\nio=>inputoutput: catch something...\n\nst->op1->cond\n\
cond(yes)->io->e\ncond(no)->sub1(right)->op1\n```"));
        else if(m_ButtonId == MarkdownEditorToolButton::ID_SequenceDiagram)
            str.append(QString::fromUtf8("```sequence\nTitle: Here is a title\n\
A->B: Normal line\nB-->C: Dashed line\nC->>D: Open arrow\nD-->>A: Dashed open arrow\n\
Note right of D: Note right of D\n```"));

        m_editorWidget->gotoLineEnd();
        m_editorWidget->insertLineBelow();
        m_editorWidget->insertPlainText(str);
        m_editorWidget->insertLineBelow();
        break;
    }
    case MarkdownEditorToolButton::ID_Help:
    {
        if(!helpDlg)
        {
            helpDlg = new MarkdownEditorHelpDialog(m_editorWidget);
        }
        helpDlg->show();
    }
    default:
        break;
    }
}
}

namespace MDEditor {
MarkdownEditorToolButton::MarkdownEditorToolButton(ButtonId id, QWidget* parent)
    :QToolButton(parent), d(new MarkdownEditorToolButtonPrivate)
{
    setButtonId(id);
}

MarkdownEditorToolButton::~MarkdownEditorToolButton()
{
    delete d;
}

void MarkdownEditorToolButton::doAction()
{
    d->apply();
}

MarkdownEditorToolButton::ButtonId MarkdownEditorToolButton::buttonId() const
{
    return d->m_ButtonId;
}

void MarkdownEditorToolButton::setButtonId(ButtonId id)
{
    d->m_ButtonId = id;
    QImage img;
    QString tooltips;
    switch (id) {
    case ID_Bold:
        tooltips = QString::fromUtf8("Bold");
        img = QImage(QLatin1String(":/mdeditor/icons/bold.png"));
        break;
    case ID_Italic:
        tooltips = QString::fromUtf8("Italic");
        img = QImage(QLatin1String(":/mdeditor/icons/italic.png"));
        break;
    case ID_StrikeThrough:
        img = QImage(QLatin1String(":/mdeditor/icons/strikethrough.png"));
        tooltips = QString::fromUtf8("Strike Through");
        break;
    case ID_H1:
        setText(QString::fromUtf8("H1"));
        break;
    case ID_H2:
        setText(QString::fromUtf8("H2"));
        break;
    case ID_H3:
        setText(QString::fromUtf8("H3"));
        break;
    case ID_H4:
        setText(QString::fromUtf8("H4"));
        break;
    case ID_H5:
        setText(QString::fromUtf8("H5"));
        break;
    case ID_H6:
        setText(QString::fromUtf8("H6"));
        break;
    case ID_HorizonalRule:
        img = QImage(QLatin1String(":/mdeditor/icons/line.png"));
        tooltips = QString::fromUtf8("Horizonal Rule");
        break;
    case ID_Tastlist:
        img = QImage(QLatin1String(":/mdeditor/icons/tasklist.png"));
        tooltips = QString::fromUtf8("Task List");
        break;
    case ID_Link:
        img = QImage(QLatin1String(":/mdeditor/icons/link.png"));
        tooltips = QString::fromUtf8("Link");
        break;
    case ID_Image:
        img = QImage(QLatin1String(":/mdeditor/icons/image.png"));
        tooltips = QString::fromUtf8("Image");
        break;
    case ID_Table:
        img = QImage(QLatin1String(":/mdeditor/icons/table.png"));
        tooltips = QString::fromUtf8("Table");
        break;
    case ID_MathFormula:
        img = QImage(QLatin1String(":/mdeditor/icons/math.png"));
        tooltips = QString::fromUtf8("Math Formula");
        break;
    case ID_Code:
        img = QImage(QLatin1String(":/mdeditor/icons/code.png"));
        tooltips = QString::fromUtf8("Code");
        break;
    case ID_FlowChart:
        img = QImage(QLatin1String(":/mdeditor/icons/flow.png"));
        tooltips = QString::fromUtf8("Flow Chart");
        break;
    case ID_SequenceDiagram:
        img = QImage(QLatin1String(":/mdeditor/icons/sequence.png"));
        tooltips = QString::fromUtf8("Sequence Diagram");
        break;

    case ID_Help:
        img = QImage(QLatin1String(":/mdeditor/icons/help.png"));
        tooltips = QString::fromUtf8("Help Contents");
        break;
    default:
        break;
    }
    if(!img.isNull())
    {
        int h, s, v, a;
        for(int i = 0; i< img.width(); i++)
        {
            for(int j = 0; j < img.height(); j++)
            {
                QRgb rgb = img.pixel(i,j);
                QColor cl(rgb);
                cl.setAlpha(qAlpha(rgb));
                cl.getHsv(&h, &s, &v, &a);
                cl.setHsv(h, s, 255 - v, a);
                img.setPixel(i, j, cl.rgba());
            }
        }
        setIcon(QIcon(QPixmap::fromImage(img)));
    }
    setToolTip(tooltips);
}

void MarkdownEditorToolButton::setEditorWidget(TextEditor::TextEditorWidget* widget)
{
    d->m_editorWidget = widget;
}
}
