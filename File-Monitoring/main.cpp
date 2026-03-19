#include <QCoreApplication>

#include <QFileInfo>
#include <QDebug>

#include "FM.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    FileManager file("C:/GitHub_Repositories/File-monitoring/File-Monitoring/a.txt");

    qDebug() << "имя файла:" << file.name();
    qDebug() << "существует:" << (file.exist() ? "да" : "нет");

    if (file.exist())
        qDebug() << "размер:" << file.size() << "байт";

    qDebug()<<"\n";

    FileManager file2;

    file2.setName("C:/GitHub_Repositories/File-monitoring/File-Monitoring/b.txt");

    qDebug() << "имя файла:" << file2.name();
    qDebug() << "существует:" << (file2.exist() ? "да" : "нет");

    if (file2.exist())
        qDebug() << "размер:" << file2.size() << "байт";

    return a.exec();
}
