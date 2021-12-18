#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QSqlDatabase>
#include <QSqlDriver>
#include <QSqlError>
#include <QSqlQuery>
#include "QDebug"
#include "database.h"

QSqlDatabase mydatabase;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mydatabase = QSqlDatabase::addDatabase("QSQLITE");
    mydatabase.setDatabaseName("/19010011041.db"); // database pathını kopyala

    if (!mydatabase.open())
    {

        this->ui->veritabani->setText("Veritabanı bağlantısı başarısız.");
    }
    else
        this->ui->veritabani->setText("Veri tabanına bağlandınız.");

    // jpg adres pathlerini kopyala
    this->ui->ogr_islemleri->setIcon(QIcon("/ogr.jpg"));
    this->ui->ogr_islemleri->setIconSize(QSize(150, 150));
    this->ui->ders_islemleri->setIcon(QIcon("/ders.jpg"));
    this->ui->ders_islemleri->setIconSize(QSize(150, 150));
    this->ui->not_islemleri->setIcon(QIcon("/notlar.jpg"));
    this->ui->not_islemleri->setIconSize(QSize(150, 150));


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_ogr_islemleri_clicked()
{
    ogr_sayfa = new ogrenciIslemleri();
    ogr_sayfa->setFixedSize(1100,900);
    ogr_sayfa->show();

}

void MainWindow::on_ders_islemleri_clicked()
{
    ders_sayfa = new dersIslemleri();
    ders_sayfa->setFixedSize(1200,900);
    ders_sayfa->show();
}

void MainWindow::on_not_islemleri_clicked()
{
    not_sayfa = new notIslemleri();
    not_sayfa->setFixedSize(1200,900);
    not_sayfa->show();
}
