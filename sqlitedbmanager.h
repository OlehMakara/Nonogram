#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QVariantList>

#include <idbmanager.h>

/* Директиви імен таблиці, полів таблиці і бази даних */
#define DATABASE_HOSTNAME   "localhost"
#define DATABASE_NAME       "nonogramDB.sqlite"

class SqliteDBManager : public IDBManager {

public:
    virtual ~SqliteDBManager();
    static SqliteDBManager* getInstance();

    /* Методи для безпосередньої роботи з класом
     * Підключення до бази даних і вставка записів у таблицю
     * */
    void connectToDataBase();
    QSqlDatabase getDB();
    bool save(NonogramImage* nonogramImage);
    virtual NonogramImage* load(int id);

private:
    // Сам об'єкт бази даних, з яким буде виконуватись робота
    QSqlDatabase    db;

private:
    static SqliteDBManager* instance;
    SqliteDBManager();


    QBitArray StringToBits(const QString &str) const;
    QString bitsToString(const QBitArray &bits) const;

    /* Внутрішні методи для роботи з базою даних
     * */
    bool openDataBase();
    bool restoreDataBase();
    void closeDataBase();
    bool createTables();
};



#endif // DATABASE_H
