#ifndef DBMANAGER_H
#define DBMANAGER_H

#include <QVariant>
#include <QSqlDatabase>

class NonogramImage;

class IDBManager
{
public:
    virtual void connectToDataBase() = 0;
    virtual QSqlDatabase getDB() = 0;
    virtual bool save(NonogramImage* nonogramImage) = 0;
};

#endif // DBMANAGER_H
