#include "classlogdicom.h"

classLogdicom::classLogdicom(QObject *parent) : QObject(parent)
{
    frmMaimWindow = new MainWindow();


    frmMaimWindow->show();
}
