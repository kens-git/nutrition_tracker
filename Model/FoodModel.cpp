#include "FoodModel.hpp"

#include "DatabaseManager.hpp"
#include "Food.hpp"

FoodModel::FoodModel() : mDatabase(DatabaseManager::instance()) {
    mFoodList = new QStringList();
    setStringList(*mFoodList);
}

void FoodModel::addFood(Food &food) {
    mDatabase.mFoodDAO.addFood(food);
}

void FoodModel::getFoods(const QString &category) {
    mFoodList = mDatabase.mFoodDAO.getFoodNames(category);
    setStringList(*mFoodList);
}
