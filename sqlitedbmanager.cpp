#include "sqlitedbmanager.h"
#include "nonogramimage.h"

#include <QObject>
#include <QSqlQuery>
#include <QSqlError>
#include <QFile>
#include <QDate>
#include <QDebug>
#include <QSqlRecord>

SqliteDBManager* SqliteDBManager::instance = nullptr;

SqliteDBManager::SqliteDBManager(){
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setHostName(DATABASE_HOSTNAME);
    db.setDatabaseName(DATABASE_NAME);
}

SqliteDBManager::~SqliteDBManager()
{

}

SqliteDBManager* SqliteDBManager::getInstance()
{
    if(instance == nullptr){
        instance = new SqliteDBManager();
    }
    return instance;
}

/* Методи для підключення до бази даних
 * */
void SqliteDBManager::connectToDataBase()
{
    // Перед підключенням до бази даних виконаємо перевірку, чи вона вже не підключена
    if (!db.isOpen())
    {
        /* Перед підключенням до бази даних виконуємо перевірку на її існування.
     * В залежності від результату виконуємо відкриття бази даних або її відновлення
     * */
        if(QFile(DATABASE_NAME).exists()){
            this->openDataBase();
        } else {
            this->restoreDataBase();
        }
    }
}

QSqlDatabase SqliteDBManager::getDB()
{
    return db;
}

/* Методи відновлення бази даних
 * */
bool SqliteDBManager::restoreDataBase()
{
    if(this->openDataBase()){
        if(!this->createTables()){
            return false;
        } else {
            return true;
        }
    } else {
        qDebug() << "Не вдалось відновити базу даних";
        return false;
    }
}

/* Методи для відкриття бази даних
 * */
bool SqliteDBManager::openDataBase()
{
    /* База даних відкривається по вказаному шляху
     * і імені бази даних, якщо вона існує
     * */
    if(db.open()){
        return true;
    } else
        return false;
}

/* Метод закриття бази даних
 * */
void SqliteDBManager::closeDataBase()
{
    db.close();
}

/* Метод для створення таблиці в базі даних
 * */
bool SqliteDBManager::createTables()
{

    /*
CREATE TABLE nonograms (
    id             INTEGER      PRIMARY KEY AUTOINCREMENT,
    name           VARCHAR (50),
    rows_amount    INTEGER,
    columns_amount INTEGER,
    matrix         BLOB
);
     * */

    //TODO
    //    /* В даному випадку використовується фурмування сирого SQL-запиту
    //     * з наступним його виконанням.
    //     * */
    //    QSqlQuery query;
    //    if(!query.exec( "CREATE TABLE " TABLE_EXAMPLE " ("
    //                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
    //                    TABLE_EXAMPLE_DATE      " DATE            NOT NULL,"
    //                    TABLE_EXAMPLE_TIME      " TIME            NOT NULL,"
    //                    TABLE_EXAMPLE_RANDOM    " INTEGER         NOT NULL,"
    //                    TABLE_EXAMPLE_MESSAGE   " VARCHAR(255)    NOT NULL"
    //                    " )"
    //                    )){
    //        qDebug() << "DataBase: error of create " << TABLE_EXAMPLE;
    //        qDebug() << query.lastError().text();
    //        return false;
    //    } else
    return true;
}

bool SqliteDBManager::save(NonogramImage* nonogramImage)
{

    QSqlQuery query;
    if (nonogramImage->getId() != 0)
    {
        query.prepare("UPDATE nonograms SET name=:name, rows_amount=:rowsAmount, columns_amount=:columnsAmount, matrix=:matrix "
                      "WHERE id=:id");
        query.bindValue(":id", nonogramImage->getId());
    } else
        query.prepare("INSERT INTO nonograms (name, rows_amount, columns_amount, matrix) "
                      "VALUES (:name, :rowsAmount, :columnsAmount, :matrix)");

    query.bindValue(":name", nonogramImage->getName());
    query.bindValue(":rowsAmount", nonogramImage->getRowsAmount());
    query.bindValue(":columnsAmount", nonogramImage->getColumnsAmount());
    query.bindValue(":matrix", bitsToString(nonogramImage->getMatrix()));

    if(!query.exec()){
        qDebug() << "Error save into table nonograms!";
        qDebug() << query.lastError().text();
        qDebug() << query.lastQuery();

        return false;
    } else
        return true;
}

NonogramImage *SqliteDBManager::load(int id)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM nonograms WHERE id=:id");
    query.bindValue(":id", id);
    if(!query.exec()){
        qDebug() << "Error select from table nonograms by id=" << id;
        qDebug() << query.lastError().text();
        qDebug() << query.lastQuery();
    }
    QString name;
    int rowsAmount(0);
    int columnsAmount(0);
    QBitArray matrix;
    query.next();
    name = query.value("name").toString();
    rowsAmount = query.value("rows_amount").toInt();
    columnsAmount = query.value("columns_amount").toInt();
    matrix = StringToBits(query.value("matrix").toString());

    return new NonogramImage(id, name, rowsAmount, columnsAmount, matrix);
}

QBitArray SqliteDBManager::StringToBits(const QString &str) const
{
    QBitArray bits(str.size());
    for (int i = 0; i < str.size(); ++i) {
        if (str.at(i) == "1")
            bits.setBit(i);
    }

    return bits;
}


QString SqliteDBManager::bitsToString(const QBitArray &bits) const
{
    QString str;
    for (int i = 0; i < bits.size(); ++i) {
        str.append(bits.at(i)? "1" : "0");
    }
    return str;
}
