#include "actionpushbutton.h"

ActionPushButton::ActionPushButton(QWidget *parent): QPushButton{parent} {

}

ActionPushButton::ActionPushButton(const QString &text, QWidget *parent): QPushButton{parent} {
    this->setText(text);
}

void ActionPushButton::setAction(QAction *action) {
    if (actionOwner && actionOwner != action) {
       disconnect(actionOwner, &QAction::changed,
                  this, &ActionPushButton::updateButtonStatusFromAction);
       disconnect(this, &ActionPushButton::clicked,
                  actionOwner, &QAction::trigger);
    }
    actionOwner = action;
    updateButtonStatusFromAction();
    connect(action, &QAction::changed,
            this, &ActionPushButton::updateButtonStatusFromAction);
    connect(this, &ActionPushButton::clicked,
            actionOwner, &QAction::trigger);
}

void ActionPushButton::updateButtonStatusFromAction() {
   if (!actionOwner)
       return;
   setText(actionOwner->text());
   setStatusTip(actionOwner->statusTip());
   setToolTip(actionOwner->toolTip());
   setIcon(actionOwner->icon());
   setEnabled(actionOwner->isEnabled());
   setCheckable(actionOwner->isCheckable());
   setChecked(actionOwner->isChecked());
}
