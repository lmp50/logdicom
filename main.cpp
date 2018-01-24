#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include "classlogdicom.h"
#include "classfiledicom.h"
#include "constdefine.h"


classLogdicom * logdicom;   // главный класс приложения содержащий все формы
classFiledicom * filedicom[MAX_DATA_ELEMENT]; //класс содержащий данные файла dicomm


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QTranslator translator;
    translator.load(":/Translations/logdicom_" + QLocale::system().name());
    a.installTranslator(&translator);

    logdicom = new classLogdicom();

    return a.exec();
}
