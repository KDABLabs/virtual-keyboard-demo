#include <QApplication>
#include <QDBusConnection>

#include "keyboard.h"

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    if (!QDBusConnection::sessionBus().registerService("com.kdab.inputmethod")) {
        qFatal("Unable to register at DBus");
        return 1;
    }

    Keyboard keyboard;

    if (!QDBusConnection::sessionBus().registerObject("/VirtualKeyboard", &keyboard, QDBusConnection::ExportAllSignals | QDBusConnection::ExportAllSlots)) {
        qFatal("Unable to register object at DBus");
        return 1;
    }

    return app.exec();
}
