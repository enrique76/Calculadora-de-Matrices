#ifndef GRAFICARFUNCION_H
#define GRAFICARFUNCION_H

#include <QDialog>
#include<QtCharts>
#include<QBarSet>
#include<QBarSeries>
#include<QLineSeries>
#include<QChartView>
#include<QVector>
#include<QValueAxis>

namespace Ui {
class GraficarFuncion;
}

class GraficarFuncion : public QDialog
{
    Q_OBJECT

public:
    explicit GraficarFuncion(QWidget *parent = nullptr);
    ~GraficarFuncion();
    void Tabular();

private slots:
    void on_fx_clicked();

    void on_PasarB_clicked();


    void on_vEcuacion_clicked();

    QString ToHTML(QString);

    void on_ecuacion_textChanged(const QString &arg1);


    void on_funciones_activated(const QString &arg1);
    void Graficar();
    void Data(QStringList);

    void on_mas_clicked();

    void on_origen_clicked();

    void on_menos_clicked();

private:
    Ui::GraficarFuncion *ui;
    int li,ls;
    double s;
    bool V = false;
    QChart *chart = new QChart();
    QChartView *cplot = new  QChartView(chart);
    QVector<double> x;
    QVector<double> y;
    double minx,maxx,miny,maxy;
    QValueAxis *Ay = new QValueAxis;
    QValueAxis *Ax = new QValueAxis;
};

#endif // GRAFICARFUNCION_H
