#ifndef DIRECCION_H
#define DIRECCION_H

#include <QDialog>

namespace Ui {
class direccion;
}

class direccion : public QDialog
{
    Q_OBJECT

public:
    explicit direccion(QWidget *parent = nullptr);
    ~direccion();
    void nombre(QString);
    void ruta(QString &);
    void ver(bool);
    void extencion(QString &);
    void titulo(QString);
    void en_text(QString );
    void en_Enabled(bool );
    bool en_checked();
    void d_Enabled(bool);
private slots:
    void on_ir_clicked();


private:
    bool V = false;
    QString r;
    Ui::direccion *ui;
};


#endif // DIRECCION_H
