#include "CategoryModel.hpp"

#include <QStringList>

CategoryModel::CategoryModel()
{
    mStringList = new QStringList();
    mStringList->push_back("Breads and Grains");
    mStringList->push_back("Cereal");
    mStringList->push_back("Dairy");
    mStringList->push_back("Drink");
    mStringList->push_back("Fruit");
    mStringList->push_back("Meat");
    mStringList->push_back("Packaged Meal");
    mStringList->push_back("Packaged Snack");
    mStringList->push_back("Sauces and Spreads");
    mStringList->push_back("Supplement");
    mStringList->push_back("Vegetable");

    setStringList(*mStringList);
}
