#include <QCoreApplication>

#include <QFileInfo>
#include <QDebug>
#include <iostream>

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    qDebug() <<"HI";
    std::cout << "HIHI" << std::endl;


    return a.exec();
}
