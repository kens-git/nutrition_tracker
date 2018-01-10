#ifndef INTAKEDAO_HPP
#define INTAKEDAO_HPP

#include <QVector>

class QSqlDatabase;
class QDate;

class Food;

class IntakeDAO {
    public:
        IntakeDAO(QSqlDatabase& database);
        void init() const;

        void addIntake(const Food& intake, const QDate& date) const;
        QVector<Food>* getIntake(QDate& date) const;

    private:
        QSqlDatabase& mDatabase;
};

#endif // INTAKEDAO_HPP
