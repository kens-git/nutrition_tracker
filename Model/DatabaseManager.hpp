#ifndef DATABASEMANAGER_HPP
#define DATABASEMANAGER_HPP

#include <QString>
class QSqlDatabase;
class QSqlQuery;

#include "FoodDAO.hpp"
#include "IntakeTargetDAO.hpp"
#include "IntakeDAO.hpp"

const QString DB_FILENAME = "database.db";

class DatabaseManager {
    public:
        static DatabaseManager& instance();
        ~DatabaseManager();

        static void queryStatus(const QSqlQuery& query);

    protected:
        DatabaseManager(const QString& filepath = DB_FILENAME);
        DatabaseManager& operator=(const DatabaseManager& rhs);

    private:
        QSqlDatabase* mDatabase;

    public:
        // Initialized after mDatabase
        const FoodDAO mFoodDAO;
        const IntakeTargetDAO mIntakeTargetDAO;
        const IntakeDAO mIntakeDAO;

};

#endif // DATABASEMANAGER_HPP
