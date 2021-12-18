#ifndef DERSISLEMLERI_H
#define DERSISLEMLERI_H

#include <QDialog>

namespace Ui {
class dersIslemleri;
}

class dersIslemleri : public QDialog
{
    Q_OBJECT

public:
    explicit dersIslemleri(QWidget *parent = nullptr);
    ~dersIslemleri();

private slots:
    void on_ekle_clicked();

    void on_update_clicked();

    void on_sil_clicked();
    void selected_ders(int row ,int colom);


private:
    Ui::dersIslemleri *ui;
    bool silme_flag = false;
    void initiliazer();
    int selected_row = -1;
    QVector<int> kod;
    QVector<QString> ad;
    QString hata  ="Hata!";
    QString ok = "OK";
    QString gerekli = "Gerekli alanları doldurunuz.";
    QString silinemez = "Bu kodda başka bir ders vardır. Farklı kodda bir ders ekleyiniz!";
    QString silinemez_ogr = "Bu ders silinemez. Bu derse kayıtlı öğrenciler vardır!";
    QString seciniz = "Ders seçiniz.";
};

#endif // DERSISLEMLERI_H
