#ifndef GRAFICARFUNCIONES_H
#define GRAFICARFUNCIONES_H

#include <QMainWindow>

namespace Ui {
class GraficarFunciones;
}

class GraficarFunciones : public QMainWindow
{
    Q_OBJECT

public:
    explicit GraficarFunciones(QWidget *parent = nullptr);
    ~GraficarFunciones();

private:
    Ui::GraficarFunciones *ui;
};

#endif // GRAFICARFUNCIONES_H
