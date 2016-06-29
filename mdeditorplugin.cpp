#include "mdeditorplugin.h"
#include "mdeditorconstants.h"
#include "markdownwizard.h"
#include "markdowneditor.h"

#include <coreplugin/icore.h>
#include <coreplugin/icontext.h>
#include <coreplugin/iwizardfactory.h>
#include <coreplugin/actionmanager/actionmanager.h>
#include <coreplugin/actionmanager/command.h>
#include <coreplugin/actionmanager/actioncontainer.h>
#include <coreplugin/coreconstants.h>

#include <utils/mimetypes/mimedatabase.h>

#include <QAction>
#include <QMessageBox>
#include <QMainWindow>
#include <QMenu>

#include <QtPlugin>
using namespace MDEditor;
using namespace MDEditor::Internal;

MDEditorPlugin* MDEditorPlugin::m_instance = 0;
MDEditorPlugin::MDEditorPlugin()
{
    m_instance = this;
    // Create your members
}

MDEditorPlugin::~MDEditorPlugin()
{
    // Unregister objects from the plugin manager's object pool
    // Delete members
}

MDEditorPlugin *MDEditorPlugin::instance()
{
    return m_instance;
}

static const char wizardCategoryC[] = "U.General";

static inline QString wizardDisplayCategory()
{
    return MDEditorPlugin::tr("General");
}


bool MDEditorPlugin::initialize(const QStringList &arguments, QString *errorString)
{
    Q_UNUSED(arguments)
    Q_UNUSED(errorString)

    Utils::MimeDatabase::addMimeTypes(QLatin1String(":/mdeditor/MDEditor.mimetypes.xml"));

    addAutoReleasedObject(new MDEditorFactory(this));

    Core::IWizardFactory::registerFactoryCreator([]() { return QList<Core::IWizardFactory *>() << new MarkdownWizard; });

    return true;
}

void MDEditorPlugin::extensionsInitialized()
{
    // Retrieve objects from the plugin manager's object pool
    // In the extensionsInitialized function, a plugin can be sure that all
    // plugins that depend on it are completely initialized.
}

ExtensionSystem::IPlugin::ShutdownFlag MDEditorPlugin::aboutToShutdown()
{
    // Save settings
    // Disconnect from signals that are not needed during shutdown
    // Hide UI (if you add UI that is not in the main window directly)
    return SynchronousShutdown;
}

void MDEditorPlugin::triggerAction()
{
    QMessageBox::information(Core::ICore::mainWindow(),
                             tr("Action triggered"),
                             tr("This is an action from MDEditor."));
}

