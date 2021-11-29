#include "chart3d.h"
#include "ui_chart3d.h"
#include<QtDataVisualization/Q3DBars>
#include<QtDataVisualization/QBarDataProxy>
#include<QtDataVisualization/QBarDataArray>
#include<QtDataVisualization/QBarDataRow>

using namespace QtDataVisualization;

chart3d::chart3d(QWidget *parent) : QDialog(parent),ui(new Ui::chart3d){
    ui->setupUi(this);



}

chart3d::~chart3d(){
    delete ui;

    for (int i = 0; i < row; i++) {
                delete [] m[i];
            }
            delete [] m;
}

void chart3d::PasarDatos(QTableWidget *a){

    row = a->rowCount();
    column = a->columnCount();

    m = new double *[row];

    for(int i=0;i<row;i++){
        m[i] = new double[column];
    }

}

void chart3d::Chart3D(){

        Q3DBars *bars = new Q3DBars();

        QWidget *base = QWidget::createWindowContainer(bars);

        QWidget *w = new QWidget;
        QHBoxLayout *hL = new QHBoxLayout(w);
        QVBoxLayout *vL = new QVBoxLayout();

        hL->addWidget(base,1);
        hL->addLayout(vL);

        bars->show();


//        Q3DBars bars;
//        bars.setFlags(bars.flags() ^ Qt::FramelessWindowHint);
//        bars.rowAxis()->setRange(0, 4);
//        bars.columnAxis()->setRange(0, 4);
//        QBar3DSeries *series = new QBar3DSeries;
//        QBarDataRow *data = new QBarDataRow;
//        *data << 1.0f << 3.0f << 7.5f << 5.0f << 2.2f;
//        series->dataProxy()->addRow(data);
//        bars.addSeries(series);
//        bars.setParent(ui->base->windowHandle());
}
