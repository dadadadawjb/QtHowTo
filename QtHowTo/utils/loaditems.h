#ifndef LOADITEMS_H
#define LOADITEMS_H

#include <QVector>

struct loadItems {
    //////////---------- Checking-Ins ----------//////////
    int checkingIns;

    //////////---------- Users ----------//////////
    int users;
    int maxUser;
    int userMax;
    int minUser;
    int userMin;

    //////////---------- POIs ----------//////////
    int POIs;
    int maxPOI;
    int POIMax;
    int minPOI;
    int POIMin;

    //////////---------- Data ----------//////////
    QVector<int> userIDArray;
    QVector<int> locationIDArray;
};

#endif // LOADITEMS_H
