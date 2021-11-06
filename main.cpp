#include "mainwindow.h"
#include <QApplication>
#include "pye.h"
#include<QFile>
#include<time.h>
#include<qdebug.h>
#include<QTextStream>

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    a.setStyle("fusion");


    double e;

        QFile E("C:/Users/Public/E.txt");

        if(!E.exists()){
            time_t now = time(0);
            tm* time = localtime(&now);
            int dia,mes,year,sec,min,hour;

            sec = time->tm_sec;
            min = time->tm_min;
            hour = time->tm_hour;
            dia = time->tm_mday;
            mes = time->tm_mon;
            year = 1900 + time->tm_year;

            qDebug()<<sec<<min<<hour<<dia<<mes<<year;

            e = (sec * min) + (hour * dia) + (mes * year);

            E.open(QFile::WriteOnly | QFile::Text);
            QTextStream out(&E);

            out<<QString::number(e);
            E.flush();
            E.close();
        }
        else{
            E.open(QFile::ReadOnly | QFile::Text);
            QTextStream in(&E);

            e = in.readAll().toDouble();

            E.flush();
            E.close();


        }




    MainWindow w;
    w.show();
    return a.exec();
}
