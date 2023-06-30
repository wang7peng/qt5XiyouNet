# Project created by QtCreator 2023-06-19
#
#-------------------------------------------------

QT       += core gui widgets xml

TARGET = qt5XiyouNet
TEMPLATE = app

# linx 6.0 default GCC only v4.9，MUST append support "-std=c++11"
QMAKE_CXXFLAGS += -std=c++11

SOURCES += main.cpp \
    customizewin.cpp \
    profile.cpp  \
    home.cpp \

HEADERS  += home.h \
    customizewin.h \
    profile.h  \
    dataglobal.h \
    profile.h \


FORMS    += home.ui \
    profile.ui \
    customizewin.ui

RESOURCES += \
    res.qrc
