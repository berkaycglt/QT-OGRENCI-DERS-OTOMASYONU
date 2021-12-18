#include "dersislemleri.h"
#include "ui_dersislemleri.h"
#include <QMessageBox>
#include "database.h"
dersIslemleri::dersIslemleri(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::dersIslemleri)
{
    ui->setupUi(this);
    initiliazer();
    this->ui->kod_lineEdit->setValidator(new QIntValidator(0, 100, this)); // only number
    QObject::connect(this->ui->dersler,SIGNAL(cellClicked(int, int)), this, SLOT(selected_ders(int,int)));

}

dersIslemleri::~dersIslemleri()
{
    delete ui;
}

void dersIslemleri::on_ekle_clicked()
{
    if(this->ui->ad_lineEdit->text() == QString("")){
        QMessageBox::warning(this, hata, gerekli, ok);
    }
    else if(this->ui->kod_lineEdit->text() == QString("")){
        QMessageBox::warning(this, hata, gerekli, ok);
    }
    else{
        bool control = true;
        this->kod.clear();
        this->ad.clear();
        database user;
        user.ders_all(this->kod,this->ad);
        int ders_kodu = this->ui->kod_lineEdit->text().toInt();
        for (int i = 0; i< kod.size(); i++){
            int temp_kod = kod.at(i);
            if(ders_kodu == temp_kod){
                control = false;
                break;
            }
        }
        if(control){
            QString ders_adi = this->ui->ad_lineEdit->text();
            user.ders_add(ders_kodu,ders_adi);
            this->ui->ad_lineEdit->clear();
            this->ui->kod_lineEdit->clear();
            initiliazer();
        }
        else
            QMessageBox::warning(this, hata, silinemez, ok);
    }
}

void dersIslemleri::on_update_clicked()
{
    if(this->ui->kod_lineEdit->text() == QString("")){
        QMessageBox::warning(this, hata, seciniz, ok);
    }
    else{
        const int ders_kodu = this->kod.at(selected_row);
        const QString ders_adi = this->ui->ad_lineEdit->text();
        database user;
        user.ders_update(ders_kodu,ders_adi);
        this->ui->ad_lineEdit->clear();
        this->ui->kod_lineEdit->clear();
        initiliazer();

    }
}

void dersIslemleri::on_sil_clicked()
{
    if(this->ui->kod_lineEdit->text() == QString("")){
        QMessageBox::warning(this, hata, seciniz, ok);
    }
    else{
        bool control = true;
        QString hata;
        QVector<int> t_no;
        QVector<int> t_kod;
        QVector<int> vize;
        QVector<int> final;
        QVector<int> esik;
        const int ders_kodu = this->kod.at(selected_row);
        database user;
        user.not_all(t_no,t_kod,vize,final,esik);
        for (int i = 0; i< t_no.size(); i++){
            int temp_kod = t_kod.at(i);
            if(ders_kodu == temp_kod){
                control = false;
                break;
            }
        }
        if(control){
            QString ders_adi = this->ui->ad_lineEdit->text();
            user.ders_delete(ders_kodu);
            this->ui->ad_lineEdit->clear();
            this->ui->kod_lineEdit->clear();
            silme_flag = true;
            initiliazer();
            silme_flag = false;

        }
        else
            QMessageBox::warning(this, hata, silinemez_ogr, ok);
    }
}

void dersIslemleri::selected_ders(int row, int colom)
{
    selected_row = row;
    this->ui->kod_lineEdit->setText(QString::number(kod.at(row)));
    this->ui->ad_lineEdit->setText(ad.at(row));
    initiliazer();
}

void dersIslemleri::initiliazer()
{
    this->ui->dersler->clear();
    this->kod.clear();
    this->ad.clear();
    database user;
    user.ders_all(kod,ad);
    this->ui->dersler->setColumnCount(2);
    this->ui->dersler->setRowCount(kod.size());

    QStringList header_ders;
    header_ders << "Ders Kodu" << "Ders Adı";
    this->ui->dersler->setHorizontalHeaderLabels(header_ders);

    for(int i = 0; i < kod.size(); ++i){

        QTableWidgetItem * newrow = new QTableWidgetItem();
        newrow = new QTableWidgetItem();
        newrow->setText(QString::number(kod.at(i)));
        this->ui->dersler->setItem(i,0,newrow);

        newrow = new QTableWidgetItem();
        newrow->setText(ad.at(i));
        this->ui->dersler->setItem(i,1,newrow);

    }
    this->ui->dersler->setSortingEnabled(false);
    this->ui->dersler->resizeColumnsToContents();
    this->ui->dersler->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);



    if(!silme_flag){
        this->ui->ogrler->clear();
        QVector<int> t_no;
        QVector<int> t_kod;
        QVector<int> vize;
        QVector<int> final;
        QVector<int> esik;
        user.not_all(t_no ,t_kod , vize , final,esik);
        this->ui->ogrler->setColumnCount(5);
        this->ui->ogrler->setRowCount(t_no.size());

        QStringList header_all;
        header_all << "Öğrenci No" << "Ders Kodu" << "Vize Notu" << "Final Notu" << "Geçme Notu";
        this->ui->ogrler->setHorizontalHeaderLabels(header_all);
        int ders_kodu =0;
        if (selected_row >=0)
            ders_kodu = this->kod.at(selected_row);

        int y=0;
        for(int i = 0; i < t_no.size(); ++i){
            if(ders_kodu == t_kod.at(i)){
                QTableWidgetItem * newrow = new QTableWidgetItem();
                newrow = new QTableWidgetItem();
                newrow->setText(QString::number(t_no.at(i)));
                this->ui->ogrler->setItem(y,0,newrow);

                newrow = new QTableWidgetItem();
                newrow->setText(QString::number(t_kod.at(i)));
                this->ui->ogrler->setItem(y,1,newrow);

                newrow = new QTableWidgetItem();
                newrow->setText(QString::number(vize.at(i)));
                this->ui->ogrler->setItem(y,2,newrow);

                newrow = new QTableWidgetItem();
                newrow->setText(QString::number(final.at(i)));
                this->ui->ogrler->setItem(y,3,newrow);

                newrow = new QTableWidgetItem();
                newrow->setText(QString::number(esik.at(i)));
                this->ui->ogrler->setItem(y,4,newrow);
                ++y;
            }
        }
        this->ui->ogrler->setSortingEnabled(false);
        this->ui->ogrler->resizeColumnsToContents();
        this->ui->ogrler->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
    }
}
