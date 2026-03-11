#ifndef FM_H
#define FM_H

#include <QFileInfo>
#include <QString>

//класс, отвечающий за наблюдение за одним файлом
class FileManager {
public:
    FileManager();
    FileManager(QString name);

    //getters
    QString name();
    bool exist();
    int size();

    //setters


    //
    void refresh();

    bool hadChanged();

private:
    QString m_name;
    bool m_exist;
    int m_size;

};

// класс, выводящий изменения всех наблюдаемых файлов
class FileManagerSystem{
public:

private:

};



#endif // FM_H
