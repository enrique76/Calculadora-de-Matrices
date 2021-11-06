#include "pye.h"
#include "ui_pye.h"
#include<stdlib.h>
#include<QDebug>
#include<QtCharts>
#include<QChartView>
#include<QPieSeries>
#include<QPieSlice>
#include<QMessageBox>
#include<math.h>
#include<QFile>
#include"direccion.h"
#include<QVector>
#include<QSharedPointer>
#include<QMouseEvent>

pye::pye(QWidget *parent) :QDialog(parent),ui(new Ui::pye){
    ui->setupUi(this);

    ui->h->setColumnCount(3);
    QStringList l2;
    l2<<"Dato"<<"Frecuencia"<<"%";
    ui->h->setHorizontalHeaderLabels(l2);
    ui->h->setColumnWidth(0,80);
    ui->h->setColumnWidth(1,80);
    ui->h->setColumnWidth(2,160);
    ui->d->setColumnWidth(0,100);
    ui->d->setColumnWidth(1,170);
    ui->d->setColumnWidth(2,120);
    ui->d->setColumnWidth(3,120);
    ui->d->setColumnWidth(4,170);
    ui->d->setColumnWidth(5,120);
    l2.clear();
    ui->d->setColumnCount(6);
    setWindowTitle("Estadistica");


}

pye::~pye()
{
    delete ui;
}

void pye::PasarDatos(QTableWidget *d){
    datos = new double*[d->rowCount()];

    for(int i=0;i<d->rowCount();i++){
        datos[i] = new double[d->columnCount()];
    }

    f = d->rowCount();
    c = d->columnCount();

    for(int i=0;i<f;i++){
        for(int j=0;j<c;j++){
            datos[i][j] = d->item(i,j)->text().toDouble();
        }
    }

    for(int i=0;i<f;i++){
        for(int j=0;j<c;j++){
            s.append(datos[i][j]);
            aux.append(0);
        }
    }
}

void pye::Histograma(){
    Shell();

    // acomodar columnas

    ui->h->setColumnWidth(0,(ui->h->width()/3));
    ui->h->setColumnWidth(1,(ui->h->width()/3));
    ui->h->setColumnWidth(2,(ui->h->width()/3));

   double y = s[0];
    x = 0;

    for(int i=0;i<(f*c);i++){
        if(s[i] == y){
            aux[x]+=1;
        }
        else{
            l<<y;
            y = s[i];
            i--;
            x++;
        }
    }

    l<<y;
    ui->h->setRowCount(x+2);
    // s = numeros<double>
    // aux = repeticiones<int>
    // l = numeros sin repetir<QStrinList>

    int nn = 0;
    double p = 0;
     max = aux[0],min = aux[0];

    for(int i=0;i<x;i++){
        if(aux[i] > max){
            max = aux[i];
        }

        if(aux[i] < min){
            min = aux[i];
        }
    }

    for(int i=0;i<x+1;i++){
            ui->h->setItem(i,0,new QTableWidgetItem("    "+QString::number(l.at(i))));
            ui->h->setItem(i,1,new QTableWidgetItem("    "+QString::number(aux[i])));
            nn+=aux[i];
            ui->h->setItem(i,2,new QTableWidgetItem("    "+QString::number((aux[i]/(f*c))*100)+"%"));
            p+=(aux[i]/(f*c))*100;
    }

    for(int i=0;i<x+1;i++){
        if(ui->h->item(i,1)->text().toDouble() == max){
            ui->h->item(i,0)->setBackground(QBrush(Qt::red));
            ui->h->item(i,1)->setBackground(QBrush(Qt::red));
            ui->h->item(i,2)->setBackground(QBrush(Qt::red));
        }
        else if(ui->h->item(i,1)->text().toDouble() == min){
            ui->h->item(i,0)->setBackground(QBrush(Qt::green));
            ui->h->item(i,1)->setBackground(QBrush(Qt::green));
            ui->h->item(i,2)->setBackground(QBrush(Qt::green));
        }
    }

    ui->h->setItem(x+1,0,new QTableWidgetItem("Total"));
    ui->h->setItem(x+1,1,new QTableWidgetItem("    "+QString::number(nn)));
    ui->h->setItem(x+1,2,new QTableWidgetItem("    "+QString::number(p)+"%"));

    // atributos
    ui->Mayor->setText(ui->Mayor->text()+"  "+QString::number(s[s.size()-1]));
    ui->Menor->setText(ui->Menor->text()+"  "+QString::number(s[0]));

    double suma = 0;
    double sumaV = 0;

    for(int i=0;i<s.size();i++){
        suma+=s[i];
    }
    ui->Sumatoria->setText(ui->Sumatoria->text()+"  "+QString::number(suma));
    ui->Media->setText(ui->Media->text()+"  "+QString::number(suma/(f*c)));

    double m = suma/(f*c);

    for(int i=0;i<s.size();i++){
        sumaV += (pow((s[i] - m),2))/(f*c);
    }

    ui->Varianza->setText(ui->Varianza->text()+"  "+QString::number(sumaV));
    ui->DesviacionE->setText(ui->DesviacionE->text()+"  "+QString::number(sqrt(sumaV)));

    // mediana

    int n = (f*c)/2;

    if((f*c)%2 == 0){
        ui->Mediana->setText(ui->Mediana->text()+"  "+QString::number(((s[n])+(s[n-1]))/2));
    }
    else{
        ui->Mediana->setText(ui->Mediana->text()+"  "+QString::number(s[n]));
    }

    // moda

    max = aux[0];
    int r = 0;

    for(int j=0;j<aux.size();j++){
        if(max < aux[j]){
            max = aux[j];
        }
    }

    QString q;

    for(int j=0;j<=x;j++){
        if(aux.at(j) == max){
            if(r > 0){
                q+=",";
            }
            r++;
            q+=QString::number(l.at(j));
        }
    }

    if(r==1){
        ui->Moda->setText(ui->Moda->text()+"    "+q);
    }
    else{
        ui->Moda->setText(ui->Moda->text()+"    Multimoda("+q+")");
    }

    if(s[0] > 0){
        Distribucion();
    }
    else{
        ui->d->setEnabled(false);
    }

    GraficaBarras(5);
}

void pye::Distribucion(){
    int n = f*c;
    // numero de clase
    int k = ceil(sqrt(f*c));

    // intervalo de clase
    int in = ceil((l.at(l.size()-1)-l.at(0))/k);

    //limites

    double li = l.at(0)-0.5;
    double ls = li + in;

    // frecuencias


    QVector<double> fa,fe;

    for(int i=0;i<s.size();i++){
        fe.append(0);
        fa.append(0);
    }

    x = 0;
    for(int i=0;i<s.size();i++){
        if(s.at(i) > li && s.at(i) < ls ){
            fe[x]++;
        }
        else if(s.at(i) >= ls){
           i--;
           li = ls;
           ls+=in;
           x++;
        }
    }

    x = 0;

    fa[0] = fe[0];

    for(int i=1;i<fe.size();i++){
        fa[i] = fa[i-1] + fe[i];
    }

     li = l.at(0)-0.5;
     ls = li + in;

    x = 0;

    ui->d->setRowCount(k+1);
    int suma_f = 0;
    double suma_fr = 0;
    for(int i=0;i<k;i++){
        ui->d->setItem(i,0,new QTableWidgetItem("       "+QString::number(i+1)));
        //Limites
        ui->d->setItem(i,1,new QTableWidgetItem("       "+QString::number(li)+","+QString::number(ls)));

        //frecuencias
        ui->d->setItem(i,2,new QTableWidgetItem("       "+QString::number(fe.at(x))));
        suma_f += fe.at(x);
        //frecuencia acumulada
        ui->d->setItem(i,3,new QTableWidgetItem("       "+QString::number(fa.at(x))));
        // frecuencia relativa
        ui->d->setItem(i,4, new QTableWidgetItem("       "+QString::number((fe.at(x))/double(n))));
        suma_fr += (fe.at(x)/double(n));
        // marca de clase
        ui->d->setItem(i,5,new QTableWidgetItem("       "+QString::number((li+ls)/2)));
        li = ls;
        ls+=in;
        x++;
    }
    ui->d->setItem(k,0,new QTableWidgetItem(" "));
    ui->d->setItem(k,1,new QTableWidgetItem(" "));
    ui->d->setItem(k,2,new QTableWidgetItem("       "+QString::number(suma_f)));
    ui->d->setItem(k,3,new QTableWidgetItem(" "));
    ui->d->setItem(k,4,new QTableWidgetItem("       "+QString::number(suma_fr)));
    ui->d->setItem(k,5,new QTableWidgetItem(" "));
    ui->d->setItem(k,6,new QTableWidgetItem(" "));

}

void pye::Shell(){
    x = f*c;
    int salto = x/2;
    double t;

    while(salto > 0){
        for(int i=salto;i<x;i++){
            int j = i - salto;
            while(j >=0){
                int k = j + salto;
                if(s[j] <= s[k]){
                        j=-1;
                }
                else{
                    t = s[j];
                    s[j] = s[k];
                    s[k] = t;
                    j-=salto;
                }
            }
        }
        salto/=2;
    }
}

long pye::Factorial(int x){

    long f = 1;

    for(int i=1;i<=x;++i){
        f *= i;
    }

    return f;
}

void pye::GraficaPastel(int z){
    QPieSeries *series = new QPieSeries();
    QString aux;

    series->setHoleSize(0.35);

    for(int i=0;i<ui->h->rowCount()-1;i++){
        aux = ui->h->item(i,2)->text();
        aux.chop(1);
        series->append(ui->h->item(i,0)->text()+" - "+aux+"%",aux.toDouble());

        QPieSlice *slice = series->slices().at(i);
        slice->setLabelVisible(true);
        if(ui->h->item(i,0)->background() == Qt::red){
            slice->setExploded(true);
        }

            //ui->h->item(i,0)->setBackgroundColor(slice->color());
    }


    QChart *plot = new QChart();
    plot->addSeries(series);
    plot->setTitle("Histograma de Frecuencias - Grafica de Pastel");
    plot->setAnimationOptions(QChart::SeriesAnimations);
    plot->setTheme(QChart::ChartThemeDark);
    plot->legend()->hide();

    if(z == 0){
        plot->zoomIn();
    }
    else if(z == 1){
        plot->zoomOut();
    }
    else if(z == 2){
        plot->zoomReset();
    }

    QChartView *chartview = new QChartView(plot);
    chartview->setRenderHint(QPainter::Antialiasing);
    chartview->setParent(ui->basePastel);


}

void pye::GraficaBarras(int z){
    QBarSet *set = new QBarSet("Frecuencia");
    QStringList categorias;

        for(int i=0;i<ui->h->rowCount()-1;i++){
            *set<<ui->h->item(i,1)->text().toDouble(); // datos en y
            categorias<<ui->h->item(i,0)->text(); // datos en x
        }

       if(HoV){
           QBarSeries *series = new QBarSeries();
           series->append(set);
           QChart *chart = new QChart();
           chart->addSeries(series);
           chart->setAnimationOptions(QChart::SeriesAnimations);

           QBarCategoryAxis *axis = new QBarCategoryAxis();
           axis->append(categorias);
           chart->createDefaultAxes();
           chart->setAxisX(axis, series);
           chart->setTheme(QChart::ChartThemeDark);
           chart->legend()->hide();
           chart->setTitle("Histograma de Frecuencias - Grafica de Barras");



           QChartView *plot = new QChartView(chart);
           plot->setParent(ui->baseBarras);
       }
       else{
           QHorizontalStackedBarSeries *series = new QHorizontalStackedBarSeries();
           series->append(set);
           QChart *chart = new QChart();
           chart->addSeries(series);
           chart->setAnimationOptions(QChart::SeriesAnimations);

           QBarCategoryAxis *axis = new QBarCategoryAxis();
           axis->append(categorias);
           chart->createDefaultAxes();
           chart->setAxisX(axis, series);
           chart->setTheme(QChart::ChartThemeDark);
           chart->legend()->hide();

           if(z == 0){
               chart->zoomIn();
           }
           else if(z == 1){
               chart->zoomOut();
           }
           else if(z == 2){
               chart->zoomReset();
           }

           QChartView *plot = new QChartView(chart);
           plot->setParent(ui->baseBarras);
       }
}

void pye::GraficaLineal(int z){
    QLineSeries *series = new QLineSeries();

    for(int i=0;i<ui->h->rowCount()-1;i++){
        series->append(ui->h->item(i,0)->text().toDouble(),ui->h->item(i,1)->text().toDouble());

    }



    //*series << QPointF(11,1) << QPointF(11,1) << QPointF(11,1) << QPointF(11,1) << QPointF(11,1) << QPointF(11,1);

     QChart *chart = new QChart();
     chart->addSeries(series);
     chart->setAnimationOptions(QChart::SeriesAnimations);
     chart->setTheme(QChart::ChartThemeDark);
     chart->legend()->hide();
     chart->setTitle("Histograma de Frecuencias - Grafica Lineal");
     chart->createDefaultAxes();

     if(z == 0){
         chart->zoomIn();
     }
     else if(z == 1){
         chart->zoomOut();
     }
     else if(z == 2){
         chart->zoomReset();
     }



     QChartView *plot = new QChartView(chart);
     plot->setParent(ui->baseLineal);
     plot->setRenderHint(QPainter::Antialiasing);



}

void pye::on_guardar_clicked(){


}


void pye::on_tabWidget_tabBarClicked(int index)
{
    switch(index){
        case 0:
            GraficaBarras(5);
        break;
        case 1:
            GraficaPastel(5);
        break;
        case 2:
            GraficaLineal(5);
        break;
    }
}


void pye::on_ventanas_tabBarClicked(int index){
    switch(index){
        case 0:
            GraficaBarras(5);
        break;
    }
}

void pye::on_MasZoom_clicked(){
    if(ui->tabWidget->currentIndex() == 0){
        GraficaBarras(0);
        qDebug()<<"Barras y Mas Zoom";
    }
    else if(ui->tabWidget->currentIndex() == 1){
        qDebug()<<"Pastel y  Mas Zoom";
    }
    else{
        qDebug()<<"Linea y Mas Zoom";
    }
}

void pye::on_ZoomOriginal_clicked(){
    if(ui->tabWidget->currentIndex() == 0){
        qDebug()<<"Barras y Zoom Original";
    }
    else if(ui->tabWidget->currentIndex() == 1){
        qDebug()<<"Pastel y Zoom Original";
    }
    else{
        qDebug()<<"Linea y Zoom Original";
    }
}

void pye::on_MenosZoom_clicked(){
    if(ui->tabWidget->currentIndex() == 0){
        qDebug()<<"Barras y Menos Zoom";
    }
    else if(ui->tabWidget->currentIndex() == 1){
        qDebug()<<"Pastel y Menos Zoom ";
    }
    else{
        qDebug()<<"Lineal y Menos Zoom ";
    }
}

