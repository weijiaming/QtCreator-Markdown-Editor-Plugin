#ifndef DISCONTCONVERTER_H
#define DISCONTCONVERTER_H

#include "markdownconverterinterface.h"
namespace MDEditor {
class DiscontConverter : public MarkdownConverterInterface
{
public:
    DiscontConverter() {}

    QUrl convert(const Utils::FileName inputFileName, const QString& inputContents) override;

};
}

#endif // DISCONTCONVERTER_H
