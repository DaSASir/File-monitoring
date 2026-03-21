#include "FM.h"
#include <QTextStream>
#include <QDebug>
#include <thread>

FileManager::FileManager()
    : m_flag(false) {}

FileManager::~FileManager(){
    clear();
}

void FileManager::addFile(const QString &name){
    if (inStock(name))
        return;

    m_files.append(QFileInfo(name));
}

void FileManager::removeFile(const QString &name){
    if (!inStock(name))
        return;

    for (int i = 0; i < m_files.size(); ++i) {
        if (m_files[i].filePath() == name) {
            m_files.removeAt(i);
            return;
        }
    }
}

void FileManager::clear(){
    if (m_flag) stop();

    m_files.clear();
}

void FileManager::start(int interval){
    if (m_files.isEmpty() || m_flag) return;

    m_flag = true;

    qDebug() << "СТАРТ, интервал:" << interval;

    QList<int> oldSizes;
    for (int i = 0; i < m_files.size(); ++i) {
        m_files[i].refresh();
        oldSizes.append(m_files[i].exists() ? m_files[i].size() : -1);
    }

    while (m_flag) {
        for (int i = 0; i < m_files.size(); ++i) {
            m_files[i].refresh();

            int newSize = m_files[i].exists() ? m_files[i].size() : -1;

            if (newSize != oldSizes[i]) {
                qDebug() << "ИЗМЕНЕНИЕ:" << m_files[i].filePath() << " размер:" << oldSizes[i] << "->" << newSize;
                oldSizes[i] = newSize;
            }
        }

        std::this_thread::sleep_for(std::chrono::milliseconds(interval));
    }
}

void FileManager::stop(){
    if (m_flag) {
        m_flag = false;
        qDebug() << "ФИНИШ";
    }
}

int FileManager::count() const{
    return m_files.size();
}

void FileManager::print() const{
    for (int i = 0; i < m_files.size(); ++i) {
        qDebug() << m_files[i];
    }
}

bool FileManager::inStock(const QString &name){
    for (int i = 0; i < m_files.size(); ++i)
        if (m_files[i].filePath() == name)
            return true;

    return false;
}
