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
        dataQueue.pop();
    }

    _file.close();
}

/*
 * write input string to last line of the file
 */
void BackupManager::push(const std::string &text)
{
    if(!_file.open(QFile::WriteOnly | QFile::Append))
    {
        qDebug()<<"file not open. Error: "<<_file.errorString();
    }

    _file.write(QByteArray::fromStdString(text)+'\n');
    _file.close();
}

/*
 * remove the first line of file
 */
void BackupManager::pop()
{
    if(!_file.open(QFile::ReadWrite | QFile::Text))
    {
        qDebug()<<"file not open. Error: "<<_file.errorString();
    }

    auto fileText = _file.readAll();
    _file.resize(0); // clear file
    fileText = fileText.remove(0, fileText.indexOf('\n')+1); //remove first line
    _file.write(fileText);
    _file.close();
}
