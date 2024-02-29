#include "BackupManager.h"

BackupManager::BackupManager(const std::string &fileName)
    : _fileName(fileName)
{
    _file.setFileName(QDir::currentPath()+QString("/")+QString::fromStdString(_fileName));
}

void BackupManager::updateBackup(std::queue<std::string> dataQueue)
{
    if(!_file.open(QFile::WriteOnly))
    {
        qDebug()<<"file not open. Error: "<<_file.errorString();
    }

    while(!dataQueue.empty())
    {
        _file.write(QByteArray::fromStdString(dataQueue.front())+'\n');
    }

    _file.close();
}
