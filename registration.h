#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <QDialog>
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
#include <QLineEdit>

namespace Ui {
class registration;
}

class registration : public QDialog
{
    Q_OBJECT

public:
    explicit registration(QWidget *parent = nullptr);
    ~registration();
    QString hashPassword(const QString& password);

    // Объявление функции keyPressEvent
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void on_pushButton_zareg_clicked();

    void setInterfaceRegStyle();

    void onShowPasswordToggled(QLineEdit* lineEdit);

private:
    Ui::registration *ui;
    QSqlDatabase db;
    QSqlTableModel *model;
    QPoint m_dragPosition;


    bool eventFilter(QObject *obj, QEvent *event) override;
};

#endif // REGISTRATION_H
