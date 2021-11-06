#ifndef AUTOR_H
#define AUTOR_H

#include <QDialog>

namespace Ui {
class Autor;
}

class Autor : public QDialog
{
    Q_OBJECT

public:
    explicit Autor(QWidget *parent = nullptr);
    ~Autor();

private slots:
    void on_Youtube_clicked();

    void on_Github_clicked();

    void on_Facebook_clicked();

    void on_Instagram_clicked();

private:
    Ui::Autor *ui;
};

#endif // AUTOR_H
