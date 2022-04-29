#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtCharts>     // not beautiful here

#include "./utils/loaditems.h"

#define APPLICATION_NAME "QtHowTo"
#define MAINWINDOW_WIDTH 600
#define MAINWINDOW_HEIGHT 330
#define FILE_LOADED_STATUS_TIME 2000
#define FILE_STORED_STATUS_TIME 2000
#define NUM_BUTTONS 3
#define NUM_BOXES 5

QT_BEGIN_NAMESPACE
class QPlainTextEdit;
class QCalendarWidget;
class QPushButton;
class QCheckBox;
class QRadioButton;
class QSlider;
class QSpinBox;
class QDoubleSpinBox;
class ActionPushButton;
class DescriptionCheckBox;
class QLabel;
class DatasetSetup;
class QLCDNumber;
QT_END_NAMESPACE

QT_CHARTS_USE_NAMESPACE // for QtCharts

/*Qt How To
 * MainWindow application
 * Central widget as QTab, with tab0 QCalendarWidget, tab1 many useful widgets, tab2 misc widgets
 * Dock widget as QPlainTextEdit
 * Include many actions in menu and tool bar
 * Include status bar
 */
class MainWindow: public QMainWindow {
    Q_OBJECT
    Q_CLASSINFO("author", "dadadadawjb");

private:
    //////////---------- Widgets ----------//////////
    QTabWidget *myTabWidget;
    QCalendarWidget *myCalendar;
    QPushButton *myPushButtons[NUM_BUTTONS];
    QCheckBox *myCheckBoxes[NUM_BOXES];
    QRadioButton *myRadioButton;
    QSlider *mySlider;
    QSpinBox *mySpinBox;
    QDoubleSpinBox *myDoubleSpinBox;
    QLCDNumber *myLCDNumber;
    ActionPushButton *newFileButton;
    ActionPushButton *openFileButton;
    ActionPushButton *saveFileButton;
    ActionPushButton *saveasFileButton;
    DescriptionCheckBox *userIDCheckBox;
    DescriptionCheckBox *locationIDCheckBox;
    DescriptionCheckBox *timeCheckBox;
    DescriptionCheckBox *latitudeCheckBox;
    DescriptionCheckBox *longitudeCheckBox;
    QLabel *description;
    QDockWidget *myDockWidget;
    QAction *newFileAction;
    QAction *openFileAction;
    QAction *saveFileAction;
    QAction *saveasFileAction;
    DatasetSetup *myDatasetSetup;
    QPlainTextEdit *myTextEdit;

    //////////---------- User Control ----------//////////
    QString currentFileName;
    int currentStart;
    int currentEnd;
    QPieSeries *myPieSeries;
    QLineSeries *myLineSeries1;
    QLineSeries *myLineSeries2;
    QString userName;
    QString userGender;
    int userAge;
    double userScore;
    QString userDescription;

    //////////---------- Meta ----------//////////
    int calendarPageIndex;
    int widgetPageIndex;
    int miscPageIndex;
    int customPageIndex;
    int datasetPageIndex;
    int chartPageIndex;

    //////////---------- Data ----------//////////
    loadItems myLoadItems;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event) override;

private:
    void setupMainWindow();
    void setupCentralWidget();
    void setupTab0();
    void setupTab1();
    void setupTab2();
    void setupTab3();
    void setupTab4();
    void setupDockWidget();
    void setupActions();
    void setupStatusBar();
    void readUserSettings();
    void writeUserSettings();
    void _loadFile(const QString &fileName);
    bool _storeFile(const QString &fileName);
    bool maybeSaveFile();
    void setCurrentFile(const QString &fileName);
    QString strippedName(const QString &fullFileName);

private slots:
    void about();
    void newFile();
    void openFile();
    bool saveFile();
    bool saveasFile();
    void documentModified();
    void patternWrite(bool enabled);
    void patternRead(bool enabled);
    void controlRangeChanged(int start, int end);
    void processLoaded();
    void setColor_();
    void setFont_();
    void setUserName();
    void setUserGender();
    void setUserAge();
    void setUserScore();
    void setUserDescription();
    void timerOut();

};

#endif // MAINWINDOW_H
