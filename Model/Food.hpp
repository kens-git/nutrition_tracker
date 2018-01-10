#ifndef FOOD_HPP
#define FOOD_HPP

#include <QString>

#include "model_global.h"

class MODELSHARED_EXPORT Food {
    public:
        Food() = default;

        void setName(const QString& name) { mName = name; }
        QString getName() const { return mName; }
        void setCategory(const QString& category) { mCategory = category; }
        QString getCategory() const { return mCategory; }

        void setServingSize(float size) { mServingSize = size; }
        float getServingSize() const { return mServingSize; }
        void setServingMeasurement(const QString& measurement) { mServingMeasurement = measurement; }
        QString getServingMeasurement() const { return mServingMeasurement; }

        virtual float getCalories() const { return (mFat * 9.0f) + (mCarbs * 4.0f) + (mProtein * 4.0f); }

        void setFat(float fat) { mFat = fat; }
        float getFat() const { return mFat; }
        void setSaturatedFat(float saturated) { mSaturatedFat = saturated; }
        float getSaturatedFat() const { return mSaturatedFat; }
        void setTransFat(float trans) { mTransFat = trans; }
        float getTransFat() const { return mTransFat; }
        void setUnsaturatedFat(float unsaturated) { mUnsaturatedFat = unsaturated; }
        float getUnsaturatedFat() const { return mUnsaturatedFat; }

        void setCholesterol(float cholesterol) { mCholesterol = cholesterol; }
        float getCholesterol() const { return mCholesterol; }
        void setSodium(float sodium) { mSodium = sodium; }
        float getSodium() const { return mSodium; }

        void setCarbs(float carbs) { mCarbs = carbs; }
        float getCarbs() const { return mCarbs; }
        void setFibre(float fibre) { mFibre = fibre; }
        float getFibre() const { return mFibre; }
        void setSugar(float sugar) { mSugar = sugar; }
        float getSugar() const { return mSugar; }

        void setProtein(float protein) { mProtein = protein; }
        float getProtein() const { return mProtein; }

        void setBiotin(float biotin) { mBiotin = biotin; }
        float getBiotin() const { return mBiotin; }
        void setCalcium(float calcium) { mCalcium = calcium; }
        float getCalcium() const { return mCalcium; }
        void setChromium(float chromium) { mChromium = chromium; }
        float getChromium() const { return mChromium; }
        void setCopper(float copper) { mCopper = copper; }
        float getCopper() const { return mCopper; }
        void setFolacin(float folacin) { mFolacin = folacin; }
        float getFolacin() const { return mFolacin; }
        void setIodide(float iodide) { mIodide = iodide; }
        float getIodide() const { return mIodide; }
        void setIron(float iron) { mIron = iron; }
        float getIron() const { return mIron; }
        void setMagnesium(float magnesium) { mMagnesium = magnesium; }
        float getMagnesium()  const { return mMagnesium; }
        void setManganese(float manganese) { mManganese = manganese; }
        float getManganese() const { return mManganese; }
        void setMolybenum(float molybdenum) { mMolybdenum = molybdenum; }
        float getMolybdenum() const { return mMolybdenum; }
        void setNiacin(float niacin) { mNiacin = niacin; }
        float getNiacin() const { return mNiacin; }
        void setPantothenate(float pantothenate) { mPantothenate = pantothenate; }
        float getPantothenate() const { return mPantothenate; }
        void setPhosphorous(float phosphorous) { mPhosphorous = phosphorous; }
        float getPhosphorous() const { return mPhosphorous; }
        void setPotassium(float potassium) { mPotassium = potassium; }
        float getPotassium() const { return mPotassium; }
        void setRiboflavin(float riboflavin) { mRiboflavin = riboflavin; }
        float getRiboflavin() const { return mRiboflavin; }
        void setSelenium(float selenium) { mSelenium = selenium; }
        float getSelenium() const { return mSelenium; }
        void setThiamine(float thiamine) { mThiamine = thiamine; }
        float getThiamine() const { return mThiamine; }
        void setVitaminA(float vitaminA) { mVitaminA = vitaminA; }
        float getVitaminA() const { return mVitaminA; }
        void setVitaminB6(float vitaminB6) { mVitaminB6 = vitaminB6; }
        float getVitaminB6() const { return mVitaminB6; }
        void setVitaminB12(float vitaminB12) { mVitaminB12 = vitaminB12; }
        float getVitaminB12() const { return mVitaminB12; }
        void setVitaminC(float vitaminC) { mVitaminC = vitaminC; }
        float getVitaminC() const { return mVitaminC; }
        void setVitaminD(float vitaminD) { mVitaminD = vitaminD; }
        float getVitaminD() const { return mVitaminD; }
        void setVitaminE(float vitaminE) { mVitaminE = vitaminE; }
        float getVitaminE() const { return mVitaminE; }
        void setZinc(float zinc) { mZinc = zinc; }
        float getZinc() const { return mZinc; }

    protected:
        QString mName = "Name not set";
        QString mCategory = "category not set";

        float mServingSize = 0;
        QString mServingMeasurement = "unit of measure not set";

        float mFat = 0;
        float mSaturatedFat = 0;
        float mTransFat = 0;
        float mUnsaturatedFat = 0;

        float mCholesterol = 0;
        float mSodium = 0;

        float mCarbs = 0;
        float mFibre = 0;
        float mSugar = 0;

        float mProtein = 0;

        float mBiotin = 0;
        float mCalcium = 0;
        float mChromium = 0;
        float mCopper = 0;
        float mFolacin = 0;
        float mIodide = 0;
        float mIron = 0;
        float mMagnesium = 0;
        float mManganese = 0;
        float mMolybdenum = 0;
        float mNiacin = 0;
        float mPantothenate = 0;
        float mPhosphorous = 0;
        float mPotassium = 0;
        float mRiboflavin = 0; // aka Vitamin B2
        float mSelenium = 0;
        float mThiamine = 0;
        float mVitaminA = 0;
        float mVitaminB6 = 0;
        float mVitaminB12 = 0;
        float mVitaminC = 0;
        float mVitaminD = 0;
        float mVitaminE = 0;
        float mZinc = 0;
};

#endif // FOOD_HPP
