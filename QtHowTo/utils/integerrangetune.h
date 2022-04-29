#ifndef INTEGERRANGETUNE_H
#define INTEGERRANGETUNE_H

#include <QWidget>

QT_BEGIN_NAMESPACE
class QSpinBox;
QT_END_NAMESPACE

class IntegerRangeTune: public QWidget {
    Q_OBJECT

private:
    int currentStart;
    int currentEnd;
    QSpinBox *startBox;
    QSpinBox *endBox;

public:
    explicit IntegerRangeTune(int defaultRangeMin = 0, int defaultRangeMax = 0,
                              int defaultStart = 0, int defaultEnd = 0,
                              int singleStep = 1, QWidget *parent = nullptr);

signals:
    void changedStartEnd(int start, int end);

public slots:
    void setRange(int rangeMin, int rangeMax);
    void setStart(int start);
    void setEnd(int end);
};

#endif // INTEGERRANGETUNE_H
