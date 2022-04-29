#include "mainwindow.h"

#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication myApplication(argc, argv);
    QCoreApplication::setOrganizationName("QtProject");
    QCoreApplication::setApplicationName("QtHowTo");

    MainWindow myMainWindow;
    myMainWindow.show();
    return myApplication.exec();
}
