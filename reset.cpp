#include "reset.h"
#include "ui_reset.h"

#include "mainwindow.h"

#include "stylehelper.h"

#include <QResource>
#include <QTcpSocket>
#include <QTextStream>
#include <QFile>
#include <QFontDatabase>
#include <QRandomGenerator>
#include <QString>

#include <QtCore>
#include <QCoreApplication>
#include <QDebug>
#include <QSqlQuery>

#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlError>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QJsonDocument>
#include <QJsonObject>
#include <QMessageBox>

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QUrl>
#include <QUrlQuery>
#include <QNetworkReply>
#include <QDebug>
#include <QRandomGenerator>

#include <QMainWindow>
#include <QTextStream>
#include <QApplication>
#include <QRegularExpression>
#include <QKeyEvent>
#include <QStyle>
#include <QTabBar>
#include <QMessageBox>

Reset::Reset(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Reset)
{
    ui->setupUi(this);

    // Устанавливаем режим отображения пароля в виде точек
    ui->lineEdit_passwordReset_one->setEchoMode(QLineEdit::Password);
    ui->lineEdit_passwordReset_two->setEchoMode(QLineEdit::Password);


    // Инициализация токена
    token = "";

    setInterfaceResetStyle();

    QApplication::setStyle("Fusion");

    // Загрузка шрифта из ресурсов
    QFile fontFile(":/resources/MultiroundPro.otf");
    if (fontFile.open(QIODevice::ReadOnly)) {
        int fontId = QFontDatabase::addApplicationFontFromData(fontFile.readAll());
        QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
        if (!fontFamilies.isEmpty()) {
            // Создание экземпляра QFont с загруженным шрифтом
            QFont font(fontFamilies.at(0), 12, QFont::Bold);
            ui->labelresetPass_5->setFont(font);
            ui->labelresetPass->setFont(font);
            ui->labelresetPass_4->setFont(font);
            ui->labelresetPass_3->setFont(font);
        }
        fontFile.close();
    }
}

Reset::~Reset()
{
    delete ui;
}

// Обработчик закрытия

void Reset::closeEvent(QCloseEvent *event)
{
    emit closed();

    QWidget::closeEvent(event);
}

void Reset::keyPressEvent(QKeyEvent* override)
{
    if (override->key() == Qt::Key_Return || override->key() == Qt::Key_Enter) {
        if (!ui->lineEdit_verifymail->text().isEmpty() && !ui->lineEdit_verifylogin->text().isEmpty()) {
            on_pushButton_next_clicked(); // Вызываем функцию, которая обрабатывает нажатие клавиши Enter
        }
    } else {
        QWidget::keyPressEvent(override); // Вызываем реализацию базового класса для обработки других клавиш
    }
}



void Reset::on_pushButton_resetPassword_clicked()
{
    QString userId = ui->lineEdit_EmailReset->text(); // Получаем введенный пользователем user id

    // Проверяем, что userId содержит только цифры и не является пустым
    bool isNumeric = !userId.isEmpty() && userId.toInt() != 0 && userId.toInt(&isNumeric);

    if (!isNumeric) {
        QMessageBox::critical(this, "Ошибка", "User ID должен содержать только цифры и быть непустым");
        return;
    }

    generateCode(userId); // Генерируем код и отправляем сообщение

    ui->tabWidget->setCurrentIndex(2); // Переход на вкладку tab_3
}


void Reset::generateCode(const QString &userId)
{
    // Генерация и отправка сообщения с кодом
    int code = QRandomGenerator::global()->bounded(100000, 1000000); // генерация числа от 100000 до 999999
    generatedCode = QString::number(code);

    QString message = "Ваш код для сброса пароля: " + generatedCode + "\n❗️Внимание❗️\n Код действует 15 минут!";  // Передаем сохраненный код в сообщение

    sendTelegramMessage(token, userId, message); // Функция для отправки сообщения
}

void Reset::sendTelegramMessage(const QString &token, const QString &chatId, const QString &message)
{
    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    connect(manager, &QNetworkAccessManager::finished, this, [=](QNetworkReply *reply) {
        if (reply->error() == QNetworkReply::NoError) {
            qDebug() << "Message sent successfully";
        } else {
            qDebug() << "Error sending message:" << reply->errorString();
        }

        reply->deleteLater();
    });

    QUrl url("https://api.telegram.org/bot" + token + "/sendMessage");
    QUrlQuery query;
    query.addQueryItem("chat_id", chatId);
    query.addQueryItem("text", message);
    url.setQuery(query);

    QNetworkRequest request(url);
    manager->get(request);
}

void Reset::setInterfaceResetStyle()
{
    ui->pushButton_next->setStyleSheet(StyleHelper::pushButton_nextStyle());
    ui->pushButton_resetPassword->setStyleSheet(StyleHelper::pushButton_resetPasswordStyle());
    ui->pushButton_resetPassword_3->setStyleSheet(StyleHelper::pushButton_resetPassword_3Style());
    ui->pushButton_resetPassword_4->setStyleSheet(StyleHelper::pushButton_resetPassword_4Style());

    ui->lineEdit_verifylogin->setStyleSheet(StyleHelper::lineEdit_verifyloginStyle());
    ui->lineEdit_verifymail->setStyleSheet(StyleHelper::lineEdit_verifymailStyle());
    ui->lineEdit_EmailReset->setStyleSheet(StyleHelper::lineEdit_EmailResetStyle());
    ui->lineEdit_EmailReset_3->setStyleSheet(StyleHelper::lineEdit_EmailReset_3Style());
    ui->lineEdit_passwordReset_one->setStyleSheet(StyleHelper::lineEdit_passwordReset_oneStyle());
    ui->lineEdit_passwordReset_two->setStyleSheet(StyleHelper::lineEdit_passwordReset_twoStyle());

    QString resetWindowStyle = StyleHelper::resetWindowStyle();
    setStyleSheet(resetWindowStyle);
}

void Reset::on_pushButton_resetPassword_3_clicked()
{
    QString userEnteredCode = ui->lineEdit_EmailReset_3->text(); // Получаем введенный пользователем код

    // Проверяем код и переключаем на tab_4, если код правильный
    if (userEnteredCode == generatedCode) { // Предположим, что generatedCode - это переменная, в которой хранится сгенерированный код
        ui->tabWidget->setCurrentIndex(3); // Переключаем на tab_!
    } else {
        QMessageBox::critical(this, "Ошибка", "Неверный код"); // Выводим сообщение об ошибке
    }
}

void Reset::on_pushButton_next_clicked()
{
    QString email = ui->lineEdit_verifymail->text();
    QString login = ui->lineEdit_verifylogin->text();


    if (email.isEmpty() || login.isEmpty()) {
        QMessageBox::critical(this, "Ошибка", "Пожалуйста, введите email и логин");
        return;
    }

    // Устанавливаем соединение с базой данных
    QSqlDatabase db = QSqlDatabase::addDatabase("QMYSQL");
    db.setHostName("");
    db.setPort(3306);
    db.setDatabaseName("");
    db.setUserName("");
    db.setPassword("");

    if (!db.open()) {
        qDebug() << "Ошибка соединения с базой данных:" << db.lastError().text();
        return;
    }

    // Выполняем SQL-запрос для проверки совпадения логина и почты
    QSqlQuery query(db);
    query.prepare("SELECT * FROM users WHERE mail = :mail AND login = :login");
    query.bindValue(":mail", email);
    query.bindValue(":login", login);

    if (query.exec() && query.next()) {
        // Email и логин существуют, сохраняем логин для использования при смене пароля
        currentLogin = login;

        // Email и логин существуют, переходим на следующую вкладку
        ui->tabWidget->setCurrentIndex(1); // Предположим, что следующая вкладка имеет индекс 2
    } else {
        // Email или логин не найдены или произошла ошибка при выполнении запроса
        QMessageBox::critical(this, "Ошибка", "Неверный email или логин");
    }

    // Закрываем соединение с базой данных
    db.close();
}

// Хеш пароля

QString Reset::hashPassword(const QString& password)
{
    QByteArray passwordBytes = password.toUtf8();
    QByteArray hashBytes = QCryptographicHash::hash(passwordBytes, QCryptographicHash::Sha256);
    QString hash = QString(hashBytes.toHex());
    return hash;
}

// Sus

// Слот для обработки изменения состояния действия показа/скрытия пароля
void Reset::onShowPasswordToggled(bool checked)
{
    if (checked)
    {
        // Устанавливаем режим отображения пароля в виде точек
        ui->lineEdit_passwordReset_one->setEchoMode(QLineEdit::Password);
    }
    else
    {
        // Устанавливаем режим отображения пароля в виде точек
        ui->lineEdit_passwordReset_two->setEchoMode(QLineEdit::Password);
    }
}

void Reset::on_pushButton_resetPassword_4_clicked()
{
    QString newPassword1 = ui->lineEdit_passwordReset_one->text();
    QString newPassword2 = ui->lineEdit_passwordReset_two->text();

    static QRegularExpression regex("[a-zA-Z0-9]");

    // Проверки пароля
    if (newPassword1.isEmpty() || newPassword2.isEmpty()) {
        QMessageBox::critical(this, "Ошибка", "Пароль не может быть пустым");
        return;
    }
    if (newPassword1 != newPassword2) {
        QMessageBox::critical(this, "Ошибка", "Пароли не совпадают");
        return;
    }
    if (newPassword1.length() < 8 || newPassword1.length() > 32) {
        QMessageBox::critical(this, "Ошибка", "Пароль должен содержать от 8 до 32 символов");
        return;
    }
    if (newPassword1 == currentLogin) {
        QMessageBox::critical(this, "Ошибка", "Пароль не может быть таким же, как логин");
        return;
    }
    if (!newPassword1.contains(regex) ||
        !newPassword1.contains(QRegularExpression("[a-z]")) ||
        !newPassword1.contains(QRegularExpression("[A-Z]")) ||
        !newPassword1.contains(QRegularExpression("[0-9]"))) {
        QMessageBox::critical(this, "Ошибка", "Пароль должен быть комбинированным и содержать символы, буквы и цифры разного регистра");
        return;
    }
    if (newPassword1.contains("дата рождения", Qt::CaseInsensitive) ||
        newPassword1.contains("имя", Qt::CaseInsensitive) ||
        newPassword1.contains("фамилия", Qt::CaseInsensitive) ||
        newPassword1.contains("телефон", Qt::CaseInsensitive) ||
        newPassword1.contains("адрес", Qt::CaseInsensitive) ||
        newPassword1.contains("кличка", Qt::CaseInsensitive)) {
        QMessageBox::critical(this, "Ошибка", "Пароль содержит запрещенные данные");
        return;
    }

    // Хеширование пароля
    QString hashedPassword = hashPassword(newPassword1);

    // Устанавливаем соединение с базой данных, если оно еще не установлено
    if (!QSqlDatabase::contains("qt_sql_default_connection")) {
        db = QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName(""); // host name
        db.setPort(3306); // port
        db.setDatabaseName(""); // name db
        db.setUserName(""); // login
        db.setPassword(""); // password

        // Проверяем, удалось ли открыть соединение с базой данных
        if (!db.open()) {
            qDebug() << "Ошибка соединения с базой данных:" << db.lastError().text();
            qDebug() << "Доступные драйверы:" << QSqlDatabase::drivers();
            return;
        } else {
            qDebug() << "Соединение с базой данных установлено";
        }
    } else {
        // Если соединение уже установлено, используем его
        db = QSqlDatabase::database("qt_sql_default_connection");
    }

    // Обновление пароля в базе данных
    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE users SET password = :password WHERE login = :login");
    updateQuery.bindValue(":password", hashedPassword);
    updateQuery.bindValue(":login", currentLogin);

    if (!updateQuery.exec()) {
        QMessageBox::critical(this, "Ошибка", "Не удалось обновить пароль");
        db.close(); // Закрываем соединение с базой данных в случае ошибки
        return;
    }

    QMessageBox::information(this, "Успех", "Пароль успешно изменён");

    // Закрываем текущее окно
    close();
}
