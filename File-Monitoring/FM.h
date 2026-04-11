#ifndef FM_H
#define FM_H

#include <QObject>
#include <QFileInfo>
#include "observer.h"

class FileManager : public QObject {
    Q_OBJECT

public:
    FileManager();
    ~FileManager();

    void addFile(const QString &name);
    void removeFile(const QString &name);
    void clear();

    void start(int interval = 100);

    int count() const;

    void attach(IObserver *observer);
    void detach(IObserver *observer);
    void notify(const QFileInfo &info);

signals:
    void fileChanged(const QFileInfo &info);

private:
    bool inStock(const QString &name);
    bool isCorrectName(const QString &name);
    bool isFoundFile(const QString &name);

private:
    QList<QFileInfo> m_files;
    QList<IObserver*> m_observers;
};

#endif // FM_H
