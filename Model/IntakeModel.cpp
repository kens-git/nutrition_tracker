#include "IntakeModel.hpp"

#include <QDate>

#include "DatabaseManager.hpp"

IntakeModel::IntakeModel(QObject* parent)
    : QAbstractTableModel(parent),
      mDatabase(DatabaseManager::instance())
{
    QDate today = QDate::currentDate();
    mIntake = mDatabase.mIntakeDAO.getIntake(today);

    mTotal = new Food();
    mTotal->setName("Total");
    mTotal->setCategory("Total");
    mTotal->setServingSize(1);
}

QVariant IntakeModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid()) {
        return QVariant();
    }

    if (role == Qt::DisplayRole) {
        if (index.column() == 0) {
            return mIntake->at(index.row()).getName();
        }
        else if (index.column() == 1) {
            return mIntake->at(index.row()).getCategory();
        }
        else if (index.column() == 2) {
            return mIntake->at(index.row()).getServingMeasurement();
        }
        else if (index.column() == 3) {
            return mIntake->at(index.row()).getServingSize();
        }
        else if (index.column() == 4) {
            return mIntake->at(index.row()).getCalories();
        }
        else if (index.column() == 5) {
            return mIntake->at(index.row()).getFat();
        }
        else if (index.column() == 6) {
            return mIntake->at(index.row()).getSaturatedFat();
        }
        else if (index.column() == 7) {
            return mIntake->at(index.row()).getTransFat();
        }
        else if (index.column() == 8) {
            return mIntake->at(index.row()).getUnsaturatedFat();
        }
        else if (index.column() == 9) {
            return mIntake->at(index.row()).getCholesterol();
        }
        else if (index.column() == 10) {
            return mIntake->at(index.row()).getSodium();
        }
        else if (index.column() == 11) {
            return mIntake->at(index.row()).getCarbs();
        }
        else if (index.column() == 12) {
            return mIntake->at(index.row()).getFibre();
        }
        else if (index.column() == 13) {
            return mIntake->at(index.row()).getSugar();
        }
        else if (index.column() == 14) {
            return mIntake->at(index.row()).getProtein();
        }
        else if (index.column() == 15) {
            return mIntake->at(index.row()).getBiotin();
        }
        else if (index.column() == 16) {
            return mIntake->at(index.row()).getCalcium();
        }
        else if (index.column() == 17) {
            return mIntake->at(index.row()).getChromium();
        }
        else if (index.column() == 18) {
            return mIntake->at(index.row()).getCopper();
        }
        else if (index.column() == 19) {
            return mIntake->at(index.row()).getFolacin();
        }
        else if (index.column() == 20) {
            return mIntake->at(index.row()).getIodide();
        }
        else if (index.column() == 21) {
            return mIntake->at(index.row()).getIron();
        }
        else if (index.column() == 22) {
            return mIntake->at(index.row()).getMagnesium();
        }
        else if (index.column() == 23) {
            return mIntake->at(index.row()).getManganese();
        }
        else if (index.column() == 24) {
            return mIntake->at(index.row()).getMolybdenum();
        }
        else if (index.column() == 25) {
            return mIntake->at(index.row()).getNiacin();
        }
        else if (index.column() == 26) {
            return mIntake->at(index.row()).getPantothenate();
        }
        else if (index.column() == 27) {
            return mIntake->at(index.row()).getPhosphorous();
        }
        else if (index.column() == 28) {
            return mIntake->at(index.row()).getPotassium();
        }
        else if (index.column() == 29) {
            return mIntake->at(index.row()).getRiboflavin();
        }
        else if (index.column() == 30) {
            return mIntake->at(index.row()).getSelenium();
        }
        else if (index.column() == 31) {
            return mIntake->at(index.row()).getThiamine();
        }
        else if (index.column() == 32) {
            return mIntake->at(index.row()).getVitaminA();
        }
        else if (index.column() == 33) {
            return mIntake->at(index.row()).getVitaminB6();
        }
        else if (index.column() == 34) {
            return mIntake->at(index.row()).getVitaminB12();
        }
        else if (index.column() == 35) {
            return mIntake->at(index.row()).getVitaminC();
        }
        else if (index.column() == 36) {
            return mIntake->at(index.row()).getVitaminD();
        }
        else if (index.column() == 37) {
            return mIntake->at(index.row()).getVitaminE();
        }
        else if (index.column() == 38) {
            return mIntake->at(index.row()).getZinc();
        }
    }

    return QVariant();
}

int IntakeModel::rowCount(const QModelIndex &parent) const {
    return mIntake->size();
}

int IntakeModel::columnCount(const QModelIndex &parent) const {
    return NUM_COLUMNS;
}

QVariant IntakeModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole) {
        return QVariant();
    }

    if (orientation == Qt::Horizontal) {
        if (section == 0) {
            return "Food Name";
        }
        else if (section == 1) {
            return "Category";
        }
        else if (section == 2) {
            return "Unit of Measure";
        }
        else if (section == 3) {
            return "Serving Size";
        }
        else if (section == 4) {
            return "Calories";
        }
        else if (section == 5) {
            return "Fat (g)";
        }
        else if (section == 6) {
            return "Saturated Fat (g)";
        }
        else if (section == 7) {
            return "Trans Fat (g)";
        }
        else if (section == 8) {
            return "Unsaturated Fat (g)";
        }
        else if (section == 9) {
            return "Cholesterol (mg)";
        }
        else if (section == 10) {
            return "Sodium (mg)";
        }
        else if (section == 11) {
            return "Carbs (g)";
        }
        else if (section == 12) {
            return "Fibre (g)";
        }
        else if (section == 13) {
            return "Sugar (g)";
        }
        else if (section == 14) {
            return "Protein (g)";
        }
        else if (section == 15) {
            return "Biotin (ug)";
        }
        else if (section == 16) {
            return "Calcium (mg)";
        }
        else if (section == 17) {
            return "Chromium (ug)";
        }
        else if (section == 18) {
            return "Copper (mg)";
        }
        else if (section == 19) {
            return "Folacin (ug)";
        }
        else if (section == 20) {
            return "Iodide (ug)";
        }
        else if (section == 21) {
            return "Iron (mg)";
        }
        else if (section == 22) {
            return "Magnesium (mg)";
        }
        else if (section == 23) {
            return "Manganese (mg)";
        }
        else if (section == 24) {
            return "Molybdenum (ug)";
        }
        else if (section == 25) {
            return "Niacin (NE)";
        }
        else if (section == 26) {
            return "Pantothenate (mg)";
        }
        else if (section == 27) {
            return "Phosphorous (mg)";
        }
        else if (section == 28) {
            return "Potassium (mg)";
        }
        else if (section == 29) {
            return "Riboflavin (mg)";
        }
        else if (section == 30) {
            return "Selenium (ug)";
        }
        else if (section == 31) {
            return "Thiamine (mg)";
        }
        else if (section == 32) {
            return "Vitamin A (RE)";
        }
        else if (section == 33) {
            return  "Vitamin B6 (mg)";
        }
        else if (section == 34) {
            return "Vitamin B12 (ug)";
        }
        else if (section == 35) {
            return "Vitamin C (mg)";
        }
        else if (section == 36) {
            return "Vitamin D (ug)";
        }
        else if (section == 37) {
            return "Vitamin E (mg)";
        }
        else if (section == 38) {
            return "Zinc (mg)";
        }
    }

    return QVariant();
}

Qt::ItemFlags IntakeModel::flags(const QModelIndex &index) const {
    return Qt::ItemIsEnabled;
}

void IntakeModel::addIntake(const QString& foodName, float servingSize, const QDate& date) {
    Food intake = mDatabase.mFoodDAO.getFood(foodName, servingSize);
    intake.setServingSize(servingSize);

    beginInsertRows(QModelIndex(), mIntake->size() - 1, mIntake->size() - 1);
    mDatabase.mIntakeDAO.addIntake(intake, date);
    mIntake->push_back(intake);
    endInsertRows();

    updateTotal();
}

void IntakeModel::dateChanged(QDate &date) {
    beginRemoveRows(QModelIndex(), 0, mIntake->size() - 1);
    endRemoveRows();

    delete mIntake;
    mIntake = mDatabase.mIntakeDAO.getIntake(date);

    beginInsertRows(QModelIndex(), 0, mIntake->size() - 1);
    endInsertRows();

    updateTotal();
}

void IntakeModel::updateTotal() {
    if (mIntake->size() > 0) {
        // if mIntake is deleted in dateChanged(), then the first element won't be total,
        // so check that it exists before trying to remove it
        if (mIntake->front().getCategory() == "Total") {
            beginRemoveRows(QModelIndex(), 0, 0);
            mIntake->pop_front();
            endRemoveRows();
        }

        delete mTotal;
        mTotal = new Food();
        mTotal->setName("Total");
        mTotal->setCategory("Total");
        mTotal->setServingMeasurement("");
        mTotal->setServingSize(1);

        foreach (const Food& food, *mIntake) {
            mTotal->setFat(mTotal->getFat() + food.getFat());
            mTotal->setSaturatedFat(mTotal->getSaturatedFat() + food.getSaturatedFat());
            mTotal->setTransFat(mTotal->getTransFat() + food.getTransFat());
            mTotal->setUnsaturatedFat(mTotal->getUnsaturatedFat() + food.getUnsaturatedFat());

            mTotal->setCholesterol(mTotal->getCholesterol() + food.getCholesterol());
            mTotal->setSodium(mTotal->getSodium() + food.getSodium());

            mTotal->setCarbs(mTotal->getCarbs() + food.getCarbs());
            mTotal->setFibre(mTotal->getFibre() + food.getFibre());
            mTotal->setSugar(mTotal->getSugar() + food.getSugar());

            mTotal->setProtein(mTotal->getProtein() + food.getProtein());

            mTotal->setBiotin(mTotal->getBiotin() + food.getBiotin());
            mTotal->setCalcium(mTotal->getCalcium() + food.getCalcium());
            mTotal->setChromium(mTotal->getChromium() + food.getChromium());
            mTotal->setCopper(mTotal->getCopper() + food.getCopper());
            mTotal->setFolacin(mTotal->getFolacin() + food.getFolacin());
            mTotal->setIodide(mTotal->getIodide() + food.getIodide());
            mTotal->setIron(mTotal->getIron() + food.getIron());
            mTotal->setMagnesium(mTotal->getMagnesium() + food.getMagnesium());
            mTotal->setManganese(mTotal->getManganese() + food.getManganese());
            mTotal->setMolybenum(mTotal->getMolybdenum() + food.getMolybdenum());
            mTotal->setNiacin(mTotal->getNiacin() + food.getNiacin());
            mTotal->setPantothenate(mTotal->getPantothenate() + food.getPantothenate());
            mTotal->setPhosphorous(mTotal->getPhosphorous() + food.getPhosphorous());
            mTotal->setPotassium(mTotal->getPotassium() + food.getPotassium());
            mTotal->setRiboflavin(mTotal->getRiboflavin() + food.getRiboflavin());
            mTotal->setSelenium(mTotal->getSelenium() + food.getSelenium());
            mTotal->setThiamine(mTotal->getThiamine() + food.getThiamine());
            mTotal->setVitaminA(mTotal->getVitaminA() + food.getVitaminA());
            mTotal->setVitaminB6(mTotal->getVitaminB6() + food.getVitaminB6());
            mTotal->setVitaminB12(mTotal->getVitaminB12() + food.getVitaminB12());
            mTotal->setVitaminC(mTotal->getVitaminC() + food.getVitaminC());
            mTotal->setVitaminD(mTotal->getVitaminD() + food.getVitaminD());
            mTotal->setVitaminE(mTotal->getVitaminE() + food.getVitaminE());
            mTotal->setZinc(mTotal->getZinc() + food.getZinc());
        }

        beginInsertRows(QModelIndex(), 0, 0);
        mIntake->push_front(*mTotal);
        endInsertRows();
    }
}

Food IntakeModel::getDailyTotal() {
    if (mIntake->size() > 0) {
        return *mTotal;
    } else {
        // mTotal is only updated when mIntake is successfully set, so return a default
        // Food as the daily total
        //
        // This is really only required to set the progress bars properly
        return Food();
    }
}
