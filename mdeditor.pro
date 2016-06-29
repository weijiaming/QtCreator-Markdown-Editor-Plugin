DEFINES += MDEDITOR_LIBRARY

INCLUDEPATH += $$PWD

HEADERS += \
    mdeditorplugin.h \
    mdeditorconstants.h \
    markdownwizard.h \
    markdowneditor.h \
    markdowneditorwidget.h \
    markdowneditortoolbutton.h \
    markdownconverterinterface.h \
    discontconverter.h \
    pandocconverter.h \
    markdown2htmlconverter.h

SOURCES += \
    mdeditorplugin.cpp \
    markdownwizard.cpp \
    markdowneditor.cpp \
    markdowneditorwidget.cpp \
    markdowneditortoolbutton.cpp \
    discontconverter.cpp \
    pandocconverter.cpp \
    markdown2htmlconverter.cpp

FORMS += \

RESOURCES += \
    mdeditor.qrc

QTC_PLUGIN_RECOMMENDS += \

include(../../qtcreatorplugin.pri)

