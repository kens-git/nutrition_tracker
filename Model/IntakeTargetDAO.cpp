#include "IntakeTargetDAO.hpp"

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QVariant>

#include "DatabaseManager.hpp"
#include "IntakeTarget.hpp"

IntakeTargetDAO::IntakeTargetDAO(QSqlDatabase& database)
    : mDatabase(database)
{

}

void IntakeTargetDAO::init() const {
    if (!mDatabase.tables().contains("target")) {
        QSqlQuery query(mDatabase);

        query.exec("CREATE TABLE target ("
                   "id INTEGER,"
                   "fat FLOAT,"
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

        QSqlQuery defaultIntake(mDatabase);

        defaultIntake.exec("INSERT INTO target ("
                      "id,"
                      "fat,"
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
                      "1,"
                       "0,"
                       "0,"
                       "0,"
                       "0,"
                       "0,"
                       "0,"
                       "0,"
                       "0,"
                       "0,"
                       "0,"
                       "0,"
                       "0,"
                       "0,"
                       "0,"
                       "0,"
                       "0,"
                       "0,"
                       "0,"
                       "0,"
                       "0,"
                       "0,"
                       "0,"
                       "0,"
                       "0,"
                       "0,"
                       "0,"
                       "0,"
                       "0,"
                       "0,"
                       "0,"
                       "0)");
        DatabaseManager::queryStatus(defaultIntake);
    }
}

void IntakeTargetDAO::setIntake(IntakeTarget &target) const {
    QSqlQuery query(mDatabase);

    query.prepare("UPDATE target SET "
                               "fat = :fat,"
                               "cholesterol = :cholesterol,"
                               "sodium = :sodium,"
                               "carbs = :carbs,"
                               "fibre = :fibre,"
                               "sugar = :sugar,"
                               "protein = :protein,"
                               "biotin = :biotin,"
                               "calcium = :calcium,"
                               "chromium = :chromium,"
                               "copper = :copper,"
                               "folacin = :folacin,"
                               "iodide = :iodide,"
                               "iron = :iron,"
                               "magnesium = :magnesium,"
                               "manganese = :manganese,"
                               "molybdenum = :molybdenum,"
                               "niacin = :niacin,"
                               "pantothenate = :pantothenate,"
                               "phosphorous = :phosphorous,"
                               "potassium = :potassium,"
                               "riboflavin = :riboflavin,"
                               "selenium = :selenium,"
                               "thiamine = :thiamine,"
                               "vitamin_a = :vitamin_a,"
                               "vitamin_b6 = :vitamin_b6,"
                               "vitamin_b12 = :vitamin_b12,"
                               "vitamin_c = :vitamin_c,"
                               "vitamin_d = :vitamin_d,"
                               "vitamin_e = :vitamin_e,"
                               "zinc = :zinc WHERE id = 1");

    query.bindValue(":fat", target.getFat());
    query.bindValue(":cholesterol", target.getCholesterol());
    query.bindValue(":sodium", target.getSodium());
    query.bindValue(":carbs", target.getCarbs());
    query.bindValue(":fibre", target.getFibre());
    query.bindValue(":sugar", target.getSugar());
    query.bindValue(":protein", target.getProtein());
    query.bindValue(":biotin", target.getBiotin());
    query.bindValue(":calcium", target.getCalcium());
    query.bindValue(":chromium", target.getChromium());
    query.bindValue(":copper", target.getCopper());
    query.bindValue(":folacin", target.getFolacin());
    query.bindValue(":iodide", target.getIodide());
    query.bindValue(":iron", target.getIron());
    query.bindValue(":magnesium", target.getMagnesium());
    query.bindValue(":manganese", target.getManganese());
    query.bindValue(":molybdenum", target.getMolybdenum());
    query.bindValue(":niacin", target.getNiacin());
    query.bindValue(":pantothenate", target.getPantothenate());
    query.bindValue(":phosphorous", target.getPhosphorous());
    query.bindValue(":potassium", target.getPotassium());
    query.bindValue(":riboflavin", target.getRiboflavin());
    query.bindValue(":selenium", target.getSelenium());
    query.bindValue(":thiamine", target.getThiamine());
    query.bindValue(":vitamin_a", target.getVitaminA());
    query.bindValue(":vitamin_b6", target.getVitaminB6());
    query.bindValue(":vitamin_b12", target.getVitaminB12());
    query.bindValue(":vitamin_c", target.getVitaminC());
    query.bindValue(":vitamin_d", target.getVitaminD());
    query.bindValue(":vitamin_e", target.getVitaminE());
    query.bindValue(":zinc", target.getZinc());

    query.exec();

    DatabaseManager::queryStatus(query);
}

IntakeTarget IntakeTargetDAO::getIntake() const {
    IntakeTarget target;

    QSqlQuery query(mDatabase);

    query.exec("SELECT * FROM target WHERE id = 1");
    DatabaseManager::queryStatus(query);

    query.next();
    target.setFat(query.value("fat").toFloat());
    target.setCholesterol(query.value("cholesterol").toFloat());
    target.setSodium(query.value("sodium").toFloat());
    target.setCarbs(query.value("carbs").toFloat());
    target.setFibre(query.value("fibre").toFloat());
    target.setSugar(query.value("sugar").toFloat());
    target.setProtein(query.value("protein").toFloat());
    target.setBiotin(query.value("biotin").toFloat());
    target.setCalcium(query.value("calcium").toFloat());
    target.setChromium(query.value("chromium").toFloat());
    target.setCopper(query.value("copper").toFloat());
    target.setFolacin(query.value("folacin").toFloat());
    target.setIodide(query.value("iodide").toFloat());
    target.setIron(query.value("iron").toFloat());
    target.setMagnesium(query.value("magnesium").toFloat());
    target.setManganese(query.value("manganese").toFloat());
    target.setMolybenum(query.value("molybdenum").toFloat());
    target.setNiacin(query.value("niacin").toFloat());
    target.setPantothenate(query.value("pantothenate").toFloat());
    target.setPhosphorous(query.value("phosphorous").toFloat());
    target.setPotassium(query.value("potassium").toFloat());
    target.setRiboflavin(query.value("riboflavin").toFloat());
    target.setSelenium(query.value("selenium").toFloat());
    target.setThiamine(query.value("thiamine").toFloat());
    target.setVitaminA(query.value("vitamin_a").toFloat());
    target.setVitaminB6(query.value("vitamin_b6").toFloat());
    target.setVitaminB12(query.value("vitamin_b12").toFloat());
    target.setVitaminC(query.value("vitamin_c").toFloat());
    target.setVitaminD(query.value("vitamin_d").toFloat());
    target.setVitaminE(query.value("vitamin_e").toFloat());
    target.setZinc(query.value("zinc").toFloat());

    return target;
}
