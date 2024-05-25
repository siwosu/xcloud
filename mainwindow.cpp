#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "registration.h"
#include "stylehelper.h"

#include "reset.h"

#include "program.h"

#include <QApplication>
#include <QAction>
#include <QCoreApplication>
#include <QMainWindow>
#include <QFontDatabase>
#include <QCryptographicHash>
#include <QKeyEvent>
#include <QStyle>
#include <QLineEdit>
#include <QSettings>
#include <QFile>
#include <QMessageBox>
#include <QSqlDriverPlugin>
#include <QSqlTableModel>
#include <QSqlDatabase>
#include <QtSql/QSql>
#include <QSql>
#include <QtSql/QSqlDatabase>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QApplication::setStyle("Fusion");

    // Устанавливаем атрибут для обработки событий наведения курсора
    ui->lineEdit_password->setAttribute(Qt::WA_Hover);

    ui->lineEdit_password->installEventFilter(this);

    // Устанавливаем режим отображения пароля в виде точек
    ui->lineEdit_password->setEchoMode(QLineEdit::Password);

    // Создаем действие для показа и скрытия пароля
    QAction *showPasswordAction = new QAction(this);
    showPasswordAction->setIcon(QIcon(":/resources/eye.png"));
    showPasswordAction->setToolTip("Показать пароль");
    showPasswordAction->setCheckable(true);

    // Добавляем действие в поле ввода пароля
    ui->lineEdit_password->addAction(showPasswordAction, QLineEdit::TrailingPosition);

    // Подключаем сигнал об изменении состояния действия
    connect(showPasswordAction, &QAction::toggled, this, &MainWindow::onShowPasswordToggled);

    setInterfaceStyle();

    // Загрузка шрифта из ресурсов
    QFile fontFile(":/resources/MultiroundPro.otf");
    if (fontFile.open(QIODevice::ReadOnly)) {
        int fontId = QFontDatabase::addApplicationFontFromData(fontFile.readAll());
        QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
        if (!fontFamilies.isEmpty()) {
            // Создание экземпляра QFont с загруженным шрифтом
            QFont font(fontFamilies.at(0), 12, QFont::Bold);
            ui->label_name->setFont(font);
        }
        fontFile.close();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->lineEdit_password) {
        if (event->type() == QEvent::Enter) {
            QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
            QPoint pos = mouseEvent->pos();

            // Проверяем, что курсор находится в правой половине lineEdit
            int halfWidth = ui->lineEdit_password->width() / 1.05;

            if (pos.x() >= halfWidth) {
                // Изменяем иконку на изображение при наведении
                ui->lineEdit_password->actions().at(0)->setIcon(QIcon(":/resources/eye_hover.png"));
            }
        } else if (event->type() == QEvent::Leave) {
            // Восстанавливаем иконку на изображение по умолчанию
            ui->lineEdit_password->actions().at(0)->setIcon(QIcon(":/resources/eye.png"));
        }
    }

    return QMainWindow::eventFilter(obj, event);
}

// Слот для обработки изменения состояния действия показа/скрытия пароля
void MainWindow::onShowPasswordToggled(bool checked)
{
    if (checked)
    {
        // Устанавливаем режим отображения пароля в виде обычного текста
        ui->lineEdit_password->setEchoMode(QLineEdit::Normal);
    }
    else
    {
        // Устанавливаем режим отображения пароля в виде точек
        ui->lineEdit_password->setEchoMode(QLineEdit::Password);
    }
}

void MainWindow::on_pushButton_login_clicked()
{
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

    QString login = ui->lineEdit_login->text();
    QString password = ui->lineEdit_password->text();

    if (login.isEmpty() || password.isEmpty()) {
        QMessageBox::critical(this, "Ошибка", "Пожалуйста, введите логин и пароль");
        return;
    }

    // Хэширование введенного пароля
    QByteArray passwordHash = QCryptographicHash::hash(password.toUtf8(), QCryptographicHash::Sha256);
    QString passwordHashString = QString(passwordHash.toHex());

    // Выполняем SQL-запрос для проверки пользователя
    QSqlQuery query;
    query.prepare("SELECT * FROM users WHERE login = :login AND password = :password");
    query.bindValue(":login", login);
    query.bindValue(":password", passwordHashString); // Сравниваем с хэшем введенного пароля

    if (query.exec() && query.next()) {
        // Пользователь существует, выводим окно об успешном входе
        QMessageBox::information(this, "Успешный вход", "Вы успешно вошли в систему!");

        // Закрытие текущего окна
        close();

        // Создание и открытие окна программы
        Program *program = new Program();
        program->show();
    } else {
        // Пользователь не существует или произошла ошибка при выполнении запроса
        QMessageBox::critical(this, "Ошибка", "Неверный логин или пароль");
    }

    db.close();
}

void MainWindow::keyPressEvent(QKeyEvent *event) // обработчик Enter
{
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        on_pushButton_login_clicked();
    } else {
        QMainWindow::keyPressEvent(event);
    }
}

void MainWindow::on_pushButton_registration_clicked() // Обработчик нажатия кнопки "Регистрация"
{
    // Скрытие текущего окна (главное окно)
    hide();

    // Создание и открытие окна регистрации
    registration registrationWindow;
    registrationWindow.setModal(true);
    registrationWindow.exec();

    // После закрытия окна регистрации, главное окно снова отображается
    show();
}

void MainWindow::setInterfaceStyle() // Установка стилей
{
    // Применяем стиль к кнопке "Вход"
    ui->pushButton_login->setStyleSheet(StyleHelper::pushButton_loginStyle());

    // Применяем стиль к кнопке "Регистрация"
    ui->pushButton_registration->setStyleSheet(StyleHelper::pushButton_registrationStyle());

    // Применяем стиль к кнопке "забыли пароль"
    ui->pushButton_reset->setObjectName("pushButton_reset");
    ui->pushButton_reset->setStyleSheet(StyleHelper::pushButton_resetStyle());
    ui->pushButton_reset->setFlat(true); // Устанавливаем кнопку в режим "flat" для удаления фона

    // Применяем стиль к lineEdit для логина
    ui->lineEdit_login->setStyleSheet(StyleHelper::lineEdit_loginStyle());

    // Применяем стиль к lineEdit для пароля
    ui->lineEdit_password->setStyleSheet(StyleHelper::lineEdit_passwordStyle());

    // Применяем стиль к главному окну
    QString mainWindowStyle = StyleHelper::mainWindowStyle();
    setStyleSheet(mainWindowStyle);
}
void MainWindow::on_pushButton_reset_clicked()
{
    // Скрытие текущего окна (главное окно)
    hide();

    // Создаем экземпляр класса окна "Reset"
    Reset *resetWindow = new Reset(this);

    resetWindow->setWindowFlags(Qt::Dialog); // Изменяем флаг окна на Qt::Dialog

    // Подключаем сигнал и слот для обработки закрытия окна Reset
    connect(resetWindow, &Reset::closed, this, &MainWindow::onResetClosed);

    // Открываем окно "Reset"
    resetWindow->show();
}

void MainWindow::onResetClosed()
{
    // После закрытия окна Reset, главное окно снова отображается
    show();
}

