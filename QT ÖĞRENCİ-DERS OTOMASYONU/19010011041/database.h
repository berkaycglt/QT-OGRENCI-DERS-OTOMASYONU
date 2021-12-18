#ifndef DATABASE_H
#define DATABASE_H
#include "qstring.h"

class database
{
public:
    database(){}
    void ogr_add(const int &no,const QString &ad,const QString &soyad);
    void ogr_update(const int &no,const QString &ad,const QString &soyad);
    void ogr_delete(const int &no);
    void ogr_all( QVector<int> &no,  QVector<QString> &ad,  QVector<QString> &soyad);

    void ders_add(const int &kod,const QString &ad);
    void ders_update(const int &kod,const QString &ad);
    void ders_delete(const int &kod);
    void ders_all(QVector<int> &kod, QVector<QString> &ad);

    void not_add(const int &no,const int &kod,const int &vize,const int &final,const int &esik);
    void not_all( QVector<int> &no, QVector<int> &kod, QVector<int> &vize, QVector<int> &final, QVector<int> &esik);


};

#endif // DATABASE_H
