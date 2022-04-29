#include "datasetloader.h"

#include <QtWidgets>

DatasetLoader::DatasetLoader(const QString &_filePath, loadItems *_myLoadItemsPtr,
                             QObject *parent): QThread(parent) {
    filePath = _filePath;
    myLoadItemsPtr = _myLoadItemsPtr;

    percent = 0;
}

void DatasetLoader::load() {
    if (!isRunning())
        start(LowPriority);
}

void DatasetLoader::run() {
    if (!filePath.isEmpty()) {
        QFile file(filePath);
        if (!file.open(QFile::ReadOnly | QFile::Text)) {
            emit cannotOpen(tr("Cannot read file %1:\n%2.")
                            .arg(QDir::toNativeSeparators(filePath), file.errorString()));
            return;
        }
        emit normal(this);

        QTextStream in(&file);
        // how to get file size
        QFileInfo fileInfo(filePath);
        qint64 fileSize = fileInfo.size();
        // how to use qDebug
        qDebug() << "file size in Btyes: " << fileSize;
        qint64 currentSize = 0;
        in.setCodec("utf8");
//#ifndef QT_NO_CURSOR
//        QGuiApplication::setOverrideCursor(Qt::WaitCursor);
//#endif // QT_NO_CURSOR
        // how to use QElapsedTimer
        QElapsedTimer elapsedTimer;
        elapsedTimer.start();
        int checkingIns = 0;
        QMap<int, int> users;
        QMap<int, int> locations;
        // how to load csv file
        while (!in.atEnd()) {
            QString onelineRawData = in.readLine();
            checkingIns++;
            currentSize += onelineRawData.size() + 2;   // with `\r\n`
            int newPercent = int((double) currentSize * 10000 / fileSize);
            if (newPercent - percent > 1) {
                percent = newPercent;
                emit setPercent(percent);
            }

            QStringList onelineData = onelineRawData.split(",");
            //////////---------- User ID ----------//////////
            int user_id = onelineData.at(0).toInt();
            // how to use QVector
            myLoadItemsPtr->userIDArray.push_back(user_id);
            // how to use QMap
            if (users.contains(user_id))
                users[user_id]++;
            else
                users[user_id] = 1;
            //////////---------- Location ID ----------//////////
            int location_id = onelineData.at(1).toInt();
            myLoadItemsPtr->locationIDArray.push_back(location_id);
            if (locations.contains(location_id))
                locations[location_id]++;
            else
                locations[location_id] = 1;
        }

        // actually progress does not consider these post-process
        myLoadItemsPtr->checkingIns = checkingIns;
        //////////---------- User ID ----------//////////
        myLoadItemsPtr->users = users.size();
        int userMax = 0;
        int maxUser = 0;
        int userMin = -1;
        int minUser = 0;
        for (QMap<int, int>::const_iterator usersIter = users.constBegin();
             usersIter != users.constEnd(); usersIter++) {
            if (usersIter.value() > userMax) {
                maxUser = usersIter.key();
                userMax = usersIter.value();
            }
            if (userMin == -1) {
                minUser = usersIter.key();
                userMin = usersIter.value();
            } else if (usersIter.value() < userMin) {
                minUser = usersIter.key();
                userMin = usersIter.value();
            }
        }
        myLoadItemsPtr->maxUser = maxUser;
        myLoadItemsPtr->userMax = userMax;
        myLoadItemsPtr->minUser = minUser;
        myLoadItemsPtr->userMin = userMin;
        //////////---------- Location ID ----------//////////
        myLoadItemsPtr->POIs = locations.size();
        int locationMax = 0;
        int maxLocation = 0;
        int locationMin = -1;
        int minLocation = 0;
        for (QMap<int, int>::const_iterator locationsIter = locations.constBegin();
             locationsIter != locations.constEnd(); locationsIter++) {
            if (locationsIter.value() > locationMax) {
                maxLocation = locationsIter.key();
                locationMax = locationsIter.value();
            }
            if (locationMin == -1) {
                minLocation = locationsIter.key();
                locationMin = locationsIter.value();
            } else if (locationsIter.value() < locationMin) {
                minLocation = locationsIter.key();
                locationMin = locationsIter.value();
            }
        }
        myLoadItemsPtr->maxPOI = maxLocation;
        myLoadItemsPtr->minPOI = minLocation;
        myLoadItemsPtr->POIMax = locationMax;
        myLoadItemsPtr->POIMin = locationMin;
        qDebug() << "file loaded with" << elapsedTimer.elapsed() / 1000.0 << "s";
        emit finish();
//#ifndef QT_NO_CURSOR
//        QGuiApplication::restoreOverrideCursor();
//#endif // QT_NO_CURSOR
    } else {
        emit isEmpty();
        return;
    }
}
