#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QKeyEvent>
#include <QPushButton>
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

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    // Объявление функции keyPressEvent
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void on_pushButton_login_clicked();

    void on_pushButton_registration_clicked();

    void on_pushButton_reset_clicked();

    void onResetClosed();

    void onShowPasswordToggled(bool checked);

private:
    Ui::MainWindow *ui;

    QSqlDatabase db;
    QSqlTableModel *model;

    QPoint m_dragPosition;

    void setInterfaceStyle();

    void setAppBackground();

    bool eventFilter(QObject *obj, QEvent *event) override;
};

#endif // MAINWINDOW_H
