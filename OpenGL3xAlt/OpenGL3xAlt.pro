#-------------------------------------------------
#
# Project created by QtCreator 2014-01-13T07:06:11
#
#-------------------------------------------------

QT += core gui widgets

CONFIG += c++11

TARGET = OpenGL3x
TEMPLATE = app

SOURCES += main.cpp \
    glwindow.cpp \
    trianglewindow.cpp

HEADERS  += \
    glwindow.h \
    trianglewindow.h

OTHER_FILES += \
    simple.frag \
    simple.vert

RESOURCES +=  core-profile.qrc

