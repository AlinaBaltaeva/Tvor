
CONFIG += console debug
QT += serialport
QT += core gui serialport widgets
TARGET = ArduinoEndStopMonitor
TEMPLATE = app

# Добавьте эти настройки
CONFIG += c++11
DEFINES += QT_DEPRECATED_WARNINGS

SOURCES += main.cpp mainwindow.cpp
HEADERS += mainwindow.h
FORMS += mainwindow.ui

win32 {
    LIBS += -lsetupapi
}

