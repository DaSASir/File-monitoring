#ifndef OBSERVER_H
#define OBSERVER_H

#include <QFileInfo>

class IObserver {
public:
    virtual void update(const QFileInfo &info) = 0;
};

class ConsoleObserver : public IObserver {
public:
    void update(const QFileInfo &info) override;
};

#endif // OBSERVER_H
