#include "direccion.h"
#include "ui_direccion.h"
#include <QFileSystemModel>
#include <QCompleter>
#include <QDebug>


direccion::direccion(QWidget *parent) : QDialog(parent), ui(new Ui::direccion){
    ui->setupUi(this);
    QCompleter *co;
    QFileSystemModel *ayuda;

    ayuda = new QFileSystemModel(this);
    co = new QCompleter(ayuda,this);
    ayuda->setRootPath(QDir::rootPath());
    ui->ruta->setCompleter(co);

    ui->extencion->addItem(".txt");
    ui->extencion->addItem(".csv");
    ui->extencion->addItem(".pdf");
    ui->extencion->addItem(".html");
    ui->extencion->addItem(".docx");
    ui->extencion->addItem(".dic");
    ui->extencion->addItem(".wri");
    ui->extencion->addItem(".nfo");
    ui->extencion->addItem(".odt");
    ui->extencion->addItem(".log");
}

direccion::~direccion(){
    delete ui;
}

void direccion::nombre(QString texto){
    ui->ir->setText(texto);
}

void direccion::ruta(QString &r){
    r = ui->ruta->text();
}

void direccion::ver(bool v){
    ui->extencion->setEnabled(v);
}

void direccion::extencion(QString &e){

    e += ui->extencion->currentText();
}

void direccion::titulo(QString titulo){
    setWindowTitle(titulo);
}

void direccion::en_text(QString text){
    ui->en->setText(text);
}

void direccion::en_Enabled(bool v){
    ui->en->setEnabled(v);
}

bool direccion::en_checked(){
    if(ui->en->isChecked()){
    return true;
    }
    else{
        return false;
    }
}

void direccion::d_Enabled(bool v){
    ui->extencion->setEnabled(v);
}

void direccion::on_ir_clicked(){
    close();
}

