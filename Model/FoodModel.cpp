#include "FoodModel.hpp"

#include "DatabaseManager.hpp"
#include "Food.hpp"

FoodModel::FoodModel() : mDatabase(DatabaseManager::instance()) {
    mFoodList = new QStringList();
    setStringList(*mFoodList);
}

bool FoodModel::addFood(Food &food) {
    // reject duplicate food names
    if (mDatabase.mFoodDAO.getFood(food.getName()).getName() == "") {
        mDatabase.mFoodDAO.addFood(food);
        return true;
    } else {
        return false;
    }

}

void FoodModel::getFoods(const QString &category) {
    mFoodList = mDatabase.mFoodDAO.getFoodNames(category);
    setStringList(*mFoodList);
}
