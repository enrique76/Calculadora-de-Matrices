#ifndef OPERACIONES_H
#define OPERACIONES_H

#include <QDialog>
#include<QTableWidget>

namespace Ui {
class operaciones;
}

class QTableWidget;

class operaciones : public QDialog
{
    Q_OBJECT

public:
    operaciones(QWidget *parent = nullptr);
    ~operaciones();
    void PasarDatos(QTableWidget *A,QTableWidget *B,QTableWidget *r,int fa,int ca, int fb, int cb);
    void Shell(double [],int,int);
    double Determinante(double a[][100]);
    double Menor(int,int);
    double Mayor(int,int);
    double Media();
    void pasar(QTableWidget *A, QTableWidget *B);
    void ventana(int);
    void ventana(int,int);
    void SubVentanas(QTableWidget *A,QTableWidget *B,QTableWidget *r,int fa,int ca, int fb, int cb);
private slots:
    void on_sumaM_clicked();
    void on_restaM_clicked();
    void on_divicionM_clicked();
    void on_productoM_clicked();
    void on_elevacionM_clicked();
    void on_logM_clicked();
    void on_raizM_clicked();
    void on_suma_clicked();
    void on_resta_clicked();
    void on_producto_clicked();
    void on_divicion_clicked();
    void on_elevacion_clicked();
    void on_elevacionA_clicked();
    void on_log_clicked();
    void on_raiz_clicked();
    void on_sinA_clicked();
    void on_cosA_clicked();
    void on_tanA_clicked();
    void on_AsinA_clicked();
    void on_AcosA_clicked();
    void on_AtanA_clicked();
    void on_adjunta_clicked();
    void on_cscA_clicked();
    void on_secA_clicked();
    void on_cotA_clicked();
    void on_histograma_clicked();
    void on_e_clicked();
    void on_inversa_clicked();
    void on_transpuesta_clicked();
    void on_Max_Min_clicked();
    void on_Min_Max_clicked();
    void on_Resolver_clicked();
    void on_distribucionE_clicked();
    void on_determinante_clicked();
    void on_Menor_clicked();
    void on_Mayor_clicked();
    void on_Media_clicked();
    void on_Sumatoria_clicked();
    void on_Mediana_clicked();
    void on_caracter_clicked();
    void on_factorial_clicked();
    void on_Divisor_clicked();
    void on_Pi_clicked();
    void on_Varianza_clicked();
    void on_desviacionE_clicked();
    void on_Triangular_clicked();
    void on_Moda_clicked();
    void on_naturales_clicked();
    void on_enteros_clicked();
    void on_fibonachi_clicked();
    void on_AinB_clicked();
    void on_rango_clicked();
    void on_mediaG_clicked();
    void on_gAtributos_clicked();
    void on_Par_clicked();
    void on_pasarMatriz_clicked();
    void on_Matriz_A_cellDoubleClicked(int row, int column);

    void on_Vector_cellDoubleClicked(int row, int column);

    void on_Matriz_B_cellDoubleClicked(int row, int column);

    void on_interpolar_2_clicked();

    void on_extrapolar_2_clicked();

private:
    double a[100][100];
    double b[100][100];
    double v[100];
    int fa=1,ca=1,fb=1,cb=1;
    double s = 0;
    Ui::operaciones *ui;
};

#endif // OPERACIONES_H
