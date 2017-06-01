#include "mainwindow.h"
#include "ui_mainwindow.h"

//*****************************************************************************
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QMenu * mnFile = new QMenu("File"); // создаём меню Файл

    QAction *msgOpenFile = new QAction("Open file",mnFile);
    connect(msgOpenFile, SIGNAL(triggered()), this, SLOT(slotOpenFile()));
    mnFile->addAction(msgOpenFile);

    QAction *msgOpenFolder = new QAction("Open folder",mnFile);
    connect(msgOpenFolder, SIGNAL(triggered()), this, SLOT(slotOpenFolder()));
    mnFile->addAction(msgOpenFolder);

    QAction *msgExit = new QAction("Exit",mnFile);
    connect(msgExit, SIGNAL(triggered()), this, SLOT(slotExit()));
    mnFile->addAction(msgExit);
    ui->menuBar->addMenu(mnFile); // Добавляем пункты меню в menuBar, т.е. те, которые будут отображаться в гл. окне

    QMenu * mnHelp = new QMenu("Help"); // Меню помощь
    ui->menuBar->addMenu(mnHelp);
}

//*****************************************************************************
void MainWindow::slotExit()
{
    close();
}

//*****************************************************************************
MainWindow::~MainWindow()
{
    delete ui;
}

//*****************************************************************************
void MainWindow::slotOpenFile()
{

}

//*****************************************************************************
void MainWindow::slotOpenFolder()
{

}

