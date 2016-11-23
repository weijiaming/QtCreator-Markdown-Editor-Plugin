#include "markdowneditorhelpdialog.h"
#include "ui_markdowneditorhelpdialog.h"

MarkdownEditorHelpDialog::MarkdownEditorHelpDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::MarkdownEditorHelpDialog)
{
    ui->setupUi(this);
    QImage  img = QImage(QLatin1String(":/mdeditor/icons/markdown.png"));

    ui->logo_label->setPixmap(QPixmap::fromImage(img).scaled(QSize(128,128)));
    ui->logo_label->setText(QString::null);

    ui->label->adjustSize();
    ui->label->setGeometry(QRect(328, 240, 329, 27*4));  //四倍行距
    ui->label->setWordWrap(true);
    ui->label->setAlignment(Qt::AlignTop);

    ui->label->setOpenExternalLinks(true);
}

MarkdownEditorHelpDialog::~MarkdownEditorHelpDialog()
{
    delete ui;
}
