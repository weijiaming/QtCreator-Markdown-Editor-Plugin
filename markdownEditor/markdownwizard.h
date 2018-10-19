#ifndef MARKDOWNWIZARD_H
#define MARKDOWNWIZARD_H

#include <coreplugin/basefilewizard.h>
#include <coreplugin/basefilewizardfactory.h>
#include <utils/wizard.h>
#include "mdeditorplugin.h"

namespace Utils { class FileWizardPage; }

namespace MDEditor {
namespace Internal {

class MarkdownWizardDialog : public Core::BaseFileWizard
{
    Q_OBJECT

public:
    explicit MarkdownWizardDialog(const Core::BaseFileWizardFactory *factory, QWidget *parent = 0);

    QString path() const;
    void setPath(const QString &path);

    QString projectName() const;

    Utils::FileWizardPage *m_firstPage;
};

class MarkdownWizard : public Core::BaseFileWizardFactory
{
    Q_OBJECT

public:
    MarkdownWizard();

protected:
    Core::BaseFileWizard *create(QWidget *parent, const Core::WizardDialogParameters &parameters) const;
    Core::GeneratedFiles generateFiles(const QWizard *w, QString *errorMessage) const override;
    bool postGenerateFiles(const QWizard *w, const Core::GeneratedFiles &l,
                           QString *errorMessage) const override;
};

} // namespace Internal
} // namespace MDEditor

#endif // MARKDOWNWIZARD_H
