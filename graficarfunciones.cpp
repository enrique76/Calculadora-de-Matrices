#include "graficarfunciones.h"
#include "ui_graficarfunciones.h"

GraficarFunciones::GraficarFunciones(QWidget *parent) : QMainWindow(parent), ui(new Ui::GraficarFunciones){
    ui->setupUi(this);

    ui->tabulacion->setColumnWidth(0,(ui->tabulacion->width()/2));
    ui->tabulacion->setColumnWidth(1,(ui->tabulacion->width()/2));
}

GraficarFunciones::~GraficarFunciones()
{
    delete ui;
}
