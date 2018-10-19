#include "discontconverter.h"
#include <QProcess>
#include <QFile>
#include <QFileInfo>
using namespace MDEditor;

QUrl DiscontConverter::convert(const Utils::FileName file, const QString& input)
{
    QString inputFileName = file.toString()+QString::fromLatin1("Temp");
    QFile inputFile(inputFileName);
    if(inputFile.exists())
        inputFile.remove();
    inputFile.open(QIODevice::WriteOnly);
    inputFile.write(input.toUtf8());
    inputFile.close();

    QString outputFileName = QFileInfo(file.toString()).baseName() + QString::fromLatin1(".html");
    outputFileName = QFileInfo(file.toString()).absolutePath() + QString::fromLatin1("/") + outputFileName;

    QString command = QString(QString::fromLatin1("markdown %1")).arg(inputFileName);
    QProcess process;
    process.start(command);
    process.waitForFinished();

    inputFile.remove();
    QString outputstring = QString::fromLatin1(process.readAllStandardOutput());
    QFile outputfile(outputFileName);
    if(outputfile.exists())
        outputfile.remove();
    outputfile.open(QIODevice::WriteOnly);
    outputfile.write(outputstring.toUtf8());
    outputfile.close();
    QString url = QString::fromLatin1("file://") + outputFileName;
    return QUrl(url);
}
