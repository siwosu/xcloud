QT += core gui widgets network sql

VERSION = 1.0

QMAKE_TARGET_COMPANY = siwosu Co
QMAKE_TARGET_PRODUCT = xCloud
QMAKE_TARGET_DISCRIPTION = The Best Cloud
QMAKE_TARGET_COPYRIGHT = Abraham Linkoln


TARGET = xCloud
TEMPLATE = app

# Указание путей к ресурсам
INCLUDEPATH += $$PWD/resources/curl/include
LIBS += -L$$PWD/resources/curl/lib -lcurl

# Настройки сборки
CONFIG += c++17
CONFIG += release

# Источники и заголовочные файлы
SOURCES += \
    main.cpp \
    mainwindow.cpp \
    program.cpp \
    registration.cpp \
    reset.cpp \
    stylehelper.cpp

HEADERS += \
    mainwindow.h \
    program.h \
    registration.h \
    reset.h \
    stylehelper.h

FORMS += \
    mainwindow.ui \
    program.ui \
    registration.ui \
    reset.ui

# Ресурсы
RESOURCES += resources.qrc

# Правила для развертывания
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

DISTFILES +=
