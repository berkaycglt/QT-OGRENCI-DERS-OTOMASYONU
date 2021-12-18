#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "ogrenciislemleri.h"
#include "notislemleri.h"
#include "dersislemleri.h"
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    ogrenciIslemleri * ogr_sayfa;
    notIslemleri *  not_sayfa;
    dersIslemleri * ders_sayfa;

private slots:
    void on_ogr_islemleri_clicked();

    void on_ders_islemleri_clicked();

    void on_not_islemleri_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
