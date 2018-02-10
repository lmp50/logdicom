#include "classfiledicom.h"

//*****************************************************************************
classFiledicom::classFiledicom(QObject *parent) : QObject(parent)
{

}

//*****************************************************************************
// Установить номер группы
void classFiledicom::setGroupNumber(QByteArray baGroup)
{
    if (baGroup.length() == 2) {
        m_i16Group = (quint8)baGroup[0] + (quint8)baGroup[1]*256;
    }
}

//*****************************************************************************
// Получить номер группы в виде строки длиной 4 символав шеснадцатеричном виде
QString classFiledicom::getGroupNumberString()
{
    return QString::number(m_i16Group,16).rightJustified(4,'0',true);
}

//*****************************************************************************
// Установить номер элемента
void classFiledicom::setElementNumber(QByteArray baElem)
{
    if (baElem.length() == 2) {
        m_i16Elem = (quint8)baElem[0] + (quint8)baElem[1]*256;
    }
}

//*****************************************************************************
// Получить номер элемента в виде строки длиной 4 символа в шестнадцатеричном виде
QString classFiledicom::getElementNumberString()
{
    return QString::number(m_i16Elem,16).rightJustified(4,'0',true);
}

//*****************************************************************************
// Установить VR
void classFiledicom::setVR(QByteArray baVR)
{
    if (baVR.length() == 2) {
        m_sVR = QString(baVR);
    }
}

//*****************************************************************************
// Получить VR
QString classFiledicom::getVRString()
{
    return m_sVR;
}

//*****************************************************************************
// Установить тип элемента данных 16 бит или 32 бита
void classFiledicom::setDataElementType(quint8 i8Type)
{
    if ((i8Type == 16) || (i8Type == 32) )
        m_i8DataElementType = i8Type;

}

//*****************************************************************************
// Получить тип элемента данных 16 бит или 32 бита
quint8 classFiledicom::getDataElementType()
{
    return m_i8DataElementType;
}

//*****************************************************************************
// Установить длину элемента данных
quint32 classFiledicom::setDataElementLength(QByteArray baLength)
{
    if (baLength.length() == 2) {
        m_i32DataElementLength = (quint8)baLength[0] + (quint8)baLength[1]*256;
    }
    else if (baLength.length() == 4) {
        m_i32DataElementLength = (quint8)baLength[0] + (quint8)baLength[1]*256 + (quint8)baLength[2]*256*256 + (quint8)baLength[3]*256*256*256;
    }
    return m_i32DataElementLength;
}

//*****************************************************************************
// Установить длину элемента данных
quint32 classFiledicom::getDataElementLength()
{\
    return m_i32DataElementLength;
}

//*****************************************************************************
// Установить значение элемента данных
void classFiledicom::setDataElementValue(QByteArray baValue)
{
    m_baValue = baValue;
}

//*****************************************************************************
// Прочитать значение элемента данных
QString classFiledicom::getDataElementValueString()
{
    return QString(m_baValue);
}

//*****************************************************************************
// Прочитать значение элемента данных
QByteArray classFiledicom::getDataElementValueByteArray()
{
    return m_baValue;
}



