#include "registration.h"
#include "ui_registration.h"

#include "stylehelper.h"

#include <QKeyEvent>
#include <QFile>
#include <QFontDatabase>
#include <QCryptographicHash>
#include <QMessageBox>
#include <QStyle>
#include <QSqlDriverPlugin>
#include <QSqlTableModel>
#include <QSqlDatabase>
#include <QtSql/QSql>
#include <QSql>
#include <QtSql/QSqlDatabase>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

registration::registration(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::registration)
{
    ui->setupUi(this);

    QApplication::setStyle("Fusion");

    // Устанавливаем фильтр событий для полей ввода пароля
    ui->lineEdit_regpass1->installEventFilter(this);
    ui->lineEdit_regpass2->installEventFilter(this);

    // Устанавливаем режим отображения пароля в виде точек
    ui->lineEdit_regpass1->setEchoMode(QLineEdit::Password);
    ui->lineEdit_regpass2->setEchoMode(QLineEdit::Password);

    // Создаем действия для показа и скрытия пароля
    QAction *showPasswordAction1 = new QAction(this);
    showPasswordAction1->setIcon(QIcon(":/resources/eye.png"));
    showPasswordAction1->setToolTip("Показать пароль");
    showPasswordAction1->setCheckable(true);

    QAction *showPasswordAction2 = new QAction(this);
    showPasswordAction2->setIcon(QIcon(":/resources/eye.png"));
    showPasswordAction2->setToolTip("Показать пароль");
    showPasswordAction2->setCheckable(true);

    // Добавляем действия в поля ввода пароля
    ui->lineEdit_regpass1->addAction(showPasswordAction1, QLineEdit::TrailingPosition);
    ui->lineEdit_regpass2->addAction(showPasswordAction2, QLineEdit::TrailingPosition);

    // Подключаем сигналы об изменении состояния действий
    connect(showPasswordAction1, &QAction::toggled, this, [this]() {
        onShowPasswordToggled(ui->lineEdit_regpass1);
    });

    connect(showPasswordAction2, &QAction::toggled, this, [this]() {
        onShowPasswordToggled(ui->lineEdit_regpass2);
    });

    setInterfaceRegStyle();

    // Загрузка шрифта из ресурсов
    QFile fontFile(":/resources/MultiroundPro.otf");
    if (fontFile.open(QIODevice::ReadOnly)) {
        int fontId = QFontDatabase::addApplicationFontFromData(fontFile.readAll());
        QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
        if (!fontFamilies.isEmpty()) {
            // Создание экземпляра QFont с загруженным шрифтом
            QFont font(fontFamilies.at(0), 12, QFont::Bold);
            ui->label_registration->setFont(font);
        }
        fontFile.close();
    }

    // Устанавливаем соединение с базой данных, если оно еще не установлено
    if (!QSqlDatabase::contains("qt_sql_default_connection")) {
        db = QSqlDatabase::addDatabase("QMYSQL");
        db.setHostName("147.78.65.249"); // host name
        db.setPort(3306); // port
        db.setDatabaseName("cs_test"); // name db
        db.setUserName("Klimenko"); // login
        db.setPassword("DCIfmTJFyy"); // password

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
}

registration::~registration()
{
    delete ui;
}

bool registration::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->lineEdit_regpass1 || obj == ui->lineEdit_regpass2) {
        QLineEdit* lineEdit = qobject_cast<QLineEdit*>(obj);

        if (event->type() == QEvent::Enter) {
            QMouseEvent* mouseEvent = static_cast<QMouseEvent*>(event);
            QPoint pos = mouseEvent->pos();

            // Проверяем, что курсор находится в правой половине lineEdit
            int halfWidth = lineEdit->width() / 1.05;

            if (pos.x() >= halfWidth) {
                // Изменяем иконку на изображение при наведении
                lineEdit->actions().at(0)->setIcon(QIcon(":/resources/eye_hover.png"));
            }
        } else if (event->type() == QEvent::Leave) {
            // Восстанавливаем иконку на изображение по умолчанию
            lineEdit->actions().at(0)->setIcon(QIcon(":/resources/eye.png"));
        }
    }

    return QWidget::eventFilter(obj, event);
}

// Слот для обработки изменения состояния действия показа/скрытия пароля
void registration::onShowPasswordToggled(QLineEdit* lineEdit)
{
    QAction *action = qobject_cast<QAction*>(sender());
    if (action && lineEdit)
    {
        bool checked = action->isChecked();

        if (checked)
        {
            // Устанавливаем режим отображения пароля в виде обычного текста
            lineEdit->setEchoMode(QLineEdit::Normal);
        }
        else
        {
            // Устанавливаем режим отображения пароля в виде точек
            lineEdit->setEchoMode(QLineEdit::Password);
        }
    }
}

QString registration::hashPassword(const QString& password) // Хэш паролей
{
    QByteArray passwordBytes = password.toUtf8();
    QByteArray hashBytes = QCryptographicHash::hash(passwordBytes, QCryptographicHash::Sha256);
    QString hash = QString(hashBytes.toHex());
    return hash;
}

void registration::keyPressEvent(QKeyEvent *event) // обработчик Enter
{
    if (event->key() == Qt::Key_Return || event->key() == Qt::Key_Enter) {
        on_pushButton_zareg_clicked();
    } else {
        registration::keyPressEvent(event);
    }
}


void registration::on_pushButton_zareg_clicked()
{
    // Объявление статических QRegularExpression
    static QRegularExpression nameRegex("^[a-zA-Zа-яА-Я]+$");
    static QRegularExpression mailRegex("^[A-Za-z0-9]+([\\.-]?[A-Za-z0-9]+)*@[A-Za-z0-9]+([\\.-]?[A-Za-z0-9]+)*(\\.[A-Za-z]{2,})$");
    static QRegularExpression loginRegex("^[a-zA-Z][a-zA-Z0-9\\-_.]*$");

    // Проверка имени
    QString name = ui->lineEdit_regname->text();
    if (name.isEmpty()) {
        QMessageBox::warning(this, "Ошибка", "Введите имя");
        return;
    }

    // Проверка размера имени (от 2 до 20 символов)
    if (name.length() < 2 || name.length() > 20) {
        QMessageBox::critical(this, "Ошибка", "Имя должно содержать от 2 до 20 символов");
        return;
    }

    // Проверка имени на допустимые символы
    if (!nameRegex.match(name).hasMatch()) {
        QMessageBox::critical(this, "Ошибка", "Имя может содержать только латинские и русские символы");
        return;
    }

    // Проверка логина
    QString login = ui->lineEdit_reglogin->text();
    if (login.isEmpty()) {
        QMessageBox::critical(this, "Ошибка", "Введите логин");
        return;
    }

    // Проверка размера логина (от 3 до 20 символов)
    if (login.length() < 3 || login.length() > 20) {
        QMessageBox::critical(this, "Ошибка", "Логин должен содержать от 3 до 20 символов");
        return;
    }

    // Проверка формата логина
    if (!loginRegex.match(login).hasMatch()) {
        QMessageBox::critical(this, "Ошибка", "Логин может содержать только латинские символы, цифры, дефис, подчеркивание и точку");
        return;
    }

    // Проверка почты
    QString mail = ui->lineEdit_regmail->text();
    if (mail.isEmpty()) {
        QMessageBox::critical(this, "Ошибка", "Введите адрес электронной почты");
        return;
    }

    // Проверка размера почты (от 5 до 32 символов)
    if (mail.length() < 5 || mail.length() > 32) {
        QMessageBox::critical(this, "Ошибка", "Адрес электронной почты должен содержать от 5 до 32 символов");
        return;
    }

    // Проверка формата почты
    if (!mailRegex.match(mail).hasMatch()) {
        QMessageBox::critical(this, "Ошибка", "Введите корректный адрес электронной почты");
        return;
    }

    // Проверка пароля
    QString password1 = ui->lineEdit_regpass1->text();
    QString password2 = ui->lineEdit_regpass2->text();

    // Проверка на пустоту полей пароля
    if (password1.isEmpty() || password2.isEmpty()) {
        QMessageBox::critical(this, "Ошибка", "Введите пароль в оба поля");
        return;
    }

    if (password1 == login || password2 == login) {
        QMessageBox::critical(this, "Ошибка", "Логин и пароль не могут быть одинаковыми");
        return;
    }

    // Проверка размера пароля (от 8 до 32 символов)
    if ((password1.length() < 8 || password1.length() > 32) || (password2.length() < 8 || password2.length() > 32)) {
        QMessageBox::critical(this, "Ошибка", "Пароль должен содержать от 8 до 32 символов");
        return;
    }

    if (password1.isEmpty()) {
        QMessageBox::critical(this, "Ошибка", "Введите пароль");
        return;
    }

    if (password2.isEmpty()) {
        QMessageBox::critical(this, "Ошибка", "Введите пароль повторно");
        return;
    }

    // Проверка комбинированности пароля
    bool hasUppercase = false;
    bool hasLowercase = false;
    bool hasDigit = false;
    bool hasSpecial = false;

    for (int i = 0; i < password1.length(); i++) {
        const QChar& ch = password1.at(i);
        if (ch.isUpper()) {
            hasUppercase = true;
        } else if (ch.isLower()) {
            hasLowercase = true;
        } else if (ch.isDigit()) {
            hasDigit = true;
        } else if (!ch.isLetterOrNumber()) {
            hasSpecial = true;
        }
    }

    for (int i = 0; i < password2.length(); i++) {
        const QChar& ch = password2.at(i);
        if (ch.isUpper()) {
            hasUppercase = true;
        } else if (ch.isLower()) {
            hasLowercase = true;
        } else if (ch.isDigit()) {
            hasDigit = true;
        } else if (!ch.isLetterOrNumber()) {
            hasSpecial = true;
        }
    }

    if (!hasUppercase || !hasLowercase || !hasDigit || !hasSpecial) {
        QMessageBox::critical(this, "Ошибка", "Пароль должен быть комбинированным и содержать символы, буквы и цифры разного регистра");
        return;
    }

    // Проверка на совпадение паролей
    if (password1 != password2) {
        QMessageBox::critical(this, "Ошибка", "Пароли не совпадают");
        return;
    }

    // Проверка на наличие смысловых данных
    QStringList forbiddenData = { "дата рождения", "имя", "фамилия", "телефон", "адрес", "кличка" };

    for (const QString& data : forbiddenData) {
        if (password1.contains(data, Qt::CaseInsensitive)) {
            QMessageBox::critical(this, "Ошибка", "Пароль содержит запрещенные данные");
            return;
        }
    }

    for (const QString& data : forbiddenData) {
        if (password2.contains(data, Qt::CaseInsensitive)) {
            QMessageBox::critical(this, "Ошибка", "Пароль содержит запрещенные данные");
            return;
        }
    }

    // Проверка наличия почты в базе данных
    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM users WHERE mail = ?");
    query.bindValue(0, mail);

    if (query.exec() && query.next()) {
        int count = query.value(0).toInt();
        if (count > 0) {
            QMessageBox::critical(this, "Ошибка", "Адрес электронной почты уже зарегистрирован");
            return; // Добавлен оператор return
        }
    }

    // Проверка наличия логина в базе данных
    query.prepare("SELECT COUNT(*) FROM users WHERE login = ?");
    query.bindValue(0, login);

    if (query.exec() && query.next()) {
        int count = query.value(0).toInt();
        if (count > 0) {
            QMessageBox::critical(this, "Ошибка", "Логин уже зарегистрирован");
            return;
        }
    }

    // Хэширование введенного пароля
    QByteArray passwordHash = QCryptographicHash::hash(password2.toUtf8(), QCryptographicHash::Sha256);
    QString passwordHashString = QString(passwordHash.toHex());

    query.prepare("INSERT INTO users (name, password, mail, login) VALUES (:name, :password, :mail, :login)");
    query.bindValue(":name", name);
    query.bindValue(":password", passwordHashString);  // Используем хэшированный пароль
    query.bindValue(":mail", mail);
    query.bindValue(":login", login);

    if (query.exec()) {
        QMessageBox::information(this, "Успех", "Регистрация успешно завершена.");
    } else {
        QMessageBox::critical(this, "Ошибка", "Не удалось добавить пользователя в базу данных: " + query.lastError().text());
    }

    db.close();

    close();
}

void registration::setInterfaceRegStyle()
{
    // Применяем стиль к главному окну регистрации
    QString regWindowStyle = StyleHelper::regWindowStyle();
    setStyleSheet(regWindowStyle);

    ui->pushButton_zareg->setStyleSheet(StyleHelper::pushButton_zaregStyle());

    ui->lineEdit_regname->setStyleSheet(StyleHelper::lineedit_regnameStyle());
    ui->lineEdit_reglogin->setStyleSheet(StyleHelper::lineedit_regloginStyle());
    ui->lineEdit_regmail->setStyleSheet(StyleHelper::lineedit_regmailStyle());
    ui->lineEdit_regpass1->setStyleSheet(StyleHelper::lineedit_regpass1Style());
    ui->lineEdit_regpass2->setStyleSheet(StyleHelper::lineedit_regpass2Style());

}
