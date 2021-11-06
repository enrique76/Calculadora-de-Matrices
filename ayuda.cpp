#include "ayuda.h"
#include "ui_ayuda.h"
#include<QDesktopServices>
#include<QUrl>

ayuda::ayuda(QWidget *parent) : QDialog(parent),ui(new Ui::ayuda){
    ui->setupUi(this);
}

ayuda::~ayuda(){
    delete ui;
}

void ayuda::on_pdf_clicked(){
    QString link = "https://drive.google.com/file/d/13xgQKHWeNjiSih8zkOBQjlBTHyvnHBC3/view?usp=sharing";
    QDesktopServices::openUrl(QUrl(link));
}

void ayuda::on_tutorial_clicked(){
    QString link = "https://www.youtube.com/channel/UCLuiLXC89Ji--gmacl6Zt3g";
    QDesktopServices::openUrl(QUrl(link));
}

void ayuda::on_libros_clicked(){
    QString link = "https://drive.google.com/drive/folders/16L7DLM-eQLaZIj5AoXsE98vwUUIVql6U?usp=sharing";
    QDesktopServices::openUrl(QUrl(link));
}

void ayuda::on_ats_clicked(){
    QString link = "https://www.youtube.com/channel/UC7QoKU6bj1QbXQuNIjan82Q";
    QDesktopServices::openUrl(QUrl(link));
}

