#include "funcion.h"
#include "ui_funcion.h"

funcion::funcion(QWidget *parent) :QDialog(parent),ui(new Ui::funcion){
    ui->setupUi(this);


}

funcion::~funcion()
{
    delete ui;
}
