#include "observer.h"
#include <QDebug>

void ConsoleObserver::update(const QFileInfo &info) {
    qDebug() << "\nFile:" << info.fileName();
    if (!info.exists()) {
        qDebug() << "status: NOT exist";
    } else {
        qDebug() << "status: exist";
        qDebug() << "size:" << info.size();
    }
}
