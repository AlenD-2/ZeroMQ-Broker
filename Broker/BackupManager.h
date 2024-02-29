#pragma once

#include <queue>

#include <QFile>
#include <QDir>

class BackupManager
{
public:
    BackupManager(const std::string& fileName="backup.txt");
    ~BackupManager();

    void updateBackup(std::queue<std::string> dataQueue);
    void push(const std::string& text);
    void pop();

private:
    QFile _backupFile;
    QFile _indexFile;
    std::string _fileName;

    size_t _firstLine;
    size_t _lastLine;

    void _saveIndexData();
};
