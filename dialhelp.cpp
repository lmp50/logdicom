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
        QStandardItemModel *modelList = new QStandardItemModel (4,1,this);
        for (int row = 0; row < 4; ++row) {
            QStandardItem *item = new QStandardItem(QString("row %0").arg(row));
            modelList->setItem(row, 0, item);
        }
        ui->listView->setModel(modelList);
    }
    else {
        QStandardItemModel *modelList = new QStandardItemModel (1,1,this);
        QStandardItem *item = new QStandardItem(QString(" "));
        modelList->setItem(0, 0, item);
        ui->listView->setModel(modelList);
    }
}
