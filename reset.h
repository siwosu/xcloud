#ifndef RESET_H
#define RESET_H

#include <QWidget>
#include <QKeyEvent>
#include <QEvent>
#include <QSqlTableModel>>
#include <QSqlDatabase>
#include <QMouseEvent>
#include <QAction>

namespace Ui {
class Reset;
}

class Reset : public QWidget
{
    Q_OBJECT

public:
    explicit Reset(QWidget *parent = nullptr);
    ~Reset();

    // Объявление функции keyPressEvent
    void keyPressEvent(QKeyEvent* event) override;

    QString hashPassword(const QString& password); // Объявление функции hashPassword

signals:
    void closed();

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void on_pushButton_resetPassword_clicked();

    void setInterfaceResetStyle();

    void on_pushButton_resetPassword_3_clicked();

    void on_pushButton_next_clicked();

    void on_pushButton_resetPassword_4_clicked();

    void onShowPasswordToggled(bool checked);

private:
    Ui::Reset *ui;

    void sendTelegramMessage(const QString &token, const QString &chatId, const QString &message);

    QString token;

    void generateCode(const QString &userId);

    QString generatedCode;

    QString currentLogin;

    QSqlDatabase db;

    QSqlTableModel *model;
};

#endif // RESET_H
