#pragma once

#include "glheader.h"
#include <QGLWidget>

class MyWidget : public QGLWidget
{
    Q_OBJECT
public:
    MyWidget( const QGLFormat& format, QWidget* parent = 0 );

protected:
    virtual void initializeGL();
    virtual void resizeGL( int w, int h );
    virtual void paintGL();

private:
    GLuint prepareShaderProgram( const QString& vertexShaderPath,
                               const QString& fragmentShaderPath );

    GLuint m_shader;
    GLuint m_vertexBuffer;
};

