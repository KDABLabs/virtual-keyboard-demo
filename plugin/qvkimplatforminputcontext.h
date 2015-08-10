#ifndef QVKIMPLATFORMINPUTCONTEXT_H
#define QVKIMPLATFORMINPUTCONTEXT_H

#include <qpa/qplatforminputcontext.h>

QT_BEGIN_NAMESPACE

class QDBusInterface;

class QVkImPlatformInputContext : public QPlatformInputContext
{
    Q_OBJECT

public:
    QVkImPlatformInputContext();
    ~QVkImPlatformInputContext();

    bool isValid() const Q_DECL_OVERRIDE;
    void setFocusObject(QObject *object) Q_DECL_OVERRIDE;

    void showInputPanel() Q_DECL_OVERRIDE;
    void hideInputPanel() Q_DECL_OVERRIDE;
    bool isInputPanelVisible() const Q_DECL_OVERRIDE;

private slots:
    void keyboardSpecialKeyClicked(int key);
    void keyboardKeyClicked(const QString &character);

private:
    QDBusInterface *m_keyboardInterface;

    QObject *m_focusObject;
};

QT_END_NAMESPACE

#endif
