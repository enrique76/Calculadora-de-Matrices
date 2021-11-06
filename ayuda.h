#ifndef AYUDA_H
#define AYUDA_H

#include <QDialog>

namespace Ui {
class ayuda;
}

class ayuda : public QDialog
{
    Q_OBJECT

public:
    explicit ayuda(QWidget *parent = nullptr);
    ~ayuda();

private slots:
    void on_pdf_clicked();

    void on_tutorial_clicked();

    void on_libros_clicked();

    void on_ats_clicked();

private:
    Ui::ayuda *ui;
};

#endif // AYUDA_H
