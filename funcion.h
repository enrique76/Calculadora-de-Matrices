#ifndef FUNCION_H
#define FUNCION_H

#include <QDialog>

namespace Ui {
class funcion;
}

class funcion : public QDialog
{
    Q_OBJECT

public:
    explicit funcion(QWidget *parent = nullptr);
    ~funcion();

private:
    Ui::funcion *ui;
};

#endif // FUNCION_H
