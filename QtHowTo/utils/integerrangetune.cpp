#include "integerrangetune.h"

#include <QtWidgets>

IntegerRangeTune::IntegerRangeTune(int defaultRangeMin, int defaultRangeMax,
                                   int defaultStart, int defaultEnd,
                                   int singleStep, QWidget *parent): QWidget{parent} {
    currentStart = defaultStart;
    currentEnd = defaultEnd;

    QHBoxLayout *mainLayout = new QHBoxLayout;

    startBox = new QSpinBox;
    startBox->setRange(defaultRangeMin, defaultRangeMax);
    startBox->setSingleStep(singleStep);
    startBox->setValue(defaultStart);
    connect(startBox, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &IntegerRangeTune::setStart);
    mainLayout->addWidget(startBox);

    QLabel *seperatorLabel = new QLabel("~");
    mainLayout->addWidget(seperatorLabel);

    endBox = new QSpinBox;
    endBox->setRange(defaultRangeMin, defaultRangeMax);
    endBox->setSingleStep(singleStep);
    endBox->setValue(defaultEnd);
    connect(endBox, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged), this, &IntegerRangeTune::setEnd);
    mainLayout->addWidget(endBox);

    setLayout(mainLayout);
}

void IntegerRangeTune::setStart(int start) {
    // no change and stop emitting
    if (start == currentStart)
        return;
    // out of range
    if (start > currentEnd) {
        startBox->setValue(currentStart);
        return;
    }
    currentStart = start;

    emit changedStartEnd(currentStart, currentEnd);
}

void IntegerRangeTune::setEnd(int end) {
    // no change and stop emitting
    if (end == currentEnd)
        return;
    // out of range
    if (end < currentStart) {
        endBox->setValue(currentEnd);
        return;
    }
    currentEnd = end;

    emit changedStartEnd(currentStart, currentEnd);
}

void IntegerRangeTune::setRange(int rangeMin, int rangeMax) {
    startBox->setRange(rangeMin, rangeMax);
    endBox->setRange(rangeMin, rangeMax);

    // deal with original setting
    bool flag = false;
    if (currentStart < rangeMin || currentEnd > rangeMax) {
        // ensure no additional events happen
        currentStart = rangeMin;
        currentEnd = rangeMax;
        startBox->setValue(rangeMin);
        endBox->setValue(rangeMax);
        emit changedStartEnd(currentStart, currentEnd);
        flag = true;
    }
    if (flag == false)
        emit changedStartEnd(currentStart, currentEnd);
}
