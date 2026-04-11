#include "FM.h"
#include <QDebug>
#include <thread>

FileManager::FileManager()
    : m_flag(false) {}

FileManager::~FileManager() {
    clear();
}

void FileManager::attach(IObserver *observer) {
    if (observer && !m_observers.contains(observer))
        m_observers.append(observer);
}

void FileManager::detach(IObserver *observer) {
    m_observers.removeOne(observer);
}

void FileManager::notify(const QFileInfo &info) {
    for (IObserver *obs : m_observers) {
        obs->update(info);
    }
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
    if (m_flag)
        stop();
    m_files.clear();
}

void FileManager::start(int interval) {
    if (m_files.isEmpty() || m_flag) return;

    m_flag = true;
    qDebug() << "\nSTART";

    QList<int> oldSizes;
    for (int i = 0; i < m_files.size(); ++i) {
        m_files[i].refresh();
        oldSizes.append(m_files[i].exists() ? m_files[i].size() : -1);
    }

    for (int i = 0; i < m_files.size(); ++i)
        notify(m_files[i]);

    while (m_flag) {
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

void FileManager::stop() {
    if (m_flag) {
        m_flag = false;
        qDebug() << "FINISH";
    }
}

int FileManager::count() const {
    return m_files.size();
}

void FileManager::print() const {
    for (int i = 0; i < m_files.size(); ++i) {
        qDebug() << m_files[i].fileName();
    }
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
