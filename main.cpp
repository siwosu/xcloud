#include "mainwindow.h"

#include <QApplication>
#include <QCoreApplication>
#include <QMainWindow>
#include <QKeyEvent>
#include <QFile>
#include <QSqlDriverPlugin>
#include <QSqlTableModel>
#include <QSqlDatabase>
#include <QtSql/QSql>
#include <QSql>
#include <QtSql/QSqlDatabase>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // Создание и открытие окна MainWindow
    MainWindow w;
    w.show();

    return a.exec();
}
