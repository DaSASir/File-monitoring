#include <QCoreApplication>
#include "FM.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    FileManager fm;
    fm.addFile("a.txt");

    fm.start();

    return 0;
}
