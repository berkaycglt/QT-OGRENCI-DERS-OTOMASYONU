#include "database.h"

#include <QSqlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include "QDebug"
extern QSqlDatabase mydatabase;

void database::ogr_add(const int &no, const QString &ad, const QString &soyad)
{
    if(!mydatabase.isOpen())
        qDebug() << "Veri Tabanı Açılmadı" ;
    QSqlQuery sorgu(mydatabase);
    QString query (QString("INSERT INTO ogrenci (ogr_no, ogr_ad,ogr_soyad)VALUES(%1,'%2','%3');").arg(QString::number(no),ad,soyad));
    if(!sorgu.exec(query)){
        qDebug() << sorgu.lastError().nativeErrorCode();
    }
}

void database::ogr_update(const int &no, const QString &ad, const QString &soyad)
{
    if(!mydatabase.isOpen())
        qDebug() << "Veri Tabanı Açılmadı" ;
    QSqlQuery sorgu(mydatabase);
    QString query (QString("UPDATE ogrenci set ogr_ad = '%1' , ogr_soyad = '%2' WHERE ogr_no = %3 ;").arg(ad,soyad,QString::number(no)));
    if(!sorgu.exec(query)){
        qDebug() << sorgu.lastError().nativeErrorCode();
    }
}

void database::ogr_delete(const int &no)
{
    if(!mydatabase.isOpen())
        qDebug() << "Veri Tabanı Açılmadı" ;
    QSqlQuery sorgu(mydatabase);
    QString query (QString("DELETE FROM ogrenci WHERE ogr_no = %1;").arg(QString::number(no)));

    if(!sorgu.exec(query)){
        qDebug() << sorgu.lastError().nativeErrorCode();
    }
}

void database::ogr_all(QVector<int> &no, QVector<QString> &ad, QVector<QString> &soyad)
{
    if(!mydatabase.isOpen())
        qDebug() << "Veri Tabanı Açılmadı" ;
    QSqlQuery sorgu(mydatabase);
    QString query (QString("SELECT * FROM ogrenci;"));
    if(!sorgu.exec(query)){
        qDebug() << sorgu.lastError().nativeErrorCode();
    }
    while(sorgu.next()){
        int temp_no;
        QString temp_ad,temp_soyad;
        temp_no = sorgu.value(0).toInt();
        temp_ad = sorgu.value(1).toString().trimmed();
        temp_soyad = sorgu.value(2).toString().trimmed();
        no.append(temp_no);
        ad.append(temp_ad);
        soyad.append(temp_soyad);
    }
}

void database::ders_add(const int &kod, const QString &ad)
{
    if(!mydatabase.isOpen())
        qDebug() << "Veri Tabanı Açılmadı" ;
    QSqlQuery sorgu(mydatabase);
    QString query (QString("INSERT INTO dersler (ders_kodu, ders_adi) VALUES (%1,'%2');").arg(QString::number(kod),ad));

    if(!sorgu.exec(query)){
        qDebug() << sorgu.lastError().nativeErrorCode();
    }
}

void database::ders_update(const int &kod, const QString &ad)
{
    if(!mydatabase.isOpen())
        qDebug() << "Veri Tabanı Açılmadı" ;
    QSqlQuery sorgu(mydatabase);
    QString query (QString("UPDATE dersler set ders_adi = '%1' WHERE ders_kodu = %2;").arg(ad,QString::number(kod)));
    if(!sorgu.exec(query)){
        qDebug() << sorgu.lastError().nativeErrorCode();
    }
}

void database::ders_delete(const int &kod)
{
    if(!mydatabase.isOpen())
        qDebug() << "Veri Tabanı Açılmadı" ;
    QSqlQuery sorgu(mydatabase);
    QString query (QString("DELETE FROM dersler WHERE ders_kodu = %1;").arg(QString::number(kod)));

    if(!sorgu.exec(query)){
        qDebug() << sorgu.lastError().nativeErrorCode();
    }
}

void database::ders_all(QVector<int> &kod, QVector<QString> &ad)
{
    if(!mydatabase.isOpen())
        qDebug() << "Veri Tabanı Açılmadı" ;
    QSqlQuery sorgu(mydatabase);
    QString query (QString("SELECT * FROM dersler;"));
    if(!sorgu.exec(query)){
        qDebug() << sorgu.lastError().nativeErrorCode();
    }
    while(sorgu.next()){
        int temp_kod;
        QString temp_ad;
        temp_kod = sorgu.value(0).toInt();
        temp_ad = sorgu.value(1).toString().trimmed();
        kod.append(temp_kod);
        ad.append(temp_ad);
    }
}

void database::not_add(const int &no, const int &kod, const int &vize, const int &final, const int &esik)
{
    if(!mydatabase.isOpen())
        qDebug() << "Veri Tabanı Açılmadı" ;
    QSqlQuery sorgu(mydatabase);
    QString query (QString("INSERT INTO notlar (ogr_no, ders_kodu, vize_not, final_not, geçme_notu) VALUES (%1,%2,%3,%4,%5);").arg(QString::number(no),QString::number(kod),QString::number(vize),QString::number(final),QString::number(esik)));
    if(!sorgu.exec(query)){
        qDebug() << sorgu.lastError().nativeErrorCode();
    }
}

void database::not_all(QVector<int> &no, QVector<int> &kod, QVector<int> &vize, QVector<int> &final, QVector<int> &esik)
{
    if(!mydatabase.isOpen())
        qDebug() << "Veri Tabanı Açılmadı" ;
    QSqlQuery sorgu(mydatabase);
    QString query (QString("SELECT * FROM notlar;"));
    if(!sorgu.exec(query)){
        qDebug() << sorgu.lastError().nativeErrorCode();
    }
    while(sorgu.next()){
        int temp_no;
        int temp_kod;
        int temp_vize;
        int temp_final;
        int temp_esik;;
        temp_no = sorgu.value(0).toInt();
        temp_kod = sorgu.value(1).toInt();
        temp_vize = sorgu.value(2).toInt();
        temp_final = sorgu.value(3).toInt();
        temp_esik = sorgu.value(4).toInt();

        no.append(temp_no);
        kod.append(temp_kod);
        vize.append(temp_vize);
        final.append(temp_final);
        esik.append(temp_esik);
    }

}
