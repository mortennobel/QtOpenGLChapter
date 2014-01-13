#include "mywidget.h"
#include <QApplication>
#include <QtGui>


int main(int argc, char *argv[])
{
    QApplication a( argc, argv );

    QGLFormat glFormat;
    glFormat.setVersion( 3, 2 );
    glFormat.setProfile( QGLFormat::CoreProfile );
    glFormat.setSampleBuffers( true );

    MyWidget w( glFormat );
    w.show();

    return a.exec();
}
