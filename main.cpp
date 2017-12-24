#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include "classlogdicom.h"

classLogdicom * logdicom;


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    translator.load(":/Translations/logdicom_" + QLocale::system().name());
    a.installTranslator(&translator);

    logdicom = new classLogdicom();

    return a.exec();
}
