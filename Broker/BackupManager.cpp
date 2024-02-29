#include "BackupManager.h"

BackupManager::BackupManager(const std::string &fileName)
    : _fileName(fileName)
{
    _backupFile.setFileName(QDir::currentPath()+QString("/")+QString::fromStdString(_fileName));
    if(!_backupFile.open(QFile::ReadWrite | QFile::Append))
    {
        qDebug()<<"file not open. Error: "<<_backupFile.errorString();
    }

    _indexFile.setFileName(QDir::currentPath()+QString("/")+QString("indexData.txt"));
    if(!_indexFile.open(QFile::ReadWrite | QFile::Append | QFile::Text))
    {
        qDebug()<<"file not open. Error: "<<_backupFile.errorString();
    }
}

BackupManager::~BackupManager()
{
    _backupFile.close();
    _indexFile.close();
}

/*
 * write input string to last line of the file
 * and increment the lastline index
 */
void BackupManager::push(const std::string &text)
{
    _backupFile.write(QByteArray::fromStdString(text)+'\n');
    _lastLine++;

    _saveIndexData();
}

/*
 * increment the firstline index. its acts like removing first line
 * if firstline reach the lastline then clear file
 */
void BackupManager::pop()
{
    _firstLine++;
    if(_firstLine == _lastLine)
    {
        // clear file
        _backupFile.resize(0);
        _firstLine = 0;
        _lastLine = 0;
    }

    _saveIndexData();
}

void BackupManager::_saveIndexData()
{
    _indexFile.resize(0);
    _indexFile.write(QByteArray::number(_firstLine)+'\n');
    _indexFile.write(QByteArray::number(_lastLine));
    _indexFile.flush();
}
