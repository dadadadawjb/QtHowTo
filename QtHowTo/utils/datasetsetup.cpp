#include "datasetsetup.h"

#include <QtWidgets>

#include "datasetloader.h"

DatasetSetup::DatasetSetup(loadItems *_myLoadItemsPtr, QWidget *parent): QWidget(parent) {
    myLoadItemsPtr = _myLoadItemsPtr;

    QVBoxLayout *loadLayout = new QVBoxLayout(parent);

    //////////---------- Open Dataset ----------//////////
    QHBoxLayout *openLayout = new QHBoxLayout(this);
    QWidget *openGroup = new QWidget(this);

    QLabel *datasetLabel = new QLabel(tr("Dataset: "), openGroup);
    filePathEditor = new QLineEdit(openGroup);
    fileOpenButton = new QPushButton(tr("Open..."), openGroup);
    datasetLabel->setBuddy(filePathEditor);
    filePathEditor->setDisabled(true);
    filePathEditor->setStatusTip(tr("Choose path to the dataset to load"));
    connect(fileOpenButton, &QPushButton::released, this, &DatasetSetup::getDatasetPath);

    openLayout->addWidget(datasetLabel);
    openLayout->addWidget(filePathEditor);
    openLayout->addWidget(fileOpenButton);

    openGroup->setLayout(openLayout);

    loadLayout->addWidget(openGroup);

    //////////---------- Load ----------//////////
    fileLoadButton = new QPushButton(tr("Load"), this);
    fileLoadButton->setObjectName("loadButton");
    connect(fileLoadButton, &QPushButton::released, this, &DatasetSetup::loadDataset);

    loadLayout->addWidget(fileLoadButton);

    // finish
    this->setLayout(loadLayout);
}

void DatasetSetup::getDatasetPath() {
    fileName = QFileDialog::getOpenFileName(this, tr("Choose dataset file"),
                                            QDir::rootPath(), tr("*.csv"));
    filePathEditor->setText(fileName);
}

void DatasetSetup::loadDataset() {
    // how to use DatasetLoader
    DatasetLoader *datasetLoader = new DatasetLoader(fileName, myLoadItemsPtr, this);

    connect(datasetLoader, &DatasetLoader::isEmpty, this, &DatasetSetup::processEmpty);
    connect(datasetLoader, &DatasetLoader::cannotOpen, this, &DatasetSetup::processCannotOpen);
    connect(datasetLoader, &DatasetLoader::normal, this, &DatasetSetup::processNormal);
    connect(datasetLoader, &DatasetLoader::finish, this, &DatasetSetup::processFinished);

    datasetLoader->load();
}

void DatasetSetup::processEmpty() {
    QMessageBox::warning(this, tr("Dataset Loader"),
                         tr("Please select your dataset"));
}

void DatasetSetup::processCannotOpen(const QString &errorMessage) {
    QMessageBox::warning(this, tr("Dataset Loader"), errorMessage);
}

void DatasetSetup::processNormal(const DatasetLoader *datasetLoader) {
    QVBoxLayout *loadLayout = static_cast<QVBoxLayout *>(this->layout());
    loadLayout->removeWidget(fileLoadButton);
    fileLoadButton->setHidden(true);

    fileOpenButton->setDisabled(true);

    // how to use QProgressBar
    QProgressBar *loadProgressBar = new QProgressBar;
    loadProgressBar->setOrientation(Qt::Horizontal);
    loadProgressBar->setMinimum(0);
    loadProgressBar->setMaximum(10000);
    loadProgressBar->setAlignment(Qt::AlignRight | Qt::AlignVCenter);
    loadLayout->addWidget(loadProgressBar);
    connect(datasetLoader, &DatasetLoader::setPercent, loadProgressBar, &QProgressBar::setValue);
}

void DatasetSetup::processFinished() {
    emit loaded();
}
