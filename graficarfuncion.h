#ifndef GRAFICARFUNCION_H
#define GRAFICARFUNCION_H

#include <QDialog>
#include<QtCharts>
#include<QBarSet>
#include<QBarSeries>
#include<QLineSeries>
#include<QChartView>

namespace Ui {
class GraficarFuncion;
}

class GraficarFuncion : public QDialog
{
    Q_OBJECT

public:
    explicit GraficarFuncion(QWidget *parent = nullptr);
    ~GraficarFuncion();
    void Tabular(QStringList);

private slots:
    void on_fx_clicked();

    void on_PasarB_clicked();


    void on_vEcuacion_clicked();

    QString ToHTML(QString);

    void on_ecuacion_textChanged(const QString &arg1);


private:
    Ui::GraficarFuncion *ui;
    int li,ls;
    double s;
    bool V = false;
    QChart *chart = new QChart();
    QChartView *cplot = new  QChartView(chart);
};

#endif // GRAFICARFUNCION_H
