#pragma once

#include "glwindow.h"
#include <QOpenGLFunctions_3_2_Core>

class TriangleWindow : public GLWindow, protected QOpenGLFunctions_3_2_Core
{
public:
    TriangleWindow(QSurfaceFormat surfaceFormat, QScreen *screen=0);

protected:
    virtual void initializeGL() override;
    virtual void paintGL() override;
    virtual void resizeGL(int width, int height) override;
private:
    GLuint prepareShaderProgram( const QString& vertexShaderPath,
                               const QString& fragmentShaderPath );

    GLuint m_shader = 0;
    GLuint m_vertexBuffer = 0;
};

