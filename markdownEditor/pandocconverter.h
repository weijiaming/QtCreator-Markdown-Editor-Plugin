#ifndef PANDOCCONVERTER_H
#define PANDOCCONVERTER_H

#include "markdownconverterinterface.h"
namespace MDEditor {
class PandocConverter:public MarkdownConverterInterface
{
public:
    PandocConverter() {}

    QUrl convert(const Utils::FileName inputFileName, const QString& inputContents) override;

    QMap<QByteArray, QByteArray> convertFlowContents(const QString& fileName);
    QMap<QByteArray, QByteArray> convertSequenceContents(const QString& fileName);
    void applyAdditionalResults(const QString& fileName,const QMap<QByteArray, QByteArray>&);

    void initHiddenFolder(const Utils::FileName inputFileName);
};
}
#endif // PANDOCCONVERTER_H
