#pragma once

#include <queue>

#include <QFile>
#include <QDir>

class BackupManager
{
public:
    BackupManager(const std::string& fileName="backup.txt");

    void updateBackup(std::queue<std::string> dataQueue);
    void push(const std::string& text);
    void pop();

private:
    QFile _file;
    std::string _fileName;
};
