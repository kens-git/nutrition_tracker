#include "FoodDAO.hpp"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>

#include "DatabaseManager.hpp"
#include "Food.hpp"

FoodDAO::FoodDAO(QSqlDatabase &database)
    : mDatabase(database)
{

}

void FoodDAO::init() const {
    if (!mDatabase.tables().contains("foods")) {
        QSqlQuery query(mDatabase);

        query.exec("CREATE TABLE foods (id INTEGER PRIMARY KEY AUTOINCREMENT,"
                   "name TEXT,"
                   "category TEXT,"
                   "serving_size FLOAT,"
                   "unit_of_measure TEXT,"
                   "fat FLOAT,"
                   "saturated_fat FLOAT,"
                   "trans_fat FLOAT,"
                   "unsaturated_fat FLOAT,"
                   "cholesterol FLOAT,"
                   "sodium FLOAT,"
                   "carbs FLOAT,"
                   "fibre FLOAT,"
                   "sugar FLOAT,"
                   "protein FLOAT,"
                   "biotin FLOAT,"
                   "calcium FLOAT,"
                   "chromium FLOAT,"
                   "copper FLOAT,"
                   "folacin FLOAT,"
                   "iodide FLOAT,"
                   "iron FLOAT,"
                   "magnesium FLOAT,"
                   "manganese FLOAT,"
                   "molybdenum FLOAT,"
                   "niacin FLOAT,"
                   "pantothenate FLOAT,"
                   "phosphorous FLOAT,"
                   "potassium FLOAT,"
                   "riboflavin FLOAT,"
                   "selenium FLOAT,"
                   "thiamine FLOAT,"
                   "vitamin_a FLOAT,"
                   "vitamin_b6 FLOAT,"
                   "vitamin_b12 FLOAT,"
                   "vitamin_c FLOAT,"
                   "vitamin_d FLOAT,"
                   "vitamin_e FLOAT,"
                   "zinc FLOAT)");

        DatabaseManager::queryStatus(query);
    }
}

void FoodDAO::addFood(Food &food) const {
    QSqlQuery query(mDatabase);

    query.prepare("INSERT INTO foods ("
                               "name,"
                               "category,"
                               "serving_size,"
                               "unit_of_measure,"
                               "fat, "
                               "saturated_fat,"
                               "trans_fat, "
                               "unsaturated_fat,"
                               "cholesterol,"
                               "sodium,"
                               "carbs,"
                               "fibre,"
                               "sugar,"
                               "protein,"
                               "biotin,"
                               "calcium,"
                               "chromium,"
                               "copper,"
                               "folacin,"
                               "iodide,"
                               "iron,"
                               "magnesium,"
                               "manganese,"
                               "molybdenum,"
                               "niacin,"
                               "pantothenate,"
                               "phosphorous,"
                               "potassium,"
                               "riboflavin,"
                               "selenium,"
                               "thiamine,"
                               "vitamin_a,"
                               "vitamin_b6,"
                               "vitamin_b12,"
                               "vitamin_c,"
                               "vitamin_d,"
                               "vitamin_e,"
                               "zinc) VALUES ("
                               ":name,"
                               ":category,"
                               ":serving_size,"
                               ":unit_of_measure,"
                               ":fat,"
                              ":saturated_fat,"
                              ":trans_fat, "
                              ":unsaturated_fat,"
                              ":cholesterol,"
                              ":sodium,"
                              ":carbs,"
                              ":fibre,"
                              ":sugar,"
                              ":protein,"
                              ":biotin,"
                              ":calcium,"
                              ":chromium,"
                              ":copper,"
                              ":folacin,"
                              ":iodide,"
                              ":iron,"
                              ":magnesium,"
                              ":manganese,"
                              ":molybdenum,"
                              ":niacin,"
                              ":pantothenate,"
                              ":phosphorous,"
                              ":potassium,"
                              ":riboflavin,"
                              ":selenium,"
                              ":thiamine,"
                              ":vitamin_a,"
                              ":vitamin_b6,"
                              ":vitamin_b12,"
                              ":vitamin_c,"
                              ":vitamin_d,"
                              ":vitamin_e,"
                              ":zinc)");

    query.bindValue(":name", food.getName());
    query.bindValue(":category", food.getCategory());
    query.bindValue(":serving_size", QVariant(food.getServingSize()));
    query.bindValue(":unit_of_measure", food.getServingMeasurement());
    query.bindValue(":fat", QVariant(food.getFat()));
    query.bindValue(":saturated_fat", food.getSaturatedFat());
    query.bindValue(":trans_fat", food.getTransFat());
    query.bindValue(":unsaturated_fat", food.getUnsaturatedFat());
    query.bindValue(":cholesterol", food.getCholesterol());
    query.bindValue(":sodium", food.getSodium());
    query.bindValue(":carbs", food.getCarbs());
    query.bindValue(":fibre", food.getFibre());
    query.bindValue(":sugar", food.getSugar());
    query.bindValue(":protein", food.getProtein());
    query.bindValue(":biotin", food.getBiotin());
    query.bindValue(":calcium", food.getCalcium());
    query.bindValue(":chromium", food.getChromium());
    query.bindValue(":copper", food.getCopper());
    query.bindValue(":folacin", food.getFolacin());
    query.bindValue(":iodide", food.getIodide());
    query.bindValue(":iron", food.getIron());
    query.bindValue(":magnesium", food.getMagnesium());
    query.bindValue(":manganese", food.getManganese());
    query.bindValue(":molybdenum", food.getMolybdenum());
    query.bindValue(":niacin", food.getNiacin());
    query.bindValue(":pantothenate", food.getPantothenate());
    query.bindValue(":phosphorous", food.getPhosphorous());
    query.bindValue(":potassium", food.getPotassium());
    query.bindValue(":riboflavin", food.getRiboflavin());
    query.bindValue(":selenium", food.getSelenium());
    query.bindValue(":thiamine", food.getThiamine());
    query.bindValue(":vitamin_a", food.getVitaminA());
    query.bindValue(":vitamin_b6", food.getVitaminB6());
    query.bindValue(":vitamin_b12", food.getVitaminB12());
    query.bindValue(":vitamin_c", food.getVitaminC());
    query.bindValue(":vitamin_d", food.getVitaminD());
    query.bindValue(":vitamin_e", food.getVitaminE());
    query.bindValue(":zinc", food.getZinc());

    query.exec();

    DatabaseManager::queryStatus(query);
}

Food FoodDAO::getFood(const QString &name) const {
    QSqlQuery query(mDatabase);
    query.prepare("SELECT * FROM foods WHERE name = :name LIMIT 1");
    query.bindValue(":name", name);
    query.exec();

    DatabaseManager::queryStatus(query);

    // TODO: if query.next() returns whatever, return an empty Food object
    query.next();

    Food food;

    food.setName(query.value("name").toString());
    food.setCategory(query.value("category").toString());
    food.setServingSize(0);
    food.setServingMeasurement(query.value("unit_of_measure").toString());
    food.setFat(query.value("fat").toFloat());
    food.setSaturatedFat(query.value("saturated_fat").toFloat());
    food.setTransFat(query.value("trans_fat").toFloat());
    food.setUnsaturatedFat(query.value("unsaturated_fat").toFloat());
    food.setCholesterol(query.value("cholesterol").toFloat());
    food.setSodium(query.value("sodium").toFloat());
    food.setCarbs(query.value("carbs").toFloat());
    food.setFibre(query.value("fibre").toFloat());
    food.setSugar(query.value("sugar").toFloat());
    food.setProtein(query.value("protein").toFloat());
    food.setBiotin(query.value("biotin").toFloat());
    food.setCalcium(query.value("calcium").toFloat());
    food.setChromium(query.value("chromium").toFloat());
    food.setCopper(query.value("copper").toFloat());
    food.setFolacin(query.value("folacin").toFloat());
    food.setIodide(query.value("iodide").toFloat());
    food.setIron(query.value("iron").toFloat());
    food.setMagnesium(query.value("magnesium").toFloat());
    food.setManganese(query.value("manganese").toFloat());
    food.setMolybenum(query.value("molybdenum").toFloat());
    food.setNiacin(query.value("niacin").toFloat());
    food.setPantothenate(query.value("pantothenate").toFloat());
    food.setPhosphorous(query.value("phosphorous").toFloat());
    food.setPotassium(query.value("potassium").toFloat());
    food.setRiboflavin(query.value("riboflavin").toFloat());
    food.setSelenium(query.value("selenium").toFloat());
    food.setThiamine(query.value("thiamine").toFloat());
    food.setVitaminA(query.value("vitamin_a").toFloat());
    food.setVitaminB6(query.value("vitamin_b6").toFloat());
    food.setVitaminB12(query.value("vitamin_b12").toFloat());
    food.setVitaminC(query.value("vitamin_c").toFloat());
    food.setVitaminD(query.value("vitamin_d").toFloat());
    food.setVitaminE(query.value("vitamin_e").toFloat());
    food.setZinc(query.value("zinc").toFloat());

    return food;
}

Food FoodDAO::getFood(const QString& name, float servingSize) const {
    Food food = getFood(name);

    if (servingSize < food.getServingSize()) {
        servingSize = food.getServingSize() / servingSize;
    }

    food.setFat(food.getFat() * servingSize);
    food.setSaturatedFat(food.getSaturatedFat() * servingSize);
    food.setTransFat(food.getTransFat() * servingSize);
    food.setUnsaturatedFat(food.getUnsaturatedFat() * servingSize);

    food.setCholesterol(food.getCholesterol() * servingSize);
    food.setSodium(food.getSodium() * servingSize);

    food.setCarbs(food.getCarbs() * servingSize);
    food.setFibre(food.getFibre() * servingSize);
    food.setSugar(food.getSugar() * servingSize);

    food.setProtein(food.getProtein() * servingSize);

    food.setBiotin(food.getBiotin() * servingSize);
    food.setCalcium(food.getCalcium() * servingSize);
    food.setChromium(food.getChromium() * servingSize);
    food.setCopper(food.getCopper() * servingSize);
    food.setFolacin(food.getFolacin() * servingSize);
    food.setIodide(food.getIodide() * servingSize);
    food.setIron((food.getIron() * servingSize));
    food.setMagnesium(food.getMagnesium() * servingSize);
    food.setManganese(food.getManganese() * servingSize);
    food.setMolybenum(food.getMolybdenum() * servingSize);
    food.setNiacin(food.getNiacin() * servingSize);
    food.setPantothenate(food.getPantothenate() * servingSize);
    food.setPhosphorous(food.getPhosphorous() * servingSize);
    food.setPotassium(food.getPotassium() * servingSize);
    food.setRiboflavin(food.getRiboflavin() * servingSize);
    food.setSelenium(food.getSelenium() * servingSize);
    food.setThiamine(food.getThiamine() * servingSize);
    food.setVitaminA(food.getVitaminA() * servingSize);
    food.setVitaminB6(food.getVitaminB6() * servingSize);
    food.setVitaminB12(food.getVitaminB12() * servingSize);
    food.setVitaminC(food.getVitaminC() * servingSize);
    food.setVitaminD(food.getVitaminD() * servingSize);
    food.setVitaminE(food.getVitaminE() * servingSize);
    food.setZinc(food.getZinc() * servingSize);

    return food;
}

QStringList* FoodDAO::getFoodNames(const QString &category) const {
    QSqlQuery query(mDatabase);
    query.prepare("SELECT * FROM foods WHERE category = :category");
    query.bindValue(":category", category);
    query.exec();

    DatabaseManager::queryStatus(query);

    QStringList* foodList = new QStringList;

    while (query.next()) {
        foodList->push_back(query.value("name").toString() + " --- " + query.value("unit_of_measure").toString());
    }

    return foodList;
}
