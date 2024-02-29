#pragma once

#include <queue>

#include <QFile>
#include <QDir>

class BackupManager
{
public:
    BackupManager(const std::string& fileName="backup.txt");

    void updateBackup(std::queue<std::string> dataQueue);

private:
    QFile _file;
    std::string _fileName;
};
