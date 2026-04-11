#ifndef FM_H
#define FM_H

#include <QFileInfo>
#include "observer.h"

class FileManager {
public:
    FileManager();
    ~FileManager();

    void addFile(const QString &name);
    void removeFile(const QString &name);
    void clear();

    void start(int interval = 100);
    void stop();

    int count() const;
    void print() const;

    void attach(IObserver *observer);
    void detach(IObserver *observer);
    void notify(const QFileInfo &info);

private:
    bool inStock(const QString &name);
    bool isCorrectName(const QString &name);
    bool isFoundFile(const QString &name);

private:
    QList<QFileInfo> m_files;
    QList<IObserver*> m_observers;
    bool m_flag = false;
};

#endif // FM_H
