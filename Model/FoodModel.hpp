#ifndef FOODMODEL_HPP
#define FOODMODEL_HPP

#include <QStringListModel>
#include <QString>

class DatabaseManager;
class Food;

class FoodModel : public QStringListModel {
    public:
        FoodModel();

        void addFood(Food& food);

        void getFoods(const QString& category);

    private:
        DatabaseManager& mDatabase;

        // Not the complete list, only the currently selected category
        QStringList* mFoodList;
};

#endif // FOODMODEL_HPP
