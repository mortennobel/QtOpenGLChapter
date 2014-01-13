// mywidget.h
#pragma once
#include <QGLWidget>

class MyWidget : public QGLWidget
{
    Q_OBJECT
public:
    explicit MyWidget(QWidget *parent = 0) :
        QGLWidget(parent)
    {
    }

    void initializeGL()
    {
        glClearColor(1.0, 0.0, 0.0, 0.0);
    }

    void paintGL()
    {
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void resizeGL(int w, int h)
    {
        glViewport(0, 0, (GLint)w, (GLint)h);
    }
};
