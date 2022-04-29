#include "mainwindow.h"

#include <QtWidgets>    // a large header file, better here than in `mainwindow.h`

#include "./utils/actionpushbutton.h"
#include "./utils/descriptioncheckbox.h"
#include "./utils/datasetsetup.h"
#include "./utils/integerrangetune.h"

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent) {
    setupMainWindow();

    setupCentralWidget();

    setupTab0();
    setupTab1();
    setupTab2();
    // setupTab3();

    setupDockWidget();

    setupActions();     // we need to connect with text edit, so should after setting up dock widget

    setupTab3();        // we need to show action pushbutton, so should after setting up action
    setupTab4();

    setupStatusBar();

    readUserSettings();

    setCurrentFile(QString());
}

MainWindow::~MainWindow() {
    delete myTextEdit;
}

void MainWindow::closeEvent(QCloseEvent *event) {
    // how to deal with close event
    if (maybeSaveFile()) {
        writeUserSettings();
        event->accept();
    } else {
        event->ignore();
    }
}

void MainWindow::setupMainWindow() {
    const QIcon applicationIcon = QIcon(":/images/applicationIcon.png");
    setWindowIcon(applicationIcon);
    setWindowTitle(tr(APPLICATION_NAME));
    resize(MAINWINDOW_WIDTH, MAINWINDOW_HEIGHT);
    // setFixedSize(MAINWINDOW_WIDTH, MAINWINDOW_HEIGHT);
}

void MainWindow::setupCentralWidget() {
    // how to set tabs
    myTabWidget = new QTabWidget(this);
    myTabWidget->setTabShape(QTabWidget::Triangular);   // another QTabWidget::Rounded
    myTabWidget->setTabPosition(QTabWidget::North);     // another South, West, East
    myTabWidget->setMovable(true);
    myTabWidget->setTabsClosable(false);
    myTabWidget->setUsesScrollButtons(true);

    setCentralWidget(myTabWidget);      // how to set central widget
}

void MainWindow::setupTab0() {
    // how to use QCalendarWidget
    myCalendar = new QCalendarWidget(myTabWidget);
    myCalendar->setFirstDayOfWeek(Qt::DayOfWeek(Qt::Monday));
    myCalendar->setSelectionMode(QCalendarWidget::SingleSelection);

    // add to tab 0
    const QIcon calendarIcon = QIcon::fromTheme("x-office-calendar", QIcon(":/images/calendar.png"));
    int index = myTabWidget->addTab(myCalendar, calendarIcon, tr("Calendar"));
    myTabWidget->setTabToolTip(index, tr("Calendar"));
    calendarPageIndex = index;
}

void MainWindow::setupTab1() {
    // how to use QGridLayout
    QGridLayout *mainLayout = new QGridLayout(myTabWidget);
    QGroupBox *mainGroupBox = new QGroupBox(myTabWidget);

    //////////---------- Horizontal PushButtons ----------//////////
    // how to use QHBoxLayout
    QHBoxLayout *horizontalLayout = new QHBoxLayout;
    // how to use QGroupBox
    QGroupBox *horizontalGroupBox = new QGroupBox(tr("Horizontal Layout"));
    horizontalGroupBox->setAlignment(Qt::AlignLeft);    // another Qt::AlignRight, Qt::AlignHCenter
    horizontalGroupBox->setCheckable(true);
    horizontalGroupBox->setFlat(false);

    // how to use QButtonGroup
    QButtonGroup *myPushButtonsGroup = new QButtonGroup;    // no visualization concept
    myPushButtonsGroup->setExclusive(true);
    for (int i = 0; i < NUM_BUTTONS; i++) {
        // how to use QPushButton
        myPushButtons[i] = new QPushButton(tr("Push Button %1").arg(i + 1));
        myPushButtons[i]->setCheckable(true);
        if (i == 0)
            myPushButtons[i]->setChecked(true);
        myPushButtonsGroup->addButton(myPushButtons[i]);
        horizontalLayout->addWidget(myPushButtons[i]);
    }
    horizontalGroupBox->setLayout(horizontalLayout);

    mainLayout->addWidget(horizontalGroupBox, 0, 0, 1, 2);

    //////////---------- Vertical CheckBoxes ----------//////////
    QVBoxLayout *verticalLayout = new QVBoxLayout;
    QGroupBox *verticalGroupBox = new QGroupBox(tr("Vertical Layout"));
    verticalGroupBox->setAlignment(Qt::AlignLeft);
    verticalGroupBox->setCheckable(true);
    verticalGroupBox->setFlat(false);

    QButtonGroup *myCheckBoxesGroup = new QButtonGroup;
    myCheckBoxesGroup->setExclusive(true);
    for (int i = 0; i < NUM_BOXES; i++) {
        // how to use QCheckBox
        myCheckBoxes[i] = new QCheckBox(tr("Check Box %1").arg(i + 1));
        if (i == 0)
            myCheckBoxes[i]->setChecked(true);
        myCheckBoxesGroup->addButton(myCheckBoxes[i]);
        verticalLayout->addWidget(myCheckBoxes[i]);
    }
    verticalGroupBox->setLayout(verticalLayout);

    mainLayout->addWidget(verticalGroupBox, 1, 0, 2, 1);

    //////////---------- Slider with Label ----------//////////
    QHBoxLayout *LabelSliderLayout = new QHBoxLayout;
    QGroupBox *LabelSliderGroup = new QGroupBox(tr("Slider with Label Example"));
    LabelSliderGroup->setAlignment(Qt::AlignLeft);
    LabelSliderGroup->setCheckable(true);
    LabelSliderGroup->setFlat(false);

    // how to use QSlider
    mySlider = new QSlider(Qt::Horizontal);

    // how to use QLabel
    QLabel *myLabel = new QLabel(tr("Label Example"));
    myLabel->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    myLabel->setScaledContents(false);
    myLabel->setOpenExternalLinks(true);
    myLabel->setBuddy(mySlider);

    LabelSliderLayout->addWidget(myLabel);
    LabelSliderLayout->addWidget(mySlider);
    LabelSliderGroup->setLayout(LabelSliderLayout);

    mainLayout->addWidget(LabelSliderGroup, 1, 1, 1, 1);

    //////////---------- RadioButton ----------//////////
    // how to use QRadioButton
    myRadioButton = new QRadioButton(tr("Radio Button Example"));

    mainLayout->addWidget(myRadioButton, 2, 1, 1, 1);

    //////////---------- SpinBox ----------//////////
    // how to use QSpinBox
    mySpinBox = new QSpinBox;
    mySpinBox->setDisplayIntegerBase(10);
    mySpinBox->setMaximum(100);
    mySpinBox->setMinimum(0);
    mySpinBox->setPrefix(tr("weight "));
    mySpinBox->setSuffix(" kg");
    mySpinBox->setSingleStep(1);

    mainLayout->addWidget(mySpinBox, 3, 0, 1, 1);

    //////////---------- DoubleSpinBox ----------//////////
    // how to use QDoubleSpinBox
    myDoubleSpinBox = new QDoubleSpinBox;
    myDoubleSpinBox->setDecimals(2);
    myDoubleSpinBox->setMaximum(5);
    myDoubleSpinBox->setMinimum(0);
    myDoubleSpinBox->setPrefix(tr("height "));
    myDoubleSpinBox->setSuffix(" m");
    myDoubleSpinBox->setSingleStep(0.01);

    mainLayout->addWidget(myDoubleSpinBox, 3, 1, 1, 1);

    mainGroupBox->setLayout(mainLayout);

    // add to tab 1
    const QIcon widgetsIcon = QIcon(":/images/widgets.png");
    int index = myTabWidget->addTab(mainGroupBox, widgetsIcon, tr("Widgets"));
    myTabWidget->setTabToolTip(index, tr("Widgets"));
    widgetPageIndex = index;
}

void MainWindow::setupTab2() {
    // how to use QLCDNumber
    myLCDNumber = new QLCDNumber(myTabWidget);
    myLCDNumber->setDigitCount(20);
    myLCDNumber->setMode(QLCDNumber::Dec);                  // another QLCDNumber::Bin, QLCDNumber::Oct, QLCDNumber::Hex
    myLCDNumber->setSegmentStyle(QLCDNumber::Filled);       // another QLCDNumber::Outline, QLCDNumber::Flat

    // add to tab 2
    const QIcon miscIcon = QIcon(":/images/misc.png");
    int index = myTabWidget->addTab(myLCDNumber, miscIcon, tr("Misc"));
    myTabWidget->setTabToolTip(index, tr("Misc"));
    miscPageIndex = index;

    // how to use QTimer
    QTimer *myTimer = new QTimer(this);
    myTimer->setInterval(1000);
    connect(myTimer, &QTimer::timeout, this, &MainWindow::timerOut);
    myTimer->start();
}

void MainWindow::setupTab3() {
    QVBoxLayout *customLayout = new QVBoxLayout(myTabWidget);
    QWidget *customPage = new QWidget(myTabWidget);

    //////////---------- Action PushButton ----------//////////
    QHBoxLayout *actionPushButtonLayout = new QHBoxLayout(customPage);
    QGroupBox *actionPushButtons = new QGroupBox(customPage);
    actionPushButtons->setAlignment(Qt::AlignHCenter | Qt::AlignVCenter);
    actionPushButtons->setFlat(false);

    // how to use ActionPushButton
    newFileButton = new ActionPushButton(actionPushButtons);
    newFileButton->setAction(newFileAction);
    actionPushButtonLayout->addWidget(newFileButton);
    openFileButton = new ActionPushButton(actionPushButtons);
    openFileButton->setAction(openFileAction);
    actionPushButtonLayout->addWidget(openFileButton);
    saveFileButton = new ActionPushButton(actionPushButtons);
    saveFileButton->setAction(saveFileAction);
    actionPushButtonLayout->addWidget(saveFileButton);
    saveasFileButton = new ActionPushButton(actionPushButtons);
    saveasFileButton->setAction(saveasFileAction);
    actionPushButtonLayout->addWidget(saveasFileButton);


    actionPushButtons->setLayout(actionPushButtonLayout);

    //////////---------- Description CheckBox -----------//////////
    QHBoxLayout *descriptionCheckBoxLayout = new QHBoxLayout(customPage);
    QWidget *descriptionWidget = new QWidget(customPage);

    QVBoxLayout *boxLayout = new QVBoxLayout(descriptionWidget);
    QGroupBox *descriptionCheckBoxes = new QGroupBox(tr("Filter fields:"), descriptionWidget);
    descriptionCheckBoxes->setAlignment(Qt::AlignLeft);
    descriptionCheckBoxes->setFlat(false);

    // how to use DescriptionCheckBox
    userIDCheckBox = new DescriptionCheckBox(tr("user_id"), descriptionCheckBoxes);
    locationIDCheckBox = new DescriptionCheckBox(tr("location_id"), descriptionCheckBoxes);
    timeCheckBox = new DescriptionCheckBox(tr("time"), descriptionCheckBoxes);
    latitudeCheckBox = new DescriptionCheckBox(tr("latitude"), descriptionCheckBoxes);
    longitudeCheckBox = new DescriptionCheckBox(tr("longitude"), descriptionCheckBoxes);
    userIDCheckBox->setStatusTip(tr("Check it to load this field from the dataset"));
    locationIDCheckBox->setStatusTip(tr("Check it to load this field from the dataset"));
    timeCheckBox->setStatusTip(tr("Check it to load this field from the dataset"));
    latitudeCheckBox->setStatusTip(tr("Check it to load this field from the dataset"));
    longitudeCheckBox->setStatusTip(tr("Check it to load this field from the dataset"));
    userIDCheckBox->setDescription(tr("user ID\nExample: 0"));
    locationIDCheckBox->setDescription(tr("location ID\nExample: 0"));
    timeCheckBox->setDescription(tr("timestamp of POI checking-in\nExample: 2010-05-22T02:49:04Z"));
    latitudeCheckBox->setDescription(tr("latitude of POI\nExample: 30.248923845"));
    longitudeCheckBox->setDescription(tr("longitude of POI\nExample: -97.74962604049999"));
    userIDCheckBox->setChecked(true);
    locationIDCheckBox->setChecked(true);
    timeCheckBox->setChecked(true);
    latitudeCheckBox->setChecked(true);
    longitudeCheckBox->setChecked(true);
    boxLayout->addWidget(userIDCheckBox);
    boxLayout->addWidget(locationIDCheckBox);
    boxLayout->addWidget(timeCheckBox);
    boxLayout->addWidget(latitudeCheckBox);
    boxLayout->addWidget(longitudeCheckBox);

    descriptionCheckBoxes->setLayout(boxLayout);

    QVBoxLayout *descriptionLayout = new QVBoxLayout(descriptionWidget);
    QGroupBox *descriptionRegion = new QGroupBox(tr("Description:"), descriptionWidget);
    descriptionRegion->setAlignment(Qt::AlignLeft);
    descriptionRegion->setFlat(false);

    description = new QLabel(descriptionRegion);
    connect(userIDCheckBox, &DescriptionCheckBox::onDescription, description, &QLabel::setText);
    connect(locationIDCheckBox, &DescriptionCheckBox::onDescription, description, &QLabel::setText);
    connect(timeCheckBox, &DescriptionCheckBox::onDescription, description, &QLabel::setText);
    connect(latitudeCheckBox, &DescriptionCheckBox::onDescription, description, &QLabel::setText);
    connect(longitudeCheckBox, &DescriptionCheckBox::onDescription, description, &QLabel::setText);

    descriptionLayout->addWidget(description);
    descriptionRegion->setLayout(descriptionLayout);

    descriptionCheckBoxLayout->addWidget(descriptionCheckBoxes);
    descriptionCheckBoxLayout->addWidget(descriptionRegion);
    descriptionWidget->setLayout(descriptionCheckBoxLayout);

    //////////---------- Integer Range Tune ----------//////////
    // how to use IntegerRangeTune
    IntegerRangeTune *controlRange = new IntegerRangeTune(0, 10, 0, 10, 1, customPage);
    currentStart = 0;
    currentEnd = 10;
    connect(controlRange, &IntegerRangeTune::changedStartEnd, this, &MainWindow::controlRangeChanged);

    //////////---------- Post ----------//////////
    customLayout->addWidget(actionPushButtons);
    customLayout->addWidget(descriptionWidget);
    customLayout->addWidget(controlRange);
    customPage->setLayout(customLayout);

    // add to tab 3
    const QIcon customIcon = QIcon(":/images/custom.png");
    int index = myTabWidget->addTab(customPage, customIcon, tr("Custom"));
    myTabWidget->setTabToolTip(index, tr("Custom"));
    customPageIndex = index;
}

void MainWindow::setupTab4() {
    // how to use dataset setup encapsulation
    myDatasetSetup = new DatasetSetup(&myLoadItems, myTabWidget);
    connect(myDatasetSetup, &DatasetSetup::loaded, this, &MainWindow::processLoaded);

    // add to tab 4
    const QIcon datasetIcon = QIcon(":/images/dataset.png");
    int index = myTabWidget->addTab(myDatasetSetup, datasetIcon, tr("Dataset Load"));
    myTabWidget->setTabToolTip(index, tr("Dataset Load"));
    datasetPageIndex = index;
}

void MainWindow::setupDockWidget() {
    // how to set dock widget
    // myDockWidget = new QDockWidget(tr("Dock Title"), this);
    myDockWidget = new QDockWidget(this);
    myDockWidget->setFeatures(QDockWidget::DockWidgetFloatable | QDockWidget::DockWidgetMovable);   // another QDockWidget::DockWidgetClosable
    myDockWidget->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);
    addDockWidget(Qt::LeftDockWidgetArea, myDockWidget);

    // how to use QPlainTextEdit, the same as QTextEdit
    myTextEdit = new QPlainTextEdit(tr("The default content"), myDockWidget);
    myTextEdit->setPlaceholderText(tr("You can write everything here."));
    // const QIcon textEditIcon = QIcon::fromTheme("x-office-document", QIcon(":/images/document.png"));

    connect(myTextEdit->document(), &QTextDocument::contentsChanged,
            this, &MainWindow::documentModified);

    myDockWidget->setWidget(myTextEdit);
    // myDockWidget->setWindowIcon(textEditIcon);   // dockWidget does not have window icon
}

void MainWindow::setupActions() {
    //////////---------- File Actions ----------//////////
    QMenu *fileMenu = menuBar()->addMenu(tr("&File"));      // how to add menu
    QToolBar *fileToolBar = addToolBar(tr("File"));         // how to add tool bar

    // new file
    const QIcon newFileIcon = QIcon::fromTheme("document-new", QIcon(":/images/newFile.png"));
    newFileAction = new QAction(newFileIcon, tr("&New"), this);    // how to add action
    newFileAction->setShortcuts(QKeySequence::New);
    newFileAction->setStatusTip(tr("Create a new file"));
    newFileAction->setToolTip(tr("Create a new file"));
    newFileAction->setWhatsThis(tr("Create a new file"));
    connect(newFileAction, &QAction::triggered, this, &MainWindow::newFile);
    fileMenu->addAction(newFileAction);
    fileToolBar->addAction(newFileAction);

    // open file
    const QIcon openFileIcon = QIcon::fromTheme("document-open", QIcon(":/images/openFile.png"));
    openFileAction = new QAction(openFileIcon, tr("&Open..."), this);
    openFileAction->setShortcuts(QKeySequence::Open);
    openFileAction->setStatusTip(tr("Open an existing file"));
    openFileAction->setToolTip(tr("Open an existing file"));
    openFileAction->setWhatsThis(tr("Open an existing file"));
    connect(openFileAction, &QAction::triggered, this, &MainWindow::openFile);
    fileMenu->addAction(openFileAction);
    fileToolBar->addAction(openFileAction);

    // save file
    const QIcon saveFileIcon = QIcon::fromTheme("document-save", QIcon(":/images/saveFile.png"));
    saveFileAction = new QAction(saveFileIcon, tr("&Save"), this);
    saveFileAction->setShortcuts(QKeySequence::Save);
    saveFileAction->setStatusTip(tr("Save the document to disk"));
    saveFileAction->setToolTip(tr("Save the document to disk"));
    saveFileAction->setWhatsThis(tr("Save the document to disk"));
    connect(saveFileAction, &QAction::triggered, this, &MainWindow::saveFile);
    fileMenu->addAction(saveFileAction);
    fileToolBar->addAction(saveFileAction);

    // save as file
    const QIcon saveasFileIcon = QIcon::fromTheme("document-save-as", QIcon(":/images/saveasFile.png"));
    saveasFileAction = new QAction(saveasFileIcon, tr("Save &As..."), this);
    saveasFileAction->setShortcuts(QKeySequence::SaveAs);
    saveasFileAction->setStatusTip(tr("Save the document under a new name"));
    saveasFileAction->setToolTip(tr("Save the document under a new name"));
    saveasFileAction->setWhatsThis(tr("Save the document under a new name"));
    connect(saveasFileAction, &QAction::triggered, this, &MainWindow::saveasFile);
    fileMenu->addAction(saveasFileAction);
    fileToolBar->addAction(saveasFileAction);

    fileMenu->addSeparator();

    // exit
    const QIcon exitIcon = QIcon::fromTheme("application-exit", QIcon(":/images/exit.png"));
    QAction *exitAction = new QAction(exitIcon, tr("E&xit"), this);
    exitAction->setShortcuts(QKeySequence::Quit);
    exitAction->setStatusTip(tr("Exit the application"));
    exitAction->setToolTip(tr("Exit the application"));
    exitAction->setWhatsThis(tr("Exit the application"));
    connect(exitAction, &QAction::triggered, this, &QWidget::close);    // how to add exit action
    // connect(exitAction, &QAction::triggered, qApp, &QCoreApplication::quit);
    fileMenu->addAction(exitAction);
    // fileToolBar->addAction(exitAction);

    //////////---------- Edit Actions ----------//////////
    QMenu *editMenu = menuBar()->addMenu(tr("&Edit"));
    QToolBar *editToolBar = addToolBar(tr("Edit"));

#ifndef QT_NO_CLIPBOARD
    // cut text
    const QIcon cutTextIcon = QIcon::fromTheme("edit-cut", QIcon(":/images/cutText.png"));
    QAction *cutTextAction = new QAction(cutTextIcon, tr("Cu&t"), this);
    cutTextAction->setShortcuts(QKeySequence::Cut);
    cutTextAction->setStatusTip(tr("Cut the current selection's contents to the clipboard"));
    cutTextAction->setToolTip(tr("Cut the current selection's contents to the clipboard"));
    cutTextAction->setWhatsThis(tr("Cut the current selection's contents to the clipboard"));
    connect(cutTextAction, &QAction::triggered, myTextEdit, &QPlainTextEdit::cut);
    editMenu->addAction(cutTextAction);
    editToolBar->addAction(cutTextAction);

    // copy text
    const QIcon copyTextIcon = QIcon::fromTheme("edit-copy", QIcon(":/images/copyText.png"));
    QAction *copyTextAction = new QAction(copyTextIcon, tr("&Copy"), this);
    copyTextAction->setShortcuts(QKeySequence::Copy);
    copyTextAction->setStatusTip(tr("Copy the current selection's contents to the clipboard"));
    copyTextAction->setToolTip(tr("Copy the current selection's contents to the clipboard"));
    copyTextAction->setWhatsThis(tr("Copy the current selection's contents to the clipboard"));
    connect(copyTextAction, &QAction::triggered, myTextEdit, &QPlainTextEdit::copy);
    editMenu->addAction(copyTextAction);
    editToolBar->addAction(copyTextAction);

    // paste text
    const QIcon pasteTextIcon = QIcon::fromTheme("edit-paste", QIcon(":/images/pasteText.png"));
    QAction *pasteTextAction = new QAction(pasteTextIcon, tr("&Paste"), this);
    pasteTextAction->setShortcuts(QKeySequence::Paste);
    pasteTextAction->setStatusTip(tr("Paste the clipboard's contents into the current selection"));
    pasteTextAction->setToolTip(tr("Paste the clipboard's contents into the current selection"));
    pasteTextAction->setWhatsThis(tr("Paste the clipboard's contents into the current selection"));
    connect(pasteTextAction, &QAction::triggered, myTextEdit, &QPlainTextEdit::paste);
    editMenu->addAction(pasteTextAction);
    editToolBar->addAction(pasteTextAction);

    menuBar()->addSeparator();
#endif // QT_NO_CLIPBOARD

    // can write or read only
    QActionGroup *patternActionsGroup = new QActionGroup(this);     // how to set action group
    patternActionsGroup->setExclusive(true);
    patternActionsGroup->setExclusionPolicy(QActionGroup::ExclusionPolicy::Exclusive);
    patternActionsGroup->setVisible(true);
    const QIcon writeEnableIcon = QIcon(":/images/writeEnable.png");
    QAction *writeEnableAction = new QAction(writeEnableIcon, tr("&Write Enable"), this);
    writeEnableAction->setCheckable(true);
    const QIcon readOnlyIcon = QIcon::fromTheme("emblem-readonly", QIcon(":/images/readOnly.png"));
    QAction *readOnlyAction = new QAction(readOnlyIcon, tr("&Read Only"), this);
    readOnlyAction->setCheckable(true);
    connect(writeEnableAction, &QAction::triggered, this, &MainWindow::patternWrite);
    connect(readOnlyAction, &QAction::triggered, this, &MainWindow::patternRead);
    patternActionsGroup->addAction(writeEnableAction);
    patternActionsGroup->addAction(readOnlyAction);
    writeEnableAction->setChecked(true);

    const QIcon patternIcon = QIcon(":/images/pattern.png");
    QMenu *patternSubMenu = editMenu->addMenu(patternIcon, tr("Pattern"));       // how to add sub menu
    patternSubMenu->addActions(patternActionsGroup->actions());

    menuBar()->addSeparator();

    //////////---------- Style Actions ----------//////////
    QMenu *styleMenu = menuBar()->addMenu(tr("&Style"));
    QToolBar *styleToolBar = addToolBar(tr("Style"));

    // color
    const QIcon colorIcon = QIcon(":/images/color.png");
    QAction *colorAction = new QAction(colorIcon, tr("&Color"), this);
    colorAction->setStatusTip(tr("Set up the window's background color"));
    colorAction->setToolTip(tr("Set up the window's background color"));
    colorAction->setWhatsThis(tr("Set up the window's background color"));
    connect(colorAction, &QAction::triggered, this, &MainWindow::setColor_);
    styleMenu->addAction(colorAction);
    styleToolBar->addAction(colorAction);

    // font
    const QIcon fontIcon = QIcon(":/images/font.png");
    QAction *fontAction = new QAction(fontIcon, tr("&Font"), this);
    fontAction->setStatusTip(tr("Set up the window's font"));
    fontAction->setToolTip(tr("Set up the window's font"));
    fontAction->setWhatsThis(tr("Set up the window's font"));
    connect(fontAction, &QAction::triggered, this, &MainWindow::setFont_);
    styleMenu->addAction(fontAction);
    styleToolBar->addAction(fontAction);

    //////////---------- User Actions ----------//////////
    QMenu *userMenu = menuBar()->addMenu(tr("&User"));
    // QToolBar *userToolBar = addToolBar(tr("User"));

    // name
    const QIcon nameIcon = QIcon(":/images/name.png");
    QAction *nameAction = new QAction(nameIcon, tr("&Name"), this);
    nameAction->setStatusTip(tr("Set your name"));
    nameAction->setToolTip(tr("Set your name"));
    nameAction->setWhatsThis(tr("Set your name"));
    connect(nameAction, &QAction::triggered, this, &MainWindow::setUserName);
    userMenu->addAction(nameAction);

    // gender
    const QIcon genderIcon = QIcon(":/images/gender.png");
    QAction *genderAction = new QAction(genderIcon, tr("&Gender"), this);
    genderAction->setStatusTip(tr("Set your gender"));
    genderAction->setToolTip(tr("Set your gender"));
    genderAction->setWhatsThis(tr("Set your gender"));
    connect(genderAction, &QAction::triggered, this, &MainWindow::setUserGender);
    userMenu->addAction(genderAction);

    // age
    const QIcon ageIcon = QIcon(":/images/age.png");
    QAction *ageAction = new QAction(ageIcon, tr("&Age"), this);
    ageAction->setStatusTip(tr("Set your age"));
    ageAction->setToolTip(tr("Set your age"));
    ageAction->setWhatsThis(tr("Set your age"));
    connect(ageAction, &QAction::triggered, this, &MainWindow::setUserAge);
    userMenu->addAction(ageAction);

    // score
    const QIcon scoreIcon = QIcon(":/images/score.png");
    QAction *scoreAction = new QAction(scoreIcon, tr("&Score"), this);
    scoreAction->setStatusTip(tr("Set your score"));
    scoreAction->setToolTip(tr("Set your score"));
    scoreAction->setWhatsThis(tr("Set your score"));
    connect(scoreAction, &QAction::triggered, this, &MainWindow::setUserScore);
    userMenu->addAction(scoreAction);

    // description
    const QIcon descriptionIcon = QIcon(":/images/description.png");
    QAction *descriptioneAction = new QAction(descriptionIcon, tr("&Description"), this);
    descriptioneAction->setStatusTip(tr("Set your description"));
    descriptioneAction->setToolTip(tr("Set your description"));
    descriptioneAction->setWhatsThis(tr("Set your description"));
    connect(descriptioneAction, &QAction::triggered, this, &MainWindow::setUserDescription);
    userMenu->addAction(descriptioneAction);

    //////////---------- Help Actions ----------//////////
    QMenu *helpMenu = menuBar()->addMenu(tr("&Help"));

    QAction *aboutAct = helpMenu->addAction(tr("&About"), this, &MainWindow::about);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    aboutAct->setToolTip(tr("Show the application's About box"));
    aboutAct->setWhatsThis(tr("Show the application's About box"));

    QAction *aboutQtAct = helpMenu->addAction(tr("About &Qt"), qApp, &QApplication::aboutQt);   // how to add aboutQt action
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
    aboutQtAct->setToolTip(tr("Show the Qt library's About box"));
    aboutQtAct->setWhatsThis(tr("Show the Qt library's About box"));

    //////////---------- Check Clipboard ----------//////////
    // how to check clipboard
#ifndef QT_NO_CLIPBOARD
    cutTextAction->setEnabled(false);
    copyTextAction->setEnabled(false);
    connect(myTextEdit, &QPlainTextEdit::copyAvailable, cutTextAction, &QAction::setEnabled);
    connect(myTextEdit, &QPlainTextEdit::copyAvailable, copyTextAction, &QAction::setEnabled);
#endif // QT_NO_CLIPBOARD
}

void MainWindow::setupStatusBar() {
    // how to set status bar
    statusBar()->showMessage(tr("Ready"));
}

void MainWindow::readUserSettings() {
    // how to read user settings
    QSettings userSettings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
    const QByteArray geometry = userSettings.value("geometry", QByteArray()).toByteArray();
    if (geometry.isEmpty()) {
        const QRect availableGeometry = screen()->availableGeometry();
        resize(availableGeometry.width() / 3, availableGeometry.height() / 2);
        move((availableGeometry.width() - width()) / 2,
             (availableGeometry.height() - height()) / 2);
    } else {
        restoreGeometry(geometry);
    }
}

void MainWindow::writeUserSettings() {
    // how to write user settings
    QSettings userSettings(QCoreApplication::organizationName(), QCoreApplication::applicationName());
    userSettings.setValue("geometry", saveGeometry());
}

void MainWindow::about() {
   QMessageBox::about(this, tr("About QtHowTo"),
            tr("The <b>QtHowTo</b> application by <b>dadadadawjb</b> "
               "shows good workflow tutorial for Qt."));
}

void MainWindow::newFile() {
    // note we need to save current file
    if (maybeSaveFile()) {
        myTextEdit->clear();
        setCurrentFile(QString());
    }
}

void MainWindow::openFile() {
    if (maybeSaveFile()) {
        // how to dialog open file
        QString fileName = QFileDialog::getOpenFileName(this, tr("Choose your txt file"),
                                                        QDir::rootPath(), tr("*.txt"));
        if (!fileName.isEmpty())
            _loadFile(fileName);
    }
}

void MainWindow::_loadFile(const QString &fileName) {
    // how to load file
    QFile file(fileName);
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        QMessageBox::warning(this, tr(APPLICATION_NAME),
                             tr("Cannot read file %1:\n%2.")
                             .arg(QDir::toNativeSeparators(fileName), file.errorString()));
        return;
    }

    QTextStream in(&file);
    in.setCodec("utf8");
#ifndef QT_NO_CURSOR
    QGuiApplication::setOverrideCursor(Qt::WaitCursor);
#endif // QT_NO_CURSOR
    myTextEdit->setPlainText(in.readAll());
#ifndef QT_NO_CURSOR
    QGuiApplication::restoreOverrideCursor();
#endif // QT_NO_CURSOR

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File loaded"), FILE_LOADED_STATUS_TIME);
}

bool MainWindow::saveFile() {
    if (currentFileName.isEmpty())
        return saveasFile();
    else
        return _storeFile(currentFileName);
}

bool MainWindow::saveasFile() {
    QFileDialog saveasDialog(this);
    saveasDialog.setWindowModality(Qt::WindowModal);
    saveasDialog.setAcceptMode(QFileDialog::AcceptSave);
    if (saveasDialog.exec() != QDialog::Accepted)
        return false;
    return _storeFile(saveasDialog.selectedFiles().first());
}

bool MainWindow::_storeFile(const QString &fileName) {
    // how to store file
    QSaveFile file(fileName);

    QString errorMessage;
#ifndef QT_NO_CURSOR
    QGuiApplication::setOverrideCursor(Qt::WaitCursor);
#endif // QT_NO_CURSOR
    if (file.open(QFile::WriteOnly | QFile::Text)) {
        QTextStream out(&file);
        out << myTextEdit->toPlainText();
        if (!file.commit()) {
            errorMessage = tr("Cannot write file %1:\n%2.")
                           .arg(QDir::toNativeSeparators(fileName), file.errorString());
        }
    } else {
        errorMessage = tr("Cannot open file %1 for writing:\n%2.")
                       .arg(QDir::toNativeSeparators(fileName), file.errorString());
    }
#ifndef QT_NO_CURSOR
    QGuiApplication::restoreOverrideCursor();
#endif // QT_NO_CURSOR

    if (!errorMessage.isEmpty()) {
        QMessageBox::warning(this, tr(APPLICATION_NAME), errorMessage);
        return false;
    }

    setCurrentFile(fileName);
    statusBar()->showMessage(tr("File saved"), FILE_STORED_STATUS_TIME);
    return true;
}

bool MainWindow::maybeSaveFile() {
    if (!myTextEdit->document()->isModified())
        return true;

    // how to ask user to make choice
    const QMessageBox::StandardButton choice =
                                QMessageBox::warning(this, tr(APPLICATION_NAME),
                                            tr("The document has been modified.\n"
                                                "Do you want to save your changes?"),
                               QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);
    switch (choice) {
        case QMessageBox::Save:
            return saveFile();
        case QMessageBox::Cancel:
            return false;
        default:
            break;
    }
    return true;
}

void MainWindow::setCurrentFile(const QString &fileName) {
    currentFileName = fileName;
    myTextEdit->document()->setModified(false);
    myDockWidget->setWindowModified(false);

    QString shownName = strippedName(currentFileName);
    if (currentFileName.isEmpty())
        shownName = "untitled.txt";
    myDockWidget->setWindowFilePath(shownName);
    myDockWidget->setWindowModified(false);     // here may be dockWidget's bug
}

QString MainWindow::strippedName(const QString &fullFileName) {
    return QFileInfo(fullFileName).fileName();
}

void MainWindow::documentModified() {
    myDockWidget->setWindowModified(myTextEdit->document()->isModified());
}

void MainWindow::patternWrite(bool enabled) {
    if (enabled)
        myTextEdit->setReadOnly(false);
}

void MainWindow::patternRead(bool enabled) {
    if (enabled)
        myTextEdit->setReadOnly(true);
}

void MainWindow::controlRangeChanged(int start, int end) {
    currentStart = start;
    currentEnd = end;
}

void MainWindow::processLoaded() {
    statusBar()->showMessage(tr("Loaded"));

    QVBoxLayout *chartLayout = new QVBoxLayout(myTabWidget);
    QWidget *chartPage = new QWidget(myTabWidget);

    //////////---------- Pie Chart ----------//////////
    // how to draw pie chart
    myPieSeries = new QPieSeries();
    // dynamic also work to just append
    myPieSeries->append("wjb", 100);
    myPieSeries->append("Junbo Wang", 99);
    myPieSeries->append("dadadadawjb", 98);
    myPieSeries->setLabelsVisible(true);

    QPieSlice *slice = myPieSeries->slices().at(0);
    slice->setExploded();
    slice->setPen(QPen(Qt::darkGreen, 2));
    slice->setBrush(Qt::green);

    QChart *pieChart = new QChart();
    pieChart->addSeries(myPieSeries);
    pieChart->setTitle(tr("Pie Chart Example"));
    pieChart->legend()->hide();

    QChartView *pieChartView = new QChartView(pieChart);
    pieChartView->setRenderHint(QPainter::Antialiasing);

    chartLayout->addWidget(pieChartView);

    //////////---------- Line Chart ----------//////////
    // how to draw line chart
    myLineSeries1 = new QLineSeries();
    myLineSeries1->setName("Line 1");
    myLineSeries2 = new QLineSeries();
    myLineSeries2->setName("Line 2");
    // dynamic also work to just append
    qint64 time11 = QDateTime::fromString("2001-12-11T22:08:00Z", "yyyy-MM-ddTHH:mm:ssZ").toMSecsSinceEpoch();
    qint64 time12 = QDateTime::fromString("2019-06-07T09:00:00Z", "yyyy-MM-ddTHH:mm:ssZ").toMSecsSinceEpoch();
    qint64 time13 = QDateTime::fromString("2022-01-03T16:11:00Z", "yyyy-MM-ddTHH:mm:ssZ").toMSecsSinceEpoch();
    myLineSeries1->append(time11, 100);
    myLineSeries1->append(time12, 720);
    myLineSeries1->append(time13, 100);
    qint64 time21 = QDateTime::fromString("2002-12-11T22:08:00Z", "yyyy-MM-ddTHH:mm:ssZ").toMSecsSinceEpoch();
    qint64 time22 = QDateTime::fromString("2020-06-07T09:00:00Z", "yyyy-MM-ddTHH:mm:ssZ").toMSecsSinceEpoch();
    qint64 time23 = QDateTime::fromString("2023-01-03T16:11:00Z", "yyyy-MM-ddTHH:mm:ssZ").toMSecsSinceEpoch();
    myLineSeries2->append(time21, 100);
    myLineSeries2->append(time22, 720);
    myLineSeries2->append(time23, 100);

    QDateTimeAxis *xAxis = new QDateTimeAxis();
    xAxis->setFormat("yyyy-MM-ddTHH:mm:ssZ");
    QValueAxis *yAxis = new QValueAxis();
    yAxis->setLabelFormat("%d");
    xAxis->setRange(QDateTime::fromString("2000-01-01T00:00:00Z", "yyyy-MM-ddTHH:mm:ssZ"),
                    QDateTime::fromString("2099-12-31T23:59:59Z", "yyyy-MM-ddTHH:mm:ssZ"));
    xAxis->setTickCount(5);
    yAxis->setRange(0, 1000);
    yAxis->setMinorTickCount(1);
    yAxis->setTickCount(9);

    QChart *lineChart = new QChart();
    lineChart->addSeries(myLineSeries1);
    lineChart->addSeries(myLineSeries2);
    lineChart->addAxis(xAxis, Qt::AlignBottom);
    lineChart->addAxis(yAxis, Qt::AlignLeft);
    myLineSeries1->attachAxis(xAxis);
    myLineSeries1->attachAxis(yAxis);
    myLineSeries2->attachAxis(xAxis);
    myLineSeries2->attachAxis(yAxis);
    lineChart->setTitle(tr("Line Chart Example"));

    QChartView *lineChartView = new QChartView(lineChart);
    lineChartView->setRenderHint(QPainter::Antialiasing);

    chartLayout->addWidget(lineChartView);

    //////////---------- Post ----------//////////
    chartPage->setLayout(chartLayout);

    const QIcon chartIcon = QIcon(":/images/chart.png");
    int index = myTabWidget->addTab(chartPage, chartIcon, tr("Chart"));
    myTabWidget->setTabToolTip(index, tr("Chart"));
    // how to achieve tab jump
    myTabWidget->removeTab(datasetPageIndex);
    myTabWidget->setCurrentIndex(index);
    chartPageIndex = index;
}

void MainWindow::setColor_() {
    // how to dialog choose color
    QColor colorChosen = QColorDialog::getColor(Qt::white, this, tr("Choose the background color"));

    // how to set mainwindow background color
    QPalette p = palette();
    p.setColor(QPalette::Window, colorChosen);
    setPalette(p);
}

void MainWindow::setFont_() {
    // how to dialog choose font
    bool ok;
    QFont fontChosen = QFontDialog::getFont(&ok, QFont("Cartograph CF", 10), this, tr("Choose the mainwindow font"));

    // how to set mainwindow font
    if (ok) {
        setFont(fontChosen);    // set to user chosen
    } else {
        setFont(fontChosen);    // set to initial value of fontChosen
    }
}

void MainWindow::setUserName() {
    // how to dialog input text
    bool ok;
    QString chosenUserName = QInputDialog::getText(this, tr("Input your name"),
                                             tr("User name:"), QLineEdit::Normal,
                                             QDir::home().dirName(), &ok);
    if (ok && !chosenUserName.isEmpty())
        userName = chosenUserName;
}

void MainWindow::setUserGender() {
    // how to dialog input item
    bool ok;
    QStringList genders;
    genders << tr("Men") << tr("Women");
    QString chosenUserGender = QInputDialog::getItem(this, tr("Choose your gender"),
                                                     tr("User gender:"), genders, 0, false, &ok);
    if (ok && !chosenUserGender.isEmpty())
            userGender = chosenUserGender;
}

void MainWindow::setUserAge() {
    // how to dialog input integer
    bool ok;
    int chosenUserAge = QInputDialog::getInt(this, tr("Input your age"),
                                     tr("Age:"), 18, 0, 100, 1, &ok);
    if (ok)
        userAge = chosenUserAge;
}

void MainWindow::setUserScore() {
    // how to dialog input double
    bool ok;
    double chosenUserScore = QInputDialog::getDouble(this, tr("Input your score"),
                                       tr("Score:"), 99.99, 0, 100, 2, &ok,
                                       Qt::WindowFlags(), 0.01);
    if (ok)
        userScore = chosenUserScore;
}

void MainWindow::setUserDescription() {
    // how to dialog input multiple line text
    bool ok;
    QString chosenUserDescription = QInputDialog::getMultiLineText(this, tr("Input your description"),
                                                  tr("Description:"), "Student in SJTU CS", &ok);
    if (ok && !chosenUserDescription.isEmpty())
        userDescription = chosenUserDescription;
}

void MainWindow::timerOut() {
    // how to get current time
    QDateTime dateTime = QDateTime::currentDateTime();
    myLCDNumber->display(dateTime.toString("yyyy-MM-dd HH:mm:ss"));
}
