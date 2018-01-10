#include "IntakeDAO.hpp"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>
#include <QDate>

#include "DatabaseManager.hpp"
#include "Food.hpp"

IntakeDAO::IntakeDAO(QSqlDatabase& database)
    : mDatabase(database)
{

}

void IntakeDAO::init() const {
    if (!mDatabase.tables().contains("intake")) {
        QSqlQuery query(mDatabase);

        query.exec("CREATE TABLE intake ("
                   "id INTEGER PRIMARY KEY AUTOINCREMENT,"
                   "food_name TEXT,"
                   "serving_size FLOAT,"
                   "month TEXT,"
                   "day INTEGER,"
                   "year INTEGER)");

        DatabaseManager::queryStatus(query);
    }
}

void IntakeDAO::addIntake(const Food& intake, const QDate& date) const {
    QSqlQuery query(mDatabase);

    query.prepare("INSERT INTO intake (food_name, serving_size, month, day, year) VALUES ("
                  ":food_name,"
                  ":serving_size,"
                  ":month,"
                  ":day,"
                  ":year)");

    query.bindValue(":food_name", intake.getName());
    query.bindValue(":serving_size", intake.getServingSize());
    query.bindValue(":month", date.month());
    query.bindValue(":day", date.day());
    query.bindValue(":year", date.year());

    query.exec();

    DatabaseManager::queryStatus(query);
}

QVector<Food>* IntakeDAO::getIntake(QDate &date) const {
    QSqlQuery query(mDatabase);

    query.prepare("SELECT * FROM intake WHERE month = :month AND day = :day AND year = :year");
    query.bindValue(":month", date.month());
    query.bindValue(":day", date.day());
    query.bindValue(":year", date.year());
    query.exec();
    DatabaseManager::queryStatus(query);

    QVector<Food>* intakeList = new QVector<Food>();

    while (query.next()) {
        Food food = DatabaseManager::instance().mFoodDAO.getFood(query.value("food_name").toString(),
                                                                 query.value("serving_size").toFloat());

        food.setServingSize(query.value("serving_size").toFloat());

        intakeList->push_back(food);
    }

    return intakeList;
}
