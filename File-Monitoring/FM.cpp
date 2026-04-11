#include "FM.h"
#include <QDebug>
#include <thread>

FileManager::FileManager() : QObject() {}

FileManager::~FileManager() {
    clear();
}

void FileManager::attach(IObserver *observer) {
    if (observer && !m_observers.contains(observer)) {
        m_observers.append(observer);
        connect(this, &FileManager::fileChanged, observer, &IObserver::update);
    }
}

void FileManager::detach(IObserver *observer) {
    disconnect(this, &FileManager::fileChanged, observer, &IObserver::update);
    m_observers.removeOne(observer);
}

void FileManager::notify(const QFileInfo &info) {
    emit fileChanged(info);
}

void FileManager::addFile(const QString &name) {
    if (!isCorrectName(name))
        return;

    if (inStock(name))
        return;

    QFileInfo info(name);
    m_files.append(info);
}

void FileManager::removeFile(const QString &name) {
    if (!inStock(name))
        return;

    for (int i = 0; i < m_files.size(); ++i) {
        if (m_files[i].filePath() == name) {
            m_files.removeAt(i);
            break;
        }
    }
}

void FileManager::clear() {
    m_files.clear();
}

void FileManager::start(int interval) {
    if (m_files.isEmpty()) return;

    qDebug() << "\nSTART";

    QList<int> oldSizes;
    for (int i = 0; i < m_files.size(); ++i) {
        m_files[i].refresh();
        oldSizes.append(m_files[i].exists() ? m_files[i].size() : -1);
    }

    for (int i = 0; i < m_files.size(); ++i)
        notify(m_files[i]);

    while (true) {
        for (int i = 0; i < m_files.size(); ++i) {
            m_files[i].refresh();

            int newSize = m_files[i].exists() ? m_files[i].size() : -1;

            if (newSize != oldSizes[i]) {
                notify(m_files[i]);
                oldSizes[i] = newSize;
            }
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(interval));
    }
}

int FileManager::count() const {
    return m_files.size();
}

bool FileManager::inStock(const QString &name) {
    for (int i = 0; i < m_files.size(); ++i)
        if (m_files[i].filePath() == name)
            return true;

    return false;
}

bool FileManager::isCorrectName(const QString &name) {
    if (name.isEmpty())
        return false;

    QString ban = "!@#$%^&*+=}{|><';\"";
    for (QChar c : name)
        if (ban.contains(c))
            return false;

    return true;
}

bool FileManager::isFoundFile(const QString &name) {
    QFileInfo check(name);
    return check.exists();
}
