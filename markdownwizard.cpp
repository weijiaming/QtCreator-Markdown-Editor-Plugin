#include "markdownwizard.h"
#include "mdeditorconstants.h"

#include <coreplugin/icore.h>
#include <projectexplorer/projectexplorerconstants.h>
#include <projectexplorer/customwizard/customwizard.h>

#include <utils/filewizardpage.h>
#include <utils/mimetypes/mimedatabase.h>

#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QFileInfo>
#include <QPainter>
#include <QPixmap>
#include <QStyle>

namespace MDEditor {
namespace Internal {

MarkdownWizardDialog::MarkdownWizardDialog(const Core::BaseFileWizardFactory *factory,
                                                       QWidget *parent) :
    Core::BaseFileWizard(factory, QVariantMap(), parent)
{
    setWindowTitle(tr("Markdown File"));

    // first page
    m_firstPage = new Utils::FileWizardPage;
    m_firstPage->setTitle(tr("Create Markdown File"));
    m_firstPage->setFileNameLabel(tr("File Name:"));
    m_firstPage->setPathLabel(tr("Location:"));
    addPage(m_firstPage);
}

QString MarkdownWizardDialog::path() const
{
    return m_firstPage->path();
}

void MarkdownWizardDialog::setPath(const QString &path)
{
    m_firstPage->setPath(path);
}

QString MarkdownWizardDialog::projectName() const
{
    return m_firstPage->fileName();
}

MarkdownWizard::MarkdownWizard()
{
//    setWizardKind(FileWizard);
    setId("A.Markdown");
    setCategory(QLatin1String(Constants::WIZARD_CATEGORY));
    QString trCat = QCoreApplication::translate(Constants::WIZARD_CATEGORY, Constants::WIZARD_TR_CATEGORY);
    setDisplayCategory(trCat);

    setFlags(Core::IWizardFactory::PlatformIndependent);
    setDescription(tr("Creates a markdown file. The default file extension is <tt>.md</tt>. "
                      "You can specify a different extension as part of the filename."));

    setDisplayName(tr("Markdown"));
    {
        QPixmap icon(22, 22);
        icon.fill(Qt::transparent);
        QPainter p(&icon);
        p.drawPixmap(3, 3, 16, 16, qApp->style()->standardIcon(QStyle::SP_FileIcon).pixmap(16));
        setIcon(icon);
    }
}

Core::BaseFileWizard *MarkdownWizard::create(QWidget *parent,
                                                   const Core::WizardDialogParameters &parameters) const
{
    MarkdownWizardDialog *wizard = new MarkdownWizardDialog(this, parent);

    wizard->setPath(parameters.defaultPath());

    foreach (QWizardPage *p, wizard->extensionPages())
        wizard->addPage(p);

    return wizard;
}

Core::GeneratedFiles MarkdownWizard::generateFiles(const QWizard *w,
                                                         QString *errorMessage) const
{
    Q_UNUSED(errorMessage)

    const MarkdownWizardDialog *wizard = qobject_cast<const MarkdownWizardDialog *>(w);
    const QString projectPath = wizard->path();
    const QDir dir(projectPath);
    const QString projectName = wizard->projectName();
    QString fileName;
    if(projectName.endsWith(QLatin1String(".md")) || projectName.endsWith(QLatin1String(".markdown")))
        fileName = QFileInfo(dir, projectName).absoluteFilePath();
    else
        fileName = QFileInfo(dir, projectName + QLatin1String(".md")).absoluteFilePath();

    Core::GeneratedFile mdFileName(fileName);
    mdFileName.setAttributes(Core::GeneratedFile::OpenEditorAttribute);
    mdFileName.setEditorId(MDEditor::Constants::MDEditor_ID);

    return Core::GeneratedFiles() << mdFileName;
}

bool MarkdownWizard::postGenerateFiles(const QWizard *w, const Core::GeneratedFiles &l,
                                             QString *errorMessage) const
{
    Q_UNUSED(w);
    return ProjectExplorer::CustomProjectWizard::postGenerateOpen(l, errorMessage);
}

} // namespace Internal
} // namespace MDEditor
