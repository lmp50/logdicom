#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>
#include "dialhelp.h"
#include "classlogdicom.h"
#include "classfiledicom.h"
#include "constdefine.h"

extern classLogdicom * logdicom;
extern classFiledicom * filedicom[MAX_DATA_ELEMENT];

//*****************************************************************************
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QMenu * mnFile = new QMenu(tr("File")); // создаём меню Файл

    QAction *msgOpenFile = new QAction(tr("Open file"),mnFile);
    connect(msgOpenFile, SIGNAL(triggered()), this, SLOT(slotOpenFile()));
    mnFile->addAction(msgOpenFile);

    QAction *msgOpenFolder = new QAction(tr("Open folder"),mnFile);
    connect(msgOpenFolder, SIGNAL(triggered()), this, SLOT(slotOpenFolder()));
    mnFile->addAction(msgOpenFolder);

    QAction *msgExport = new QAction(tr("Export"),mnFile);
    connect(msgExport, SIGNAL(triggered()), this, SLOT(slotExport()));
    mnFile->addAction(msgExport);

    QAction *msgImport = new QAction(tr("Import"),mnFile);
    connect(msgImport, SIGNAL(triggered()), this, SLOT(slotImport()));
    mnFile->addAction(msgImport);

    QAction *msgExit = new QAction(tr("Exit"),mnFile);
    connect(msgExit, SIGNAL(triggered()), this, SLOT(slotExit()));
    mnFile->addAction(msgExit);
    ui->menuBar->addMenu(mnFile); // Добавляем пункты меню в menuBar, т.е. те, которые будут отображаться в гл. окне

    QMenu * mnHelp = new QMenu(tr("Help")); // Меню помощь

    QAction *msgContents = new QAction(tr("Contents"),mnHelp);
    connect(msgContents, SIGNAL(triggered()), this, SLOT(slotContents()));
    mnHelp->addAction(msgContents);

    QAction *msgAbout = new QAction(tr("About Program logdicom"),mnHelp);
    connect(msgAbout, SIGNAL(triggered()), this, SLOT(slotAbout()));
    mnHelp->addAction(msgAbout);

    ui->menuBar->addMenu(mnFile); // Добавляем пункты меню в menuBar, т.е. те, которые будут отображаться в гл. окне
    ui->menuBar->addMenu(mnHelp);
}

//*****************************************************************************
MainWindow::~MainWindow()
{
    delete ui;
}

//*****************************************************************************
void MainWindow::slotExit()
{
    close();
}

//*****************************************************************************
void MainWindow::slotOpenFile()
{
    QString sFileName;
    int iDataElementNo = 0;
    quint64 i64Pos = 0;
    sFileName = QFileDialog::getOpenFileName(this,
        tr("Open File"), "/home", tr("All Files *.* (*);;Dicom Files *.dicom (*.dicom)"));
    if (sFileName != "") {
        QFile file(sFileName);
        if (!file.open(QIODevice::ReadOnly))
            return;
        QByteArray line;
        line = file.read(128); //Первые 128 символов содержимое не определено (обычно там нули)
        line = file.read(4);
        i64Pos = 132;
        if (line != "DICM") //Далее 4 символа - DICM
            QMessageBox::warning(0,"Warning","Неправильная структура файла DICOM");
        while (readDataElement(line,&file,iDataElementNo,i64Pos)) {  //прочитать значение данных

        }

        file.close();
        QMessageBox::information(0,"Info","Обработка файла прошла успешно. Всего групп " + QString::number(iDataElementNo));
    }

}

//*****************************************************************************
bool MainWindow::readDataElement(QByteArray line, QFile * file, int &iDataElementNo,quint64 &i64Pos)
{
    line = file->read(2); i64Pos += 2;
    if (line.length() == 0) {
        return false;
    }
    if (line.length() < 2) {
        QMessageBox::warning(0,"Warning","Неправильная структура файла DICOM");
        return false;
    }

    filedicom[iDataElementNo] = new classFiledicom;
    filedicom[iDataElementNo]->setGroupNumber(line);

    line = file->read(2); i64Pos += 2;
    if (line.length() < 2) {
        QMessageBox::warning(0,"Warning","Неправильная структура файла DICOM");
        return false;
    }
    filedicom[iDataElementNo]->setElementNumber(line);

    line = file->read(2); i64Pos += 2;
    if (line.length() < 2) {
        QMessageBox::warning(0,"Warning","Неправильная структура файла DICOM");
        return false;
    }
    filedicom[iDataElementNo]->setVR(line);
    if ( ((line[0] == 'O') && (line[1] == 'B')) || ((line[0] == 'O') && (line[1] == 'W')) || ((line[0] == 'O') && (line[1] == 'F')) ||
        ((line[0] == 'S') && (line[1] == 'Q')) || ((line[0] == 'U') && (line[1] == 'T')) || ((line[0] == 'U') && (line[1] == 'N')) ) {
        filedicom[iDataElementNo]->setDataElementType(32);
    }
    else {
        filedicom[iDataElementNo]->setDataElementType(16);
    }

    quint32 i32Length;
    if (filedicom[iDataElementNo]->getDataElementType() == 16) {
        line = file->read(2); i64Pos += 2;
        if (line.length() < 2) {
            QMessageBox::warning(0,"Warning","Неправильная структура файла DICOM");
            return false;
        }
        i32Length = filedicom[iDataElementNo]->setDataElementLength(line);
    }
    else {
        line = file->read(2); i64Pos += 2;
        if (line.length() < 2) {
            QMessageBox::warning(0,"Warning","Неправильная структура файла DICOM");
            return false;
        }
        line = file->read(4); i64Pos += 4;
        if (line.length() < 4) {
            QMessageBox::warning(0,"Warning","Неправильная структура файла DICOM");
            return false;
        }
        i32Length = filedicom[iDataElementNo]->setDataElementLength(line);
    }
    if (i32Length > 1000 ) {
        QMessageBox::warning(0,"Warning","Длина группы " + filedicom[iDataElementNo]->getGroupNumberString() +
        " элемент " + filedicom[iDataElementNo]->getElementNumberString() +
        " равна " + QString::number(i32Length));

    }

    line = file->read(filedicom[iDataElementNo]->getDataElementLength());
    i64Pos += filedicom[iDataElementNo]->getDataElementLength();
    if (quint32(line.length()) != filedicom[iDataElementNo]->getDataElementLength()) {
        QMessageBox::warning(0,"Warning","Неправильная длина элемента данных");
        return false;
    }
    filedicom[iDataElementNo]->setDataElementValue(line);

/*
    if (filedicom[iDataElementNo]->getDataElementLength() > 1000) {
        QFile file("3");
        if (!file.open(QIODevice::ReadWrite))
            return false;
        file.write(line);
        file.close();
        QGraphicsScene *scene = new QGraphicsScene;
        QByteArray baData(filedicom[iDataElementNo]->getDataElementValueByteArray().left(filedicom[iDataElementNo]->getDataElementValueByteArray().length()));
        QPixmap * pmData = new QPixmap;
        pmData->loadFromData(line);
        scene->addPixmap(QPixmap("3"));
        scene->addText("proba");
        ui->graphicsView->setScene(scene);
        ui->graphicsView->show();
    }
*/

    if (filedicom[iDataElementNo]->getDataElementLength() < 1000) {
        if ( (filedicom[iDataElementNo]->getGroupNumberString() == "0028") && (filedicom[iDataElementNo]->getElementNumberString() == "0010") ) {
            quint64 iSum = 0;
            for (quint8 i = 0 ; i < filedicom[iDataElementNo]->getDataElementLength(); i++) {
                iSum += (quint8)filedicom[iDataElementNo]->getDataElementValueByteArray().at(i)*(i*256);
            }
            ui->plainTextEdit->appendPlainText(filedicom[iDataElementNo]->getGroupNumberString() + ":" + filedicom[iDataElementNo]->getElementNumberString()
                + "  Rows: " + QString::number(iSum) );
        }
        else
            ui->plainTextEdit->appendPlainText(filedicom[iDataElementNo]->getGroupNumberString() + ":" + filedicom[iDataElementNo]->getElementNumberString()
                + "  " + filedicom[iDataElementNo]->getDataElementValueString());

    }
    if (iDataElementNo < (MAX_DATA_ELEMENT - 1))
        iDataElementNo++;
    else {
        QMessageBox::warning(0,"Warning","Превышено максимальное количество элементов данных - " + QString::number(MAX_DATA_ELEMENT));
        return false;
    }
    return true;
}    \


//*****************************************************************************
void MainWindow::slotOpenFolder()
{
    QString sFolderName;
    sFolderName = QFileDialog::getExistingDirectory(this,
        tr("Open Folder"), "/home", QFileDialog::ShowDirsOnly);
    if (sFolderName != "") {

    }
}

//*****************************************************************************
void MainWindow::slotContents()
{
    if ( logdicom->frmDialHelp == NULL) {
        logdicom->frmDialHelp = new DialHelp();
        logdicom->frmDialHelp->setModal(false);
        logdicom->frmDialHelp->show();
    }
    logdicom->frmDialHelp->activateWindow();
}


//*****************************************************************************
void MainWindow::slotAbout()
{
    QMessageBox::information(0, tr("About Program logdicom"), tr("logdicom 0.1.1 \n Viewing dicom files"));
}

