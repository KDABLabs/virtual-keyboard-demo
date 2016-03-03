#ifndef KEYBOARD_H
#define KEYBOARD_H

#include <QWidget>

class Keyboard : public QWidget
{
    Q_OBJECT

public:
    explicit Keyboard(QWidget *parent = Q_NULLPTR);

public slots:
    void showKeyboard(int globalX, int globalY);
    void hideKeyboard();
    bool keyboardVisible() const;

signals:
    void specialKeyClicked(int key);
    void keyClicked(const QString &text);

private slots:
    void buttonClicked(int key);
};

#endif
