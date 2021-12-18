#ifndef OGRENCIISLEMLERI_H
#define OGRENCIISLEMLERI_H

#include <QDialog>

namespace Ui {
class ogrenciIslemleri;
}

class ogrenciIslemleri : public QDialog
{
    Q_OBJECT

public:
    explicit ogrenciIslemleri(QWidget *parent = nullptr);
    ~ogrenciIslemleri();
    void initializer();

private slots:
    void on_yeni_kayit_clicked();
    void on_sil_clicked();
    void on_guncelle_clicked();
    void selected_ogr(int row, int column);


private:
    Ui::ogrenciIslemleri *ui;
    QVector<int> no;
    QVector<QString> ad;
    QVector<QString> soyad;
    int selected_people;
    QString hata  ="Hata!";
    QString ok = "OK";
    QString gerekli = "Gerekli alanları doldurunuz.";
    QString silinemez = "Bu öğrenci silinemez. Bu öğrencinin üstüne tanımlanmış dersler vardır!";
};

#endif // OGRENCIISLEMLERI_H
