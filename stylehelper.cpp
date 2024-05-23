#include "stylehelper.h"

// Окно со входом


// Окно

QString StyleHelper::mainWindowStyle()
{
    return "QMainWindow {"
           "    background-color: rgb(30, 32, 37);"
           "}";
}

// Кнопки

QString StyleHelper::pushButton_resetStyle()
{
    return "QPushButton#pushButton_reset {"
           "    background-color: transparent;"
           "    color: rgb(129, 143, 155);"
           "    font-weight: bold;"
           "}"
           "QPushButton#pushButton_reset:hover {"
           "    color: rgb(80, 80, 80);"
           "}"
           "QPushButton#pushButton_reset:pressed {"
           "    background-color: transparent;"
           "    color: rgb(129, 143, 155);"
           "    font-weight: bold;"
           "}";
}

QString StyleHelper::pushButton_loginStyle()
{
    return "QPushButton {"
           "    background-color: #FF3355;"
           "    color: #ffffff;"
           "    border: 1px;"
           "    font-weight: bold;"
           "    border-radius: 18px;"
           "    border-color: #FF3355;"
           "    min-width: 100px;"
           "    padding: 10px;"
           "}"
           "QPushButton:hover {"
           "    background-color: #bc263f;"
           "}";
}

QString StyleHelper::pushButton_registrationStyle()
{
    return "QPushButton {"
           "    background-color: #FF3355;"
           "    color: #ffffff;"
           "    border: 1px;"
           "    font-weight: bold;"
           "    border-radius: 18px;"
           "    border-color: #FF3355;"
           "    min-width: 100px;"
           "    padding: 10px;"
           "}"
           "QPushButton:hover {"
           "    background-color: #bc263f;"
           "}";
}

// LineEdit

QString StyleHelper::lineEdit_loginStyle()
{
    return "QLineEdit {"
           "    background-color: rgb(21, 23, 26);"
           "    color: #ffffff;"
           "    border: 1px;"
           "    border-radius: 7px;"
           "    min-width: 100px;"
           "    padding: 9px 12px;"
           "    font-weight: bold;"
           "}";
}

QString StyleHelper::lineEdit_passwordStyle()
{
    return "QLineEdit {"
           "    background-color: rgb(21, 23, 26);"
           "    border: 1px;"
           "    border-radius: 7px;"
           "    min-width: 100px;"
           "    padding: 9px 12px;"
           "}"
           "QLineEdit[echoMode=\"2\"] {"
           "    color: #ffffff;"
           "}";
}

// Окно регистрации


// Окно

QString StyleHelper::regWindowStyle()
{
    return "registration {"
           "    background-color: rgb(30, 32, 37);"
           "}";
}

// Кнопки

QString StyleHelper::pushButton_zaregStyle()
{
    return "QPushButton {"
           "    background-color: #FF3355;"
           "    color: #ffffff;"
           "    border: 1px;"
           "    font-weight: bold;"
           "    border-radius: 15px;"
           "    border-color: #FF3355;"
           "    min-width: 100px;"
           "    padding: 10px;"
           "}"
           "QPushButton:hover {"
           "    background-color: #bc263f;"
           "}";
}

// LineEdit

QString StyleHelper::lineedit_regnameStyle()
{
    return "QLineEdit {"
           "    background-color: rgb(21, 23, 26);"
           "    color: #ffffff;"
           "    border: 1px;"
           "    border-radius: 7px;"
           "    padding: 9px 12px;"
           "    font-weight: bold;"
           "}";
}

QString StyleHelper::lineedit_regloginStyle()
{
    return "QLineEdit {"
           "    background-color: rgb(21, 23, 26);"
           "    color: #ffffff;"
           "    border: 1px;"
           "    border-radius: 7px;"
           "    padding: 9px 12px;"
           "    font-weight: bold;"
           "}";
}

QString StyleHelper::lineedit_regmailStyle()
{
    return "QLineEdit {"
           "    background-color: rgb(21, 23, 26);"
           "    color: #ffffff;"
           "    border: 1px;"
           "    border-radius: 7px;"
           "    padding: 9px 12px;"
           "    font-weight: bold;"
           "}";
}

QString StyleHelper::lineedit_regpass1Style()
{
    return "QLineEdit {"
           "    background-color: rgb(21, 23, 26);"
           "    color: #ffffff;"
           "    border: 1px;"
           "    border-radius: 7px;"
           "    padding: 9px 12px;"
           "    font-weight: bold;"
           "}";
}

QString StyleHelper::lineedit_regpass2Style()
{
    return "QLineEdit {"
           "    background-color: rgb(21, 23, 26);"
           "    color: #ffffff;"
           "    border: 1px;"
           "    border-radius: 7px;"
           "    padding: 9px 12px;"
           "    font-weight: bold;"
           "}";
}



// Окно со сбросом пароля


// Окно

QString StyleHelper::resetWindowStyle()
{
    return "QWidget {"
           "    background-color: rgb(30, 32, 37);"
           "}";
}

// Кнопки

QString StyleHelper::pushButton_resetPasswordStyle()
{
    return "QPushButton {"
           "    background-color: #FF3355;"
           "    color: #ffffff;"
           "    border: 1px;"
           "    font-weight: bold;"
           "    border-radius: 10px;"
           "    border-color: #FF3355;"
           "    min-width: 100px;"
           "    padding: 10px;"
           "}"
           "QPushButton:hover {"
           "    background-color: #bc263f;"
           "}";
}

QString StyleHelper::pushButton_resetPassword_3Style()
{
    return "QPushButton {"
           "    background-color: #FF3355;"
           "    color: #ffffff;"
           "    border: 1px;"
           "    font-weight: bold;"
           "    border-radius: 10px;"
           "    border-color: #FF3355;"
           "    min-width: 100px;"
           "    padding: 10px;"
           "}"
           "QPushButton:hover {"
           "    background-color: #bc263f;"
           "}";
}

QString StyleHelper::pushButton_resetPassword_4Style()
{
    return "QPushButton {"
           "    background-color: #FF3355;"
           "    color: #ffffff;"
           "    border: 1px;"
           "    font-weight: bold;"
           "    border-radius: 10px;"
           "    border-color: #FF3355;"
           "    min-width: 100px;"
           "    padding: 10px;"
           "}"
           "QPushButton:hover {"
           "    background-color: #bc263f;"
           "}";
}

QString StyleHelper::pushButton_nextStyle()
{
    return "QPushButton {"
           "    background-color: #FF3355;"
           "    color: #ffffff;"
           "    border: 1px;"
           "    font-weight: bold;"
           "    border-radius: 10px;"
           "    border-color: #FF3355;"
           "    min-width: 100px;"
           "    padding: 10px;"
           "}"
           "QPushButton:hover {"
           "    background-color: #bc263f;"
           "}";
}

// LineEdit

QString StyleHelper::lineEdit_verifyloginStyle()
{
    return "QLineEdit {"
           "    background-color: rgb(21, 23, 26);"
           "    color: #ffffff;" // Установка цвета текста
           "    border: 1px;"
           "    border-radius: 7px;"
           "    min-width: 100px;"
           "    padding: 9px 12px;"
           "    font-weight: bold;"
           "}";
}

QString StyleHelper::lineEdit_verifymailStyle()
{
    return "QLineEdit {"
           "    background-color: rgb(21, 23, 26);"
           "    color: #ffffff;" // Установка цвета текста
           "    border: 1px;"
           "    border-radius: 7px;"
           "    min-width: 100px;"
           "    padding: 9px 12px;"
           "    font-weight: bold;"
           "}";
}

QString StyleHelper::lineEdit_EmailResetStyle()
{
    return "QLineEdit {"
           "    background-color: rgb(21, 23, 26);"
           "    color: #ffffff;" // Установка цвета текста
           "    border: 1px;"
           "    border-radius: 7px;"
           "    min-width: 100px;"
           "    padding: 9px 12px;"
           "    font-weight: bold;"
           "}";
}

QString StyleHelper::lineEdit_EmailReset_3Style()
{
    return "QLineEdit {"
           "    background-color: rgb(21, 23, 26);"
           "    color: #ffffff;" // Установка цвета текста
           "    border: 1px;"
           "    border-radius: 7px;"
           "    min-width: 100px;"
           "    padding: 9px 12px;"
           "    font-weight: bold;"
           "}";
}

QString StyleHelper::lineEdit_passwordReset_oneStyle()
{
    return "QLineEdit {"
           "    background-color: rgb(21, 23, 26);"
           "    color: #ffffff;" // Установка цвета текста
           "    border: 1px;"
           "    border-radius: 7px;"
           "    min-width: 100px;"
           "    padding: 9px 12px;"
           "    font-weight: bold;"
           "}";
}

QString StyleHelper::lineEdit_passwordReset_twoStyle()
{
    return "QLineEdit {"
           "    background-color: rgb(21, 23, 26);"
           "    color: #ffffff;" // Установка цвета текста
           "    border: 1px;"
           "    border-radius: 7px;"
           "    min-width: 100px;"
           "    padding: 9px 12px;"
           "    font-weight: bold;"
           "}";
}

// Основное окно


// Окно

QString StyleHelper::programWindowStyle()
{
    return "QWidget {"
           "    background-color: rgb(30, 32, 37);"
           "}";
}

QString StyleHelper::listWidget_files()
{
    return "QWidget {"
           "    background-color: rgb(28, 28, 28);"
           "}";
}


// Frame

QString StyleHelper::frame_left()
{
    return "QFrame {"
           "    background-color: rgb(37, 39, 46);"
           "}";
}

// Кнопки

QString StyleHelper::pushButton_upload()
{
    return "QPushButton {"
           "    background-color: #FF3355;"
           "    color: #ffffff;"
           "    border: 1px;"
           "    font-weight: bold;"
           "    border-radius: 18px;"
           "    border-color: #FF3355;"
           "    min-width: 100px;"
           "    padding: 10px;"
           "}"
           "QPushButton:hover {"
           "    background-color: #bc263f;"
           "}";
}

QString StyleHelper::pushButton_download()
{
    return "QPushButton {"
           "    background-color: #FF3355;"
           "    color: #ffffff;"
           "    border: 1px;"
           "    font-weight: bold;"
           "    border-radius: 18px;"
           "    border-color: #FF3355;"
           "    min-width: 100px;"
           "    padding: 10px;"
           "}"
           "QPushButton:hover {"
           "    background-color: #bc263f;"
           "}";
}

QString StyleHelper::pushButton_delete()
{
    return "QPushButton {"
           "    background-color: #FF3355;"
           "    color: #ffffff;"
           "    border: 1px;"
           "    font-weight: bold;"
           "    border-radius: 18px;"
           "    border-color: #FF3355;"
           "    min-width: 100px;"
           "    padding: 10px;"
           "}"
           "QPushButton:hover {"
           "    background-color: #bc263f;"
           "}";
}

QString StyleHelper::pushButton_user_reset()
{
    return "QPushButton {"
           "    background-color: #FF3355;"
           "    color: #ffffff;"
           "    border: 1px;"
           "    font-weight: bold;"
           "    border-radius: 18px;"
           "    border-color: #FF3355;"
           "    min-width: 100px;"
           "    padding: 10px;"
           "}"
           "QPushButton:hover {"
           "    background-color: #bc263f;"
           "}";
}

QString StyleHelper::pushButton_home()
{
    return "QPushButton {"
           "    background-color: transparent;"
           "    border: none;"
           "}";
}

QString StyleHelper::pushButton_user()
{
    return "QPushButton {"
           "    background-color: transparent;"
           "    border: none;"
           "}";
}


QString StyleHelper::pushButton_settings()
{
    return "QPushButton {"
           "    background-color: transparent;"
           "    border: none;"
           "}";
}

QString StyleHelper::pushButton_info()
{
    return "QPushButton {"
           "    background-color: transparent;"
           "    border: none;"
           "}";
}

// Вкладка info

QString StyleHelper::pushButton_telegram()
{
    return "QPushButton {"
           "    background-color: transparent;"
           "    border: none;"
           "}";
}

QString StyleHelper::pushButton_github()
{
    return "QPushButton {"
           "    background-color: transparent;"
           "    border: none;"
           "}";
}

QString StyleHelper::pushButton_vk()
{
    return "QPushButton {"
           "    background-color: transparent;"
           "    border: none;"
           "}";
}
