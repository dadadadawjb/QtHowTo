#ifndef DATASETLOADER_H
#define DATASETLOADER_H

#include <QThread>

#include "loaditems.h"

/*DatasetLoader
 * how to use QThread
 * how to load csv file
 */
class DatasetLoader: public QThread {
    Q_OBJECT

private:
    QString filePath;
    loadItems *myLoadItemsPtr;
    int percent;

public:
    DatasetLoader(const QString &_filePath, loadItems *_myLoadItemsPtr, QObject *parent = nullptr);

    void load();

protected:
    void run() override;

signals:
    void setPercent(int currentPercent);
    void isEmpty();
    void cannotOpen(const QString &errorMessage);
    void normal(const DatasetLoader *itself);
    void finish();

};

#endif // DATASETLOADER_H
