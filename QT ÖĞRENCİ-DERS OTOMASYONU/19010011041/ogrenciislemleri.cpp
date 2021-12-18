#include "ogrenciislemleri.h"
#include "ui_ogrenciislemleri.h"
#include "database.h"
#include <QMessageBox>

ogrenciIslemleri::ogrenciIslemleri(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ogrenciIslemleri)
{
    ui->setupUi(this);
    this->ui->no_lineEdit->setValidator(new QIntValidator(0, 100, this));
    this->initializer();
    QObject::connect(this->ui->ogrenciler,SIGNAL(cellClicked(int, int)), this, SLOT(selected_ogr(int,int)));

}

ogrenciIslemleri::~ogrenciIslemleri()
{
    delete ui;
}

void ogrenciIslemleri::initializer()
{

    this->ui->ogrenciler->clear();
    this->no.clear();
    this->ad.clear();
    this->soyad.clear();
    database user;
    user.ogr_all(no,ad,soyad);
    this->ui->ogrenciler->setColumnCount(3);
    this->ui->ogrenciler->setRowCount(ad.size());

    QStringList header;
    header << "Öğrenci No" << "Öğrenci Adı" <<  "Öğrenci Soyadı";
    this->ui->ogrenciler->setHorizontalHeaderLabels(header);

    for(int i = 0; i < ad.size(); ++i){

        QTableWidgetItem * newrow = new QTableWidgetItem();
        newrow = new QTableWidgetItem();
        newrow->setText(QString::number(no.at(i)));
        this->ui->ogrenciler->setItem(i,0,newrow);

        newrow = new QTableWidgetItem();
        newrow->setText(ad.at(i));
        this->ui->ogrenciler->setItem(i,1,newrow);

        newrow = new QTableWidgetItem();
        newrow->setText(soyad.at(i));
        this->ui->ogrenciler->setItem(i,2,newrow);

    }
    this->ui->ogrenciler->setSortingEnabled(false);
    this->ui->ogrenciler->resizeColumnsToContents();
    this->ui->ogrenciler->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);

}

void ogrenciIslemleri::on_yeni_kayit_clicked()
{
    if(this->ui->ad_lineEdit->text() == QString("")){
        QMessageBox::warning(this, hata, gerekli, ok);
    }
    else if(this->ui->soyad_lineEdit->text() == QString("")){
        QMessageBox::warning(this, hata, gerekli, ok);
    }
    else if(this->ui->no_lineEdit->text() == QString("")){
        QMessageBox::warning(this, hata, gerekli, ok);
    }
    else{
        database user;
        const int ogr_no = this->ui->no_lineEdit->text().toInt();
        const QString ogr_ad = this->ui->ad_lineEdit->text();
        const QString ogr_soyad = this->ui->soyad_lineEdit->text();
        user.ogr_add( ogr_no, ogr_ad, ogr_soyad);
        this->initializer();
        this->ui->ad_lineEdit->clear();
        this->ui->soyad_lineEdit->clear();
        this->ui->no_lineEdit->clear();
    }
}

void ogrenciIslemleri::on_sil_clicked()
{
    if(this->ui->no_lineEdit->text() == QString("")){
        QMessageBox::warning(this, hata, gerekli, ok);
    }
    else{
        bool control = true;
        QString hata;
        QVector<int> temp;
        QVector<int> kod;
        QVector<int> vize;
        QVector<int> final;
        QVector<int> esik;

        int ogr_no =this->no.at(selected_people);
        database user;
        user.not_all(temp,kod, vize, final, esik);
        for (int i = 0; i< kod.size(); i++){
            int tmpno = temp.at(i);
            if(ogr_no == tmpno){
                control = false;
                break;
            }
        }
        if(control){
            user.ogr_delete(ogr_no);
            this->initializer();
            this->ui->ad_lineEdit->clear();
            this->ui->soyad_lineEdit->clear();
            this->ui->no_lineEdit->clear();
        }
        else
            QMessageBox::warning(this, hata, silinemez, ok);
    }
}

void ogrenciIslemleri::on_guncelle_clicked()
{
    if(this->ui->ad_lineEdit->text() == QString("")){
        QMessageBox::warning(this, hata, gerekli, ok);
    }
    else if(this->ui->soyad_lineEdit->text() == QString("")){
        QMessageBox::warning(this, hata, gerekli, ok);
    }
    else if(this->ui->no_lineEdit->text() == QString("")){
        QMessageBox::warning(this, hata, gerekli, ok);
    }
    else{
        database user;
        const int temp_no = no.at(selected_people);
        const QString temp_ad = this->ui->ad_lineEdit->text();
        const  QString temp_soyad = this->ui->soyad_lineEdit->text();
        user.ogr_update(temp_no,temp_ad,temp_soyad);
        this->initializer();
        this->ui->ad_lineEdit->clear();
        this->ui->soyad_lineEdit->clear();
        this->ui->no_lineEdit->clear();
    }
}

void ogrenciIslemleri::selected_ogr(int row, int column)
{
    selected_people = row;
    QString temp_ad = ad.at(selected_people);
    QString temp_soyad = soyad.at(selected_people);
    this->ui->ad_lineEdit->setText(temp_ad);
    this->ui->soyad_lineEdit->setText(temp_soyad);
    this->ui->no_lineEdit->setText(QString::number(no.at(row)));


}
