#include "autor.h"
#include "ui_autor.h"
#include<QDesktopServices>
#include<QUrl>

Autor::Autor(QWidget *parent) :QDialog(parent),ui(new Ui::Autor){
    ui->setupUi(this);


}

Autor::~Autor(){
    delete ui;
}


void Autor::on_Youtube_clicked(){
    QString link = "https://www.youtube.com/channel/UCLuiLXC89Ji--gmacl6Zt3g";
    QDesktopServices::openUrl(QUrl(link));
}


void Autor::on_Github_clicked(){
    QString link = "https://github.com/enrique76";
    QDesktopServices::openUrl(QUrl(link));
}


void Autor::on_Facebook_clicked(){
    QString link = "https://www.facebook.com/luisenrique.cruz.5201/";
    QDesktopServices::openUrl(QUrl(link));
}

void Autor::on_Instagram_clicked(){
    QString link = "https://www.instagram.com/luis_cruz_xd/";
    QDesktopServices::openUrl(QUrl(link));
}

