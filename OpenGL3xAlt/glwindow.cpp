#include "glwindow.h"

#include <QDebug>
#include <QKeyEvent>
#include <QCoreApplication>
#include <iostream>
#include <memory>

using namespace std;

GLWindow::GLWindow( QSurfaceFormat surfaceFormat, QScreen *screen  )
    : QWindow(screen)
{
    setSurfaceType( OpenGLSurface );
    setFormat( surfaceFormat );
    create();

    // Create an OpenGL context
    m_context = new QOpenGLContext();
    m_context->setFormat( surfaceFormat );
    m_context->create();

    // Make the context current on this window
    m_context->makeCurrent( this );

}

void GLWindow::exposeEvent(QExposeEvent *event)
{
    Q_UNUSED(event);
    if (!glInitialized){
        glInitialized = true;
        initializeGL();
        // make sure that resize event is performed after initialization
        QSize s = size();
        resizeGL(s.width(), s.height());
    }
    if (isExposed()) {
        renderNow();
    }
}

void GLWindow::resizeEvent(QResizeEvent *event)
{
    QSize size = event->size();
    if (glInitialized) {
        resizeGL(size.width(), size.height());
    }
}

void GLWindow::setAnimating(bool animating){
    if (animating != this->animating) {
        this->animating = animating;
        if (animating) {
            renderLater();
        }
    }
}

bool GLWindow::event(QEvent *event)
{
    switch (event->type()) {
    case QEvent::UpdateRequest:
        renderNow();
        return true;
    default:
        return QWindow::event(event);
    }
}

void GLWindow::renderLater(){
    if (!m_update_pending){
        m_update_pending = true;
        QCoreApplication::postEvent(this, new QEvent(QEvent::UpdateRequest));
    }
}

void GLWindow::renderNow()
{
    m_context->makeCurrent(this);
    paintGL();
    m_context->swapBuffers(this);
    m_update_pending = false;
    if (animating){
        renderLater();
    }
}

