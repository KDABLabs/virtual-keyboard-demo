TARGET = vkimplatforminputcontextplugin

QT += dbus gui-private widgets
SOURCES += $$PWD/qvkimplatforminputcontext.cpp \
           $$PWD/main.cpp

HEADERS += $$PWD/qvkimplatforminputcontext.h

OTHER_FILES += $$PWD/vkim.json

PLUGIN_TYPE = platforminputcontexts
PLUGIN_EXTENDS = -
PLUGIN_CLASS_NAME = QVkImPlatformInputContextPlugin
load(qt_plugin)
