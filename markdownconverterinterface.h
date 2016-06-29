#ifndef MARKDOWNCONVERTERINTERFACE_H
#define MARKDOWNCONVERTERINTERFACE_H
#include "utils/fileutils.h"
#include <QUrl>
namespace MDEditor {
class MarkdownConverterInterface
{
public:
    MarkdownConverterInterface() {}
    virtual ~MarkdownConverterInterface(){}

    virtual QUrl convert(const Utils::FileName inputFileName, const QString& inputContents) = 0;
};
}

#endif // MARKDOWNCONVERTERINTERFACE_H
