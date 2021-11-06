#ifndef RESULTADO_H
#define RESULTADO_H

#include <QDialog>

namespace Ui {
    class resultado;
}

class QTableWidget;

class resultado : public QDialog{
    Q_OBJECT

public:
    resultado(QWidget *parent = nullptr);
    ~resultado();
    void setDimenciones(int,int);
    void agregar(int i, int j, double n);
    void agregar(int i, int j, QString n);
    void agregarV(int i, double n);
    void agregarV(int i, QString n);
    double dar(int);
    void ver(bool,int);
    void titulos(int,QString);
    void titulos(QString,int);
    void titulos(int);
    void titulos(QString);
    void pasar(double a[][100],double b[][100]);
    void pasarA();
    int getV();
    void setV(int);
    void setC(int,int);
    void setR(int);
    void DistrubucionFrecuencia(double [][100],int, double,int,int);
    void NoPasar();
    void Histograma(int,int,int,int,int,int,QStringList,QStringList,double [],int,double [][100]);
    void Color(bool,int,int);
private slots:
    void on_pasarA_clicked();
    void on_pasarB_clicked();
    void on_guardarM_clicked();
    void on_guardarV_clicked();
private:
    int n;
    int V;
    int f,c;
    double m[100][100];
    Ui::resultado *ui;
};

#endif // RESULTADO_H
