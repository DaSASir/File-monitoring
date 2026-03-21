#ifndef FM_H
#define FM_H

#include <QFileInfo>

class FileManager {
public:
    FileManager();
    ~FileManager();

    void addFile(const QString &name);
    void removeFile(const QString &name);
    void clear();

    void start(int interval = 100);
    void stop();

    int count() const;
    void print() const;

private:
    bool inStock(const QString &name);

private:
    QList<QFileInfo> m_files;
    bool m_flag;

};

#endif // FM_H
