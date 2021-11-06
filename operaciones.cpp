#include "operaciones.h"
#include "ui_operaciones.h"
#include"resultado.h"
#include"funcion.h"
#include "direccion.h"
#include<QMessageBox>
#include<chrono>
#include<QDebug>
#include<math.h>
#include<QFile>
#include<QTextStream>

operaciones::operaciones(QWidget *parent) : QDialog(parent) , ui(new Ui::operaciones){
    ui->setupUi(this);
}

operaciones::~operaciones(){
    delete ui;
}

// inicio de funciones

void operaciones::PasarDatos(QTableWidget *A, QTableWidget *B, QTableWidget *r, int fa, int ca, int fb, int cb){
    this->fa = fa;
    this->ca = ca;
    this->fb = fb;
    this->cb = cb;
    if(fa == fb && ca == cb){
        for(int i=0;i<fa;i++){
            for(int j=0;j<ca;j++){
                a[i][j] = A->item(i,j)->text().toDouble();
                b[i][j] = B->item(i,j)->text().toDouble();
            }
            v[i] = r->item(i,0)->text().toDouble();
        }
    }
    else{
        for(int i=0;i<fa;i++){
            for(int j=0;j<ca;j++){
                a[i][j] = A->item(i,j)->text().toDouble();
            }
            v[i] = r->item(i,0)->text().toDouble();
        }
        for(int i=0;i<fb;i++){
            for(int j=0;j<cb;j++){
                b[i][j] = B->item(i,j)->text().toDouble();
            }
        }
    }
}

void operaciones::Shell(double s[], int f, int c){
    int x = f*c;
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

double operaciones::Menor(int f,int c){
    double menor = a[0][0];

    for(int i=0;i<f;i++){
        for(int j=0;j<c;j++){
            if(a[i][j] < menor){
                menor = a[i][j];
            }
        }
    }

    return menor;
}

double operaciones::Mayor(int f,int c){
    double mayor = a[0][0];

    for(int i=0;i<f;i++){
        for(int j=0;j<c;j++){
            if(a[i][j] > mayor){
                mayor = a[i][j];
            }
        }
    }
    return mayor;
}

double operaciones::Media(){
    double suma = 0;

    for(int i=0;i<fa;i++){
        for(int j=0;j<ca;j++){
            suma+=a[i][j];
        }
    }

    return (suma/(fa*ca));
}

void operaciones::pasar(QTableWidget *A, QTableWidget *B){
    for(int i=0;i<fa;i++){
        for(int j=0;j<ca;j++){
            A->setItem(i,j,new QTableWidgetItem(QString::number(a[i][j])));
        }
    }

    for(int i=0;i<fb;i++){
        for(int j=0;j<cb;j++){
            B->setItem(i,j,new QTableWidgetItem(QString::number(b[i][j])));
        }
    }
}

void operaciones::ventana(int i){
    ui->ventana->setCurrentIndex(i);
}

void operaciones::ventana(int x, int y){
    ui->ventana->setCurrentIndex(x);
    ui->variables->setCurrentIndex(y);
}

void operaciones::SubVentanas(QTableWidget *A,QTableWidget *B,QTableWidget *r,int fa,int ca, int fb, int cb){
    ui->Matriz_A->setRowCount(fa);
    ui->Matriz_A->setColumnCount(ca);
    ui->Matriz_B->setColumnCount(cb);
    ui->Matriz_B->setRowCount(fb);
    ui->Vector->setRowCount(fa);
    ui->Vector->setColumnCount(1);


    ui->Vector->setColumnWidth(0,50);

    QStringList l;

    for(int i=0;i<fa;i++){
        ui->Matriz_A->setColumnWidth(i,50);
        for(int j=0;j<ca;j++){
            ui->Matriz_A->setItem(i,j,new QTableWidgetItem(A->item(i,j)->text()));   
        }
        ui->Vector->setItem(i,0,new QTableWidgetItem(r->item(i,0)->text()));
        l <<"x"+QString::number(i);
    }

    ui->Matriz_A->setHorizontalHeaderLabels(l);

    l.clear();

    l<<"R";

    ui->Vector->setHorizontalHeaderLabels(l);

    l.clear();

    for(int i=0;i<fb;i++){
        ui->Matriz_B->setColumnWidth(i,50);
        l <<"x"+QString::number(i);
        for(int j=0;j<cb;j++){
            ui->Matriz_B->setItem(i,j,new QTableWidgetItem(B->item(i,j)->text()));
        }
    }

    ui->Matriz_B->setHorizontalHeaderLabels(l);
}

double operaciones::Determinante(double a[][100]){
    int nxn = fa;
    double d[100][102];
    double aux[100][100];
    double Det;
    for(int i=0;i<nxn;i++){
        for(int j=0;j<2;j++){
            aux[i][j] = a[i][j];
        }
    }
    for(int i=0;i<nxn;i++){
        for(int j=0;j<nxn+2;j++){
            if(j < nxn){
                d[i][j] = a[i][j];
            }
            else{
                d[i][j] = aux[i][j-nxn];
            }
        }
    }
    int z = 0;
    double mul = 1;
    double p1 = 0,p2 = 0;
    for(int i=0;i<nxn;i++){
        for(int j=0;j<nxn;j++){
            mul*= d[j][j+z];
        }
        z++;
        p1+= mul;
        mul = 1 ;
    }
    z = nxn+1;
    for(int i=0;i<nxn;i++){
        for(int j=0;j<nxn;j++){
            mul*= d[j][z];
            z--;
        }
        z+=2;
        p2+=mul;
        mul = 1;
    }
    Det = p1 - p2;
    return Det;
}

// final de funciones
////////////////////////////////////////////////////////////////////////
// inicio de operaciones entre matrices
void operaciones::on_sumaM_clicked(){
    if(fa == fb && ca == cb){
        double s;
        auto inicio = std::chrono::system_clock::now();
        resultado r(this);
        r.setDimenciones(fa,ca);
        r.setWindowTitle("Suma de matrices A+B");
        r.ver(false,2);
        r.titulos(ca);
        for(int i=0;i<fa;i++){
            for(int j=0;j<ca;j++){
                s = a[i][j] + b[i][j];
                r.agregar(i,j,s);
            }
        }
        auto final = std::chrono::system_clock::now();
        std::chrono::duration<float> duracion = final - inicio;
        ui->tiempo->setText(QString::number(duracion.count()));
        r.exec();
        r.pasar(a,b);
    }
    else{
        QMessageBox::critical(this,"Suma de matrices","Las Dimenciones de A\nNo concuerdan con las dimenciones de B");
    }
}

void operaciones::on_restaM_clicked(){
    if(fa == fb && ca == cb){
        double s;
        auto inicio = std::chrono::system_clock::now();
        resultado r(this);
        r.setDimenciones(fa,ca);
        r.setWindowTitle("Resta de Matrices A-B");
        r.ver(false,2);
        r.titulos(ca);
        for(int i=0;i<fa;i++){
            for(int j=0;j<ca;j++){
                s = a[i][j] - b[i][j];
                r.agregar(i,j,s);
            }
        }
        auto final = std::chrono::system_clock::now();
        std::chrono::duration<float> duracion = final - inicio;
        ui->tiempo->setText(QString::number(duracion.count()));
        r.exec();
        r.pasar(a,b);
    }
    else{
        QMessageBox::critical(this,"Resta de matrices","Las Dimenciones de A\nNo concuerdan con las dimenciones de B");
    }
}

void operaciones::on_productoM_clicked(){
    if(ca == fb){
        double s;
        auto inicio = std::chrono::system_clock::now();
        resultado r(this);
        r.setDimenciones(fa,cb);
        r.setWindowTitle("Producto de Matrices A*B");
        r.ver(false,2);
        r.titulos(ca);
        for(int i=0;i<fa;i++){
            for(int j=0;j<cb;j++){
                s = 0;
                for(int k=0;k<ca;k++){
                    s+=a[i][k]*b[k][j];
                }
                r.agregar(i,j,s);
            }
        }
        auto final = std::chrono::system_clock::now();
        std::chrono::duration<float> duracion = final - inicio;
        ui->tiempo->setText(QString::number(duracion.count()));
        r.exec();
        r.pasar(a,b);
    }
    else{
        QMessageBox::critical(this,"Producto de Matrices","Estas matrices no se pueden multiplicar\n\nYa que las Columnas de A son diferentes\nA las filas de B");
    }
}

void operaciones::on_divicionM_clicked(){
    if(fa == fb && ca == cb){
        double s;
        auto inicio = std::chrono::system_clock::now();
        resultado r(this);
        r.setDimenciones(fa,ca);
        r.setWindowTitle("Divicion de Matrices A/B");
        r.ver(false,2);
        r.titulos(ca);
        for(int i=0;i<fa;i++){
            for(int j=0;j<ca;j++){
                if(b[i][j] == 0){
                    r.agregar(i,j,"NULL");
                }
                else{
                    s = a[i][j] + b[i][j];
                    r.agregar(i,j,s);
                }

            }
        }
        auto final = std::chrono::system_clock::now();
        std::chrono::duration<float> duracion = final - inicio;
        ui->tiempo->setText(QString::number(duracion.count()));
        r.exec();
        r.pasar(a,b);
    }
    else{
        QMessageBox::critical(this,"Divicion de matrices","Las Dimenciones de A\nNo concuerdan con las dimenciones de B");
    }
}

void operaciones::on_elevacionM_clicked(){
    if(fa == fb && ca == cb){
        double s;
        auto inicio = std::chrono::system_clock::now();
        resultado r(this);
        r.setDimenciones(fa,ca);
        r.setWindowTitle("Elevacion de matrices A^B");
        r.ver(false,2);
        r.titulos(ca);
        for(int i=0;i<fa;i++){
            for(int j=0;j<ca;j++){
                if(b[i][j] < 0){
                    s = 1/pow(a[i][j],-1*b[i][j]);
                    r.agregar(i,j,s);
                }
                else{
                    s = pow(a[i][j],b[i][j]);
                    r.agregar(i,j,s);
                }

            }
        }
        auto final = std::chrono::system_clock::now();
        std::chrono::duration<float> duracion = final - inicio;
        ui->tiempo->setText(QString::number(duracion.count()));
        r.exec();
        r.pasar(a,b);
    }
    else{
        QMessageBox::critical(this,"Elevacion de matrices","Las Dimenciones de A\nNo concuerdan con las dimenciones de B");
    }
}

void operaciones::on_logM_clicked(){
    if(fa == fb && ca == cb){
        double s;
        auto inicio = std::chrono::system_clock::now();
        resultado r(this);
        r.setDimenciones(fa,ca);
        r.setWindowTitle("LogB(A)");
        r.ver(false,2);
        r.titulos(ca);
        for(int i=0;i<fa;i++){
            for(int j=0;j<ca;j++){
                if(a[i][j]  <=  1 || b[i][j] <= 1){
                    r.agregar(i,j,"NULL");
                }
                else if(a[i][j]  <=  1 && b[i][j] <= 1){
                    r.agregar(i,j,"NULL");
                }
                else{
                    s = log(a[i][j])/log(b[i][j]);
                    r.agregar(i,j,s);
                }
            }
        }
        auto final = std::chrono::system_clock::now();
        std::chrono::duration<float> duracion = final - inicio;
        ui->tiempo->setText(QString::number(duracion.count()));
        r.exec();
        r.pasar(a,b);
    }
    else{
        QMessageBox::critical(this,"LogB(A)","Las Dimenciones de A\nNo concuerdan con las dimenciones de B");
    }
}

void operaciones::on_raizM_clicked(){
    if(fa == fb && ca == cb){
        double s;
        auto inicio = std::chrono::system_clock::now();
        resultado r(this);
        r.setDimenciones(fa,ca);
        r.setWindowTitle("LogB(A)");
        r.ver(false,2);
        r.titulos(ca);
        for(int i=0;i<fa;i++){
            for(int j=0;j<ca;j++){
                if(b[i][j] < 2){
                    r.agregar(i,j,"NULL");
                }
                else if(a[i][j] < 0){
                    r.agregar(i,j,"En proceso");
                }
                else{
                    s = pow(a[i][j],1/b[i][j]);
                    r.agregar(i,j,s);
                }
            }
        }
        auto final = std::chrono::system_clock::now();
        std::chrono::duration<float> duracion = final - inicio;
        ui->tiempo->setText(QString::number(duracion.count()));
        r.exec();
        r.pasar(a,b);
    }
    else{
        QMessageBox::critical(this,"A^(1/B)","Las Dimenciones de A\nNo concuerdan con las dimenciones de B");
    }
}

void operaciones::on_AinB_clicked(){
    auto inicio = std::chrono::system_clock::now();
    resultado r(this);
    r.setDimenciones(fa,ca);

    r.setWindowTitle("Valores de A en B");

    bool v;

    for(int i=0;i<fa;i++){
        for(int j=0;j<ca;j++){
            r.agregar(i,j,a[i][j]);
            // ver si pertenece a la serie de fibonachi o no

            for(int z=0;z<fa;z++){
                for(int x=0;x<ca;x++){
                    if(a[i][j] == b[z][x]){
                        v = true;
                    }
                    else{
                        v = false;
                    }
                }
            }

            if(v){
                r.Color(false,i,j);
            }
            else {
               r.Color(true,i,j);
            }
        }
    }

    r.titulos(ca,"R");
    r.ver(false,2);
    auto final = std::chrono::system_clock::now();
    std::chrono::duration<float> duracion = final - inicio;
    ui->tiempo->setText(QString::number(duracion.count()));
    r.exec();
}
// final de operaciones entre matrices
///////////////////////////////////////////////////////////////////////
// inicio de operaciones entre escalar

void operaciones::on_suma_clicked(){
    double s;
    auto inicio = std::chrono::system_clock::now();
    resultado r(this);
    r.setDimenciones(fa,ca);
    r.setWindowTitle("Suma de Matriz con un Escalar A+x");
    r.titulos(ca,"R");
    for(int i=0;i<fa;i++){
        for(int j=0;j<ca;j++){
            s = a[i][j] + ui->operar->value();
            r.agregar(i,j,s);
        }
        s = v[i] + ui->operar->value();
        r.agregarV(i,s);
    }
    auto final = std::chrono::system_clock::now();
    std::chrono::duration<float> duracion = final - inicio;
    ui->tiempo->setText(QString::number(duracion.count()));
    r.exec();
    r.pasar(a,b);
}

void operaciones::on_resta_clicked(){
    double s;
    auto inicio = std::chrono::system_clock::now();
    resultado r(this);
    r.setDimenciones(fa,ca);
    r.setWindowTitle("Resta de Matriz con un Escalar A-x");
    r.titulos(ca,"R");
    for(int i=0;i<fa;i++){
        for(int j=0;j<ca;j++){
            s = a[i][j] - ui->operar->value();
            r.agregar(i,j,s);
        }
        s = v[i] - ui->operar->value();
        r.agregarV(i,s);
    }
    auto final = std::chrono::system_clock::now();
    std::chrono::duration<float> duracion = final - inicio;
    ui->tiempo->setText(QString::number(duracion.count()));
    r.exec();
    r.pasar(a,b);
}

void operaciones::on_producto_clicked(){
    double s;
    auto inicio = std::chrono::system_clock::now();
    resultado r(this);
    r.setDimenciones(fa,ca);
    r.setWindowTitle("Producto de Matriz con un Escalar A*x");
    r.titulos(ca,"R");
    for(int i=0;i<fa;i++){
        for(int j=0;j<ca;j++){
            s = a[i][j] * ui->operar->value();
            r.agregar(i,j,s);
        }
        s = v[i] * ui->operar->value();
        r.agregarV(i,s);
    }
    auto final = std::chrono::system_clock::now();
    std::chrono::duration<float> duracion = final - inicio;
    ui->tiempo->setText(QString::number(duracion.count()));
    r.exec();
    r.pasar(a,b);
}

void operaciones::on_divicion_clicked(){
    double s;
    auto inicio = std::chrono::system_clock::now();
    resultado r(this);
    r.setDimenciones(fa,ca);
    r.setWindowTitle("Divicion de Matriz con un Escalar A/x");
    r.titulos(ca,"R");
    for(int i=0;i<fa;i++){
        for(int j=0;j<ca;j++){
            if(ui->operar->value() == 0){
                r.agregar(i,j,"NULL");
            }
            else{
                s = a[i][j] / ui->operar->value();
                r.agregar(i,j,s);
            }
        }
        if(ui->operar->value() == 0){
            r.agregarV(i,"NULL");
        }
        else{
            s = v[i] / ui->operar->value();
            r.agregarV(i,s);
        }
    }
    auto final = std::chrono::system_clock::now();
    std::chrono::duration<float> duracion = final - inicio;
    ui->tiempo->setText(QString::number(duracion.count()));
    r.exec();
    r.pasar(a,b);
}

void operaciones::on_elevacion_clicked(){
    double s;
    auto inicio = std::chrono::system_clock::now();
    resultado r(this);
    r.setDimenciones(fa,ca);
    r.setWindowTitle("Elevacion de Matriz con un Escalar A^x");
    r.titulos(ca,"R");
    for(int i=0;i<fa;i++){
        for(int j=0;j<ca;j++){
            if(ui->operar->value() < 0){
                s = 1/pow(a[i][j],-1*ui->operar->value());
            }
            else{
                s = pow(a[i][j],ui->operar->value());
            }
            r.agregar(i,j,s);
        }
        if(ui->operar->value() < 0){
            s = 1/pow(v[i],-1*ui->operar->value());
        }
        else{
            s = pow(v[i],ui->operar->value());
        }
        r.agregarV(i,s);
    }
    auto final = std::chrono::system_clock::now();
    std::chrono::duration<float> duracion = final - inicio;
    ui->tiempo->setText(QString::number(duracion.count()));
    r.exec();
    r.pasar(a,b);
}

void operaciones::on_elevacionA_clicked(){
    double s;
    auto inicio = std::chrono::system_clock::now();
    resultado r(this);
    r.setDimenciones(fa,ca);
    r.setWindowTitle("Elevacion de Matriz con un Escalar x^A");
    r.titulos(ca,"R");
    for(int i=0;i<fa;i++){
        for(int j=0;j<ca;j++){
            if(a[i][j] < 0){
                s = 1/pow(ui->operar->value(),-1*a[i][j]);
            }
            else{
                s = pow(ui->operar->value(),a[i][j]);
            }
            r.agregar(i,j,s);
        }
        if(ui->operar->value() < 0){
            s = 1/pow(ui->operar->value(),-1*v[i]);
        }
        else{
            s = pow(ui->operar->value(),v[i]);
        }
        r.agregarV(i,s);
    }
    auto final = std::chrono::system_clock::now();
    std::chrono::duration<float> duracion = final - inicio;
    ui->tiempo->setText(QString::number(duracion.count()));
    r.exec();
    r.pasar(a,b);
}

void operaciones::on_log_clicked(){
    double s;
    auto inicio = std::chrono::system_clock::now();
    resultado r(this);
    r.setDimenciones(fa,ca);
    r.setWindowTitle("Logx(A)");
    r.titulos(ca,"R");
    for(int i=0;i<fa;i++){
        for(int j=0;j<ca;j++){
            if(ui->operar->value() <= 1 || a[i][j] <= 0){
                r.agregar(i,j,"NULL");
            }
            else{
                s  = log(a[i][j])/log(ui->operar->value());
                r.agregar(i,j,s);
            }
        }
        if(ui->operar->value() <= 1 || v[i] <= 0){
            r.agregarV(i,"NULL");
        }
        else{
            s  = log(v[i])/log(ui->operar->value());
            r.agregarV(i,s);
        }

    }
    auto final = std::chrono::system_clock::now();
    std::chrono::duration<float> duracion = final - inicio;
    ui->tiempo->setText(QString::number(duracion.count()));
    r.exec();
    r.pasar(a,b);
}

void operaciones::on_raiz_clicked(){
    double s;
    auto inicio = std::chrono::system_clock::now();
    resultado r(this);
    r.setDimenciones(fa,ca);
    r.setWindowTitle("Raiz de Matriz con un Escalar A^(1/x)");
    r.titulos(ca,"R");
    for(int i=0;i<fa;i++){
        for(int j=0;j<ca;j++){
            if(a[i][j] < 0){
                r.agregar(i,j,"En Proceso");
            }
            else if(ui->operar->value() == 0){
                r.agregar(i,j,"NULL");
            }
            else if(a[i][j] == 0){
                r.agregar(i,j,"NULL");
            }
            else{
                s = pow(a[i][j],1/ui->operar->value());
                r.agregar(i,j,s);
            }
        }
        if(v[i] < 0){
            r.agregarV(i,"En Proceso");
        }
        else if(ui->operar->value() == 0){
            r.agregarV(i,"NULL");
        }
        else if(v[i] == 0){
             r.agregarV(i,"NULL");
        }
        else{
            s = pow(v[i],1/ui->operar->value());
            r.agregarV(i,s);
        }
    }
    auto final = std::chrono::system_clock::now();
    std::chrono::duration<float> duracion = final - inicio;
    ui->tiempo->setText(QString::number(duracion.count()));
    r.exec();
    r.pasar(a,b);
}

void operaciones::on_Par_clicked(){
    auto inicio = std::chrono::system_clock::now();
    resultado r(this);
    r.setDimenciones(fa,ca);

    r.setWindowTitle("Pares");

    for(int i=0;i<fa;i++){
        for(int j=0;j<ca;j++){
            if(int(a[i][j])%2 == 0){
                r.agregar(i,j,a[i][j]);
                r.Color(false,i,j);
            }
            else{
                r.agregar(i,j,a[i][j]);
                r.Color(true,i,j);
            }
        }
    }

    r.titulos(ca,"R");
    r.ver(false,2);
    r.ver(false,3);
    r.ver(false,5);
    r.ver(false,6);
    auto final = std::chrono::system_clock::now();
    std::chrono::duration<float> duracion = final - inicio;
    ui->tiempo->setText(QString::number(duracion.count()));
    r.exec();
}

void operaciones::on_Divisor_clicked(){
    auto inicio = std::chrono::system_clock::now();
    resultado r(this);
    r.setDimenciones(fa,ca);

    r.setWindowTitle("Divisor de  "+QString::number(ui->operar->value()));

    for(int i=0;i<fa;i++){
        for(int j=0;j<ca;j++){
            if(ui->operar->value() == 0){
                r.agregar(i,j,"NULL");
            }
            else if((int(a[i][j]) % int(ui->operar->value())) == 0){
                r.agregar(i,j,a[i][j]);
                r.Color(false,i,j);
            }
            else{
                r.agregar(i,j,a[i][j]);
                r.Color(true,i,j);
            }
        }
    }

    r.titulos(ca,"R");
    r.ver(false,2);
    r.ver(false,3);
    r.ver(false,5);
    r.ver(false,6);
    auto final = std::chrono::system_clock::now();
    std::chrono::duration<float> duracion = final - inicio;
    ui->tiempo->setText(QString::number(duracion.count()));
    r.exec();
}

// final deoperacionesentreescalar
////////////////////////////////////////////////////////////////
// inicio de funciones de una matriz A
void operaciones::on_sinA_clicked(){
    auto inicio = std::chrono::system_clock::now();
    resultado r(this);
    r.setDimenciones(fa,ca);
    r.setWindowTitle("Sin(A)");
    r.titulos(ca,"R");
    for(int i=0;i<fa;i++){
        for(int j=0;j<ca;j++){
            s = sin(a[i][j]);
            r.agregar(i,j,s);
        }
        s = sin(v[i]);
        r.agregarV(i,s);
    }

    auto final = std::chrono::system_clock::now();
    std::chrono::duration<float> duracion = final - inicio;
    ui->tiempo->setText(QString::number(duracion.count()));
    r.exec();
    r.pasar(a,b);
}

void operaciones::on_cosA_clicked(){
    auto inicio = std::chrono::system_clock::now();
    resultado r(this);
    r.setDimenciones(fa,ca);
    r.setWindowTitle("Cos(A)");
    r.titulos(ca,"R");
    for(int i=0;i<fa;i++){
        for(int j=0;j<ca;j++){
            s = cos(a[i][j]);
            r.agregar(i,j,s);
        }
        s = cos(v[i]);
        r.agregarV(i,s);
    }

    auto final = std::chrono::system_clock::now();
    std::chrono::duration<float> duracion = final - inicio;
    ui->tiempo->setText(QString::number(duracion.count()));
    r.exec();
    r.pasar(a,b);
}

void operaciones::on_tanA_clicked(){
    auto inicio = std::chrono::system_clock::now();
    resultado r(this);
    r.setDimenciones(fa,ca);
    r.setWindowTitle("Tan(A)");
    r.titulos(ca,"R");
    for(int i=0;i<fa;i++){
        for(int j=0;j<ca;j++){
            s = tan(a[i][j]);
            r.agregar(i,j,s);
        }
        s = tan(v[i]);
        r.agregarV(i,s);
    }

    auto final = std::chrono::system_clock::now();
    std::chrono::duration<float> duracion = final - inicio;
    ui->tiempo->setText(QString::number(duracion.count()));
    r.exec();
    r.pasar(a,b);
}

void operaciones::on_e_clicked(){
    const double e = 2.7182818284590452353602874713527;

    auto inicio = std::chrono::system_clock::now();
    resultado r(this);
    r.setDimenciones(fa,ca);
    r.setWindowTitle("e^A");
    r.ver(false,2);
    r.titulos(fa);
    for(int i=0;i<fa;i++){
        for(int j=0;j<ca;j++){
            r.agregar(i,j,pow(e,a[i][j]));
        }
    }

    auto final = std::chrono::system_clock::now();
    std::chrono::duration<float> duracion = final - inicio;
    ui->tiempo->setText(QString::number(duracion.count()));
    r.exec();
    r.pasar(a,b);
}

void operaciones::on_transpuesta_clicked(){
    auto inicio = std::chrono::system_clock::now();
    resultado r(this);
    r.setDimenciones(fa,ca);
    r.setWindowTitle("Matriz transpuesta");
    r.ver(false,2);
    r.titulos(fa);
    for(int i=0;i<fa;i++){
        for(int j=0;j<ca;j++){
            r.agregar(i,j,a[j][i]);
        }
    }

    auto final = std::chrono::system_clock::now();
    std::chrono::duration<float> duracion = final - inicio;
    ui->tiempo->setText(QString::number(duracion.count()));
    r.exec();
    r.pasar(a,b);
}

void operaciones::on_histograma_clicked(){
    auto inicio = std::chrono::system_clock::now();
    int x = 0;
    double s[10000];
    double aux[10000];

    for(int i=0;i<fa;i++){
        for(int j=0;j<ca;j++){
            s[x] = a[i][j];
            aux[x] = 0;
            x++;
        }
    }



    Shell(s,fa,ca);

    // ver cuantas veces se repite un numero
    double y = s[0];
    x = 0;
    QStringList l;

    for(int i=0;i<(fa*ca);i++){
        if(s[i] == y){
            aux[x]+=1;
        }
        else{
            l<<QString::number(y);
            y = s[i];
            i--;
            x++;
        }
    }

    l<<QString::number(y);
    QStringList l2;
    l2<<"Apariciones"<<"%";
    resultado r(this);
    r.setDimenciones(fa,2);
    r.setWindowTitle("Histograma");
    r.ver(false,2);
    r.Histograma(2,x+1,0,70,1,80,l,l2,aux,(fa*ca),a);
    auto final = std::chrono::system_clock::now();
    std::chrono::duration<float> duracion = final - inicio;
    ui->tiempo->setText(QString::number(duracion.count()));
    r.exec();
}

void operaciones::on_factorial_clicked(){

    auto inicio = std::chrono::system_clock::now();
    resultado r(this);
    r.setDimenciones(fa,ca);

    r.setWindowTitle("Factorial");

    qlonglong aux;

    for(int i=0;i<fa;i++){
        for(int j=0;j<ca;j++){
            aux = 1;
            if(a[i][j] > 0){
                for(int z=1;z<=int(a[i][j]);z++){
                    aux *= z;
                }

                r.agregar(i,j,QString::number(aux));
            }
            else{
                r.agregar(i,j,"NULL");
            }
        }

        aux = 1;
        if(v[i] > 0){
            for(int z=1;z<=int(v[i]);z++){
                aux *= z;
            }

            r.agregarV(i,QString::number(aux));
        }
        else{
            r.agregarV(i,"NULL");
        }
    }

    r.titulos(ca,"R");
    auto final = std::chrono::system_clock::now();
    std::chrono::duration<float> duracion = final - inicio;
    ui->tiempo->setText(QString::number(duracion.count()));
    r.exec();
    r.pasar(a,b);
}

void operaciones::on_naturales_clicked(){
    auto inicio = std::chrono::system_clock::now();
    resultado r(this);
    r.setDimenciones(fa,ca);

    r.setWindowTitle("Numeros Naturales");

    for(int i=0;i<fa;i++){
        for(int j=0;j<ca;j++){
            r.agregar(i,j,a[i][j]);
            if((a[i][j] == int(a[i][j])) && (a[i][j] > 0)){
                r.Color(false,i,j);
            }
            else{
                r.Color(true,i,j);
            }
        }
    }

    r.titulos(ca,"R");
    r.ver(false,2);
    auto final = std::chrono::system_clock::now();
    std::chrono::duration<float> duracion = final - inicio;
    ui->tiempo->setText(QString::number(duracion.count()));
    r.exec();
}

void operaciones::on_cscA_clicked(){
    auto inicio = std::chrono::system_clock::now();
    resultado r(this);
    r.setDimenciones(fa,ca);
    r.setWindowTitle("Csc(A)");
    r.titulos(ca,"R");
    for(int i=0;i<fa;i++){
        for(int j=0;j<ca;j++){
            s = sin(a[i][j]);
            if(s != 0){
                r.agregar(i,j,1/s);
            }
            else{
                r.agregar(i,j,"NULL");
            }
        }
        s = sin(v[i]);
        if(s != 0){
            r.agregarV(i,1/s);
        }
        else{
            r.agregarV(i,"NULL");
        }
    }

    auto final = std::chrono::system_clock::now();
    std::chrono::duration<float> duracion = final - inicio;
    ui->tiempo->setText(QString::number(duracion.count()));
    r.exec();
    r.pasar(a,b);
}

void operaciones::on_secA_clicked(){
    auto inicio = std::chrono::system_clock::now();
    resultado r(this);
    r.setDimenciones(fa,ca);
    r.setWindowTitle("Sec(A)");
    r.titulos(ca,"R");
    for(int i=0;i<fa;i++){
        for(int j=0;j<ca;j++){
            s = cos(a[i][j]);
            if(s != 0){
                r.agregar(i,j,1/s);
            }
            else{
                r.agregar(i,j,"NULL");
            }
        }
        s = cos(v[i]);
        if(s != 0){
            r.agregarV(i,1/s);
        }
        else{
            r.agregarV(i,"NULL");
        }
    }

    auto final = std::chrono::system_clock::now();
    std::chrono::duration<float> duracion = final - inicio;
    ui->tiempo->setText(QString::number(duracion.count()));
    r.exec();
    r.pasar(a,b);
}

void operaciones::on_cotA_clicked(){
    auto inicio = std::chrono::system_clock::now();
    resultado r(this);
    r.setDimenciones(fa,ca);
    r.setWindowTitle("Csc(A)");
    r.titulos(ca,"R");
    for(int i=0;i<fa;i++){
        for(int j=0;j<ca;j++){
            s = tan(a[i][j]);
            if(s != 0){
                r.agregar(i,j,1/s);
            }
            else{
                r.agregar(i,j,"NULL");
            }
        }
        s = tan(v[i]);
        if(s != 0){
            r.agregarV(i,1/s);
        }
        else{
            r.agregarV(i,"NULL");
        }
    }

    auto final = std::chrono::system_clock::now();
    std::chrono::duration<float> duracion = final - inicio;
    ui->tiempo->setText(QString::number(duracion.count()));
    r.exec();
    r.pasar(a,b);
}

void operaciones::on_Pi_clicked(){
    const double pi = 3.1415926535897932384626433832795;

    auto inicio = std::chrono::system_clock::now();
    resultado r(this);
    r.setDimenciones(fa,ca);
    r.setWindowTitle("Pi^A");
    r.ver(false,2);
    r.titulos(fa);
    for(int i=0;i<fa;i++){
        for(int j=0;j<ca;j++){
            r.agregar(i,j,pow(pi,a[i][j]));
        }
    }

    auto final = std::chrono::system_clock::now();
    std::chrono::duration<float> duracion = final - inicio;
    ui->tiempo->setText(QString::number(duracion.count()));
    r.exec();
    r.pasar(a,b);
}

void operaciones::on_Max_Min_clicked(){
    auto inicio = std::chrono::system_clock::now();
    int x = 0;
    double s[10000];
    resultado r(this);
    r.setDimenciones(fa,ca);
    r.ver(false,2);
    r.setWindowTitle("Ordenamiento de A, de Mayor a Menor");
    for(int i=0;i<fa;i++){
        for(int j=0;j<ca;j++){
            s[x++] = a[i][j];
        }
    }
    x-=1;
    Shell(s,fa,ca);
    for(int i=0;i<fa;i++){
        for(int j=0;j<ca;j++){
            r.agregar(i,j,s[x]);
            x--;
        }
    }
    r.titulos(fa);
    auto final = std::chrono::system_clock::now();
    std::chrono::duration<float> duracion = final - inicio;
    ui->tiempo->setText(QString::number(duracion.count()));
    r.exec();

}

void operaciones::on_Resolver_clicked(){
     auto inicio = std::chrono::system_clock::now();
    int nxn = fa;
    double vaux[100];
    double nDet[101];
    int nM = 0;
    double t = 0;

    if(fa != ca ){
        QMessageBox::critical(this,"Resolver matriz","La matriz debe de ser cuadrada");
    }
    else if(nxn < 2){
        QMessageBox::critical(this,"Resolver matriz","La matriz debe de ser cuadrada y con dimenciones mayores a 1 ");
    }
    else if(nxn == 3){

        //determinante
        resultado r(this);
        r.setWindowTitle("Resolviendo matriz");
        r.setDimenciones(fa,ca);
        r.ver(false,1);
        nDet[0] = Determinante(a);
        if(nDet[0] == 0){
            QMessageBox::critical(this,"Resolver mediante determinante","El determinante principal es 0, no se puede usar este metodo");
        }
        else{

            for(int i=0;i<nxn;i++){
                for(int j=0;j<nxn;j++){
                    vaux[j] = a[j][i];
                    a[j][i] = v[j];
                }
                nM++;
                //determinante
                nDet[nM] = Determinante(a);
                //qDebug()<<nDet[nM];
                for(int j=0;j<nxn;j++){
                    a[j][i] = vaux[j];
                }
            }
            r.titulos("Valores",nxn);
            for(int k=0;k<nxn;k++){
                //qDebug()<<nDet[k+1];
                double resultado = nDet[k+1]/nDet[0];
                //qDebug()<<resultado;
                r.agregarV(k,resultado);
            }
            auto final = std::chrono::system_clock::now();
            std::chrono::duration<float> duracion = final - inicio;
            ui->tiempo->setText(QString::number(duracion.count()));
            r.exec();
        }
    }
    else if(nxn > 3){
        // gaus jordan
        try{
            resultado r(this);
            r.setDimenciones(fa,ca);
            r.ver(false,1);
            double al[100][101];
            double x[100];
            for(int i=0;i<nxn;i++){
                for(int j=0;j<nxn;j++){
                    al[i][j] = a[i][j];
                    for(j;j == (nxn-1);j++){
                        j++;
                        al[i][j] = v[i];
                    }
                }
            }
            int i,j,k,max;
            double l;
            for(i=0;i<nxn;i++){
                for(j = i + 1; j < nxn; j++){
                    l = al[j][i] / al[i][i];
                    for(k = i; k <= nxn; k++) {
                        al[j][k] -= l * al[i][k];
                    }
                }
                max = i;
                for(j = i + 1; j < nxn; j++){
                    if (fabs(al[j][i]) > fabs(al[max][i])){
                        max = j;
                    }
                    if(i != max){
                        for (k = i; k <= nxn; k++) {
                            t = a[i][k];
                            a[i][k] = a[max][k];
                            a[max][k] = t;
                            }
                    }
                }
            }
            for (i = nxn - 1; i >= 0; i--) {
                    al[i][nxn] /= al[i][i];
                    al[i][i] = 1;
                    for (j = i - 1; j >= 0; j--) {
                        al[j][nxn] -= al[j][i] * al[i][nxn];
                        al[j][i] = 0;
                    }
                    x[i] = al[i][nxn];
                }
            for(int i=0;i<nxn;i++){
                r.agregarV(i,x[i]);
            }
            r.setWindowTitle("Resolviendo matriz");
            r.titulos("Valores",nxn);
            r.NoPasar();
            auto final = std::chrono::system_clock::now();
            std::chrono::duration<float> duracion = final - inicio;
            ui->tiempo->setText(QString::number(duracion.count()));
            r.exec();
        }
        catch(const char){
            QMessageBox::critical(this,"Resolver matriz","Con esos valores no hay solucion");
        }
    }

}

void operaciones::on_adjunta_clicked(){
    auto inicio = std::chrono::system_clock::now();
    double Det = Determinante(a);
    if(Det == 0 || Det == NAN){
        QMessageBox::critical(this,"Matriz Adjunta","La matriz A no tiene adjunta");
    }
    else{
        double I[100][100];
        double ai[100][100];
        double aux,pivote;
        for(int i=0;i<fa;i++){
            for(int j=0;j<ca;j++){
                if(i == j){
                    I[i][j] = 1;
                }
                else{
                    I[i][j] = 0;
                }
                ai[i][j] = a[i][j];
            }
        }
        resultado r(this);
        r.setDimenciones(fa,ca);
        r.ver(false,2);
        r.titulos(fa);
        for(int i=0;i<fa;i++){
            pivote = ai[i][i];
            for(int k=0;k<ca;k++){
                ai[i][k]/=pivote;
                I[i][k]/=pivote;
            }
            for(int j=0;j<fa;j++){
                if(i!=j){
                    aux = ai[j][i];
                    for(int k=0;k<fa;k++){
                        ai[j][k]-=(aux*ai[i][k]);
                        I[j][k]-=(aux*I[i][k]);
                    }
                }
            }
        }

        for(int i=0;i<fa;i++){
            for(int j=0;j<ca;j++){
                I[i][j]*=Det;
            }
        }

        for(int i=0;i<fa;i++){
            for(int j=0;j<ca;j++){
                r.agregar(i,j,I[j][i]);
            }
        }
        r.setWindowTitle("Matriz Adjunta de de A");
        auto final = std::chrono::system_clock::now();
        std::chrono::duration<float> duracion = final - inicio;
        ui->tiempo->setText(QString::number(duracion.count()));
        r.exec();
        r.pasar(a,b);
    }
}

void operaciones::on_enteros_clicked(){
    auto inicio = std::chrono::system_clock::now();
    resultado r(this);
    r.setDimenciones(fa,ca);

    r.setWindowTitle("Numeros Enteros");

    for(int i=0;i<fa;i++){
        for(int j=0;j<ca;j++){
            r.agregar(i,j,a[i][j]);
            if((a[i][j] == int(a[i][j]))){
                r.Color(false,i,j);
            }
            else{
                r.Color(true,i,j);
            }
        }
    }

    r.titulos(ca,"R");
    r.ver(false,2);
    auto final = std::chrono::system_clock::now();
    std::chrono::duration<float> duracion = final - inicio;
    ui->tiempo->setText(QString::number(duracion.count()));
    r.exec();
    r.pasar(a,b);
}

void operaciones::on_AsinA_clicked(){
    auto inicio = std::chrono::system_clock::now();
    resultado r(this);
    r.setDimenciones(fa,ca);
    r.setWindowTitle("ArcoSin(A)");
    r.titulos(ca,"R");
    for(int i=0;i<fa;i++){
        for(int j=0;j<ca;j++){
            if(a[i][j] < -1 || a[i][j] > 1){
                r.agregar(i,j,"NULL");
            }
            else{
                s = asin(a[i][j]);
                r.agregar(i,j,s);
            }
        }
        if(v[i] < -1 || v[i] > 1){
            r.agregarV(i,"NULL");
        }
        else{
            s = asin(v[i]);
            r.agregarV(i,s);
        }
    }

    auto final = std::chrono::system_clock::now();
    std::chrono::duration<float> duracion = final - inicio;
    ui->tiempo->setText(QString::number(duracion.count()));
    r.exec();
    r.pasar(a,b);
}

void operaciones::on_AcosA_clicked(){
    auto inicio = std::chrono::system_clock::now();
    resultado r(this);
    r.setDimenciones(fa,ca);
    r.setWindowTitle("ArcoCos(A)");
    r.titulos(ca,"R");
    for(int i=0;i<fa;i++){
        for(int j=0;j<ca;j++){
            if(a[i][j] < -1 || a[i][j] > 1){
                r.agregar(i,j,"NULL");
            }
            else{
                s = acos(a[i][j]);
                r.agregar(i,j,s);
            }
        }
        if(v[i] < -1 || v[i] > 1){
            r.agregarV(i,"NULL");
        }
        else{
            s = acos(v[i]);
            r.agregarV(i,s);
        }
    }

    auto final = std::chrono::system_clock::now();
    std::chrono::duration<float> duracion = final - inicio;
    ui->tiempo->setText(QString::number(duracion.count()));
    r.exec();
    r.pasar(a,b);
}

void operaciones::on_AtanA_clicked(){
    auto inicio = std::chrono::system_clock::now();
    resultado r(this);
    r.setDimenciones(fa,ca);
    r.setWindowTitle("Tan(A)");
    r.titulos(ca,"R");
    for(int i=0;i<fa;i++){
        for(int j=0;j<ca;j++){
            s = atan(a[i][j]);
            r.agregar(i,j,s);
        }
        s = atan(v[i]);
        r.agregarV(i,s);
    }

    auto final = std::chrono::system_clock::now();
    std::chrono::duration<float> duracion = final - inicio;
    ui->tiempo->setText(QString::number(duracion.count()));
    r.exec();
    r.pasar(a,b);
}

void operaciones::on_inversa_clicked(){
    auto inicio = std::chrono::system_clock::now();
    double Det = Determinante(a);
    if(Det == 0 || Det == NAN){
        QMessageBox::critical(this,"Matriz inversa","La matriz A no tiene inversa");
    }
    else{
        double I[100][100];
        double ai[100][100];
        double aux,pivote;
        for(int i=0;i<fa;i++){
            for(int j=0;j<ca;j++){
                if(i == j){
                    I[i][j] = 1;
                }
                else{
                    I[i][j] = 0;
                }
                ai[i][j] = a[i][j];
            }
        }
        resultado r(this);
        r.setDimenciones(fa,ca);
        r.ver(false,2);
        r.titulos(fa);
        for(int i=0;i<fa;i++){
            pivote = ai[i][i];
            for(int k=0;k<ca;k++){
                ai[i][k]/=pivote;
                I[i][k]/=pivote;
            }
            for(int j=0;j<fa;j++){
                if(i!=j){
                    aux = ai[j][i];
                    for(int k=0;k<fa;k++){
                        ai[j][k]-=(aux*ai[i][k]);
                        I[j][k]-=(aux*I[i][k]);
                    }
                }
            }
        }
        for(int i=0;i<fa;i++){
            for(int j=0;j<ca;j++){
                r.agregar(i,j,I[i][j]);
            }
        }
        r.setWindowTitle("Matriz Inversa de A");
        auto final = std::chrono::system_clock::now();
        std::chrono::duration<float> duracion = final - inicio;
        ui->tiempo->setText(QString::number(duracion.count()));
        r.exec();
        r.pasar(a,b);
    }
}

void operaciones::on_Min_Max_clicked(){
    auto inicio = std::chrono::system_clock::now();
    int x = 0;
    double s[10000];
    resultado r(this);
    r.setDimenciones(fa,ca);
    r.ver(false,2);
    r.setWindowTitle("Ordenamiento de A, de Menor a Mayor");
    for(int i=0;i<fa;i++){
        for(int j=0;j<ca;j++){
            s[x++] = a[i][j];
        }
    }
    x=0;
    Shell(s,fa,ca);
    for(int i=0;i<fa;i++){
        for(int j=0;j<ca;j++){
            r.agregar(i,j,s[x++]);
        }
    }
    r.titulos(fa);
    auto final = std::chrono::system_clock::now();
    std::chrono::duration<float> duracion = final - inicio;
    ui->tiempo->setText(QString::number(duracion.count()));
    r.exec();
}

void operaciones::on_distribucionE_clicked(){
    auto inicio = std::chrono::system_clock::now();
    double m = Menor(fa,ca);
    if((fa > 2 && ca > 2) && m > 0){
        resultado r(this);
        r.ver(false,2);
        r.DistrubucionFrecuencia(a,fa,m,fa,ca);
        auto final = std::chrono::system_clock::now();
        std::chrono::duration<float> duracion = final - inicio;
        ui->tiempo->setText(QString::number(duracion.count()));
        r.exec();
    }
    else if(m < 1){
        QMessageBox::critical(this,"Distribucion de frecuencia de A","El valor menor debe de ser mayor a 0");
    }
    else{
        QMessageBox::critical(this,"Distrubucion de frecuencia de A","Hay muy pocos datos");
    }
}

void operaciones::on_caracter_clicked(){
    auto inicio = std::chrono::system_clock::now();
    resultado r(this);
    r.setDimenciones(fa,ca);

    r.setWindowTitle("Caracter");

    QString aux;

    for(int i=0;i<fa;i++){
        for(int j=0;j<ca;j++){
            aux.append(char(int(a[i][j])));
            r.agregar(i,j,aux);
            aux.clear();
        }

        aux.append(char(int(v[i])));
        r.agregarV(i,aux);
        aux.clear();
    }

    r.titulos(ca,"R");
    auto final = std::chrono::system_clock::now();
    std::chrono::duration<float> duracion = final - inicio;
    ui->tiempo->setText(QString::number(duracion.count()));
    r.exec();
}

void operaciones::on_fibonachi_clicked(){
    auto inicio = std::chrono::system_clock::now();
    resultado r(this);
    r.setDimenciones(fa,ca);

    r.setWindowTitle("Fibonachi");

    for(int i=0;i<fa;i++){
        for(int j=0;j<ca;j++){
            r.agregar(i,j,a[i][j]);
            // ver si pertenece a la serie de fibonachi o no

        }
    }

    r.titulos(ca,"R");
    r.ver(false,2);
    auto final = std::chrono::system_clock::now();
    std::chrono::duration<float> duracion = final - inicio;
    ui->tiempo->setText(QString::number(duracion.count()));
    r.exec();
}
// final de funciones de una matriz A
/////////////////////////////////////////////////////////////////////

// inicio Atributos de la matriz A
void operaciones::on_determinante_clicked(){
    auto inicio = std::chrono::system_clock::now();

    ui->rDeterminante->setText(QString::number(Determinante(a)));

    auto final = std::chrono::system_clock::now();
    std::chrono::duration<float> duracion = final - inicio;
    ui->tiempo->setText(QString::number(duracion.count()));
}

void operaciones::on_rango_clicked(){

}

void operaciones::on_Menor_clicked(){
    auto inicio = std::chrono::system_clock::now();
    ui->rMenor->setText(QString::number(Menor(fa,ca)));
    auto final = std::chrono::system_clock::now();
    std::chrono::duration<float> duracion = final - inicio;
   ui->tiempo->setText(QString::number(duracion.count()));
}

void operaciones::on_Mayor_clicked(){
    auto inicio = std::chrono::system_clock::now();
    ui->rMayor->setText(QString::number(Mayor(fa,ca)));
    auto final = std::chrono::system_clock::now();
    std::chrono::duration<float> duracion = final - inicio;
   ui->tiempo->setText(QString::number(duracion.count()));
}

void operaciones::on_Media_clicked(){
    auto inicio = std::chrono::system_clock::now();
    ui->rMedia->setText(QString::number(Media()));
    auto final = std::chrono::system_clock::now();
    std::chrono::duration<float> duracion = final - inicio;
    ui->tiempo->setText(QString::number(duracion.count()));
}

void operaciones::on_Mediana_clicked(){
    auto inicio = std::chrono::system_clock::now();

    double s[10000];
    int x = 0;


    for(int i=0;i<fa;i++){
        for(int j=0;j<ca;j++){
            s[x] = a[i][j];
            x++;
        }
    }

    int n = (fa*ca)/2;

    if((fa*ca)%2 == 0){
        ui->rMediana->setText(QString::number(((s[n])+(s[n-1]))/2));
    }
    else{
        ui->rMediana->setText(QString::number(s[n]));
    }

    auto final = std::chrono::system_clock::now();
    std::chrono::duration<float> duracion = final - inicio;
    ui->tiempo->setText(QString::number(duracion.count()));
}

void operaciones::on_Moda_clicked(){
    auto inicio = std::chrono::system_clock::now();
    int x = 0;
    double s[10000];
    double aux[10000];

    for(int i=0;i<fa;i++){
        for(int j=0;j<ca;j++){
            s[x] = a[i][j];
            aux[x] = 0;
            x++;
        }
    }

    Shell(s,fa,ca);

    double y = s[0];
    x = 0;
    QStringList l;

    for(int i=0;i<(fa*ca);i++){
        if(s[i] == y){
            aux[x]+=1;
        }
        else{
            l<<QString::number(y);
            y = s[i];
            i--;
            x++;
        }
    }

    l<<QString::number(y);

    int max = aux[0];
    int r = 0;
    int i;

    for(int j=0;j<=x;j++){
        if(max < aux[j]){
            max = aux[j];
        }

        i++;
    }
    QString q;

    for(int j=0;j<=x;j++){
        if(aux[j] == max){
            if(r > 0){
                q+=",";
            }
            r++;
            q+=l.at(j);
        }
    }

    if(r==1){
        ui->rModa->setText(q);
    }
    else{
        ui->rModa->setText("Multimoda("+q+")");
    }

    auto final = std::chrono::system_clock::now();
    std::chrono::duration<float> duracion = final - inicio;
    ui->tiempo->setText(QString::number(duracion.count()));
}

void operaciones::on_Triangular_clicked(){
    auto inicio = std::chrono::system_clock::now();

    bool su = true,in = true;

    for(int i=0;i<fa;i++){
        for(int j=0;j<ca;j++){
            if(i < j){
                if(a[i][j] != 0){
                    su = false;
                    break;
                }
            }
        }
    }

    for(int i=0;i<fa;i++){
        for(int j=0;j<ca;j++){
            if(i > j){
                if(a[i][j] != 0){
                    in = false;
                    break;
                }
            }
        }
    }

    if(su && in){
        ui->rTriangular->setText("Mixta");
    }
    else if(su){
        ui->rTriangular->setText("Superior");
    }
    else if(in){
        ui->rTriangular->setText("Inferior");
    }
    else{
        ui->rTriangular->setText("NULL");
    }

    auto final = std::chrono::system_clock::now();
    std::chrono::duration<float> duracion = final - inicio;
    ui->tiempo->setText(QString::number(duracion.count()));
}

void operaciones::on_mediaG_clicked(){
    auto inicio = std::chrono::system_clock::now();

    int g = (fa*ca);
    double suma = 1;

    for(int i=0;i<fa;i++){
        for(int j=0;j<ca;j++){
            suma *= a[i][j];
        }
    }

    double mgeometrica;

    if(suma > 0){
        mgeometrica = pow(suma,(float)1/g);
        ui->mGeometrica->setText(QString::number(mgeometrica));
    }
    else{
        ui->mGeometrica->setText("NULL");
    }

    auto final = std::chrono::system_clock::now();
    std::chrono::duration<float> duracion = final - inicio;
    ui->tiempo->setText(QString::number(duracion.count()));
}

void operaciones::on_Sumatoria_clicked(){
    auto inicio = std::chrono::system_clock::now();

    double suma = 0;

    for(int i=0;i<fa;i++){
        for(int j=0;j<ca;j++){
            suma+=a[i][j];
        }
    }

    ui->rSumatoria->setText(QString::number(suma));
    auto final = std::chrono::system_clock::now();
    std::chrono::duration<float> duracion = final - inicio;
    ui->tiempo->setText(QString::number(duracion.count()));
}

void operaciones::on_Varianza_clicked(){
    auto inicio = std::chrono::system_clock::now();
    int n = fa * ca;
    double m = Media();

    for(int i=0;i<fa;i++){
        for(int j=0;j<ca;j++){
            s += (pow((a[i][j] - m),2))/n;
        }
    }

    ui->rVarianza->setText(QString::number(s));

    auto final = std::chrono::system_clock::now();
    std::chrono::duration<float> duracion = final - inicio;
    ui->tiempo->setText(QString::number(duracion.count()));
}

void operaciones::on_desviacionE_clicked(){
    auto inicio = std::chrono::system_clock::now();
    int n = fa * ca;
    double m = Media();

    for(int i=0;i<fa;i++){
        for(int j=0;j<ca;j++){
            s += (pow((a[i][j] - m),2))/n;
        }
    }

    ui->rdistribucionE->setText(QString::number(sqrt(s)));

    auto final = std::chrono::system_clock::now();
    std::chrono::duration<float> duracion = final - inicio;
    ui->tiempo->setText(QString::number(duracion.count()));
}

// final de atributos de la matriz A
////////////////////////////////////////////////////////////////////

void operaciones::on_gAtributos_clicked(){
    QString ruta,extencion,texto;
    if(ui->rDeterminante->text() == ""){
        on_determinante_clicked();
    }

    if(ui->rRango->text() == ""){

    }

    if(ui->rMenor->text() == ""){
        on_Menor_clicked();
    }

    if(ui->rMayor->text() == ""){
        on_Mayor_clicked();
    }

    if(ui->rMedia->text() == ""){
        on_Media_clicked();
    }

    if(ui->rMediana->text() == ""){
        on_Mediana_clicked();
    }

    if(ui->rModa->text() == ""){
        on_Moda_clicked();
    }

    if(ui->rTriangular->text() == ""){
        on_Triangular_clicked();
    }

    if(ui->mGeometrica->text() == ""){
        on_mediaG_clicked();
    }

    if(ui->rSumatoria->text() == ""){
        on_Sumatoria_clicked();
    }

    if(ui->rVarianza->text() == ""){
        on_Varianza_clicked();
    }

    if(ui->rdistribucionE->text() == ""){
        on_desviacionE_clicked();
    }

    direccion d(this);

    d.nombre("Guardando Atributos de A");
    d.titulo("Ruta     ruta/nombre(elija una extencion)");
    d.en_Enabled(false);
    d.exec();
    d.ruta(ruta);

    if(!ruta.isNull()){
        d.extencion(extencion);
        if(!extencion.isNull()){
            extencion = ".txt";
        }

        QFile a(ruta+extencion);

        a.open(QFile::WriteOnly | QFile::Text);

        QTextStream out(&a);

        texto = "Determinante:\t"+ui->rDeterminante->text()+"\n";
        texto += "Rango:\t"+ui->rRango->text()+"\n";
        texto += "Menor:\t"+ui->rMenor->text()+"\n";
        texto += "Mayor:\t"+ui->rMayor->text()+"\n";
        texto += "Media:\t"+ui->rMedia->text()+"\n";
        texto += "Mediana:\t"+ui->rMediana->text()+"\n";
        texto += "Moda:\t"+ui->rModa->text()+"\n";
        texto += "Triangular:\t"+ui->rTriangular->text()+"\n";
        texto += "Media Geometrica:\t"+ui->mGeometrica->text()+"\n";
        texto += "Sumatoria:\t"+ui->rSumatoria->text()+"\n";
        texto += "Varianza:\t"+ui->rVarianza->text()+"\n";
        texto += "Distribucion Estandar:\t"+ui->rdistribucionE->text()+"\n";
        out << texto;
        texto.clear();

        a.flush();
        a.close();
    }
}

void operaciones::on_pasarMatriz_clicked(){
    if(ui->pasarMatriz->text() == "Matriz B"){
        ui->pasarMatriz->setText("Matriz A");
        ui->cambio->setCurrentIndex(1);
    }
    else{
        ui->pasarMatriz->setText("Matriz B");
        ui->cambio->setCurrentIndex(0);
    }

    s = 0;
}

void operaciones::on_Matriz_A_cellDoubleClicked(int row, int column){

    if(ui->variables->currentIndex() == 0){
        if(s == 0){

            ui->x1_1->setValue(ui->Matriz_A->item(row,column)->text().toDouble());
        }
        else if(s == 1){
            ui->y1_1->setValue(ui->Matriz_A->item(row,column)->text().toDouble());
        }
        else if(s == 2){
            ui->x2_1->setValue(ui->Matriz_A->item(row,column)->text().toDouble());
        }
        else if(s == 3){
            ui->y2_1->setValue(ui->Matriz_A->item(row,column)->text().toDouble());
        }

        if(s == 3){
            s = 0;
        }
        else{
            s++;
        }
    }
    else{
        if(s == 0){

            ui->x1_2->setValue(ui->Matriz_A->item(row,column)->text().toDouble());
        }
        else if(s == 1){
            ui->y1_2->setValue(ui->Matriz_A->item(row,column)->text().toDouble());
        }
        else if(s == 2){
            ui->x2_2->setValue(ui->Matriz_A->item(row,column)->text().toDouble());
        }
        else if(s == 3){
            ui->y2_2->setValue(ui->Matriz_A->item(row,column)->text().toDouble());
        }

        if(s == 3){
            s = 0;
        }
        else{
            s++;
        }
    }
}

void operaciones::on_Vector_cellDoubleClicked(int row, int column){
    if(ui->variables->currentIndex() == 0){
        if(s == 0){

            ui->x1_1->setValue(ui->Vector->item(row,column)->text().toDouble());
        }
        else if(s == 1){
            ui->y1_1->setValue(ui->Vector->item(row,column)->text().toDouble());
        }
        else if(s == 2){
            ui->x2_1->setValue(ui->Vector->item(row,column)->text().toDouble());
        }
        else if(s == 3){
            ui->y2_1->setValue(ui->Vector->item(row,column)->text().toDouble());
        }

        if(s == 3){
            s = 0;
        }
        else{
            s++;
        }
    }
    else{
        if(s == 0){

            ui->x1_2->setValue(ui->Vector->item(row,column)->text().toDouble());
        }
        else if(s == 1){
            ui->y1_2->setValue(ui->Vector->item(row,column)->text().toDouble());
        }
        else if(s == 2){
            ui->x2_2->setValue(ui->Vector->item(row,column)->text().toDouble());
        }
        else if(s == 3){
            ui->y2_2->setValue(ui->Vector->item(row,column)->text().toDouble());
        }

        if(s == 3){
            s = 0;
        }
        else{
            s++;
        }
    }

}

void operaciones::on_Matriz_B_cellDoubleClicked(int row, int column){

    if(ui->variables->currentIndex() == 0){
        if(s == 0){

            ui->x1_1->setValue(ui->Matriz_B->item(row,column)->text().toDouble());
        }
        else if(s == 1){
            ui->y1_1->setValue(ui->Matriz_B->item(row,column)->text().toDouble());
        }
        else if(s == 3){
            ui->x2_1->setValue(ui->Matriz_B->item(row,column)->text().toDouble());
        }
        else if(s == 4){
            ui->y2_1->setValue(ui->Matriz_B->item(row,column)->text().toDouble());
        }

        if(s == 3){
            s = 0;
        }
        else{
            s++;
        }
    }
    else{
        if(s == 0){

            ui->x1_2->setValue(ui->Matriz_B->item(row,column)->text().toDouble());
        }
        else if(s == 1){
            ui->y1_2->setValue(ui->Matriz_B->item(row,column)->text().toDouble());
        }
        else if(s == 3){
            ui->x2_2->setValue(ui->Matriz_B->item(row,column)->text().toDouble());
        }
        else if(s == 4){
            ui->y2_2->setValue(ui->Matriz_B->item(row,column)->text().toDouble());
        }

        if(s == 3){
            s = 0;
        }
        else{
            s++;
        }
    }
}

void operaciones::on_interpolar_2_clicked(){
    double y;

    y = ui->y1_1->value() + (  ( (ui->x_1->value() - ui->x1_1->value()) * (ui->x2_1->value() - ui->x1_1->value()) ) / (ui->y2_1->value() - ui->y1_1->value()) );

    ui->resultado->setText(QString::number(y));
}

void operaciones::on_extrapolar_2_clicked(){
    double y;

    y = ui->y1_2->value() + ( ( (ui->x_2->value() - ui->x1_2->value()) * (ui->y1_2->value() - ui->y2_2->value()) ) / (ui->x1_2->value() - ui->x2_2->value()) );

    ui->resultado->setText(QString::number(y));
}
