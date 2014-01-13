#-------------------------------------------------
#
# Project created by QtCreator 2014-01-13T07:06:11
#
#-------------------------------------------------

QT += core gui\
      opengl widgets

CONFIG += c++11

win32:INCLUDEPATH += "C:\Users\mono\Documents\glew-1.10.0\include"
win32:LIBS += "C:\Users\mono\Documents\glew-1.10.0\lib\Release\x64\glew32.lib"


TARGET = OpenGL3x
TEMPLATE = app

SOURCES += main.cpp \
    mywidget.cpp \
    glheader.cpp

HEADERS  += \
    mywidget.h \
    glheader.h

OTHER_FILES += \
    simple.frag \
    simple.vert

RESOURCES +=  core-profile.qrc

