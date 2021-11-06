#ifndef COPIARMATRICES_H
#define COPIARMATRICES_H

#include <QDialog>

namespace Ui {
class copiarMatrices;
}

class copiarMatrices : public QDialog
{
    Q_OBJECT

public:
    explicit copiarMatrices(QWidget *parent = nullptr);
    ~copiarMatrices();
    bool AOB();

public slots:
    bool on_buttonBox_accepted();


private slots:
    bool on_buttonBox_rejected();

private:
    Ui::copiarMatrices *ui;
};

#endif // COPIARMATRICES_H
