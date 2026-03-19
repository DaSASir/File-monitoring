#ifndef FM_H
#define FM_H

#include <QFileInfo>
#include <QString>

//класс, отвечающий за наблюдение за одним файлом
class FileManager {
public:
    FileManager();
    FileManager(const QString &name);

    //getters
    QString name() const;
    bool exist() const;
    int size() const;

    //setters
    void setName(const QString &name);

    //проверка на изменения файла
    bool hadChanged();

private:
    //обновление состояния файла
    void refresh();

private:
    QString m_name;
    bool m_exist;
    int m_size;

    QFileInfo m_fileInfo;
};

// класс, выводящий изменения всех наблюдаемых файлов
class FileManagerSystem{
public:
    FileManagerSystem();
    ~FileManagerSystem();



private:
    QList<FileManager> m_files;

};



#endif // FM_H
