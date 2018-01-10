#ifndef FOODDAO_HPP
#define FOODDAO_HPP

#include <QStringList>
class QSqlDatabase;

class Food;

class FoodDAO {
    public:
        FoodDAO(QSqlDatabase& database);
        void init() const;

        void addFood(Food& food) const;

        Food getFood(const QString& name) const;
        // helper method to get the food and automatically figure out the nutrient values
        // relative to the serving size
        Food getFood(const QString& name, float servingSize) const;
        QStringList* getFoodNames(const QString& category) const;

    private:
        QSqlDatabase& mDatabase;
};

#endif // FOODDAO_HPP
