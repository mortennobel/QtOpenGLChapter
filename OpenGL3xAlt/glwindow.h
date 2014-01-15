#pragma once

#include <QWindow>
#include <QOpenGLPaintDevice>

class GLWindow : public QWindow
{
    Q_OBJECT
public:
    GLWindow( QSurfaceFormat surfaceFormat, QScreen *screen=0 );
    void setAnimating(bool animating);
public slots:
    void renderLater();
    void renderNow();
protected:
    virtual void initializeGL() = 0;
    virtual void paintGL() = 0;
    virtual void resizeGL(int w, int h) = 0;
    bool event(QEvent *event);
    void resizeEvent(QResizeEvent *event);
    void exposeEvent(QExposeEvent *event);

private:
    bool glInitialized = false;
    bool animating = false;
    bool m_update_pending = false;
    QOpenGLContext* m_context;
    QOpenGLPaintDevice *m_device;
};

