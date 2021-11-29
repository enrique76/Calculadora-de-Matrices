#ifndef CHART3D_H
#define CHART3D_H

#include <QDialog>
#include<QTableWidget>
#include<QWindow>

namespace Ui {
class chart3d;
}

class chart3d : public QDialog
{
    Q_OBJECT

public:
    explicit chart3d(QWidget *parent = nullptr);
    ~chart3d();

    void PasarDatos(QTableWidget *);
    void Chart3D();

private:
    Ui::chart3d *ui;
    double **m;
    int row,column;
    QWindow *w;
};

#endif // CHART3D_H
