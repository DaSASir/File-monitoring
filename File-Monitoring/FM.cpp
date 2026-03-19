#include "FM.h"
#include <QTextStream>

//FileManager
FileManager::FileManager()
    : m_name(""), m_exist(false), m_size(0)
{}

FileManager::FileManager(const QString &name)
    : m_name(name), m_exist(false), m_size(0), m_fileInfo(name)
{
    refresh();
}

QString FileManager::name() const{
    return m_name;
}

bool FileManager::exist() const{
    return m_exist;
}

int FileManager::size() const{
    return m_size;
}

void FileManager::setName(const QString &name){
    m_name = name;
    m_fileInfo.setFile(name);
    refresh();
}

void FileManager::refresh(){
    m_fileInfo.refresh();
    m_exist = m_fileInfo.exists();

    m_size = m_exist ? m_fileInfo.size() : 0;
}

bool FileManager::hadChanged(){
    bool oldExist = m_exist;
    int oldSize = m_size;

    refresh();

    if (m_exist != oldExist)
        return true;

    if (m_exist && m_size != oldSize)
        return true;

    return false;
}

//FileManagerSystem


