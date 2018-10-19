#ifndef MARKDOWN2HTMLCONVERTER_H
#define MARKDOWN2HTMLCONVERTER_H

#include "markdownconverterinterface.h"
namespace MDEditor {
class Markdown2HtmlConverter:public MarkdownConverterInterface
{
public:
    Markdown2HtmlConverter() {}

    QUrl convert(const Utils::FileName inputFileName, const QString& inputContents) override;

    void initHiddenFolder(const Utils::FileName inputFileName);
};
}

#endif // MARKDOWN2HTMLCONVERTER_H
