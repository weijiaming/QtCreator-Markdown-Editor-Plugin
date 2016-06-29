#include "markdown2htmlconverter.h"

#include <coreplugin/icore.h>

#include <QFile>
#include <QFileInfo>

using namespace MDEditor;

QUrl Markdown2HtmlConverter::convert(const Utils::FileName originalFileName, const QString& initContents)
{
    initHiddenFolder(originalFileName);

    QFileInfo fileinfo(originalFileName.toString());
    QString outfileName = originalFileName.parentDir().appendPath(
                fileinfo.baseName() + QString::fromLatin1(".html")).toString();

    /// init input file
    QString outputContents;
    outputContents.append(QString::fromUtf8("<!DOCTYPE html>\n \
<html>\n\
<head>\n\
<meta http-equiv=\"Content-Type\" content=\"text/html; charset=utf-8\">\n\
<link href=\".markdown/css/bootstrap.min.css\" rel=\"stylesheet\">\n\
<link href=\".markdown/css/style.css\" rel=\"stylesheet\">\n\
<style>\n\
textarea {display: none}\n\
</style>\n\
</head>\n\
\n\
<body>\n\
    <div id=\"content\"></div>\n\
    <textarea id=\"md\">%initContents\n\
</textarea> \n\
    <script src=\".markdown/markdown-to-html.min.js\"></script>\n\
<script>\n\
     markdownToHtml(document.getElementById(\'md\').value, document.getElementById(\'content\'));\n\
</script>\n\
</body>\n\n\
</html>\n\n"));
    outputContents.replace(QString::fromUtf8("%initContents"),initContents);
    QFile outfile(outfileName);
    if(outfile.exists())
         outfile.remove();
    outfile.open(QFile::ReadWrite);
    outfile.write(outputContents.toUtf8());
    outfile.close();

    QString url = QString::fromLatin1("file://") + outfileName;
    return QUrl(url);
}

void Markdown2HtmlConverter::initHiddenFolder(const Utils::FileName inputFileName)
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
        system((const char*)extractCmd.toLocal8Bit());
    }
}
