#include "dialhelp.h"
#include "ui_dialhelp.h"
#include <QPushButton>
#include <QStandardItemModel>
#include <QStandardItem>

QStandardItemModel *model;

DialHelp::DialHelp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::DialHelp)
{
    ui->setupUi(this);

    ui->splitter->setStretchFactor(0,1);
    ui->splitter->setStretchFactor(1,2);

    model = new QStandardItemModel (this);

    QStandardItem *parentItem = model->invisibleRootItem();

    QStandardItem *item1 = new QStandardItem("About logdicom");
    parentItem->appendRow(item1);

    QStandardItem *item2 = new QStandardItem("Standards");
    parentItem->appendRow(item2);

    QStandardItem *item3 = new QStandardItem("File");
    parentItem->appendRow(item3);

    QStandardItem *item4 = new QStandardItem("Tools");
    parentItem->appendRow(item4);

    QStandardItem *item5 = new QStandardItem("Setting");
    parentItem->appendRow(item5);


    parentItem = item2;

    QStandardItem *item21 = new QStandardItem("DICOM file structure");
    parentItem->appendRow(item21);

    parentItem = item3;

    QStandardItem *item31 = new QStandardItem("Open file");
    parentItem->appendRow(item31);

    QStandardItem *item32 = new QStandardItem("Open folder");
    parentItem->appendRow(item32);

    QStandardItem *item33 = new QStandardItem("Export");
    parentItem->appendRow(item33);

    QStandardItem *item34 = new QStandardItem("Import");
    parentItem->appendRow(item34);

    QStandardItem *item35 = new QStandardItem("Exit");
    parentItem->appendRow(item35);

    ui->treeView->setModel(model);
    connect(ui->treeView, SIGNAL(clicked(QModelIndex)),
            this, SLOT(slotTreeClicked(QModelIndex)));

}

DialHelp::~DialHelp()
{
    delete ui;
}

void DialHelp::slotTreeClicked(const QModelIndex &index)
{
    //int i = index.row();
    QStandardItem *item = model->itemFromIndex(index);
    QString itemName = item->text();
    if (itemName == "DICOM file structure") {
        QStandardItemModel *modelList = new QStandardItemModel (16,1,this); //четыре строки и 1 колонка
        QStandardItem *item = new QStandardItem("Первые 128 байт не испльзуются в формате DICOM  и обычно заполнены нулями.");
        modelList->setItem(0, 0, item);
        QStandardItem *item1 = new QStandardItem("Далее следуют символы 'D','I','C','M'.");
        modelList->setItem(1, 0, item1);
        QStandardItem *item2 = new QStandardItem("После них идут несколько групп, каждая группа начинается тегом (tag),");
        modelList->setItem(2, 0, item2);
        QStandardItem *item3 = new QStandardItem("потом идет представление значения (VR), потом длина значения и само значение.");
        modelList->setItem(3, 0, item3);
        QStandardItem *item4 = new QStandardItem("В зависимости от значения VR существуют два варианта структуры группы");
        modelList->setItem(4, 0, item4);
        QStandardItem *item5 = new QStandardItem("Вариант 1. VR равно OB, OW, OF, SQ, UT или UN");
        modelList->setItem(5, 0, item5);
        QStandardItem *item6 = new QStandardItem("Тег (tag) состоит из 4-х байт, 2 байта номер группы (16 bit unsigned integer) и 2 байта номер элемента (16 bit unsigned integer)");
        modelList->setItem(6, 0, item6);
        QStandardItem *item7 = new QStandardItem("VR состоит из 4-х байт, 2-х байт символов OB, oW и других и 2-х байт резервных заполненных нулями");
        modelList->setItem(7, 0, item7);
        QStandardItem *item8 = new QStandardItem("Длина значения занимает 4 байта (32 bit unsigned integer)");
        modelList->setItem(8, 0, item8);
        QStandardItem *item9 = new QStandardItem("Само значение занимает столько, сколько содержит длина значения");
        modelList->setItem(9, 0, item9);
        QStandardItem *item10 = new QStandardItem("Вариант 2. VR принимает другие значения чем в варианте 1");
        modelList->setItem(10, 0, item10);
        QStandardItem *item11 = new QStandardItem("Тег (tag) состоит из 4-х байт, 2 байта номер группы (16 bit unsigned integer) и 2 байта номер элемента (16 bit unsigned integer)");
        modelList->setItem(11, 0, item11);
        QStandardItem *item12 = new QStandardItem("VR состоит из 2-х байт символов ");
        modelList->setItem(12, 0, item12);
        QStandardItem *item13 = new QStandardItem("Длина значения занимает 2 байта (16 bit unsigned integer)");
        modelList->setItem(13, 0, item13);
        QStandardItem *item14 = new QStandardItem("Само значение занимает столько, сколько содержит длина значения");
        modelList->setItem(14, 0, item14);
        QStandardItem *item15 = new QStandardItem("");
        modelList->setItem(15, 0, item15);


        /*for (int row = 0; row < 4; ++row) {
            QStandardItem *item = new QStandardItem(QString("row %0").arg(row));
            modelList->setItem(row, 0, item);
        }
        */
        ui->listView->setModel(modelList);
    }
    else {
        QStandardItemModel *modelList = new QStandardItemModel (1,1,this);
        QStandardItem *item = new QStandardItem(QString(" "));
        modelList->setItem(0, 0, item);
        ui->listView->setModel(modelList);
    }
}
