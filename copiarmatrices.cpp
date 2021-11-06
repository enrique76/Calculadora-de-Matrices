#include "copiarmatrices.h"
#include "ui_copiarmatrices.h"

copiarMatrices::copiarMatrices(QWidget *parent) :QDialog(parent),ui(new Ui::copiarMatrices){
    ui->setupUi(this);

}

copiarMatrices::~copiarMatrices(){
    delete ui;
}

bool copiarMatrices::on_buttonBox_accepted(){
    if(ui->Ma->isChecked() || ui->Mb->isChecked()){
        return true;
    }
    else{
        return false;
    }
}

bool copiarMatrices::AOB(){
    if(ui->Ma->isChecked()){
        return true;
    }
    else if(ui->Mb->isChecked()){
        return false;
    }
}

bool copiarMatrices::on_buttonBox_rejected(){
    return true;
}

