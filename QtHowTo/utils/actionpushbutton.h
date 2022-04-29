#ifndef ACTIONPUSHBUTTON_H
#define ACTIONPUSHBUTTON_H

#include <QAction>
#include <QPushButton>

class ActionPushButton: public QPushButton {
    Q_OBJECT

private:
    QAction *actionOwner = nullptr;

public:
    explicit ActionPushButton(QWidget *parent = nullptr);
    explicit ActionPushButton(const QString &text, QWidget *parent = nullptr);
    void setAction(QAction *action);

signals:


public slots:
    void updateButtonStatusFromAction();

};

#endif // ACTIONPUSHBUTTON_H
