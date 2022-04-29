#ifndef DESCRIPTIONCHECKBOX_H
#define DESCRIPTIONCHECKBOX_H

#include <QCheckBox>

class DescriptionCheckBox: public QCheckBox {
    Q_OBJECT

private:
    QString description;

public:
    explicit DescriptionCheckBox(QWidget *parent = nullptr);
    explicit DescriptionCheckBox(const QString &text, QWidget *parent = nullptr);
    void setDescription(const QString &_description);

protected:
    void hoverEnter(QHoverEvent *event);
    void hoverLeave(QHoverEvent *event);
    void hoverMove(QHoverEvent *event);
    bool event(QEvent *event);

signals:
    void onDescription(QString description);
};

#endif // DESCRIPTIONCHECKBOX_H
