#include "BackupManager.h"

BackupManager::BackupManager(const std::string &fileName)
    : _fileName(fileName)
{
    _backupFile.setFileName(QDir::currentPath()+QString("/")+QString::fromStdString(_fileName));
    if(!_backupFile.open(QFile::ReadWrite | QFile::Text))
    {
        qDebug()<<"file not open. Error: "<<_backupFile.errorString();
    }

    _indexFile.setFileName(QDir::currentPath()+QString("/")+QString("indexData.txt"));
    if(!_indexFile.open(QFile::ReadWrite| QFile::Text))
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
    _backupFile.flush();
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

std::queue<std::string> BackupManager::getQueue()
{
    std::queue<std::string> result;

    _firstLine = _indexFile.readLine().toInt();
    /* first line shouldd not be odd cause odd lines are counter section of packets
     * if it's odd then it means in a rare moment program terminate middle of
     * saving data or somthing like this
     */
    if(_firstLine%2 != 0)
    {
        _firstLine++;
    }
    _lastLine = _indexFile.readLine().toInt();

    for(size_t i=0 ; i<_firstLine ; i++)
    {
        _backupFile.readLine();
    }

    while(!_backupFile.atEnd())
    {
        result.push(_backupFile.readLine().trimmed().toStdString());
    }

    return result;
}

void BackupManager::_saveIndexData()
{
    _indexFile.resize(0);
    _indexFile.write(QByteArray::number(_firstLine)+'\n');
    _indexFile.write(QByteArray::number(_lastLine));
    _indexFile.flush();
}
