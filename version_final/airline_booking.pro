QT += core gui widgets sql printsupport
QT += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

CONFIG += c++17

SOURCES += \
    src/DatabaseManager.cpp \
    src/dao/ClientFonction.cpp \
    src/dao/ReservationFonction.cpp \
    src/dao/VolFonction.cpp \
    src/main.cpp \
    src/ui/MainWindow.cpp \
    src/ui/LoginDialog.cpp \
    src/ui/ClientDialog.cpp \
    src/ui/VolDialog.cpp \
    src/ui/ReservationDialog.cpp \
    src/ui/TicketWidget.cpp

HEADERS += \
    src/dao/ClientFonction.h \
    src/dao/ReservationFonction.h \
    src/dao/VolFonction.h \
    src/database/DatabaseManager.h \
    src/models/Client.h \
    src/models/Reservation.h \
    src/models/Vol.h \
    src/ui/MainWindow.h \
    src/ui/LoginDialog.h \
    src/ui/ClientDialog.h \
    src/ui/VolDialog.h \
    src/ui/ReservationDialog.h \
    src/ui/TicketWidget.h

FORMS += \
    src/ui/MainWindow.ui \
    src/ui/LoginDialog.ui \
    src/ui/ClientDialog.ui \
    src/ui/VolDialog.ui \
    src/ui/ReservationDialog.ui \
    src/ui/TicketWidget.ui

INCLUDEPATH += src

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target
