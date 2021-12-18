#include "notislemleri.h"
#include "ui_notislemleri.h"
#include <QMessageBox>
#include "database.h"
notIslemleri::notIslemleri(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::notIslemleri)
{
    ui->setupUi(this);
    this->initilizer();
    this->ui->no_lineEdit->setEnabled(false);
    this->ui->kod_lineEdit->setEnabled(false);
    this->ui->vize_lineEdit->setValidator(new QIntValidator(0, 100, this));
    this->ui->final_lineEdit->setValidator(new QIntValidator(0, 100, this));
    QObject::connect(this->ui->ogrler,SIGNAL(cellClicked(int, int)), this, SLOT(selected_ogr(int,int)));
    QObject::connect(this->ui->dersler,SIGNAL(cellClicked(int, int)), this, SLOT(selected_ders(int,int)));
}

notIslemleri::~notIslemleri()
{
    delete ui;
}

void notIslemleri::on_pushButton_clicked()
{
    if(this->ui->no_lineEdit->text() == QString("")){
        QMessageBox::warning(this, hata, gerekli, ok);
    }
    else if(this->ui->kod_lineEdit->text() == QString("")){
        QMessageBox::warning(this, hata, gerekli, ok);
    }
    else if(this->ui->vize_lineEdit->text() == QString("")){
        QMessageBox::warning(this, hata, gerekli, ok);
    }
    else if(this->ui->final_lineEdit->text() == QString("")){
        QMessageBox::warning(this, hata, gerekli, ok);
    }
    else{

        bool control = true;
        //        no.clear();
        QVector<int> t_no;
        QVector<int> t_kod;
        QVector<int> vize;
        QVector<int> final;
        QVector<int> esik;
        const int temp_no = no.at(selected_no);
        const  int temp_kod = kod.at(selected_kod);
        database user;
        user.not_all(t_no,t_kod,vize,final,esik);
        for (int i = 0; i< t_no.size(); i++){
            int number = t_no.at(i);
            int koder = t_kod.at(i);
            if(temp_no == number) {
                if(temp_kod == koder){
                    control = false;
                    break;
                }
            }
        }
        if(control){
            const int vize_not = this->ui->vize_lineEdit->text().toInt();
            const int final_not = this->ui->final_lineEdit->text().toInt();
            const int  esik =  ((60*final_not) + (40*vize_not ))/100;
            user.not_add( temp_no, temp_kod,  vize_not, final_not, esik);
            initilizer();
        }
        else
            QMessageBox::warning(this, "Hata!", "Bu öğrenci üzerinde bu ders zaten tanımlı!", "OK");
    }
}

void notIslemleri::selected_ogr(int row, int column)
{
    selected_no = row;
    int text = this->no.at(row);
    this->ui->no_lineEdit->setText(QString::number(text));
}

void notIslemleri::selected_ders(int row, int column)
{
    selected_kod = row;
    int text = this->kod.at(row);
    this->ui->kod_lineEdit->setText(QString::number(text));
}

void notIslemleri::initilizer()
{
    this->ui->ogrler->clear();
    this->ui->final_lineEdit->clear();
    this->ui->kod_lineEdit->clear();
    this->ui->no_lineEdit->clear();
    this->ui->vize_lineEdit->clear();
    this->no.clear();
    QVector<QString> ad;
    QVector<QString> soyad;
    database user;
    user.ogr_all(no,ad,soyad);
    this->ui->ogrler->setColumnCount(3);
    this->ui->ogrler->setRowCount(ad.size());

    QStringList header_ogr;
    header_ogr << "Öğrenci No" << "Öğrenci Adı" <<  "Öğrenci Soyadı"; ;
    this->ui->ogrler->setHorizontalHeaderLabels(header_ogr);

    for(int i = 0; i < ad.size(); ++i){

        QTableWidgetItem * newrow = new QTableWidgetItem();
        newrow = new QTableWidgetItem();
        newrow->setText(QString::number(no.at(i)));
        this->ui->ogrler->setItem(i,0,newrow);

        newrow = new QTableWidgetItem();
        newrow->setText(ad.at(i));
        this->ui->ogrler->setItem(i,1,newrow);

        newrow = new QTableWidgetItem();
        newrow->setText(soyad.at(i));
        this->ui->ogrler->setItem(i,2,newrow);

    }
    this->ui->ogrler->setSortingEnabled(false);
    this->ui->ogrler->resizeColumnsToContents();
    this->ui->ogrler->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);


    this->ui->dersler->clear();
    this->kod.clear();
    QVector<QString> adlar;
    user.ders_all(kod,adlar);
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
        newrow->setText(adlar.at(i));
        this->ui->dersler->setItem(i,1,newrow);

    }
    this->ui->dersler->setSortingEnabled(false);
    this->ui->dersler->resizeColumnsToContents();
    this->ui->dersler->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);



    this->ui->all->clear();
    QVector<int> t_no;
    QVector<int> t_kod;
    QVector<int> vize;
    QVector<int> final;
    QVector<int> esik;
    user.not_all(t_no ,t_kod , vize , final,esik);
    this->ui->all->setColumnCount(5);
    this->ui->all->setRowCount(t_no.size());

    QStringList header_all;
    header_all << "Öğrenci No" << "Ders Kodu" << "Vize Notu" << "Final Notu" << "Geçme Notu";
    this->ui->all->setHorizontalHeaderLabels(header_all);

    for(int i = 0; i < t_no.size(); ++i){

        QTableWidgetItem * newrow = new QTableWidgetItem();
        newrow = new QTableWidgetItem();
        newrow->setText(QString::number(t_no.at(i)));
        this->ui->all->setItem(i,0,newrow);

        newrow = new QTableWidgetItem();
        newrow->setText(QString::number(t_kod.at(i)));
        this->ui->all->setItem(i,1,newrow);

        newrow = new QTableWidgetItem();
        newrow->setText(QString::number(vize.at(i)));
        this->ui->all->setItem(i,2,newrow);

        newrow = new QTableWidgetItem();
        newrow->setText(QString::number(final.at(i)));
        this->ui->all->setItem(i,3,newrow);

        newrow = new QTableWidgetItem();
        newrow->setText(QString::number(esik.at(i)));
        this->ui->all->setItem(i,4,newrow);

    }
    this->ui->all->setSortingEnabled(false);
    this->ui->all->resizeColumnsToContents();
    this->ui->all->horizontalHeader()->setSectionResizeMode(QHeaderView::Stretch);
}
