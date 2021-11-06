#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
#include<QMessageBox>
#include<math.h>
#include<QStringList>
#include<time.h>
#include<chrono>
#include<sstream>
#include<string>
#include<stdlib.h>
#include<QFile>
#include<QTextStream>
#include<QTranslator>
#include "operaciones.h"
#include "direccion.h"
#include "copiarmatrices.h"
#include "autor.h"
#include "ayuda.h"
#include "pye.h"
#include<QTimer>
#include<QDateTime>
#include<QDesktopServices>
#include<QUrl>
#include<graficarfuncion.h>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    srand(time(NULL));
    ui->vResultados->setColumnCount(1);

    ui->vResultados->setHorizontalHeaderItem(0,new QTableWidgetItem("R"));
    for(int i=0;i<10;i++){
        ui->A->setColumnWidth(i,50);
    }

    // R
    ui->vResultados->setColumnWidth(0,90);
    l<<"R    ";
    ui->vResultados->setHorizontalHeaderLabels(l);
    l.clear();

    //B
    ui->B->setColumnWidth(0,50);
    l<<"x1";
    ui->B->setHorizontalHeaderLabels(l);
    l.clear();
    // fecha
    time_t now = time(0);
    tm* time = localtime(&now);
    QString dia,mes,year;

    QStringList meses;
    meses<<"ENERO"<<"FEBRERO"<<"MARZO"<<"ABRIL"<<"MAYO"<<"JUNIO"<<"JULIO"<<"AGOSTO";
    meses<<"SEPTIEMBRE"<<"OCTUBRE"<<"NOVIEMBRE"<<"DICIEMBRE";

    if(time->tm_mday < 10){
        dia = "0"+QString::number(time->tm_mday);
    }
    else{
        dia = QString::number(time->tm_mday);
    }

    mes = meses.at(time->tm_mon);
    year = QString::number(1900 + time->tm_year);

    QString texto;
    texto+=dia+"/"+mes+"/"+year;

    ui->fecha->setText(texto);

    // descripcciones de los botones

    ui->AleatorioA->setToolTip("Numeros Aleatorios en A y en V");
    ui->AleatorioB->setToolTip("Numeros Aleatorios en B");

    ui->identidad_A->setToolTip("Matriz identidad en A");
    ui->identidad_B->setToolTip("Matriz identidad en B");

    ui->llenarNA->setToolTip("Llenar todo de Aux en A");
    ui->llenarNB->setToolTip("Llenar todo de Aux en B");

    ui->OrdenarA->setToolTip("Ordenar A");
    ui->OrdenarB->setToolTip("Ordenar B");

    ui->desordenar_A->setToolTip("Desordenar A");
    ui->desordenar_B->setToolTip("Desordenar B");

    ui->IncrementoA->setToolTip("Salto Medio en A");
    ui->IncrementoB->setToolTip("Salto Medio en B");

    ui->i_s_A->setToolTip("De inferior a nxn en A");
    ui->i_s_B->setToolTip("De inferior a nxn en B");

    ui->saltos_A->setToolTip("De inferior a superior con intervalos de aux en A");
    ui->saltos_B->setToolTip("De inferior a superior con intervalos de aux en B");

    ui->cambio->setToolTip("Cambio entre Matrices");
    ui->vLlenar->setToolTip("Llenar vector de ..");
    ui->copiar_M->setToolTip("Copiar una matriz en otra");
    nA();
    nB();

    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(showTime()));
    timer->start();
}

MainWindow::~MainWindow(){
    delete ui;
}

void MainWindow::on_vLlenar_clicked(){
    auto inicio = std::chrono::system_clock::now();
    QString texto = ui->vLlenar->text();

    for(int i=0;i<fa;++i){
        ui->vResultados->setItem(i,0,new QTableWidgetItem(texto));
    }

    if(ui->vLlenar->text() == "0"){
        ui->vLlenar->setText("1");
    }
    else{
        ui->vLlenar->setText("0");
    }
    auto final = std::chrono::system_clock::now();
    std::chrono::duration<float> duracion = final - inicio;
    ui->tiempo->setText(QString::number(duracion.count()));
}

void MainWindow::on_cb_valueChanged(){
    cb = ui->cb->value();
    nB();
    ui->B->setColumnCount(cb);
    for(int i=0;i<cb;i++){
        ui->B->setHorizontalHeaderItem(i,new QTableWidgetItem("x"+QString::number(i+1)));
        ui->B->setColumnWidth(i,50);
    }
}

void MainWindow::on_ca_valueChanged(){
    ca = ui->ca->value();
    nA();
    ui->A->setColumnCount(ca);
    for(int i=0;i<ca;i++){
        ui->A->setHorizontalHeaderItem(i,new QTableWidgetItem("x"+QString::number(i+1)));
        ui->A->setColumnWidth(i,50);
    }
}

void MainWindow::on_fb_valueChanged(){
    fb = ui->fb->value();
    nB();
    ui->B->setRowCount(fb);
}

void MainWindow::on_fa_valueChanged(){
    fa = ui->fa->value();
    nA();
    ui->A->setRowCount(fa);
    ui->vResultados->setRowCount(fa);
}

void MainWindow::agregarA(int i, int j, double n){
    ui->A->setItem(i,j, new QTableWidgetItem(QString::number(n)));
}

void MainWindow::agregarB(int i, int j, double n){
    ui->B->setItem(i,j, new QTableWidgetItem(QString::number(n)));
}

void MainWindow::on_cambio_clicked(){
    auto inicio = std::chrono::system_clock::now();

    // llenar los compos nulos
    for(int i=0;i<fa;i++){
        for(int j=0;j<ca;j++){
            if(ui->A->item(i,j) == nullptr){
                ui->A->setItem(i,j,new QTableWidgetItem("0"));
            }
        }
    }
    for(int i=0;i<fb;i++){
        for(int j=0;j<cb;j++){
            if(ui->B->item(i,j) == nullptr){
                ui->B->setItem(i,j,new QTableWidgetItem("0"));
            }
        }
    }

    QString aux[100][100];
    QString aux2[100][100];
    if(fa == fb && ca == cb){
        for(int i=0;i<fa;i++){
            for(int j=0;j<ca;j++){
                aux[i][j] = ui->A->item(i,j)->text();
                ui->A->setItem(i,j, new QTableWidgetItem(ui->B->item(i,j)->text()));
                ui->B->setItem(i,j, new QTableWidgetItem(aux[i][j]));
            }
        }
    }
    else{
        for(int i=0;i<ui->A->rowCount();i++){
            for(int j=0;j<ui->A->columnCount();j++){
                aux[i][j] = ui->A->item(i,j)->text();
            }
        }
        for(int i=0;i<ui->B->rowCount();i++){
            for(int j=0;j<ui->B->columnCount();j++){
                aux2[i][j] = ui->B->item(i,j)->text();
            }
        }
        fa = ui->B->rowCount();
        ca = ui->B->columnCount();
        fb = ui->A->rowCount();
        cb = ui->A->columnCount();
        ui->A->setColumnCount(ca);
        ui->A->setRowCount(fa);
        ui->B->setColumnCount(cb);
        ui->B->setRowCount(fb);


        for(int i=0;i<fa;i++){
            for(int j=0;j<ca;j++){
                ui->A->setItem(i,j,new QTableWidgetItem(aux2[i][j]));
                ui->A->setHorizontalHeaderItem(j,new QTableWidgetItem("x"+QString::number(j+1)));
                ui->A->setColumnWidth(j,50);
            }

        }
        for(int i=0;i<fb;i++){
            for(int j=0;j<cb;j++){
                ui->B->setItem(i,j,new QTableWidgetItem(aux[i][j]));
                ui->B->setHorizontalHeaderItem(j,new QTableWidgetItem("x"+QString::number(j+1)));
                ui->B->setColumnWidth(j,50);
            }
        }
    }

    int f,c;
    double fc;
    f = ui->fa->value();
    c = ui->ca->value();
    ui->fa->setValue(ui->fb->value());
    ui->ca->setValue(ui->cb->value());
    ui->fb->setValue(f);
    ui->cb->setValue(c);

    for(int i=0;i<fa;i++){
        if(ui->vResultados->item(i,0) == nullptr){
            ui->vResultados->setItem(i,0,new QTableWidgetItem("0"));
        }
    }

    f = ui->sA->value();
    c = ui->iA->value();
    fc = ui->aux_A->value();
    ui->sA->setValue(ui->sB->value());
    ui->iA->setValue(ui->iB->value());
    ui->aux_A->setValue(ui->aux_B->value());
    ui->sB->setValue(f);
    ui->iB->setValue(c);
    ui->aux_B->setValue(fc);

    auto final = std::chrono::system_clock::now();
    std::chrono::duration<float> duracion = final - inicio;
    ui->tiempo->setText(QString::number(duracion.count()));
}

void MainWindow::Shell(bool V,int ta){
    int salto = ta/2;
    while(salto > 0){
        for(int i=salto;i<ta;i++){
             int j = i - salto;
             while(j>=0){
                 int k = j + salto;
                 if(V){
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
                 else{
                     if(s[j] >= s[k]){
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
        }
        salto/=2;
    }
}

void MainWindow::Llenar(){
    for(int i=0;i<fb;i++){
        for(int j=0;j<cb;j++){
            if(ui->B->item(i,j) == nullptr){
                ui->B->setItem(i,j,new QTableWidgetItem("0"));
            }
        }
    }

    for(int i=0;i<fa;i++){
        for(int j=0;j<ca;j++){
             if(ui->A->item(i,j) == nullptr){
                 ui->A->setItem(i,j,new QTableWidgetItem("0"));
             }
        }
        if(ui->vResultados->item(i,0) == nullptr){
            ui->vResultados->setItem(i,0,new QTableWidgetItem("0"));
       }
    }
}

void MainWindow::nA(){
    ui->nA->setText(QString::number(fa*ca));
}

void MainWindow::nB(){
    ui->nB->setText(QString::number(fb*cb));
}

// rojo
void MainWindow::on_identidad_A_clicked(){
    auto inicio = std::chrono::system_clock::now();
    for(int i=0;i<fa;i++){
        for(int j=0;j<ca;j++){
            if(i == j){
                ui->A->setItem(i,j,new QTableWidgetItem("1"));
            }
            else{
                ui->A->setItem(i,j,new QTableWidgetItem("0"));
            }
        }
    }
    auto final = std::chrono::system_clock::now();
    std::chrono::duration<float> duracion = final - inicio;
    ui->tiempo->setText(QString::number(duracion.count()));
}

void MainWindow::on_identidad_B_clicked(){
    auto inicio = std::chrono::system_clock::now();
    for(int i=0;i<fb;i++){
        for(int j=0;j<cb;j++){
            if(i == j){
                ui->B->setItem(i,j,new QTableWidgetItem("1"));
            }
            else{
                ui->B->setItem(i,j,new QTableWidgetItem("0"));
            }
        }
    }
    auto final = std::chrono::system_clock::now();
    std::chrono::duration<float> duracion = final - inicio;
    ui->tiempo->setText(QString::number(duracion.count()));
}
//amarillo
void MainWindow::on_AleatorioA_clicked(){
    if(ui->iA->value() == 0 && ui->sA->value() == 0){
        QMessageBox::critical(this,"Aleatorios","Los limites no concuerdan");
    }
    else if((ui->sA->value() - ui->iA->value()) < 1){
        QMessageBox::critical(this,"Aleatorios","El limite superior debe de ser\nComo minimo 1 unidades superiores al limite inferior");
    }
    else{
        auto inicio = std::chrono::system_clock::now();
        double am,av;
        for(int i=0;i<fa;i++){
            for(int j=0;j<ca;j++){
                am = (ui->iA->value() + rand()%(ui->sA->value()-ui->iA->value()));
                ui->A->setItem(i,j,new QTableWidgetItem(QString::number(am)));
                av = (ui->iA->value() + rand()%(ui->sA->value()-ui->iA->value()));
                ui->vResultados->setItem(i,0,new QTableWidgetItem(QString::number(av)));
            }
        }
        auto final = std::chrono::system_clock::now();
        std::chrono::duration<float> duracion = final - inicio;
        ui->tiempo->setText(QString::number(duracion.count()));
    }
}

void MainWindow::on_AleatorioB_clicked(){
    if(ui->iB->value() == 0 && ui->sB->value() == 0){
        QMessageBox::critical(this,"Aleatorios","Los limites no concuerdan");
    }
    else if((ui->sB->value() - ui->iB->value()) < 1){
        QMessageBox::critical(this,"Aleatorios","El limite superior debe de ser\nComo minimo 1 unidades superiores al limite inferior");
    }
    else{
        auto inicio = std::chrono::system_clock::now();
        for(int i=0;i<fb;i++){
            for(int j=0;j<cb;j++){
                ui->B->setItem(i,j,new QTableWidgetItem(QString::number((ui->iB->value() + rand()%(ui->sB->value()-ui->iB->value())))));
            }
        }
        auto final = std::chrono::system_clock::now();
        std::chrono::duration<float> duracion = final - inicio;
        ui->tiempo->setText(QString::number(duracion.count()));
    }
}
//azul
void MainWindow::on_IncrementoA_clicked(){
    auto inicio = std::chrono::system_clock::now();
    double in = (ui->iA->value() + ui->sA->value())/(2);
    t = ui->iA->value();
    if(ui->iA->value() == 0 && ui->sA->value() == 0){
        QMessageBox::critical(this,"Aleatorios","Los limites no concuerdan");
    }
    else if((ui->sA->value() - ui->iA->value()) < 1){
        QMessageBox::critical(this,"Aleatorios","El limite superior debe de ser\nComo minimo 2 unidades superiores al limite inferior");
    }
    else{
        for(int i=0;i<fa;i++){
            for(int j=0;j<ca;j++){
                ui->A->setItem(i,j,new QTableWidgetItem(QString::number(t)));
                t+=in;
            }
        }
    }
    auto final = std::chrono::system_clock::now();
    std::chrono::duration<float> duracion = final - inicio;
    ui->tiempo->setText(QString::number(duracion.count()));
}

void MainWindow::on_IncrementoB_clicked(){
    auto inicio = std::chrono::system_clock::now();
    double in = (ui->iB->value() + ui->sB->value())/(2);
    t = ui->iB->value();
    if(ui->iB->value() == 0 && ui->sB->value() == 0){
        QMessageBox::critical(this,"Aleatorios","Los limites no concuerdan");
    }
    else if((ui->sB->value() - ui->iB->value()) < 1){
        QMessageBox::critical(this,"Aleatorios","El limite superior debe de ser\nComo minimo 2 unidades superiores al limite inferior");
    }
    else{
        for(int i=0;i<fb;i++){
            for(int j=0;j<cb;j++){
                ui->B->setItem(i,j,new QTableWidgetItem(QString::number(t)));
                t+=in;
            }
        }
    }
    auto final = std::chrono::system_clock::now();
    std::chrono::duration<float> duracion = final - inicio;
    ui->tiempo->setText(QString::number(duracion.count()));
}

void MainWindow::on_i_s_A_clicked(){
    auto inicio = std::chrono::system_clock::now();
    t = ui->iA->value();
    for(int i=0;i<fa;i++){
        for(int j=0;j<ca;j++){
            ui->A->setItem(i,j,new QTableWidgetItem(QString::number(t)));
            t++;
        }
    }
    auto final = std::chrono::system_clock::now();
    std::chrono::duration<float> duracion = final - inicio;
    ui->tiempo->setText(QString::number(duracion.count()));
}

void MainWindow::on_i_s_B_clicked(){
    auto inicio = std::chrono::system_clock::now();
    t = ui->iB->value();
    for(int i=0;i<fb;i++){
        for(int j=0;j<cb;j++){
            ui->B->setItem(i,j,new QTableWidgetItem(QString::number(t)));
            t++;
        }
    }
    auto final = std::chrono::system_clock::now();
    std::chrono::duration<float> duracion = final - inicio;
    ui->tiempo->setText(QString::number(duracion.count()));
}
//verde
void MainWindow::on_llenarNA_clicked(){
    auto inicio = std::chrono::system_clock::now();
    for(int i=0;i<fa;i++){
        for(int j=0;j<ca;j++){
            ui->A->setItem(i,j,new QTableWidgetItem(QString::number(ui->aux_A->value())));
            ui->vResultados->setItem(i,0,new QTableWidgetItem(QString::number(ui->aux_A->value())));
        }
    }
    auto final = std::chrono::system_clock::now();
    std::chrono::duration<float> duracion = final - inicio;
    ui->tiempo->setText(QString::number(duracion.count()));
}

void MainWindow::on_llenarNB_clicked(){
    auto inicio = std::chrono::system_clock::now();
    for(int i=0;i<fb;i++){
        for(int j=0;j<cb;j++){
            ui->B->setItem(i,j,new QTableWidgetItem(QString::number(ui->aux_B->value())));
        }
    }
    auto final = std::chrono::system_clock::now();
    std::chrono::duration<float> duracion = final - inicio;
   ui->tiempo->setText(QString::number(duracion.count()));
}
// naranja
void MainWindow::on_OrdenarA_clicked(){
    auto inicio = std::chrono::system_clock::now();
    // Pasar todo al ventor
    x = 0;
    for(int i=0;i<fa;i++){
        for(int j=0;j<ca;j++){
            if(ui->A->item(i,j) == nullptr){
                QMessageBox::critical(this,"Ordenar matriz","Hay un valor vacio en "+QString::number(i+1)+","+QString::number(j+1));
                return;
            }
            else{
                 s[x++] = ui->A->item(i,j)->text().toDouble();
            }
        }
     }
    if(ordenar){
        // menor a mayor
        //Shell

        Shell(true,x);

        ordenar = false;
    }
    else{
        // mayor a menor

        Shell(false,x);

        ordenar = true;
    }
    //Pasar todo ordenado a la matriz A
    x = 0;
    for(int i=0;i<fa;i++){
        for(int j=0;j<ca;j++){
            ui->A->setItem(i,j,new QTableWidgetItem(QString::number(s[x++])));
        }
    }
    auto final = std::chrono::system_clock::now();
    std::chrono::duration<float> duracion = final - inicio;
    ui->tiempo->setText(QString::number(duracion.count()));
}

void MainWindow::on_OrdenarB_clicked(){
    auto inicio = std::chrono::system_clock::now();
    x = 0;
    for(int i=0;i<fb;i++){
        for(int j=0;j<cb;j++){
            if(ui->B->item(i,j) == nullptr){
                QMessageBox::critical(this,"Ordenar matriz","Hay un valor vacio en "+QString::number(i+1)+","+QString::number(j+1));
                return;
            }
            else{
                 s[x++] = ui->B->item(i,j)->text().toDouble();
            }
        }
     }
    if(ordenar){
        // menor a mayor
        //Shell
        Shell(true,x);
        ordenar = false;
    }
    else{
        // mayor a menor
        Shell(false,x);
        ordenar = true;
    }
    x = 0;
    for(int i=0;i<fb;i++){
        for(int j=0;j<cb;j++){
            ui->B->setItem(i,j,new QTableWidgetItem(QString::number(s[x++])));
        }
    }
    auto final = std::chrono::system_clock::now();
    std::chrono::duration<float> duracion = final - inicio;
    ui->tiempo->setText(QString::number(duracion.count()));
}

void MainWindow::on_A_cellChanged(int row, int column){
    std::string i = ui->A->item(row,column)->text().toStdString();
    std::istringstream s(i);
    double preal,pimaginaria;
    s >> preal >> pimaginaria;
    if(ui->A->item(row,column)->text().count('i') == 1 || ui->A->item(row,column)->text().count('j') == 1){
        double z = sqrt(pow(preal,2) + pow(pimaginaria,2));
        ui->A->setItem(row,column,new QTableWidgetItem(QString::number(z)));
    }
    else if(ui->A->item(row,column)->text().count('<') == 1 ){
        double z = sqrt(pow(preal*cos(pimaginaria),2) + pow(preal*sin(pimaginaria),2));
        ui->A->setItem(row,column,new QTableWidgetItem(QString::number(z)));
    }
    else{
            int tam;
            QString aux2;
            tam = ui->A->item(row,column)->text().size();
            for(int z=0;z<tam;z++){
                 aux2.append(QString::number(int(ui->A->item(row,column)->text().at(z).toLatin1())));
            }
            //qDebug()<<aux2;
            //ui->A->setItem(row,column,new QTableWidgetItem(aux2));
    }
}

void MainWindow::on_vResultados_cellChanged(int row, int column){
    if(ui->vResultados->item(row,column) != nullptr){
        std::string i = ui->vResultados->item(row,column)->text().toStdString();
        std::istringstream s(i);
        double preal,pimaginaria;
        s >> preal >> pimaginaria;
        if(ui->vResultados->item(row,column)->text().count('i') == 1 || ui->vResultados->item(row,column)->text().count('j') == 1){
            double z = sqrt(pow(preal,2) + pow(pimaginaria,2));
            ui->vResultados->setItem(row,column,new QTableWidgetItem(QString::number(z)));
        }
        else if(ui->vResultados->item(row,column)->text().count('<') == 1 ){
            double z = sqrt(pow(preal*cos(pimaginaria),2) + pow(preal*sin(pimaginaria),2));
            ui->vResultados->setItem(row,column,new QTableWidgetItem(QString::number(z)));
        }
    }
    else{
        ui->vResultados->setItem(row,column, new QTableWidgetItem("0"));
    }
}

void MainWindow::on_B_cellChanged(int row, int column){
    std::string i = ui->B->item(row,column)->text().toStdString();
    std::istringstream s(i);
    double preal,pimaginaria;
    s >> preal >> pimaginaria;
    if(ui->B->item(row,column)->text().count('i') == 1 || ui->B->item(row,column)->text().count('j') == 1){
        double z = sqrt(pow(preal,2) + pow(pimaginaria,2));
        ui->B->setItem(row,column,new QTableWidgetItem(QString::number(z)));
    }
    else if(ui->B->item(row,column)->text().count('<') == 1 ){
        double z = sqrt(pow(preal*cos(pimaginaria),2) + pow(preal*sin(pimaginaria),2));
        ui->B->setItem(row,column,new QTableWidgetItem(QString::number(z)));
    }
}

void MainWindow::on_actionA_triggered(){
    QString ruta;
    direccion d(this);
    d.nombre("Abrir");
    d.ver(false);
    d.titulo("Ruta   ruta/nombre.extencion");
    d.en_text("Desencriptar");
    d.exec();
    d.ruta(ruta);
    //ruta = "C:/Users/enriq/Desktop/A.txt";


    QFile a(ruta);
    auto inicio = std::chrono::system_clock::now();

    if(a.exists()){
        a.open(QFile::ReadOnly | QFile::Text);

        QTextStream out(&a);
        QString texto = a.readAll();

        QStringList tf = texto.split(',');
        int tam = tf.size()-1;

        // dandole tama;o a la matriz
        int pfa,pca;
        bool p = true;

        pfa = pca = floor(sqrt(tam));

        do{
            if(((pfa*pca) != tam) && (p == true)){
                pca++;
                p = false;
            }
            else if(((pfa*pca) != tam) && (p == false)){
                pfa--;
                p = true;
            }
        }while((pfa*pca) != tam);
        //
        ui->fa->setValue(pfa);
        ui->ca->setValue(pca);

        ui->A->setRowCount(pfa);
        ui->A->setColumnCount(pca);

        x = 0;

        if(d.en_checked()){
            for(int i=0;i<fa;i++){
                ui->A->setHorizontalHeaderItem(i,new QTableWidgetItem("x"+QString::number(i+1)));
                ui->A->setColumnWidth(i,50);
                for(int j=0;j<ca;j++){
                    if(tf[x].count("\n") == 1){
                        tf[x].remove("\n");
                    }
                    ui->A->setItem(i,j,new QTableWidgetItem(QString::number(tf[x].toDouble() / 2)));
                    if(x == tam-1){
                        x = 0;
                    }
                    else{
                        x++;
                    }
                }
            }
        }
        else{
            for(int i=0;i<fa;i++){
                ui->A->setHorizontalHeaderItem(i,new QTableWidgetItem("x"+QString::number(i+1)));
                ui->A->setColumnWidth(i,50);
                for(int j=0;j<ca;j++){
                    if(tf[x].count("\n") == 1){
                        tf[x].remove("\n");
                    }
                    ui->A->setItem(i,j,new QTableWidgetItem(tf[x]));
                    if(x == tam-1){
                        x = 0;
                    }
                    else{
                        x++;
                    }
                }
            }
        }


        a.flush();
        a.close();
    }
    else{
        QMessageBox::critical(this,"Abrir Archivo","El archivo no existe");
    }
    auto final = std::chrono::system_clock::now();
    std::chrono::duration<float> duracion = final - inicio;
    ui->tiempo->setText(QString::number(duracion.count()));
}

void MainWindow::on_actionA_2_triggered(){
    QString ruta;
    QString extencion;
    direccion d(this);
    d.nombre("Guardar");
    d.titulo("Ruta    ruta/nombre(sin extension)");
    d.en_text("Encriptar");
    d.exec();
    d.ruta(ruta);
    auto inicio = std::chrono::system_clock::now();

    QString texto;

    if(d.en_checked()){
        extencion = "_e";
        d.extencion(extencion);

        if(extencion.isNull()){
            extencion += "txt";
        }
        QFile a(ruta+extencion);

        a.open(QFile::WriteOnly | QFile::Text);
        QTextStream out(&a);


        int e;

        QFile E("C:/Users/Public/E.txt");

        E.open(QFile::ReadOnly | QFile::Text);
        QTextStream in(&E);

        e = in.readAll().toDouble();

        E.flush();
        E.close();

        for(int i=0;i<fa;i++){
            for(int j=0;j<ca;j++){
                texto += QString::number(ui->A->item(i,j)->text().toDouble() * e) + ",";
            }
            texto+="\n";
            out << texto;
            texto.clear();
        }
        a.flush();
        a.close();

    }
    else{
        d.extencion(extencion);

        if(extencion.isNull()){
            extencion += "txt";
        }
        QFile a(ruta+extencion);

        a.open(QFile::WriteOnly | QFile::Text);
        QTextStream out(&a);

        for(int i=0;i<fa;i++){
            for(int j=0;j<ca;j++){
                texto += ui->A->item(i,j)->text() + ",";
            }
            texto+="\n";
            out << texto;
            texto.clear();
        }
        a.flush();
        a.close();
    }



    auto final = std::chrono::system_clock::now();
    std::chrono::duration<float> duracion = final - inicio;
    ui->tiempo->setText(QString::number(duracion.count()));
}

void MainWindow::on_actionB_triggered(){
    QString ruta;
    direccion d(this);
    d.nombre("Abrir");
    d.ver(false);
    d.titulo("Ruta   ruta/nombre.extencion");
    d.en_text("Desencriptar");
    d.exec();
    d.ruta(ruta);
    auto inicio = std::chrono::system_clock::now();
    //ruta = "C:/Users/enriq/Desktop/A.txt";

    QFile a(ruta);

    if(d.en_checked()){
        if(a.exists()){
            a.open(QFile::ReadOnly | QFile::Text);

            QTextStream out(&a);
            QString texto = a.readAll();

            QStringList tf = texto.split(',');
            int tam = tf.size() - 1;

            // dandole tama;o a la matriz
            int pfb,pcb;
            bool p = true;

            pfb = pcb = floor(sqrt(tam));

            do{
                if(((pfb*pcb) != tam) && (p == true)){
                    pcb++;
                    p = false;
                }
                else if(((pfb*pcb) != tam) && (p == false)){
                    pfb--;
                    p = true;
                }
            }while((pfb*pcb) != tam);
            //
            ui->fb->setValue(pfb);
            ui->cb->setValue(pcb);

            ui->B->setRowCount(pfb);
            ui->B->setColumnCount(pcb);

            int e;

            QFile E("C:/Users/Public/E.txt");

            E.open(QFile::ReadOnly | QFile::Text);
            QTextStream in(&E);

            e = in.readAll().toDouble();

            x = 0;
            for(int i=0;i<fb;i++){
                ui->B->setHorizontalHeaderItem(i,new QTableWidgetItem("x"+QString::number(i+1)));
                ui->B->setColumnWidth(i,50);
                for(int j=0;j<cb;j++){
                    if(tf[x].count("\n") == 1){
                        tf[x].remove("\n");
                    }
                    ui->B->setItem(i,j,new QTableWidgetItem(QString::number(tf[x].toDouble() / e)));

                    if(x == tam-1){
                        x = 0;
                    }
                    else{
                        x++;
                    }
                }
            }

        }
        else{
            QMessageBox::critical(this,"Abrir Archivo","El archivo no existe");
        }
    }
    else{
        if(a.exists()){
            a.open(QFile::ReadOnly | QFile::Text);

            QTextStream out(&a);
            QString texto = a.readAll();

            QStringList tf = texto.split(',');
            int tam = tf.size() - 1;

            // dandole tama;o a la matriz
            int pfb,pcb;
            bool p = true;

            pfb = pcb = floor(sqrt(tam));

            do{
                if(((pfb*pcb) != tam) && (p == true)){
                    pcb++;
                    p = false;
                }
                else if(((pfb*pcb) != tam) && (p == false)){
                    pfb--;
                    p = true;
                }
            }while((pfb*pcb) != tam);
            //
            ui->fb->setValue(pfb);
            ui->cb->setValue(pcb);

            ui->B->setRowCount(pfb);
            ui->B->setColumnCount(pcb);

            x = 0;
            for(int i=0;i<fb;i++){
                ui->B->setHorizontalHeaderItem(i,new QTableWidgetItem("x"+QString::number(i+1)));
                ui->B->setColumnWidth(i,50);
                for(int j=0;j<cb;j++){
                    if(tf[x].count("\n") == 1){
                        tf[x].remove("\n");
                    }
                    ui->B->setItem(i,j,new QTableWidgetItem(tf[x]));
                    if(x == tam-1){
                        x = 0;
                    }
                    else{
                        x++;
                    }
                }
            }

        }
        else{
            QMessageBox::critical(this,"Abrir Archivo","El archivo no existe");
        }

    }

    a.flush();
    a.close();
    auto final = std::chrono::system_clock::now();
    std::chrono::duration<float> duracion = final - inicio;
    ui->tiempo->setText(QString::number(duracion.count()));
}

void MainWindow::on_actionB_2_triggered(){
    QString ruta;
    QString extencion;
    direccion d(this);
    d.nombre("Guardar");
    d.titulo("Ruta    ruta/nombre(sin extension)");
    d.en_text("Encriptar");
    d.exec();
    d.ruta(ruta);
    auto inicio = std::chrono::system_clock::now();
    QString texto;
    //ruta = "C:/Users/enriq/Desktop/A.txt";

    if(d.en_checked()){

        extencion = "_e";
        d.extencion(extencion);

        if(extencion.isNull()){
            extencion += ".txt";
        }
        QFile a(ruta+extencion);

        a.open(QFile::WriteOnly | QFile::Text);
        QTextStream out(&a);

        int e;

        QFile E("C:/Users/Public/E.txt");

        E.open(QFile::ReadOnly | QFile::Text);
        QTextStream in(&E);

        e = in.readAll().toDouble();


        for(int i=0;i<fb;i++){
            for(int j=0;j<cb;j++){
                texto += QString::number(ui->B->item(i,j)->text().toDouble() * e) + ",";
            }
            texto+="\n";
            out << texto;
            texto.clear();
        }
        a.flush();
        a.close();
    }
    else{
            d.extencion(extencion);
        if(extencion.isNull()){
            extencion += ".txt";
        }
        QFile a(ruta+extencion);

        a.open(QFile::WriteOnly | QFile::Text);
        QTextStream out(&a);

        for(int i=0;i<fb;i++){
            for(int j=0;j<cb;j++){
                texto += ui->B->item(i,j)->text() + ",";
            }
            texto+="\n";
            out << texto;
            texto.clear();
        }
        a.flush();
        a.close();
    }
    auto final = std::chrono::system_clock::now();
    std::chrono::duration<float> duracion = final - inicio;
    ui->tiempo->setText(QString::number(duracion.count()));
}

void MainWindow::on_actionV_triggered(){
    QString ruta;
    direccion d(this);
    d.nombre("Abrir");
    d.ver(false);
    d.titulo("Ruta   ruta/nombre.extencion");
    d.en_text("Desencriptar");
    d.exec();
    d.ruta(ruta);
    auto inicio = std::chrono::system_clock::now();
    //ruta = "C:/Users/enriq/Desktop/A.txt";

    QFile a(ruta);

    if(d.en_checked()){
        if(a.exists()){
            a.open(QFile::ReadOnly | QFile::Text);

            QTextStream out(&a);
            QString texto = a.readAll();

            QStringList tf = texto.split(',');
            int tam = tf.size() - 1;

            ui->fa->setValue(tam);

            ui->vResultados->setRowCount(tam);

            int e;

            QFile E("C:/Users/Public/E.txt");

            E.open(QFile::ReadOnly | QFile::Text);
            QTextStream in(&E);

            e = in.readAll().toDouble();

            x = 0;
            for(int i=0;i<fa;i++){
                if(tf[x].count("\n") == 1){
                    tf[x].remove("\n");
                }
                    ui->vResultados->setItem(i,0,new QTableWidgetItem(QString::number(tf[x].toDouble() / e)));
                    if(x == tam-1){
                        x = 0;
                    }
                    else{
                        x++;
                    }

            }
            a.flush();
            a.close();
        }
        else{
            QMessageBox::critical(this,"Abrir Archivo","El archivo no existe");
        }
    }
    else{
        if(a.exists()){
            a.open(QFile::ReadOnly | QFile::Text);

            QTextStream out(&a);
            QString texto = a.readAll();

            QStringList tf = texto.split(',');
            int tam = tf.size() - 1;

            ui->fa->setValue(tam);

            ui->vResultados->setRowCount(tam);

            x = 0;
            for(int i=0;i<fa;i++){
                if(tf[x].count("\n") == 1){
                    tf[x].remove("\n");
                }
                    ui->vResultados->setItem(i,0,new QTableWidgetItem(tf[x]));
                    if(x == tam-1){
                        x = 0;
                    }
                    else{
                        x++;
                    }

            }
            a.flush();
            a.close();
        }
        else{
            QMessageBox::critical(this,"Abrir Archivo","El archivo no existe");
        }
    }


    auto final = std::chrono::system_clock::now();
    std::chrono::duration<float> duracion = final - inicio;
    ui->tiempo->setText(QString::number(duracion.count()));
}

void MainWindow::on_actionV_2_triggered(){
    QString ruta;
    QString extencion;
    direccion d(this);
    d.nombre("Guardar");
    d.titulo("Ruta    ruta/nombre(sin extension)");
    d.en_text("Encriptar");
    d.exec();
    d.ruta(ruta);
    auto inicio = std::chrono::system_clock::now();

    QString texto;

    if(d.en_checked()){
        extencion = "_e";
        d.extencion(extencion);
        //ruta = "C:/Users/enriq/Desktop/A.txt";
        if(extencion.isNull()){
            extencion += ".txt";
        }
        QFile a(ruta+extencion);

         a.open(QFile::WriteOnly | QFile::Text);
         QTextStream out(&a);

         int e;

         QFile E("C:/Users/Public/E.txt");

         E.open(QFile::ReadOnly | QFile::Text);
         QTextStream in(&E);

         e = in.readAll().toDouble();

        for(int i=0;i<fa;i++){

                texto += QString::number(ui->vResultados->item(i,0)->text().toDouble() * e ) + ",";

            out << texto;
            texto.clear();
        }
        a.flush();
        a.close();
    }
    else{
        d.extencion(extencion);
        //ruta = "C:/Users/enriq/Desktop/A.txt";
        if(extencion.isNull()){
            extencion += ".txt";
        }
        QFile a(ruta+extencion);

         a.open(QFile::WriteOnly | QFile::Text);
         QTextStream out(&a);

        for(int i=0;i<fa;i++){

                texto += ui->vResultados->item(i,0)->text() + ",";

            out << texto;
            texto.clear();
        }
        a.flush();
        a.close();
    }


    auto final = std::chrono::system_clock::now();
    std::chrono::duration<float> duracion = final - inicio;
    ui->tiempo->setText(QString::number(duracion.count()));
}

void MainWindow::on_actionGuardar_Todo_triggered(){
    for(int i=0;i<fb;i++){
        for(int j=0;j<cb;j++){
            if(ui->B->item(i,j) == nullptr){
                ui->B->setItem(i,j,new QTableWidgetItem("0"));
            }
        }
    }

    for(int i=0;i<fa;i++){
        //ui->vResultados->setColumnWidth(i,50);
        for(int j=0;j<ca;j++){
                if(ui->A->item(i,j) == nullptr){
                    ui->A->setItem(i,j,new QTableWidgetItem("0"));
                }
                if(ui->vResultados->item(i,0) == nullptr){
                    ui->vResultados->setItem(i,0,new QTableWidgetItem("0"));
            }
        }
    }

    int e;

    QFile E("C:/Users/Public/E.txt");

    E.open(QFile::ReadOnly | QFile::Text);
    QTextStream in(&E);

    e = in.readAll().toDouble();

    // A
    QString ruta;
    direccion d(this);
    d.nombre("Guardar");
    d.titulo("Ruta    ruta/(sin nombre elije una extencion)");
    d.en_text("Encriptar");
    d.exec();
    d.ruta(ruta);
    auto inicio = std::chrono::system_clock::now();
    QString texto;

    if(d.en_checked()){
        QString A = "_e";
        d.extencion(A);
        if(A.isNull()){
            A += ".txt";
        }

        QFile a(ruta+"A"+A);
        a.open(QFile::WriteOnly | QFile::Text);
        QTextStream out(&a);

        for(int i=0;i<fa;i++){
            for(int j=0;j<ca;j++){
                texto += QString::number(ui->A->item(i,j)->text().toDouble() * e) + ",";
            }
            texto+="\n";
            out << texto;
            texto.clear();
        }
        a.flush();
        a.close();



        texto.clear();
        QString B = "_e";
        d.extencion(B);
        if(B.isNull()){
            B += ".txt";
        }
        QFile a_3(ruta+"B"+B);

        a_3.open(QFile::WriteOnly | QFile::Text);
        QTextStream out_3(&a_3);

        for(int i=0;i<fb;i++){
            for(int j=0;j<cb;j++){
                texto += QString::number(ui->B->item(i,j)->text().toDouble() * e) + ",";
            }
            texto+="\n";
            out_3 << texto;
            texto.clear();
        }
        a_3.flush();
        a_3.close();


        texto.clear();
        QString V = "_e";
        d.extencion(V);
        if(V.isNull()){
            V += ".txt";
        }
        QFile a_2(ruta+"V"+V);
        a_2.open(QFile::WriteOnly | QFile::Text);
        QTextStream out_2(&a_2);

        for(int i=0;i<fa;i++){
            texto += QString::number(ui->vResultados->item(i,0)->text().toDouble() * e) + ",";
            out_2 << texto;
            texto.clear();
        }

        a_2.flush();
        a_2.close();

    }
    else{
        QString A;
        d.extencion(A);
        if(A.isNull()){
            A += ".txt";
        }

        QFile a(ruta+"A"+A);
        a.open(QFile::WriteOnly | QFile::Text);
        QTextStream out(&a);

        for(int i=0;i<fa;i++){
            for(int j=0;j<ca;j++){
                texto += ui->A->item(i,j)->text() + ",";
            }
            texto+="\n";
            out << texto;
            texto.clear();
        }
        a.flush();
        a.close();

        QString B;
        texto.clear();
        d.extencion(B);
        if(B.isNull()){
            B += ".txt";
        }
        QFile a_3(ruta+"B"+B);

        a_3.open(QFile::WriteOnly | QFile::Text);
        QTextStream out_3(&a_3);

        for(int i=0;i<fb;i++){
            for(int j=0;j<cb;j++){
                texto += ui->B->item(i,j)->text() + ",";
            }
            texto+="\n";
            out_3 << texto;
            texto.clear();
        }
        a_3.flush();
        a_3.close();

        texto.clear();
        QString V;
        d.extencion(V);
        if(V.isNull()){
            V += ".txt";
        }
        QFile a_2(ruta+"V"+V);
        a_2.open(QFile::WriteOnly | QFile::Text);
        QTextStream out_2(&a_2);

        for(int i=0;i<fa;i++){
            texto += ui->vResultados->item(i,0)->text() + ",";
            out_2 << texto;
            texto.clear();
        }

        a_2.flush();
        a_2.close();
    }


    auto final = std::chrono::system_clock::now();
    std::chrono::duration<float> duracion = final - inicio;
    ui->tiempo->setText(QString::number(duracion.count()));
}

void MainWindow::on_actionSobre_QT_triggered(){
    QMessageBox::aboutQt(this);
}

void MainWindow::on_actionAyuda_triggered(){
    ayuda a(this);

    a.exec();
}

void MainWindow::on_actionSobre_Autor_triggered(){
    Autor a(this);

    a.exec();
}

void MainWindow::on_saltos_A_clicked(){
    if((ui->iA->value() > ui->sA->value()) || (ui->aux_A->value() >= ui->sA->value()) || (ui->aux_A->value() == 0)){
        QMessageBox::critical(this,"Saltos","Los limites no coenciden\nEl limite inferior no puede ser mayor al limite superior\nni el salto\nY el Salto tiene que ser diferente a 0");
    }
    else{
        auto inicio = std::chrono::system_clock::now();
        t = ui->iA->value();
        for(int i=0;i<fa;i++){
            for(int j=0;j<ca;j++){
                ui->A->setItem(i,j,new QTableWidgetItem(QString::number(t)));
                if(t == ui->sA->value() || (t += ui->aux_A->value()) > ui->sA->value()){
                    t = ui->iA->value();
                }
            }
        }
        auto final = std::chrono::system_clock::now();
        std::chrono::duration<float> duracion = final - inicio;
        ui->tiempo->setText(QString::number(duracion.count()));
    }
}

void MainWindow::on_saltos_B_clicked(){
    if((ui->iB->value() > ui->sB->value()) || (ui->aux_B->value() >= ui->sB->value()) || (ui->aux_B->value() == 0)){
        QMessageBox::critical(this,"Saltos","Los limites no coenciden\nEl limite inferior no puede ser mayor al limite superior\nni el salto\nY el Salto tiene que ser diferente a 0");
    }
    else{
        auto inicio = std::chrono::system_clock::now();
        t = ui->iB->value();
        for(int i=0;i<fb;i++){
            for(int j=0;j<cb;j++){
                ui->B->setItem(i,j,new QTableWidgetItem(QString::number(t)));
                if(t == ui->sB->value() || (t += ui->aux_B->value()) > ui->sB->value()){
                    t = ui->iB->value();
                }
            }
        }
        auto final = std::chrono::system_clock::now();
        std::chrono::duration<float> duracion = final - inicio;
        ui->tiempo->setText(QString::number(duracion.count()));
    }
}

void MainWindow::on_desordenar_A_clicked(){
    auto inicio = std::chrono::system_clock::now();

    for(int i=0;i<fa;i++){
        for(int j=0;j<ca;j++){
            if(ui->A->item(i,j) == nullptr){
                QMessageBox::critical(this,"Ordenar matriz","Hay un valor vacio en "+QString::number(i+1)+","+QString::number(j+1));
                return;
            }
        }
     }

    int s[5];

    for(int i=0;i<fa;i++){
        for(int j=0;j<ca;j++){
            s[0] = rand()%fa;
            s[1] = rand()%fa;
            s[2] = rand()%ca;
            s[3] = rand()%ca;
            s[4] = ui->A->item(s[0],s[2])->text().toDouble();
            ui->A->setItem(s[0],s[2], new QTableWidgetItem(ui->A->item(s[1],s[3])->text()));
            ui->A->setItem(s[1],s[3], new QTableWidgetItem(QString::number(s[4])));
        }
    }
    auto final = std::chrono::system_clock::now();
    std::chrono::duration<float> duracion = final - inicio;
    ui->tiempo->setText(QString::number(duracion.count()));
}

void MainWindow::on_desordenar_B_clicked(){
    auto inicio = std::chrono::system_clock::now();

    for(int i=0;i<fb;i++){
        for(int j=0;j<cb;j++){
            if(ui->B->item(i,j) == nullptr){
                QMessageBox::critical(this,"Ordenar matriz","Hay un valor vacio en "+QString::number(i+1)+","+QString::number(j+1));
                return;
            }
        }
     }

    int s[5];

    for(int i=0;i<fb;i++){
        for(int j=0;j<cb;j++){
            s[0] = rand()%fb;
            s[1] = rand()%fb;
            s[2] = rand()%cb;
            s[3] = rand()%cb;
            s[4] = ui->B->item(s[0],s[2])->text().toDouble();
            ui->B->setItem(s[0],s[2], new QTableWidgetItem(ui->B->item(s[1],s[3])->text()));
            ui->B->setItem(s[1],s[3], new QTableWidgetItem(QString::number(s[4])));
        }
    }
    auto final = std::chrono::system_clock::now();
    std::chrono::duration<float> duracion = final - inicio;
    ui->tiempo->setText(QString::number(duracion.count()));
}

void MainWindow::on_copiar_M_clicked(){
    copiarMatrices o(this);

    o.exec();
    auto inicio = std::chrono::system_clock::now();
    if(o.on_buttonBox_accepted()){
        if(o.AOB()){
            // A
            ui->iB->setValue(ui->iA->value());
            ui->sB->setValue(ui->sA->value());
            ui->aux_B->setValue(ui->aux_A->value());
            for(int i=0;i<fa;i++){
                for(int j=0;j<ca;j++){
                    if(ui->A->item(i,j) == nullptr){
                        QMessageBox::critical(this,"Copiar matriz","Hay un valor vacio en "+QString::number(i+1)+",x"+QString::number(j+1));
                        return;
                    }
                }
            }


            fb = ui->A->rowCount();
            cb = ui->A->columnCount();
            ui->B->setColumnCount(cb);
            ui->B->setRowCount(fb);
            ui->fb->setValue(fb);
            ui->cb->setValue(cb);

            for(int i=0;i<ca;i++){
                ui->B->setHorizontalHeaderItem(i,new QTableWidgetItem("x"+QString::number(i+1)));
                ui->B->setColumnWidth(i,50);
            }

            for(int i=0;i<fa;i++){
                for(int j=0;j<ca;j++){
                    ui->B->setItem(i,j, new QTableWidgetItem(ui->A->item(i,j)->text()));
                }
            }
        }
        else{
            // B
            ui->iA->setValue(ui->iB->value());
            ui->sA->setValue(ui->sB->value());
            ui->aux_A->setValue(ui->aux_B->value());
            for(int i=0;i<fb;i++){
                for(int j=0;j<cb;j++){
                    if(ui->B->item(i,j) == nullptr){
                        QMessageBox::critical(this,"Copiar matriz","Hay un valor vacio en "+QString::number(i+1)+",x"+QString::number(j+1));
                        return;
                    }
                }
            }

            fa = ui->B->rowCount();
            ca = ui->B->columnCount();
            ui->A->setColumnCount(ca);
            ui->A->setRowCount(fa);
            ui->fa->setValue(fa);
            ui->ca->setValue(ca);

            for(int i=0;i<ca;i++){
                ui->A->setHorizontalHeaderItem(i,new QTableWidgetItem("x"+QString::number(i+1)));
                ui->A->setColumnWidth(i,50);
            }

            for(int i=0;i<fb;i++){
                for(int j=0;j<cb;j++){
                    ui->A->setItem(i,j, new QTableWidgetItem(ui->B->item(i,j)->text()));
                }
            }
        }
    }

    auto final = std::chrono::system_clock::now();
    std::chrono::duration<float> duracion = final - inicio;
    ui->tiempo->setText(QString::number(duracion.count()));
}

void MainWindow::on_actionEntre_Matrices_triggered(){
    Llenar();
    operaciones o(this);
    o.ventana(0);
    o.setWindowTitle("Operacion Entre A y B");
    o.setWindowIcon(ui->actionEntre_Matrices->icon());
    o.PasarDatos(ui->A,ui->B,ui->vResultados,fa,ca,fb,cb);
    o.setGeometry(500,300,555,293);
    o.exec();
    o.pasar(ui->A,ui->B);
}

void MainWindow::on_actionEntre_Escalar_triggered(){
    Llenar();
    operaciones o(this);
    o.ventana(1);
    o.setWindowTitle("Operacion Entre Escalar");
    o.setWindowIcon(ui->actionEntre_Escalar->icon());
    o.PasarDatos(ui->A,ui->B,ui->vResultados,fa,ca,fb,cb);
    o.setGeometry(500,300,555,293);
    o.exec();
    o.pasar(ui->A,ui->B);
}

void MainWindow::on_actionTrigonometria_triggered(){
    Llenar();
    operaciones o(this);
    o.ventana(2);
    o.setWindowTitle("Trigonometria");
    o.setWindowIcon(ui->actionTrigonometria->icon());
    o.PasarDatos(ui->A,ui->B,ui->vResultados,fa,ca,fb,cb);
    o.setGeometry(500,300,555,293);
    o.exec();
    o.pasar(ui->A,ui->B);
}

void MainWindow::on_actionExtras_triggered(){
    Llenar();
    operaciones o(this);
    o.ventana(3);
    o.setWindowTitle("Extras");
    o.setWindowIcon(ui->actionExtras->icon());
    o.PasarDatos(ui->A,ui->B,ui->vResultados,fa,ca,fb,cb);
    o.setGeometry(500,300,555,293);
    o.exec();
    o.pasar(ui->A,ui->B);
}

void MainWindow::on_actionAtributos_triggered(){
    Llenar();
    operaciones o(this);
    o.ventana(4);
    o.setWindowTitle("Atributos");
    o.setWindowIcon(ui->actionAtributos->icon());
    o.PasarDatos(ui->A,ui->B,ui->vResultados,fa,ca,fb,cb);
    o.setGeometry(500,300,555,293);
    o.exec();
    o.pasar(ui->A,ui->B);
}

void MainWindow::on_actionInterpolar_triggered(){
    Llenar();
    operaciones o(this);
    o.setWindowTitle("Interpolacion");
    o.setWindowIcon(ui->actionInterpolar->icon());
    o.setGeometry(300,200,900,480);
    o.ventana(5,0);
    o.SubVentanas(ui->A,ui->B,ui->vResultados,fa,ca,fb,cb);
    o.exec();
    o.pasar(ui->A,ui->B);
}

void MainWindow::on_actionExtrapolar_triggered(){
    Llenar();
    operaciones o(this);
    o.setWindowTitle("Extrapolacion");
    o.setWindowIcon(ui->actionExtrapolar->icon());
    o.setGeometry(300,200,900,480);
    o.ventana(5,1);
    o.SubVentanas(ui->A,ui->B,ui->vResultados,fa,ca,fb,cb);
    o.exec();
    o.pasar(ui->A,ui->B);
}


void MainWindow::on_actionPorbabilidad_y_Estadistica_triggered(){
    Llenar();

    pye o(this);

    o.PasarDatos(ui->A);
    o.Histograma();

    o.exec();
}

void MainWindow::showTime(){
    QTime time = QTime::currentTime();

    ui->hora->setText(time.toString(" hh : mm : ss"));
}


void MainWindow::on_actionCodigo_Fuente_triggered(){
    QString link = "https://github.com/enrique76/Calculadora-de-Matrices";
    QDesktopServices::openUrl((QUrl(link)));
    link = "https://www.youtube.com/channel/UCLuiLXC89Ji--gmacl6Zt3g";
    QDesktopServices::openUrl((QUrl(link)));
}


void MainWindow::on_actionDescargar_triggered(){
    QString link = "https://github.com/enrique76/Calculadora-De-Matrices-SetUp";
    QDesktopServices::openUrl((QUrl(link)));
    link = "https://www.youtube.com/channel/UCLuiLXC89Ji--gmacl6Zt3g";
    QDesktopServices::openUrl((QUrl(link)));
}

void MainWindow::on_actionGraficar_Funciones_triggered(){
    GraficarFuncion f(this);

    f.setWindowTitle("Graficar Funsiones");
    f.setWindowIcon(ui->actionGraficar_Funciones->icon());

    f.exec();
}

