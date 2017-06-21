#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>

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

    QAction *msgExit = new QAction(tr("Exit"),mnFile);
    connect(msgExit, SIGNAL(triggered()), this, SLOT(slotExit()));
    mnFile->addAction(msgExit);
    ui->menuBar->addMenu(mnFile); // Добавляем пункты меню в menuBar, т.е. те, которые будут отображаться в гл. окне

    QMenu * mnHelp = new QMenu(tr("Help")); // Меню помощь

    QAction *msgContents = new QAction(tr("Contents"),mnHelp);
    connect(msgContents, SIGNAL(triggered()), this, SLOT(slotContents()));
    mnHelp->addAction(msgContents);

    QAction *msgAbout = new QAction(tr("About logdicom"),mnHelp);
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
    sFileName = QFileDialog::getOpenFileName(this,
        tr("Open File"), "/home", tr("Dicom Files (*.dicom);;All Files(*)"));
}

//*****************************************************************************
void MainWindow::slotOpenFolder()
{
    QString sFolderName;
    sFolderName = QFileDialog::getExistingDirectory(this,
        tr("Open Folder"), "/home", QFileDialog::ShowDirsOnly);
}

//*****************************************************************************
void MainWindow::slotAbout()
{

}

