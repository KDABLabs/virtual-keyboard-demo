#include "qvkimplatforminputcontext.h"

#include <QDBusConnection>
#include <QDBusInterface>
#include <QDBusReply>
#include <QGuiApplication>
#include <QInputMethodEvent>
#include <QWidget>

QVkImPlatformInputContext::QVkImPlatformInputContext()
    : m_focusObject(0)
{
    m_keyboardInterface = new QDBusInterface("com.kdab.inputmethod", "/VirtualKeyboard", "local.server.Keyboard", QDBusConnection::sessionBus(), this);

    connect(m_keyboardInterface, SIGNAL(keyClicked(QString)), SLOT(keyboardKeyClicked(QString)));
    connect(m_keyboardInterface, SIGNAL(specialKeyClicked(int)), SLOT(keyboardSpecialKeyClicked(int)));
}

QVkImPlatformInputContext::~QVkImPlatformInputContext()
{
}

bool QVkImPlatformInputContext::isValid() const
{
    return m_keyboardInterface->isValid();
}

void QVkImPlatformInputContext::setFocusObject(QObject *object)
{
    m_focusObject = object;
}

void QVkImPlatformInputContext::showInputPanel()
{
    QPoint globalPos(0, 0);

    QWidget *widget = qobject_cast<QWidget*>(m_focusObject);
    if (widget)
        globalPos = widget->mapToGlobal(QPoint(0, widget->height()));

    m_keyboardInterface->call("showKeyboard", globalPos.x(), globalPos.y());
}

void QVkImPlatformInputContext::hideInputPanel()
{
    m_keyboardInterface->call("hideKeyboard");
}

bool QVkImPlatformInputContext::isInputPanelVisible() const
{
    const QDBusReply<bool> reply = m_keyboardInterface->call("keyboardVisible");

    if (reply.isValid())
        return reply.value();
    else
        return false;
}

void QVkImPlatformInputContext::keyboardSpecialKeyClicked(int key)
{
    if (!m_focusObject)
        return;

    if (key == Qt::Key_Enter) {
        QKeyEvent *pressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_Enter, Qt::NoModifier);
        QGuiApplication::postEvent(m_focusObject, pressEvent);

        QKeyEvent *releaseEvent = new QKeyEvent(QEvent::KeyRelease, Qt::Key_Enter, Qt::NoModifier);
        QGuiApplication::postEvent(m_focusObject, releaseEvent);
    } else if (key == Qt::Key_Backspace) {
        QKeyEvent *pressEvent = new QKeyEvent(QEvent::KeyPress, Qt::Key_Backspace, Qt::NoModifier);
        QGuiApplication::postEvent(m_focusObject, pressEvent);

        QKeyEvent *releaseEvent = new QKeyEvent(QEvent::KeyRelease, Qt::Key_Backspace, Qt::NoModifier);
        QGuiApplication::postEvent(m_focusObject, releaseEvent);
    }
}

void QVkImPlatformInputContext::keyboardKeyClicked(const QString &characters)
{
    if (!m_focusObject)
        return;

    QInputMethodEvent event;
    event.setCommitString(characters);

    QGuiApplication::sendEvent(m_focusObject, &event);
}
