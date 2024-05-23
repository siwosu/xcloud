#ifndef STYLEHELPER_H
#define STYLEHELPER_H

#include <QString>

class StyleHelper
{
public:
    static QString pushButton_resetStyle();
    static QString pushButton_loginStyle();
    static QString pushButton_registrationStyle();

    static QString mainWindowStyle();

    static QString lineEdit_loginStyle();
    static QString lineEdit_passwordStyle();

    static QString pushButton_nextStyle();
    static QString pushButton_resetPasswordStyle();
    static QString pushButton_resetPassword_3Style();
    static QString pushButton_resetPassword_4Style();

    static QString lineEdit_verifyloginStyle();
    static QString lineEdit_verifymailStyle();
    static QString lineEdit_EmailResetStyle();
    static QString lineEdit_EmailReset_3Style();
    static QString lineEdit_passwordReset_oneStyle();
    static QString lineEdit_passwordReset_twoStyle();

    static QString resetWindowStyle();

    static QString regWindowStyle();

    static QString pushButton_zaregStyle();

    static QString lineedit_regnameStyle();
    static QString lineedit_regloginStyle();
    static QString lineedit_regmailStyle();
    static QString lineedit_regpass1Style();
    static QString lineedit_regpass2Style();


    static QString programWindowStyle();

    static QString listWidget_files();

    static QString pushButton_upload();

    static QString pushButton_download();
    static QString pushButton_delete();

    static QString pushButton_user_reset();

    static QString pushButton_settings();
    static QString pushButton_info();
    static QString pushButton_user();
    static QString pushButton_home();
    static QString pushButton_telegram();
    static QString pushButton_github();
    static QString pushButton_vk();

    static QString frame_left();
};

#endif // STYLEHELPER_H
