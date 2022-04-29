#ifndef DATASETSETUP_H
#define DATASETSETUP_H

#include <QWidget>

#include "loaditems.h"

QT_BEGIN_NAMESPACE
class QLineEdit;
class QPushButton;
class DatasetLoader;
QT_END_NAMESPACE

/*DatasetSetup
 * An encapsulation for dataset loading setup page
 */
class DatasetSetup: public QWidget {
    Q_OBJECT

private:
    QLineEdit *filePathEditor;
    QPushButton *fileOpenButton;
    QPushButton *fileLoadButton;

    QString fileName;

    loadItems *myLoadItemsPtr;

public:
    explicit DatasetSetup(loadItems *_myLoadItemsPtr, QWidget *parent = nullptr);

signals:
    void datasetPathSelected(QString datasetPath);
    void setPercent(int percent);
    void loaded();

private slots:
    void getDatasetPath();
    void loadDataset();
    void processEmpty();
    void processCannotOpen(const QString &errorMessage);
    void processNormal(const DatasetLoader *datasetLoader);
    void processFinished();
};

#endif // DATASETSETUP_H
