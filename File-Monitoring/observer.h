#ifndef OBSERVER_H
#define OBSERVER_H

#include <QObject>
#include <QFileInfo>

class IObserver : public QObject {
    Q_OBJECT

public slots:
    virtual void update(const QFileInfo &info) = 0;
};

class ConsoleObserver : public IObserver {
    Q_OBJECT

public slots:
    void update(const QFileInfo &info) override;
};

#endif // OBSERVER_H
