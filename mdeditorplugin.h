#ifndef MDEDITORPLUGIN_H
#define MDEDITORPLUGIN_H

#include "mdeditor_global.h"

#include <extensionsystem/iplugin.h>

namespace MDEditor {
namespace Internal {
class MDEDITORSHARED_EXPORT MDEditorPlugin : public ExtensionSystem::IPlugin
{
    Q_OBJECT
    Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QtCreatorPlugin" FILE "MDEditor.json")

public:
    MDEditorPlugin();
    ~MDEditorPlugin();

    static MDEditorPlugin *instance();
    bool initialize(const QStringList &arguments, QString *errorString);
    void extensionsInitialized();
    ShutdownFlag aboutToShutdown();

private slots:
    void triggerAction();
private:
    static MDEditorPlugin* m_instance;
};

} // namespace Internal
} // namespace MDEditor

#endif // MDEDITORPLUGIN_H

