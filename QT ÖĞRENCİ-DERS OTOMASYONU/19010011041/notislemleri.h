#ifndef NOTISLEMLERI_H
#define NOTISLEMLERI_H

#include <QDialog>

namespace Ui {
class notIslemleri;
}

class notIslemleri : public QDialog
{
    Q_OBJECT

public:
    explicit notIslemleri(QWidget *parent = nullptr);
    ~notIslemleri();

private slots:
    void on_pushButton_clicked();
    void selected_ogr(int row, int column);
    void selected_ders(int row, int column);

private:
    Ui::notIslemleri *ui;
    QString hata  ="Hata!";
    QString ok = "OK";
    QString gerekli = "Gerekli alanları doldurunuz.";
    QString silinemez = "Bu öğrenci silinemez. Bu öğrencinin üstüne tanımlanmış dersler vardır!";
    int selected_kod;
    int selected_no;
    QVector<int> no;
    QVector<int> kod;
    void initilizer();
//    QVector<QString> ad;
//    QVector<QString> soyad;
};

#endif // NOTISLEMLERI_H
