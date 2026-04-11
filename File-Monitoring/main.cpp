#include <QCoreApplication>

#include <QDebug>
#include "FM.h"
#include "observer.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    FileManager manager;
    ConsoleObserver observer;

    manager.attach(&observer);

    manager.addFile(f1);
    manager.addFile(f2);
    manager.addFile(f3);
    manager.addFile(f4);
    manager.addFile(f5);

    manager.start();

    return a.exec();
}
