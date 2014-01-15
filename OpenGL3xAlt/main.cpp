#include "trianglewindow.h"
#include <QApplication>
#include <QtGui>

int main(int argc, char *argv[])
{
    QApplication a( argc, argv );

    QSurfaceFormat surfaceFormat;
    surfaceFormat.setVersion( 3, 2 );
    surfaceFormat.setProfile( QSurfaceFormat::CoreProfile );
    surfaceFormat.setDepthBufferSize( 24 );

    TriangleWindow w( surfaceFormat );

    w.resize(640, 480);
    w.setAnimating(true);
    w.show();

    return a.exec();
}
