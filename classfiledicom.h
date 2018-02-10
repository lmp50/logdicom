#ifndef CLASSFILEDICOM_H
#define CLASSFILEDICOM_H

#include <QObject>

class classFiledicom : public QObject
{
    Q_OBJECT
public:
    explicit classFiledicom(QObject *parent = nullptr);

signals:

public slots:
    void setGroupNumber(QByteArray baGroup);
    QString getGroupNumberString();

    void setElementNumber(QByteArray baElem);
    QString getElementNumberString();

    void setVR(QByteArray baVR);
    QString getVRString();

    void setDataElementType(quint8 i8Type);
    quint8 getDataElementType();

    quint32 setDataElementLength(QByteArray baLength);
    quint32 getDataElementLength();

    void setDataElementValue(QByteArray baValue);
    QString getDataElementValueString();
    QByteArray getDataElementValueByteArray();

private:
    quint16 m_i16Group;
    quint16 m_i16Elem;
    QString m_sVR;
    quint8 m_i8DataElementType;
    quint32 m_i32DataElementLength;
    QByteArray m_baValue;

};

#endif // CLASSFILEDICOM_H
