#include "program.h"
#include "ui_program.h"

#include "stylehelper.h"
#include "reset.h"
#include "mainwindow.h"

#include <fstream>
#include <string>
#include <iostream>

#include <QPropertyAnimation>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QIcon>
#include <QUrl>
#include <QUrlQuery>
#include <QSqlError>
#include <QSqlDatabase>
#include <QDesktopServices>
#include <QMessageBox>
#include <QRadioButton>
#include <QFileDialog>
#include <fstream>
#include <QFileInfo>
#include <QDebug>
#include <QFileIconProvider>
#include <curl/curl.h>
#include <sstream>
#include <QTranslator>

#include <curl/curl.h>

Program::Program(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::Program)
    , label_avatar(new QLabel(this)) // Инициализация label_avatar
{
    ui->setupUi(this);

    setInterfaceStyle();

    setButtonIcon();

    networkManager = new QNetworkAccessManager(this);

    // Вызов функции для получения списка файлов с Dropbox
    getFilesListFromDropbox();

    // Настраиваем аватарку
    label_avatar->setFixedSize(100, 100); // Устанавливаем желаемый размер аватарки
    setupAvatar();

    // Создаем layout для размещения label_avatar по центру в верхней части окна
    QVBoxLayout *mainLayout = new QVBoxLayout();

    // Создаем SpacerItem для центрирования
    QSpacerItem *topSpacer = new QSpacerItem(20, -330, QSizePolicy::Minimum, QSizePolicy::Fixed);

    // Добавляем SpacerItem и label_avatar в mainLayout
    mainLayout->addItem(topSpacer);
    mainLayout->addWidget(label_avatar, 0, Qt::AlignHCenter);

    // Устанавливаем layout на page_2_u
    ui->page_2_u->setLayout(mainLayout);
}

Program::~Program()
{
    delete ui;

    networkManager->deleteLater();
}

void Program::setInterfaceStyle()
{
    // Окно

    QString mainWindowStyle = StyleHelper::programWindowStyle();
    setStyleSheet(mainWindowStyle);

    ui->listWidget_files->setStyleSheet(StyleHelper::listWidget_files());

    // Устанавливаем стиль для левой части окна

    ui->frame_left->setStyleSheet(StyleHelper::frame_left());

    // Кнопки

    ui->pushButton_upload->setStyleSheet(StyleHelper::pushButton_upload());

    ui->pushButton_download->setStyleSheet(StyleHelper::pushButton_download());

    ui->pushButton_delete->setStyleSheet(StyleHelper::pushButton_delete());

    ui->pushButton_user_reset->setStyleSheet(StyleHelper::pushButton_user_reset());

}

void Program::setupAvatar() {
    QPixmap avatar(":/resources/profile_photo.png"); // Укажите путь к вашей аватарке
    if (avatar.isNull()) {
        qDebug() << "Failed to load avatar image!";
        return;
    }

    // Масштабируем изображение до размера QLabel с сохранением пропорций
    int labelWidth = label_avatar->width();
    int labelHeight = label_avatar->height();
    QPixmap scaledAvatar = avatar.scaled(labelWidth, labelHeight, Qt::KeepAspectRatio, Qt::SmoothTransformation);

    label_avatar->setPixmap(scaledAvatar);
    qDebug() << "Avatar setup completed!";
}

void Program::setButtonIcon()
{
    // Создаем экземпляр класса QPixmap с путями к файлам изображений

    // Левая вкладка

    QPixmap normalSettingsPixmap(":/resources/settingsBlack.png");
    QPixmap hoverSettingsPixmap(":/resources/settingsWhite.png");

    QPixmap normalInfoPixmap(":/resources/infoBlack.png");
    QPixmap hoverInfoPixmap(":/resources/infoWhite.png");

    QPixmap normalUserPixmap(":/resources/userBlack.png");
    QPixmap hoverUserPixmap(":/resources/userWhite.png");

    QPixmap normalHomePixmap(":/resources/homeBlack.png");
    QPixmap hoverHomePixmap(":/resources/homeWhite.png");

    // Вкладка info

    QPixmap normalTelegramPixmap(":/resources/telegramBlack.png");
    QPixmap hoverTelegramPixmap(":/resources/telegramWhite.png");

    QPixmap normalVkPixmap(":/resources/vkBlack.png");
    QPixmap hoverVkPixmap(":/resources/vkWhite.png");

    QPixmap normalGitHubPixmap(":/resources/githubBlack.png");
    QPixmap hoverGitHubPixmap(":/resources/githubWhite.png");

    // Масштабируем изображения до нужного размера
    QSize scaledSize(512, 512);

    // Лвевая вкладка

    QPixmap scaledNormalSettingsPixmap = normalSettingsPixmap.scaled(scaledSize, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    QPixmap scaledHoverSettingsPixmap = hoverSettingsPixmap.scaled(scaledSize, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

    QPixmap scaledNormalInfoPixmap = normalInfoPixmap.scaled(scaledSize, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    QPixmap scaledHoverInfoPixmap = hoverInfoPixmap.scaled(scaledSize, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

    QPixmap scaledNormalUserPixmap = normalUserPixmap.scaled(scaledSize, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    QPixmap scaledHoverUserPixmap = hoverUserPixmap.scaled(scaledSize, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

    QPixmap scaledNormalHomePixmap = normalHomePixmap.scaled(scaledSize, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    QPixmap scaledHoverHomePixmap = hoverHomePixmap.scaled(scaledSize, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

    // Вкладка info

    QPixmap scaledNormalTelegramPixmap = normalTelegramPixmap.scaled(scaledSize, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    QPixmap scaledHoverTelegramPixmap = hoverTelegramPixmap.scaled(scaledSize, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

    QPixmap scaledNormalVkPixmap = normalVkPixmap.scaled(scaledSize, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    QPixmap scaledHoverVkPixmap = hoverVkPixmap.scaled(scaledSize, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

    QPixmap scaledNormalGitHubPixmap = normalGitHubPixmap.scaled(scaledSize, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    QPixmap scaledHoverGitHubPixmap = hoverGitHubPixmap.scaled(scaledSize, Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);


    // Создаем экземпляр класса QIcon с масштабированными изображениями

    hoverSettingsIcon = QIcon(scaledHoverSettingsPixmap);
    normalSettingsIcon = QIcon(scaledNormalSettingsPixmap);

    hoverInfoIcon = QIcon(scaledHoverInfoPixmap);
    normalInfoIcon = QIcon(scaledNormalInfoPixmap);

    hoverUserIcon = QIcon(scaledHoverUserPixmap);
    normalUserIcon = QIcon(scaledNormalUserPixmap);

    hoverHomeIcon = QIcon(scaledHoverHomePixmap);
    normalHomeIcon = QIcon(scaledNormalHomePixmap);

    // Вкладка info

    hoverTelegramIcon = QIcon(scaledHoverTelegramPixmap);
    normalTelegramIcon = QIcon(scaledNormalTelegramPixmap);

    hoverVkIcon = QIcon(scaledHoverVkPixmap);
    normalVkIcon = QIcon(scaledNormalVkPixmap);

    hoverGitHubIcon = QIcon(scaledHoverGitHubPixmap);
    normalGitHubIcon = QIcon(scaledNormalGitHubPixmap);

    // Устанавливаем иконки и размеры для кнопок

    // Левая вкладка

    ui->pushButton_settings->setIcon(normalSettingsIcon);
    ui->pushButton_settings->setIconSize(QSize(32, 32));
    ui->pushButton_settings->setFixedSize(32, 32);
    ui->pushButton_settings->setStyleSheet(StyleHelper::pushButton_settings());
    ui->pushButton_settings->installEventFilter(this);
    ui->pushButton_settings->setToolTip("Настройки");

    ui->pushButton_info->setIcon(normalInfoIcon);
    ui->pushButton_info->setIconSize(QSize(32, 32));
    ui->pushButton_info->setFixedSize(32, 32);
    ui->pushButton_info->setStyleSheet(StyleHelper::pushButton_info());
    ui->pushButton_info->installEventFilter(this);
    ui->pushButton_info->setToolTip("Информация");

    ui->pushButton_user->setIcon(normalUserIcon);
    ui->pushButton_user->setIconSize(QSize(32, 32));
    ui->pushButton_user->setFixedSize(32, 32);
    ui->pushButton_user->setStyleSheet(StyleHelper::pushButton_user());
    ui->pushButton_user->installEventFilter(this);
    ui->pushButton_user->setToolTip("Профиль");

    ui->pushButton_home->setIcon(normalHomeIcon);
    ui->pushButton_home->setIconSize(QSize(32, 32));
    ui->pushButton_home->setFixedSize(32, 32);
    ui->pushButton_home->setStyleSheet(StyleHelper::pushButton_home());
    ui->pushButton_home->installEventFilter(this);
    ui->pushButton_home->setToolTip("Главная");

    // Вкладка info

    ui->pushButton_telegram->setIcon(normalTelegramIcon);
    ui->pushButton_telegram->setIconSize(QSize(32, 32));
    ui->pushButton_telegram->setFixedSize(32, 32);
    ui->pushButton_telegram->setStyleSheet(StyleHelper::pushButton_telegram());
    ui->pushButton_telegram->installEventFilter(this);
    ui->pushButton_telegram->setToolTip("Telegram");

    ui->pushButton_vk->setIcon(normalVkIcon);
    ui->pushButton_vk->setIconSize(QSize(32, 32));
    ui->pushButton_vk->setFixedSize(32, 32);
    ui->pushButton_vk->setStyleSheet(StyleHelper::pushButton_vk());
    ui->pushButton_vk->installEventFilter(this);
    ui->pushButton_vk->setToolTip("VK");

    ui->pushButton_github->setIcon(normalGitHubIcon);
    ui->pushButton_github->setIconSize(QSize(32, 32));
    ui->pushButton_github->setFixedSize(32, 32);
    ui->pushButton_github->setStyleSheet(StyleHelper::pushButton_github());
    ui->pushButton_github->installEventFilter(this);
    ui->pushButton_github->setToolTip("GitHub");

}

bool Program::eventFilter(QObject* obj, QEvent* event)
{
    // Левая вкладка

    if (obj == ui->pushButton_settings)
    {
        if (event->type() == QEvent::Enter)
        {
            ui->pushButton_settings->setIcon(hoverSettingsIcon);
            ui->pushButton_settings->setIconSize(QSize(30, 30));
            ui->pushButton_settings->update();
        }
        else if (event->type() == QEvent::Leave)
        {
            ui->pushButton_settings->setIcon(normalSettingsIcon);
            ui->pushButton_settings->setIconSize(QSize(30, 30));
            ui->pushButton_settings->update();
        }
    }
    else if (obj == ui->pushButton_info)
    {
        if (event->type() == QEvent::Enter)
        {
            ui->pushButton_info->setIcon(hoverInfoIcon);
            ui->pushButton_info->setIconSize(QSize(30, 30));
            ui->pushButton_info->update();
        }
        else if (event->type() == QEvent::Leave)
        {
            ui->pushButton_info->setIcon(normalInfoIcon);
            ui->pushButton_info->setIconSize(QSize(30, 30));
            ui->pushButton_info->update();
        }
    }
    else if (obj == ui->pushButton_user)
    {
        if (event->type() == QEvent::Enter)
        {
            ui->pushButton_user->setIcon(hoverUserIcon);
            ui->pushButton_user->setIconSize(QSize(30, 30));
            ui->pushButton_user->update();
        }
        else if (event->type() == QEvent::Leave)
        {
            ui->pushButton_user->setIcon(normalUserIcon);
            ui->pushButton_user->setIconSize(QSize(30, 30));
            ui->pushButton_user->update();
        }
    }
    else if (obj == ui->pushButton_home)
    {
        if (event->type() == QEvent::Enter)
        {
            ui->pushButton_home->setIcon(hoverHomeIcon);
            ui->pushButton_home->setIconSize(QSize(30, 30));
            ui->pushButton_home->update();
        }
        else if (event->type() == QEvent::Leave)
        {
            ui->pushButton_home->setIcon(normalHomeIcon);
            ui->pushButton_home->setIconSize(QSize(30, 30));
            ui->pushButton_home->update();
        }
    }

    // Вкладка info

    else if (obj == ui->pushButton_telegram)
    {
        if (event->type() == QEvent::Enter)
        {
            ui->pushButton_telegram->setIcon(hoverTelegramIcon);
            ui->pushButton_telegram->setIconSize(QSize(30, 30));
            ui->pushButton_telegram->update();
        }
        else if (event->type() == QEvent::Leave)
        {
            ui->pushButton_telegram->setIcon(normalTelegramIcon);
            ui->pushButton_telegram->setIconSize(QSize(30, 30));
            ui->pushButton_telegram->update();
        }
    }

    else if (obj == ui->pushButton_vk)
    {
        if (event->type() == QEvent::Enter)
        {
            ui->pushButton_vk->setIcon(hoverVkIcon);
            ui->pushButton_vk->setIconSize(QSize(30, 30));
            ui->pushButton_vk->update();
        }
        else if (event->type() == QEvent::Leave)
        {
            ui->pushButton_vk->setIcon(normalVkIcon);
            ui->pushButton_vk->setIconSize(QSize(30, 30));
            ui->pushButton_vk->update();
        }
    }

    else if (obj == ui->pushButton_github)
    {
        if (event->type() == QEvent::Enter)
        {
            ui->pushButton_github->setIcon(hoverGitHubIcon);
            ui->pushButton_github->setIconSize(QSize(30, 30));
            ui->pushButton_github->update();
        }
        else if (event->type() == QEvent::Leave)
        {
            ui->pushButton_github->setIcon(normalGitHubIcon);
            ui->pushButton_github->setIconSize(QSize(30, 30));
            ui->pushButton_github->update();
        }
    }

    return QObject::eventFilter(obj, event);
}

void Program::on_pushButton_home_clicked()
{
    ui->stackedWidget_program->setCurrentIndex(0); // Устанавливаем индекс 0 для перехода на 1 страницу
}

void Program::on_pushButton_user_clicked()
{
    ui->stackedWidget_program->setCurrentIndex(1); // Устанавливаем индекс 1 для перехода на 2 страницу
}

void Program::on_pushButton_settings_clicked()
{
    QMessageBox::information(this, tr("Soon"), tr("В ближайшее время!"));
}

// Кнопки

void Program::on_pushButton_info_clicked()
{
    ui->stackedWidget_program->setCurrentIndex(3); // Устанавливаем индекс 3 для перехода на 4 страницу
}

void Program::on_pushButton_vk_clicked()
{
    QDesktopServices::openUrl(QUrl("https://vk.com/xcloudinfo"));
}

void Program::on_pushButton_github_clicked()
{
    QDesktopServices::openUrl(QUrl("https://github.com/siwosu"));
}

void Program::on_pushButton_telegram_clicked()
{
    QDesktopServices::openUrl(QUrl("https://t.me/siwosu"));
}

// Основная кнопка

void Program::getFilesListFromDropbox()
{
    QString apiUrl = "https://api.dropboxapi.com/2/files/list_folder";
    QString accessToken = "cmiQtn-_AS9JQXRUDtyyLXGQZl6VtJ5YTnGndzocm_KxRZPa4QKIuf2RyrTEZT7S5MVvLh2JbrPLlBN"; // Замените на ваш access token

    QNetworkRequest request;
    request.setUrl(QUrl(apiUrl));
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", QString("Bearer %1").arg(accessToken).toUtf8());

    QJsonObject requestData;
    requestData["path"] = "";
    requestData["recursive"] = false;
    requestData["include_media_info"] = false;
    requestData["include_deleted"] = false;
    requestData["include_has_explicit_shared_members"] = false;
    requestData["include_mounted_folders"] = true;

    QJsonDocument requestDataJson(requestData);
    QByteArray requestDataBytes = requestDataJson.toJson();

    networkReply = networkManager->post(request, requestDataBytes);
    connect(networkReply, &QNetworkReply::finished, this, &Program::onFilesListReceived);
}

void Program::onFilesListReceived()
{
    if (networkReply->error() == QNetworkReply::NoError) {
        QByteArray responseData = networkReply->readAll();
        QJsonDocument responseJson = QJsonDocument::fromJson(responseData);
        QJsonObject responseObject = responseJson.object();

        if (responseObject.contains("entries") && responseObject["entries"].isArray()) {
            QJsonArray entriesArray = responseObject["entries"].toArray();

            // Очищаем список перед добавлением новых элементов
            ui->listWidget_files->clear();

            for (const QJsonValue& entryValue : entriesArray) {
                if (entryValue.isObject()) {
                    QJsonObject entryObject = entryValue.toObject();

                    if (entryObject.contains("name") && entryObject["name"].isString()) {
                        QString fileName = entryObject["name"].toString();
                        QIcon fileIcon = QFileIconProvider().icon(QFileInfo(fileName));

                        QListWidgetItem* item = new QListWidgetItem(fileIcon, fileName);
                        ui->listWidget_files->addItem(item);
                    }
                }
            }
        }
    } else {
        qDebug() << "Error: " << networkReply->errorString();
    }

    networkReply->deleteLater();
}


void Program::on_pushButton_upload_clicked()
{
    QString filePath = QFileDialog::getOpenFileName(this, tr("Выберите файл для загрузки"), "", tr("Все файлы (*)"));

    if (filePath.isEmpty()) {
        QMessageBox::warning(this, tr("Ошибка"), tr("Файл не выбран"));
        return;
    }

    QString dropboxFilePath = "/" + QFileInfo(filePath).fileName(); // Или можете настроить по-другому

    if (uploadFileToDropbox(filePath, dropboxFilePath)) {
        QMessageBox::information(this, tr("Успех"), tr("Файл успешно загружен в Dropbox: %1").arg(dropboxFilePath));

        // Получение информации о загруженном файле
        CloudFileInfo fileInfo;
        fileInfo.name = QFileInfo(filePath).fileName();
        fileInfo.icon = QFileIconProvider().icon(QFileInfo(filePath));

        // Создание элемента списка с иконкой и названием файла
        QListWidgetItem* item = new QListWidgetItem(fileInfo.icon, fileInfo.name);

        // Добавление элемента в список
        ui->listWidget_files->addItem(item);

        getFilesListFromDropbox(); // Получение списка файлов с Dropbox
    } else {
        QMessageBox::critical(this, tr("Ошибка"), tr("Не удалось загрузить файл в Dropbox"));
    }
}

bool Program::uploadFileToDropbox(const QString &localFilePath, const QString &dropboxFilePath)
{
    std::string accessToken = "fHrv5zc3SiXm-0LKXoz7jEMJrmWhmJvTgPo97YmfpPsXvMaGHcmiQtn-_AS9JQXRUDtyyLXGQZl6VtJ5YTnGndzocm_KxRZPa4QKIuf2RyrTEZT7S5MVvLh2JbrPLlBN"; // Замените на ваш access token
    CURL *curl;
    CURLcode res = CURLE_OK;
    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init();

    if (curl) {
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers, ("Authorization: Bearer " + accessToken).c_str());
        headers = curl_slist_append(headers, "Content-Type: application/octet-stream");
        headers = curl_slist_append(headers, ("Dropbox-API-Arg: {\"path\": \"" + dropboxFilePath.toStdString() + "\",\"mode\": \"add\",\"autorename\": true,\"mute\": false,\"strict_conflict\": false}").c_str());

        std::ifstream file(localFilePath.toStdString(), std::ios::binary);
        if (!file.is_open()) {
            qWarning() << "Не удалось открыть файл: " << localFilePath;
            curl_easy_cleanup(curl);
            curl_global_cleanup();
            return false;
        }

        std::ostringstream fileContents;
        fileContents << file.rdbuf();
        file.close();
        std::string fileData = fileContents.str();

        curl_easy_setopt(curl, CURLOPT_URL, "https://content.dropboxapi.com/2/files/upload");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, fileData.c_str());
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, fileData.size());

        // Укажите правильный путь к cacert.pem
        QString certPath = QCoreApplication::applicationDirPath() + "/cacert.pem";
        qDebug() << "Using certificate path: " << certPath;
        curl_easy_setopt(curl, CURLOPT_CAINFO, certPath.toStdString().c_str());
        curl_easy_setopt(curl, CURLOPT_CAPATH, certPath.toStdString().c_str());

        // Отключите проверку статуса SSL для тестирования
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYSTATUS, 0L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 1L);
        curl_easy_setopt(curl, CURLOPT_SSL_VERIFYHOST, 2L);

        // Включите отладочную информацию
        curl_easy_setopt(curl, CURLOPT_VERBOSE, 1L);

        qDebug() << "Starting file upload...";
        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            qWarning() << "curl_easy_perform() failed: " << curl_easy_strerror(res);
        } else {
            qDebug() << "Upload successful.";
        }

        curl_slist_free_all(headers);
        curl_easy_cleanup(curl);
    } else {
        qWarning() << "Failed to initialize CURL.";
    }

    curl_global_cleanup();
    return (res == CURLE_OK);
}


void Program::on_pushButton_download_clicked()
{
    QList<QListWidgetItem *> selectedItems = ui->listWidget_files->selectedItems();
    if (selectedItems.isEmpty()) {
        QMessageBox::warning(this, tr("Ошибка"), tr("Файл не выбран"));
        return;
    }

    QString fileName = selectedItems.first()->text(); // Получаем имя выбранного файла

    QString localFilePath = QFileDialog::getSaveFileName(this, tr("Сохранить файл"), fileName);
    if (localFilePath.isEmpty()) {
        QMessageBox::warning(this, tr("Ошибка"), tr("Файл не сохранен"));
        return;
    }

    // Скачивание выбранного файла
    QString dropboxFilePath = "/" + fileName;
    if (downloadFileFromDropbox(dropboxFilePath, localFilePath)) {
        QMessageBox::information(this, tr("Успех"), tr("Файл успешно скачан: %1").arg(localFilePath));
    } else {
        QMessageBox::critical(this, tr("Ошибка"), tr("Не удалось скачать файл"));
    }
}

bool Program::downloadFileFromDropbox(const QString &dropboxFilePath, const QString &localFilePath)
{
    QString accessToken = "sl.B1sj-Vbg-khiD4g8cdv0fHrv5zc3SiXm-0LKXoz7jEMJrmWhmJvTgPo97YmfpPsXvMaGHcmiQtn-_AS9JQXRUDtyyLXGQZl6VtJ5YTnGndzocm_KxRZPa4QKIuf2RyrTEZT7S5MVvLh2JbrPLlBN"; // Замените на ваш access token

    QString apiUrl = "https://content.dropboxapi.com/2/files/download";
    QNetworkRequest request(apiUrl);
    request.setRawHeader("Authorization", QString("Bearer %1").arg(accessToken).toUtf8());
    request.setRawHeader("Dropbox-API-Arg", QString("{\"path\": \"%1\"}").arg(dropboxFilePath).toUtf8());

    QNetworkReply *reply = networkManager->get(request);
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    if (reply->error() == QNetworkReply::NoError) {
        QFile file(localFilePath);
        if (file.open(QIODevice::WriteOnly)) {
            file.write(reply->readAll());
            file.close();
            reply->deleteLater();
            return true;
        } else {
            qDebug() << "Failed to open file for writing:" << file.errorString();
        }
    } else {
        qDebug() << "Error downloading file:" << reply->errorString();
    }

    reply->deleteLater();
    return false;
}

bool Program::deleteFileFromDropbox(const QString &dropboxFilePath)
{
    QString accessToken = "-0LKXoz7jEMJrmWhmJvTgPo97YmfpPsXvMaGHcmiQtn-_AS9JQXRUDtyyLXGQZl6VtJ5YTnGndzocm_KxRZPa4QKIuf2RyrTEZT7S5MVvLh2JbrPLlBN"; // Замените на ваш access token

    QString apiUrl = "https://api.dropboxapi.com/2/files/delete_v2";
    QNetworkRequest request(apiUrl);
    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");
    request.setRawHeader("Authorization", QString("Bearer %1").arg(accessToken).toUtf8());

    QJsonObject requestData;
    requestData["path"] = dropboxFilePath;

    QJsonDocument requestDataJson(requestData);
    QByteArray requestDataBytes = requestDataJson.toJson();

    QNetworkReply *reply = networkManager->post(request, requestDataBytes);
    QEventLoop loop;
    connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
    loop.exec();

    if (reply->error() == QNetworkReply::NoError) {
        reply->deleteLater();
        return true;
    } else {
        qDebug() << "Error deleting file:" << reply->errorString();
        reply->deleteLater();
        return false;
    }
}

void Program::on_pushButton_delete_clicked()
{
    QList<QListWidgetItem *> selectedItems = ui->listWidget_files->selectedItems();
    if (selectedItems.isEmpty()) {
        QMessageBox::warning(this, tr("Ошибка"), tr("Файл не выбран"));
        return;
    }

    QString fileName = selectedItems.first()->text(); // Получаем имя выбранного файла
    QString dropboxFilePath = "/" + fileName;

    if (deleteFileFromDropbox(dropboxFilePath)) {
        int row = ui->listWidget_files->row(selectedItems.first()); // Получаем индекс выбранного элемента
        delete ui->listWidget_files->takeItem(row); // Удаляем элемент из списка
        QMessageBox::information(this, tr("Успех"), tr("Файл успешно удален: %1").arg(fileName));
    } else {
        QMessageBox::critical(this, tr("Ошибка"), tr("Не удалось удалить файл"));
    }
}


void Program::on_pushButton_user_reset_clicked()
{

}
