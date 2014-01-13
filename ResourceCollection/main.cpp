#include <QString>
#include <QFile>
#include <QDebug>

int main(int argc, char *argv[])
{
    QString resourceName(":/hello.txt");
    QFile file(resourceName);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)){
        QByteArray data = file.readAll();
        file.close();
        qDebug() << data.data();
    } else {
        qWarning() << "Cannot open file " << resourceName;

    }


    return 0;
}
