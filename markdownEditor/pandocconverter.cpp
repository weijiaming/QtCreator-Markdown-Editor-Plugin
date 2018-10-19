#include "pandocconverter.h"

#include <coreplugin/icore.h>

#include <QProcess>
#include <QFileInfo>
#include <QFile>
#include <QMap>

using namespace MDEditor;

QUrl PandocConverter::convert(const Utils::FileName originalFileName, const QString& input)
{
    initHiddenFolder(originalFileName);

    /// 其实效果挺不错的，但依赖外部软件Pandoc，也废弃了
    QString infileName = originalFileName.toString()+QLatin1String("temp");
//    parentDir().appendPath(QLatin1String(".markdown-to-html"))
//            .appendPath(originalFileName.fileName()).toString();

    QFileInfo fileinfo(originalFileName.toString());
    QString outfileName = originalFileName.parentDir().appendPath(
                fileinfo.baseName() + QString::fromLatin1(".html")).toString();

        /// init input file
    QFile infile(infileName);
    infile.open(QFile::ReadWrite);
    infile.write(input.toUtf8());
    infile.close();
    QMap<QByteArray, QByteArray> flowResults = convertFlowContents(infileName);
    QMap<QByteArray, QByteArray> seqResults = convertSequenceContents(infileName);

    if(QFile::exists(outfileName))
        QFile::remove(outfileName);
    QString command = QString::fromLatin1("pandoc -f markdown --smart --css=css/style.css --mathjax=.markdown/MathJax/MathJax.js?config=TeX-AMS_SVG -t html5 %1 -o %2 ")
            .arg(infileName).arg(outfileName);

    QProcess process;
    process.start(command);
    process.waitForFinished();
    QFile::remove(infileName);

    applyAdditionalResults(outfileName,flowResults);
    applyAdditionalResults(outfileName,seqResults);

    QString url = QString::fromLatin1("file://") + outfileName;
    return QUrl(url);
}

QMap<QByteArray, QByteArray> PandocConverter::convertFlowContents(const QString& fileName)
{
    QMap<QByteArray, QByteArray> results;
    QFile file(fileName);
    bool bOk = file.open(QFile::ReadWrite);
    if(!bOk)
        return results;

    QByteArray beginFlag("```flow");
    QByteArray endFlag("```");
    QByteArray ba = file.readAll();

    if(!ba.contains(beginFlag))
    {
        file.close();
        return results;
    }

    QList<QByteArray>baList = ba.split('\n');
    QList<QByteArray>baListCopy;

    QList<QByteArray>::iterator beginIter;
    QList<QByteArray>::iterator endIter;
    QList<QByteArray>::iterator it;
    int diagramNum = 1;

    for(it = baList.begin(); it != baList.end(); ++it)
    {
        if(*it == beginFlag)
        {
            beginIter = it;
            for(endIter = beginIter;endIter != baList.end(); ++endIter)
            {
                if(*endIter == endFlag)
                {
                    it = endIter;
                    break;
                }
            }
            QList<QByteArray> flowArrayList;
            for(QList<QByteArray>::iterator tempIt = beginIter; tempIt <= endIter; ++tempIt)
            {
                if(*tempIt != beginFlag && *tempIt != endFlag)
                {
                    QByteArray b = *tempIt;
                    b.replace(QByteArray("\\"), QByteArray("\\\\"));
                    flowArrayList.append(b);
                }
            }
            QByteArray flowInput = flowArrayList.join(QByteArray("\\n"));
            QByteArray flowOutput;
            QByteArray diagramFlag = QByteArray("diagram")+ QString::fromLatin1("%1").arg(diagramNum, 5, 10, QChar(QLatin1Char('0'))).toUtf8();
            {
                flowOutput.append(QByteArray("\
<p><script src=\".markdown/uml.js\"></script>\n \
<div id=\"%diagram\"></div>\n \
<script>\n "));

                flowOutput.append(QByteArray("\
var code = \'%code\';\n"));

                flowOutput.append(QByteArray("\
var diagram = flowchart.parse(code);\n \
diagram.drawSVG(\'%diagram\', {\n \
                              \'x\': 0,\n \
                              \'y\': 0,\n \
                              \'line-width\': 3,\n \
                              \'line-length\': 50,\n \
                              \'text-margin\': 10,\n \
                              \'font-size\': 14,\n \
                              \'font-color\': \'black\',\n \
                              \'line-color\': \'black\',\n \
                              \'element-color\': \'black\',\n \
                              \'fill\': \'white\',\n \
                              \'yes-text\': \'yes\',\n \
                              \'no-text\': \'no\',\n \
                              \'arrow-end\': \'block\',\n \
                              \'scale\': 1,\n \
                              \'symbols\': {\n \
                                \'start\': {\n \
                                  \'font-color\': \'red\',\n \
                                  \'element-color\': \'green\',\n \
                                  \'fill\': \'yellow\'\n \
                                },\n \
                                \'end\':{\n \
                                  \'class\': \'end-element\'\n \
                                }\n \
                              },\n \
                              \'flowstate\' : {\n \
                                \'past\' : { \'fill\' : \'#CCCCCC\', \'font-size\' : 12},\n \
                                \'current\' : {\'fill\' : \'yellow\', \'font-color\' : \'red\', \'font-weight\' : \'bold\'},\n \
                                \'future\' : { \'fill\' : \'#FFFF99\'},\n \
                                \'request\' : { \'fill\' : \'blue\'},\n \
                                \'invalid\': {\'fill\' : \'#444444\'},\n \
                                \'approved\' : { \'fill\' : \'#58C4A3\', \'font-size\' : 12, \'yes-text\' : \'APPROVED\', \'no-text\' : \'n/a\' },\n \
                                \'rejected\' : { \'fill\' : \'#C45879\', \'font-size\' : 12, \'yes-text\' : \'n/a\', \'no-text\' : \'REJECTED\' }\n \
                              }\n \
                            });\n \
</script></p>\n "));
                flowOutput.replace(QByteArray("%code"), flowInput);
                flowOutput.replace(QByteArray("%diagram"), diagramFlag);
                diagramNum++;
            }
            QByteArray resultFlag = QByteArray("____TemporotyFlow"+ diagramFlag);
            baListCopy.append(resultFlag);
            results.insert(resultFlag,flowOutput);
        }
        else
            baListCopy.append(*it);
    }
    file.close();
    file.remove();
    file.open(QFile::ReadWrite);
    file.write(baListCopy.join("\n"));
    file.close();
    return results;
}

QMap<QByteArray, QByteArray> PandocConverter::convertSequenceContents(const QString& fileName)
{
    QMap<QByteArray, QByteArray> results;
    QFile file(fileName);
    bool bOk = file.open(QFile::ReadWrite);
    if(!bOk)
        return results;

    QByteArray beginFlag("```sequence");
    QByteArray endFlag("```");
    QByteArray ba = file.readAll();

    if(!ba.contains(beginFlag))
    {
        file.close();
        return results;
    }
    QList<QByteArray>baList = ba.split('\n');
    QList<QByteArray>baListCopy;

    QList<QByteArray>::iterator beginIter;
    QList<QByteArray>::iterator endIter;
    QList<QByteArray>::iterator it;
    int diagramNum = 1;

    for(it = baList.begin(); it != baList.end(); ++it)
    {
        if(*it == beginFlag)
        {
            beginIter = it;
            for(endIter = beginIter;endIter != baList.end(); ++endIter)
            {
                if(*endIter == endFlag)
                {
                    it = endIter;
                    break;
                }
            }
            QList<QByteArray> flowArrayList;
            for(QList<QByteArray>::iterator tempIt = beginIter; tempIt <= endIter; ++tempIt)
            {
                if(*tempIt != beginFlag && *tempIt != endFlag)
                {
                    QByteArray b = *tempIt;
                    b.replace(QByteArray("\\"), QByteArray("\\\\"));
                    flowArrayList.append(b);
                }
            }
            QByteArray flowInput = flowArrayList.join(QByteArray("\\n"));
            QByteArray flowOutput;
            QByteArray diagramFlag = QByteArray("Diagram")+ QString::fromLatin1("%1").arg(diagramNum, 5, 10, QChar(QLatin1Char('0'))).toUtf8();
            {
                flowOutput.append(QByteArray("\
<script src=\".markdown/uml.js\"></script>\n \
<div id=\"%diagram\"></div>\n \
<script>\n "));

                flowOutput.append(QByteArray("\
var code = \'%code\';\n"));

                flowOutput.append(QByteArray("\
var diagram = Diagram.parse(code);\n \
diagram.drawSVG(\'%diagram\', {theme: \'simple\'});\n \
</script>\n "));
                flowOutput.replace(QByteArray("%code"), flowInput);
                flowOutput.replace(QByteArray("%diagram"), diagramFlag);
                diagramNum++;
            }
            QByteArray resultFlag = QByteArray("____TemporotySequence"+ diagramFlag);
            baListCopy.append(resultFlag);
            results.insert(resultFlag,flowOutput);
        }
        else
            baListCopy.append(*it);

    }
    file.close();
    file.remove();
    file.open(QFile::ReadWrite);
    file.write(baListCopy.join("\n"));
    file.close();
    return results;
}

void PandocConverter::applyAdditionalResults(const QString& fileName,const QMap<QByteArray, QByteArray>&results)
{
    if(results.isEmpty())
        return;

    QFile file(fileName);
    bool bOk = file.open(QFile::ReadWrite);
    if(!bOk)
        return;
    QByteArray ba = file.readAll();
    QList<QByteArray> baList = ba.split('\n');
    QList<QByteArray> keys = results.keys();
    for(int i = 0; i< baList.size(); i++) {
        foreach (const QByteArray& key, keys) {
            if(baList.at(i).contains(key))
            {
                baList[i] = results.value(key);
            }
        }
    }
    file.close();
    file.remove();
    file.open(QFile::ReadWrite);
    file.write(baList.join('\n'));
    file.close();
}

void PandocConverter::initHiddenFolder(const Utils::FileName inputFileName)
{
    Utils::FileName targetPath = inputFileName.parentDir();
    QFileInfo fi(targetPath.toString() + QLatin1String("/.markdown"));
    if(fi.exists())
        return;
    QString sourcePkg = Core::ICore::userResourcePath() + QLatin1Char('/')
            + QLatin1String("markdown.tar.gz");

    fi = QFileInfo(sourcePkg);
    if(!fi.exists())
    {
        sourcePkg = Core::ICore::resourcePath() + QLatin1Char('/')
                + QLatin1String("markdown.tar.gz");
        fi = QFileInfo(sourcePkg);
    }

    if(fi.exists())
    {
        QString extractCmd = QString::fromLatin1("tar zxvf %1 -C %2").arg(sourcePkg).arg(targetPath.toString());
        QProcess process;
        process.start(extractCmd);
        process.waitForFinished();
    }
}
