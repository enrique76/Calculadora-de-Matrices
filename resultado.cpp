#include "resultado.h"
#include "ui_resultado.h"
#include "direccion.h"
#include<QMessageBox>
#include<QFile>
#include<QTextStream>
#include<fstream>
#include<QFile>
#include<QTextStream>
#include<math.h>

resultado::resultado(QWidget *parent) : QDialog(parent), ui(new Ui::resultado){
    ui->setupUi(this);

}

resultado::~resultado(){
    delete ui;
}

void resultado::setDimenciones(int f,int c){
    ui->mResultado->setColumnCount(c);
    ui->mResultado->setRowCount(f);
    ui->vResultado->setColumnCount(1);
    ui->vResultado->setRowCount(f);
}

void resultado::agregar(int i, int j, double n){
    ui->mResultado->setItem(i,j,new QTableWidgetItem(QString::number(n)));
}

void resultado::agregar(int i, int j, QString n){
    ui->mResultado->setItem(i,j,new QTableWidgetItem(n));
}

void resultado::agregarV(int i, double n){
    ui->vResultado->setItem(i,0,new QTableWidgetItem(QString::number(n)));
}

void resultado::agregarV(int i, QString n){
    ui->vResultado->setItem(i,0,new QTableWidgetItem(n));
}

double resultado::dar(int i){
    return ui->vResultado->item(i,0)->text().toDouble();
}

void resultado::ver(bool V, int n){
    if(n == 1){
        ui->mResultado->setEnabled(V);
        ui->guardarM->setEnabled(V);
    }
    else if(n == 2){
        ui->vResultado->setEnabled(V);
        ui->guardarV->setEnabled(V);
    }
    else if(n == 3){
        ui->guardarM->setEnabled(V);
    }
    else if(n == 4){
        ui->guardarV->setEnabled(V);
    }
    else if(n == 5){
        ui->pasarA->setEnabled(V);
    }
    else if(n == 6){
        ui->pasarB->setEnabled(V);
    }
}

void resultado::titulos(int n,QString t){
    for(int i=0;i<n;i++){
        ui->mResultado->setHorizontalHeaderItem(i,new QTableWidgetItem("x"+QString::number(i+1)));
        ui->mResultado->setColumnWidth(i,50);
    }
    ui->vResultado->setHorizontalHeaderItem(0,new QTableWidgetItem(t));
}

void resultado::titulos(QString t, int n){
    ui->vResultado->setHorizontalHeaderItem(0,new QTableWidgetItem(t));
    for(int i=0;i<n;i++){
        ui->vResultado->setVerticalHeaderItem(i,new QTableWidgetItem("x"+QString::number(i+1)));
    }
}

void resultado::titulos(int n){
    for(int i=0;i<n;i++){
        ui->mResultado->setColumnWidth(i,50);
        ui->mResultado->setHorizontalHeaderItem(i,new QTableWidgetItem("x"+QString::number(i+1)));
    }
}

void resultado::titulos(QString t){
    ui->vResultado->setHorizontalHeaderItem(0,new QTableWidgetItem(t));
}

void resultado::pasar(double a[][100], double b[][100]){
    if(V == 1){
        for(int i=0;i<ui->mResultado->rowCount();i++){
            for(int j=0;j<ui->mResultado->columnCount();j++){
                a[i][j] = ui->mResultado->item(i,j)->text().toDouble();
            }
        }
    }
    else if(V == 2){
        for(int i=0;i<ui->mResultado->rowCount();i++){
            for(int j=0;j<ui->mResultado->columnCount();j++){
                b[i][j] = ui->mResultado->item(i,j)->text().toDouble();
            }
        }
        V = 0;
    }
}

int resultado::getV()
{
    return V;
}

void resultado::setV(int V)
{
    this->V = V;
}

void resultado::setC(int n,int t){
    ui->mResultado->setColumnCount(n);
    for(int i=0;i<6;i++){
        ui->mResultado->setColumnWidth(i,t);
    }
}

void resultado::setR(int n){
    ui->mResultado->setRowCount(n);

}

void resultado::DistrubucionFrecuencia(double a[][100],int n, double min,int f,int c){
    if(min > 0){
        ui->mResultado->setColumnCount(6);
        ui->mResultado->setColumnWidth(0,50);
        ui->mResultado->setColumnWidth(1,95);
        for(int i=2;i<5;i++){
            ui->mResultado->setColumnWidth(i,70);
        }
        ui->mResultado->setColumnWidth(5,70);

        double aux[100][100];
        this->f = f;
        this->c = c;
        // ordenar los datos
        //shell
        double s[10000];
        double au;
        int x = 0;
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                s[x++] = a[i][j];
                m[i][j] = a[i][j];
            }
        }

        x = n*n;
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
        //shell
        x = 0;
        double max = s[0];
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(s[x] > max){
                    max = s[x];
                }
                aux[i][j] = s[x++];
            }
        }

        QStringList l;
        l<<"Clase"<<"Limites"<<"Frecuencia"<<"Frecuencia\nAcomulada"<<"Frecuencia\nRelativa"<<"Marca de\nClase";
        ui->mResultado->setHorizontalHeaderLabels(l);

        int k = ceil(sqrt(n));
        double f[10];
        double fa[10];
        for(int i=0;i<10;i++){
            f[i] = 0;
            fa[i] = 0;
        }

        int in = ceil((max - min)/k);
        // Calcular los limites reales de clases

        double li = min-0.5;
        double ls = li + in;

        //frecuencia
        x = 0;
        for(int i=0;i<n;i++){
            for(int j=0;j<n;j++){
                if(aux[i][j] > li && aux[i][j] < ls){
                    f[x]++;
                }
                else if(aux[i][j] > ls){
                    j--;
                    li = ls;
                    ls+=in;
                    x++;
                }
            }

        }

        fa[0] = f[0];

        for(int i=0;i<x;i++){
            fa[i+1] = fa[i]+f[i];
        }

        li = min-0.5;
        ls = li + in;
        x = 0;
        ui->mResultado->setRowCount(k);
        for(int i=0;i<k;i++){
            double s;
            ui->mResultado->setItem(i,0,new QTableWidgetItem(QString::number(i+1)));
            // Limites
            ui->mResultado->setItem(i,1, new QTableWidgetItem(QString::number(li)+","+QString::number(ls)));
            // Frecuencia
            ui->mResultado->setItem(i,2,new QTableWidgetItem(QString::number(f[x])));
            // frecuencia acomulada
            ui->mResultado->setItem(i,3,new QTableWidgetItem(QString::number(fa[x])));
            //frecuencia relativa
            ui->mResultado->setItem(i,4,new QTableWidgetItem(QString::number(f[x]/n)));
            //Marca de clase
            s = (li+ls)/2;
            ui->mResultado->setItem(i,5,new QTableWidgetItem(QString::number(s)));
            li = ls;
            ls+=in;
            x++;
        }
        setWindowTitle("Distribucion de Frecuencia");
        ui->pasarA->setEnabled(false);
        ui->pasarB->setEnabled(false);
    }
    else{
            QMessageBox::critical(this,"Distribucion de Frecuencia","El valor minimo debe ser mayor a 0");
        }
}

void resultado::NoPasar(){
    ui->pasarA->setEnabled(false);
    ui->pasarB->setEnabled(false);
}

void resultado::Histograma(int n1,int n2,int n3,int n4,int n5,int n6,QStringList l1,QStringList l2,double aux[],int n,double m[][100]){
    ui->mResultado->setColumnCount(n1);
    ui->mResultado->setRowCount(n2+1);
    l1<<"Total";
    ui->mResultado->setVerticalHeaderLabels(l1);
    ui->mResultado->setHorizontalHeaderLabels(l2);
    ui->mResultado->setColumnWidth(n3,n4);
    ui->mResultado->setColumnWidth(n5,n6);


    //
    int nn = 0;
    double p = 0;
    for(int i=0;i<n2;i++){
        ui->mResultado->setItem(i,0,new QTableWidgetItem(QString::number(aux[i])));
        nn+=aux[i];
        ui->mResultado->setItem(i,1,new QTableWidgetItem(QString::number((aux[i]/n)*100)+"%"));
        p+=(aux[i]/n)*100;
    }

    ui->mResultado->setItem(n2,0,new QTableWidgetItem(QString::number(nn)));
    ui->mResultado->setItem(n2,1,new QTableWidgetItem(QString::number(p)+"%"));
}

void resultado::Color(bool v,int i,int j){
    if(v){
        ui->mResultado->item(i,j)->setBackground(QBrush(Qt::red));
    }
    else{
        ui->mResultado->item(i,j)->setBackground(QBrush(Qt::green));
    }
}

void resultado::pasarA(){
//    if(V != 0){

//        QFile a("C:/Users/Public/AUXILIAR_CM_QT.txt");

//        a.open(QFile::WriteOnly | QFile::Text);

//        QTextStream out(&a);

//        QString texto;

//        for(int i=0;i<ui->mResultado->rowCount();i++){
//            for(int j=0;j<ui->mResultado->columnCount();j++){
//                texto += ui->mResultado->item(i,j)->text() + ",";
//            }
//            texto+="\n";
//            out << texto;
//            texto.clear();
//        }
//        a.flush();
//        a.close();
//    }
}

void resultado::on_pasarA_clicked(){
    //QMessageBox::information(this,"Pasar todo a la matriz A","En proceso");
    if(V == 1){
        V = 0;
        ui->me->setText(" ");
    }
    else{
        V = 1;
        ui->me->setText("Pasar hacia A");
    }
}

void resultado::on_pasarB_clicked(){
    //QMessageBox::information(this,"Pasar todo a la matriz B","En proceso");
    if(V == 2){
        V = 0;
        ui->me->setText(" ");
    }
    else{
        V = 2;
        ui->me->setText("Pasar hacia B");

    }
}

void resultado::on_guardarM_clicked(){

    QString ruta;
    QString extencion;


    if(windowTitle() == "Histograma"){
        direccion d(this);
        d.nombre("Guardar Histograma");
        d.titulo("Ruta     ruta/nombre(elija una extencion)");
        d.en_Enabled(false);
        d.exec();
        d.ruta(ruta);
        if(!ruta.isNull()){
           d.extencion(extencion);
           if(extencion.isNull()){
               extencion = ".txt";
           }

           ruta+=extencion;

           QFile a(ruta);

           a.open(QFile::WriteOnly | QFile::Text);

           QTextStream out(&a);
           QString texto;
           texto =  "Dato,"+ui->mResultado->horizontalHeaderItem(0)->text()+","+ui->mResultado->horizontalHeaderItem(1)->text()+"\n";
           out << texto;
           texto.clear();
           for(int i=0;i<ui->mResultado->rowCount();i++){
               texto += ui->mResultado->verticalHeaderItem(i)->text()+",";
               for(int j=0;j<ui->mResultado->columnCount();j++){
                   texto += ui->mResultado->item(i,j)->text() + ",";
               }
               texto+="\n";
               out << texto;
               texto.clear();
           }
           ruta.clear();
           d.nombre("Guardar Datos");
           d.en_Enabled(true);
           d.en_text("Encriptar");
           d.exec();
           d.ruta(ruta);
           d.extencion(extencion);
            QFile b(ruta+"_DATOS"+extencion);
            b.open(QFile::WriteOnly | QFile::Text);
            QTextStream out_2(&b);
           for(int i=0;i<f;i++){
               for(int j=0;j<c;j++){
                   texto += QString::number(m[i][j])+",";
               }
               texto+="\n";
               out_2 << texto;
               texto.clear();
           }

           a.flush();
           a.close();
           b.flush();
           b.close();
        }
    }
    else if(windowTitle() == "Distribucion de Frecuencia"){
        direccion d(this);
        d.nombre("Guardar Distribucion de Frecuencias");
        d.titulo("Ruta     ruta/nombre(elija una extencion)");
        d.en_Enabled(false);
        d.exec();

        d.ruta(ruta);
        if(!ruta.isNull()){
           d.extencion(extencion);
           if(extencion.isNull()){
               extencion = ".txt";
           }

           QFile a(ruta+extencion);


           a.open(QFile::WriteOnly | QFile::Text);


           QTextStream out(&a);

           QString texto;

           texto += "Clase,Limite_i,Limite_s,Frecuencia,Frecuencia_A,Frecuencia_R,Marca_c\n";

           out << texto;
           texto.clear();
           for(int i=0;i<ui->mResultado->rowCount();i++){
               for(int j=0;j<ui->mResultado->columnCount();j++){
                   texto += ui->mResultado->item(i,j)->text() + ",";
               }
               texto+="\n";
               out << texto;
               texto.clear();
           }

           ruta.clear();
           d.nombre("Guardar Datos");
           d.en_Enabled(true);
           d.en_text("Encriptar");
           d.exec();
           d.ruta(ruta);
           d.extencion(extencion);
            QFile b(ruta+"_DATOS"+extencion);
            b.open(QFile::WriteOnly | QFile::Text);
            QTextStream out_2(&b);
           for(int i=0;i<f;i++){
               for(int j=0;j<c;j++){
                   texto += QString::number(m[i][j])+",";
               }
               texto+="\n";
               out_2 << texto;
               texto.clear();
           }

           a.flush();
           a.close();
           b.flush();
           b.close();
        }
    }
    else{
        direccion d(this);
        d.nombre("Guardar");
        d.titulo("Ruta     ruta/nombre(elija una extencion)");
        d.en_Enabled(true);
        d.en_text("Encriptar");
        d.exec();
        d.ruta(ruta);
        if(d.en_checked()){
            if(!ruta.isNull()){
               extencion = "_e";
               d.extencion(extencion);
               if(extencion.isNull()){
                   extencion = ".txt";
               }

               ruta+=extencion;

               QFile a(ruta);

               a.open(QFile::WriteOnly | QFile::Text);

               QTextStream out(&a);
               QString texto;

               for(int i=0;i<ui->mResultado->rowCount();i++){
                   for(int j=0;j<ui->mResultado->columnCount();j++){
                       texto += QString::number(ui->mResultado->item(i,j)->text().toDouble() * 2 ) + ",";
                   }
                   texto+="\n";
                   out << texto;
                   texto.clear();
               }
               a.flush();
               a.close();
            }

        }
        else{
            if(!ruta.isNull()){
               d.extencion(extencion);
               if(extencion.isNull()){
                   extencion = ".txt";
               }

               ruta+=extencion;

               QFile a(ruta);

               a.open(QFile::WriteOnly | QFile::Text);

               QTextStream out(&a);
               QString texto;

               for(int i=0;i<ui->mResultado->rowCount();i++){
                   for(int j=0;j<ui->mResultado->columnCount();j++){
                       texto += ui->mResultado->item(i,j)->text() + ",";
                   }
                   texto+="\n";
                   out << texto;
                   texto.clear();
               }
               a.flush();
               a.close();
            }
        }
    }
}

void resultado::on_guardarV_clicked(){
    direccion d(this);
    d.nombre("Guardar Matriz");
    d.titulo("Ruta     ruta/nombre(elija una extencion)");
    d.en_Enabled(true);
    d.en_text("Encriptar");
    d.exec();
    QString ruta;
    QString extencion;
    d.ruta(ruta);

    if(d.en_checked()){
        extencion = "_e";
        if(!ruta.isNull()){
           d.extencion(extencion);
           if(extencion.isNull()){
               extencion = ".txt";
           }

           ruta+=extencion;

           QFile a(ruta);

           a.open(QFile::WriteOnly | QFile::Text);

           QTextStream out(&a);
           QString texto;

           for(int i=0;i<ui->vResultado->rowCount();i++){
               texto += QString::number(ui->vResultado->item(i,0)->text().toDouble() * 2 );
               texto+="\n";
           }
           out << texto;
           a.flush();
           a.close();
        }
    }
    else{
        if(!ruta.isNull()){
           d.extencion(extencion);
           if(extencion.isNull()){
               extencion = ".txt";
           }

           ruta+=extencion;

           QFile a(ruta);

           a.open(QFile::WriteOnly | QFile::Text);

           QTextStream out(&a);
           QString texto;

           for(int i=0;i<ui->vResultado->rowCount();i++){
               texto += ui->vResultado->item(i,0)->text();
               texto+="\n";
           }
           out << texto;
           a.flush();
           a.close();
        }
    }
}

