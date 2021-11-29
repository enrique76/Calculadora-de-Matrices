#include "graficarfuncion.h"
#include "ui_graficarfuncion.h"
#include<QMessageBox>
#include<QtCharts>
#include<QBarSet>
#include<QBarSeries>
#include<QLineSeries>
#include<QChartView>
#include<math.h>

#define EXP 718281828459045235360

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
        if(pasos.at(i).count("^") == 1){
            QStringList Subindice = pasos.at(i).split("^");
            aux+= Subindice.at(0)+"<sup>"+Subindice.at(1)+"</sup> ";
        }
        else if(pasos.at(i).count("^") == 1){
            QStringList Subindice = pasos.at(i).split("^");
            aux+= Subindice.at(0)+"<sub>"+Subindice.at(1)+"</sub> ";
        }
        else{
            aux+=pasos.at(i)+" ";
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

    qDebug()<<ui->ecuacion->text();

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

    for(int i=0;i<t.size();i++){
        if(t.at(i) == '+'){
            sr.append("+");
        }
        else if(t.at(i) == '-'){
            sr.append("-");
        }
    }

    QStringList n3 = t.split("-");
    QStringList n3a;

    qDebug()<<n3;

    for(int i=0;i<n3.size();i++){
        if(n3.at(i).count("+")){
            n3a = n3.at(i).split("+");
        }
        else{
            n3a.append(n3.at(i));
        }
    }



    //qDebug()<<t;
//    qDebug()<<"Suma o resta "<<sr;
//    qDebug()<<"Operaciones "<<n3a;



        Data(n3a);

        Graficar();



}

void GraficarFuncion::Graficar(){



     //cplot->setInteractive(true);

//    for(int i=0;i<x.size();i++){
//        this->maxx = x[i];
//        if(this->maxx < x[i]){
//            this->maxx = x[i];
//        }

//        this->minx = x[i];
//        if(this->minx > x[i]){
//            this->minx = x[i];
//        }

//        this->maxy = y[i];
//        if(this->maxy  < y[i]){
//            this->maxy = y[i];
//        }

//        this->miny = y[i];

//        if(this->miny > y[i]){
//            this->miny = y[i];
//        }
//    }

//    ui->plot->addGraph();
//    ui->plot->graph(0)->setData(x, y);
//    // give the axes some labels:
//    ui->plot->xAxis->setLabel("x");
//    ui->plot->yAxis->setLabel("y");
//    // set axes ranges, so we see all data:
//    ui->plot->xAxis->setRange(this->minx,this->maxx);
//    ui->plot->yAxis->setRange(this->miny,this->maxy);

//    //connect(ui->=plot->xAxis, SIGNAL(rangeChanged(QCPRange)), ui->=plot->xAxis2, SLOT(setRange(QCPRange)));
//   // connect(ui->=plot->yAxis, SIGNAL(rangeChanged(QCPRange)), ui->=plot->yAxis2, SLOT(setRange(QCPRange)));

//    ui->plot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectPlottables);

//    //ui->=plot->graph(0)->setBrush(QBrush(QColor(0, 0, 255, 20)));
//    ui->plot->graph(0)->setPen(QPen(Qt::red)); // line color blue for first graph

//    ui->plot->replot();

    ui->tabulacion->setRowCount(x.size());

    for(int i=0;i<x.size();i++){
        ui->tabulacion->setItem(i,0,new QTableWidgetItem(QString::number(x[i])));
        ui->tabulacion->setItem(i,1,new QTableWidgetItem(QString::number(y[i])));
    }

    chart->removeAllSeries();
    chart->setTitle(ui->ecuacion->text());

    QLineSeries *series = new QLineSeries();

    for(int i=0;i<x.size();i++){
        series->append(x[i],y[i]);
    }

     chart->addSeries(series);
     chart->setAnimationOptions(QChart::SeriesAnimations);
     chart->setTheme(QChart::ChartThemeDark);
     chart->legend()->hide();
     //chart->createDefaultAxes();

     Ay->setTitleText("Y");
     Ay->setRange(ui->li->value()-1,ui->ls->value()+1);
     Ax->setTitleText("X");
     Ax->setRange(ui->tabulacion->item(0,0)->text().toDouble(),ui->tabulacion->item(ui->tabulacion->rowCount()-1,0)->text().toDouble());

     chart->addAxis(Ay,Qt::AlignBottom);
     chart->addAxis(Ax,Qt::AlignLeft);

     cplot->setParent(ui->basePlot);
     cplot->setRubberBand(QChartView::HorizontalRubberBand);



    x.clear();
    y.clear();

}

void GraficarFuncion::Data(QStringList a){
    QStringList aux;
    int f = 0;


    for(double i=ui->li->value();i<ui->ls->value();i+=ui->s->value()){
        x.append(i);
    }

    for(int j=0;j<x.size();j++){
        for(int i=0;i<a.size();i++){
            if(a.at(i).count("x")){
                aux = a.at(i).split("^");
                y.append(pow(x[j],aux[1].toInt()));
            }
            else if(a.at(i).count("e^x")){
                aux = a.at(i).split("^");
                y.append(pow(EXP,x[j]));
            }
            else{
                y.append(a.at(i).toDouble());
            }
//            else if(a.at(i).count("sin(x)")){
//                y.append(sin(x[f]));
//            }

        }
    }




    qDebug()<<x;
    qDebug()<<y;

}

void GraficarFuncion::Tabular(){
//   QLineSeries *series = new QLineSeries();

//   for(int i=0;i<x.size();i++){
//       series->append(x.at(i),y.at(i));
//   }


//    chart->addSeries(series);
//    chart->setAnimationOptions(QChart::SeriesAnimations);
//    chart->setTheme(QChart::ChartThemeDark);
//    chart->legend()->hide();
//    chart->createDefaultAxes();
//    chart->series().clear();

//    cplot->setParent(ui->basePlot);

}

void GraficarFuncion::on_ecuacion_textChanged(const QString &arg1){

    QString aux = arg1[ui->ecuacion->cursorPosition()-1];




}

void GraficarFuncion::on_funciones_activated(const QString &arg1){


    int opc = arg1.toInt();
    double y;

    try{

        switch(opc){
            case 0:
                for(double x=ui->li->value();x<ui->ls->value();x+=ui->s->value()){
                    this->x.append(x);
                    this->y.append(sin(x));
                }
            break;
        case 1:
            for(double x=ui->li->value();x<ui->ls->value();x+=ui->s->value()){
                this->x.append(x);
                this->y.append(cos(x));
            }
        break;
        case 2:
            for(double x=ui->li->value();x<ui->ls->value();x+=ui->s->value()){
                this->x.append(x);
                this->y.append(tan(x));
            }
        break;
        case 3:
            for(double x=ui->li->value();x<ui->ls->value();x+=ui->s->value()){
                this->x.append(x);
                this->y.append(1/sin(x));
            }
        break;
        case 4:
            for(double x=ui->li->value();x<ui->ls->value();x+=ui->s->value()){
                this->x.append(x);
                this->y.append(1/cos(x));
            }
        break;
        case 5:
            for(double x=ui->li->value();x<ui->ls->value();x+=ui->s->value()){
                this->x.append(x);
                this->y.append(1/tan(x));
            }
        break;

        }

        Graficar();
    }
    catch(const QString e){
        QMessageBox::critical(this,"Limites","Asegurate que los limites corespondan al rango de la funcion");
    }


}

void GraficarFuncion::on_mas_clicked()
{
    chart->zoomIn();
}

void GraficarFuncion::on_origen_clicked()
{
    chart->zoomReset();
}

void GraficarFuncion::on_menos_clicked()
{
    chart->zoomOut();
}

