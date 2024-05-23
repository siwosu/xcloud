#ifndef PROGRAM_H
#define PROGRAM_H

#include <QMainWindow>
#include <QButtonGroup>
#include <QRadioButton>
#include <QObject>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QWidget>
#include <QStringList>
#include <QListWidget>
#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QLabel>
#include <QFileDialog>
#include <QMessageBox>
#include <QPainter>
#include <QRandomGenerator>
#include <QColor>
#include <curl/curl.h>
#include <fstream>
#include <sstream>

struct CloudFileInfo
{
    QString name;
    QIcon icon;
};

namespace Ui {
class Program;
}

class Program : public QMainWindow
{
    Q_OBJECT

public:
    explicit Program(QWidget *parent = nullptr);
    ~Program();

private slots:
    void on_pushButton_home_clicked();
    void on_pushButton_user_clicked();
    void on_pushButton_settings_clicked();
    void on_pushButton_info_clicked();
    void on_pushButton_vk_clicked();
    void on_pushButton_github_clicked();
    void on_pushButton_telegram_clicked();
    void on_pushButton_upload_clicked();

    void setInterfaceStyle();

    void onFilesListReceived();

    void on_pushButton_download_clicked();

    void on_pushButton_delete_clicked();

    bool deleteFileFromDropbox(const QString &dropboxFilePath);

    void on_pushButton_user_reset_clicked();

private:
    Ui::Program *ui;

    // Левая вкладка
    QIcon hoverSettingsIcon;
    QIcon normalSettingsIcon;
    QIcon hoverInfoIcon;
    QIcon normalInfoIcon;
    QIcon hoverUserIcon;
    QIcon normalUserIcon;
    QIcon hoverHomeIcon;
    QIcon normalHomeIcon;

    // Вкладка info
    QIcon hoverTelegramIcon;
    QIcon normalTelegramIcon;
    QIcon hoverVkIcon;
    QIcon normalVkIcon;
    QIcon hoverGitHubIcon;
    QIcon normalGitHubIcon;

    void setButtonIcon();

    // Основное окно
    bool uploadFileToDropbox(const QString &localFilePath, const QString &dropboxFilePath);
    void getFilesListFromDropbox();

    void updateFileListView(const QStringList& fileNames);
    QStringList loadPreviousFiles();

    QNetworkAccessManager *networkManager;
    QNetworkReply *networkReply;
    QListWidget *fileListView;

    QLabel *label_avatar;

    void setupAvatar();

    bool downloadFileFromDropbox(const QString &dropboxFilePath, const QString &localFilePath);


protected:
    bool eventFilter(QObject* obj, QEvent* event) override;
};

#endif // PROGRAM_H
