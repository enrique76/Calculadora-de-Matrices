#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

class QTabWidget;

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    void agregarA(int,int,double);
    void agregarB(int,int,double);
    void Shell(bool,int);
    void Usuario(QString);
    void Llenar();
    void nA();
    void nB();
private slots:
    void on_vLlenar_clicked();
    void on_cb_valueChanged();
    void on_ca_valueChanged();
    void on_fb_valueChanged();
    void on_fa_valueChanged();
    void on_cambio_clicked();
    void on_identidad_A_clicked();
    void on_identidad_B_clicked();
    void on_AleatorioA_clicked();
    void on_AleatorioB_clicked();
    void on_IncrementoA_clicked();
    void on_IncrementoB_clicked();
    void on_i_s_A_clicked();
    void on_i_s_B_clicked();
    void on_llenarNA_clicked();
    void on_llenarNB_clicked();
    void on_OrdenarA_clicked();
    void on_OrdenarB_clicked();
    void on_A_cellChanged(int row, int column);
    void on_vResultados_cellChanged(int row, int column);
    void on_B_cellChanged(int row, int column);
    void on_actionGuardar_Todo_triggered();
    void on_actionSobre_QT_triggered();
    void on_actionAyuda_triggered();
    void on_actionSobre_Autor_triggered();
    void on_saltos_A_clicked();
    void on_saltos_B_clicked();
    void on_desordenar_A_clicked();
    void on_desordenar_B_clicked();
    void on_copiar_M_clicked();
    void on_actionA_triggered();
    void on_actionB_triggered();
    void on_actionV_triggered();
    void on_actionA_2_triggered();
    void on_actionB_2_triggered();
    void on_actionV_2_triggered();
    void on_actionInterpolar_triggered();
    void on_actionExtrapolar_triggered();
    void on_actionEntre_Matrices_triggered();
    void on_actionEntre_Escalar_triggered();
    void on_actionAtributos_triggered();
    void on_actionExtras_triggered();
    void on_actionPorbabilidad_y_Estadistica_triggered();
    void on_actionTrigonometria_triggered();
    void showTime();
    void on_actionCodigo_Fuente_triggered();
    void on_actionDescargar_triggered();

    void on_actionGraficar_Funciones_triggered();

    void on_chart3d_triggered();

private:
    Ui::MainWindow *ui;
    double s[10000];
    double t = 0;
    int x = 0;
    int fa = 1;
    int ca = 1;
    int fb = 1;
    int cb = 1;
    int nxn = 0;
    bool V = false;
    const double e = 2.718281828;
    QStringList l;
    bool ordenar;
    int coloresA;
    int coloresB;
};
#endif // MAINWINDOW_H
