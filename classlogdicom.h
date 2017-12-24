#ifndef CLASSLOGDICOM_H
#define CLASSLOGDICOM_H

#include <QObject>
#include "mainwindow.h"
#include "dialhelp.h"

class classLogdicom : public QObject
{
    Q_OBJECT
public:
    explicit classLogdicom(QObject *parent = nullptr);
    DialHelp * frmDialHelp = NULL;

private:
    MainWindow * frmMaimWindow;

signals:

public slots:
};

#endif // CLASSLOGDICOM_H
