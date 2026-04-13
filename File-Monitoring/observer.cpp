#include "observer.h"
#include <QDebug>

void ConsoleObserver::update(const QFileInfo &info) {
    qDebug() << "\nFile:" << info.filePath();
    if (!info.exists()) {
        qDebug() << "status: NOT exist";
    } else {
        qDebug() << "status: exist";
        qDebug() << "size:" << info.size();
        if (info.size() == 0) {
            qDebug() << "warning: file is empty!";
        }
    }
}
