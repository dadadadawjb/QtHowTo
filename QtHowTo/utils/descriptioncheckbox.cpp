#include "descriptioncheckbox.h"

#include <QtWidgets>

DescriptionCheckBox::DescriptionCheckBox(QWidget *parent): QCheckBox{parent} {

}

DescriptionCheckBox::DescriptionCheckBox(const QString &text, QWidget *parent): QCheckBox{parent} {
    setText(text);
}

void DescriptionCheckBox::setDescription(const QString &_description) {
    description = _description;
}

bool DescriptionCheckBox::event(QEvent *event) {
    switch (event->type()) {
        case QEvent::HoverEnter:
            hoverEnter(static_cast<QHoverEvent*>(event));
            return true;
            break;
        case QEvent::HoverLeave:
            hoverLeave(static_cast<QHoverEvent*>(event));
            return true;
            break;
        case QEvent::HoverMove:
            hoverMove(static_cast<QHoverEvent*>(event));
            return true;
            break;
        default:
            break;
    }
    return QCheckBox::event(event);
}

void DescriptionCheckBox::hoverEnter(QHoverEvent *) {
    emit onDescription(description);
}

void DescriptionCheckBox::hoverMove(QHoverEvent *) {

}

void DescriptionCheckBox::hoverLeave(QHoverEvent *) {
    emit onDescription(QString());
}
