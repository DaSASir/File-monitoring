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

    manager.stop();

    return a.exec();
}

/*
#include <iostream>

class Parishioner;

class Church {
public:
    virtual void registerParishioner(Parishioner* parishioner) = 0;
    virtual void removeParishioner(Parishioner* parishioner) = 0;
    virtual void notifyParishioners() = 0;
};

class Parishioner {
private:
    std::string m_name;

public:
    Parishioner(std::string name, Church* church) : m_name(name) {
        church->registerParishioner(this);
    }

    void update(std::string& newsChurch) {
        std::cout << m_name << " get: " << newsChurch << std::endl;
    }
};

class CatholicChurch : public Church {
private:
    std::list<Parishioner*> parishioners;
    std::string newsChurch;

public:
    CatholicChurch() = default;

    void setNewsChurch(std::string news) {
        this->newsChurch = news;
        notifyParishioners();
    }

    void registerParishioner(Parishioner* parishioner) override {
        parishioners.push_back(parishioner);
    }

    void removeParishioner(Parishioner* parishioner) override {
        parishioners.remove(parishioner);
    }

    void notifyParishioners() override {
        for (Parishioner* parishioner : parishioners) {
            parishioner->update(newsChurch);
        }
    }
};

int main()
{
    CatholicChurch church;

    Parishioner p1("IVAN", &church);
    Parishioner p2("MISHA", &church);

    church.setNewsChurch("OOO");

    return 0;
}
*/
