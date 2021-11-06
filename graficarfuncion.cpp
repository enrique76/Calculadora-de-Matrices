#include "graficarfuncion.h"
#include "ui_graficarfuncion.h"
#include<QMessageBox>
#include<QtCharts>
#include<QBarSet>
#include<QBarSeries>
#include<QLineSeries>
#include<QChartView>
#include<math.h>

GraficarFuncion::GraficarFuncion(QWidget *parent) :QDialog(parent), ui(new Ui::GraficarFuncion){
    ui->setupUi(this);

    ui->vEcuacion->setEnabled(false);
    ui->vEcuacion->setStyleSheet("background-color: rgb(170, 0, 0)");

    chart->setTheme(QChart::ChartThemeDark);
    chart->legend()->hide();
    chart->createDefaultAxes();

    cplot->setParent(ui->basePlot);
}

GraficarFuncion::~GraficarFuncion()
{
    delete ui;
}

QString GraficarFuncion::ToHTML(QString t)
{
    QString aux;
    QStringList pasos = t.split(" ");

    for(int i=0;i<pasos.size();i++){
        if(pasos.at(i).count("^") == 0){
            aux+=pasos.at(i)+" ";
        }
        else{
            QStringList Subindice = pasos.at(i).split("^");
            aux+= Subindice.at(0)+"<sup>"+Subindice.at(1)+"</sup> ";
        }


    }

    return aux;
}

void GraficarFuncion::on_fx_clicked(){
    // Convertir a una ecuacion decente
    ui->vEcuacion->setEnabled(false);
    QString t = ui->ecuacion->text();

    ui->funcion->setText(ToHTML(t));
    // fin
    // Limites
    if(ui->li->value() >= ui->ls->value()){
        QMessageBox::critical(this,"Limites","El limite inferior no debe de ser mayor al superior");
    }
    else if(ui->s->value() >= ui->ls->value()){
        QMessageBox::critical(this,"Limites","El Salto no debe de ser mayor al superior");
    }
    else{
        V = true;
    }

    if(V){
        ui->vEcuacion->setEnabled(true);
        ui->vEcuacion->setStyleSheet("background-color: rgb(0, 255, 0)");
    }


}


void GraficarFuncion::on_PasarB_clicked(){
    if(ui->pasar->text() == " "){
        ui->pasar->setText("Pasar Hacia B");
    }
    else{
        ui->pasar->setText(" ");
    }
}

void GraficarFuncion::on_vEcuacion_clicked(){
    ui->vEcuacion->setEnabled(false);
    ui->vEcuacion->setStyleSheet("background-color: rgb(170, 0, 0)");

    QString t = ui->ecuacion->text();
    QVector<QString> sr;

//    for(int i=0;i<t.size();i++){
//        if(t.at(i) == '+'){
//            sr.append("+");
//        }
//        else if(t.at(i) == '-'){
//            sr.append("-");
//        }
//    }

//    QStringList n3 = t.split(" + ");
//    QStringList n3a;

//    for(int i=0;i<n3.size();i++){
//        if(n3.at(i).count("-")){
//            n3a= n3.at(i).split(" - ");
//            n3.append(n3a.at(0));
//            n3.append(n3a.at(1));
//            n3.removeOne(n3.at(i));
//        }
//    }

//    QStringList n2 = n3;
//    QStringList n2a;

//    for(int i=0;i<n2.size();i++){
//        if(n2.at(i).count("^")){
//            n2a.append(n2.at(i));
//        }
//        else if(n2.at(i).count("x")){
//            n2a.append(n2.at(i)+"^1");
//        }
//        else {
//            n2a.append(n2.at(i)+"x^0");
//        }
//    }

//    n2 = n2a;

//    QStringList n1;
//    QStringList n1a;

//    for(int i=0;i<n2.size();i++){
//        n1a = n2.at(i).split("x^");
//        if(n1a.at(0) == " "){
//            n1.append("1");
//        }
//        else{
//            n1.append(n1a.at(0));
//        }
//        n1.append(n1a.at(1));
//    }


    // tabular



    // Graficar

        QLineSeries *series = new QLineSeries();

        for(float i=0;i<5;i+=0.1){
            series->append(i,pow(i,2));
        }


         chart->addSeries(series);
         chart->setAnimationOptions(QChart::SeriesAnimations);
         chart->setTheme(QChart::ChartThemeDark);
         chart->legend()->hide();
         chart->createDefaultAxes();


         cplot->setParent(ui->basePlot);

}

void GraficarFuncion::Tabular(QStringList f){
    QVector<double> x,y;
    double  aux;
    double aux2;
    int c = 0;
    int cf = 0;
    int cs = 0;

    //qDebug()<<f;

    for(double i=ui->li->value();i<ui->ls->value();i+=ui->s->value()){

        x.append(i);



    }

    ui->tabulacion->setRowCount(x.size());

    for(int i=0;i<x.size();i++){
        ui->tabulacion->setItem(i,0, new QTableWidgetItem(QString::number(x.at(i))));
    }

   //qDebug()<<y;
}

void GraficarFuncion::on_ecuacion_textChanged(const QString &arg1){
//    QString texto;

//    for(int i=0;i<arg1.size();i++){
//        if(arg1.at(i) != '(' && arg1.at(i) != ')' && arg1.at(i) != '/' && arg1.at(i) != '*'){
//            texto+=arg1.at(i);
//        }
//    }

//    ui->ecuacion->setText(texto);
}

