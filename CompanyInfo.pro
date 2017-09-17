#-------------------------------------------------
#
# Project created by QtCreator 2017-09-17T22:30:18
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = CompanyInfo
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    company.cpp \
    employee.cpp \
    employeewithsubordinates.cpp \
    global.cpp \
    manager.cpp \
    person.cpp \
    personinposition.cpp \
    position.cpp \
    sales.cpp

HEADERS  += mainwindow.h \
    Company.h \
    employee.h \
    employeewithsubordinates.h \
    enumpersontype.h \
    global.h \
    manager.h \
    person.h \
    personinposition.h \
    position.h \
    sales.h

FORMS    += mainwindow.ui
