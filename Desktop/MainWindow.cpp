#include "MainWindow.hpp"
#include "ui_MainWindow.h"

#include <QMessageBox>

#include "Food.hpp"
#include "FoodModel.hpp"
#include "CategoryModel.hpp"
#include "IntakeTargetModel.hpp"
#include "IntakeTarget.hpp"
#include "IntakeModel.hpp"

#include <QDate>

// TODO: break up the widgets into separate files so this file isn't so long
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mFoodModel(new FoodModel),
    mCategoryModel(new CategoryModel),
    mIntakeTargetModel(new IntakeTargetModel),
    mIntakeModel(new IntakeModel)
{
    ui->setupUi(this);

    ui->categoryComboBox->setModel(mCategoryModel);
    ui->intakeCategoryComboBox->setModel(mCategoryModel);
    ui->intakeTableView->setModel(mIntakeModel);

    connect(ui->submitNewFoodButton, &QPushButton::clicked, this, &MainWindow::addNewFood);
    connect(ui->tabWidget, &QTabWidget::tabBarClicked, this, &MainWindow::tabSelected);
    connect(ui->intakeCategoryComboBox, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this, &MainWindow::categorySelected);
    connect(ui->submitTargetButton, &QPushButton::clicked, this, &MainWindow::targetIntakeSubmitted);
    connect(ui->submitIntakeButton, &QPushButton::clicked, this, &MainWindow::intakeSubmitted);
    connect(ui->yearSpinBox, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this, &MainWindow::dateChanged);
    connect(ui->monthComboBox, static_cast<void(QComboBox::*)(int)>(&QComboBox::currentIndexChanged),
            this, &MainWindow::dateChanged);
    connect(ui->daySpinBox, static_cast<void(QSpinBox::*)(int)>(&QSpinBox::valueChanged),
            this, &MainWindow::dateChanged);

    QStringList months = { "January", "February", "March", "April", "May", "June", "July", "August",
                           "Septemeber", "October", "November", "December" };
    ui->monthComboBox->addItems(months);
    ui->monthComboBox->setCurrentIndex(QDate::currentDate().month() - 1);
    ui->daySpinBox->setValue(QDate::currentDate().day());
    ui->yearSpinBox->setValue(QDate::currentDate().year());

    mFoodModel->getFoods(mCategoryModel->index(0).data().toString());
    ui->foodNameComboBox->setModel(mFoodModel);

    setProgressBarsMaxValue();
    updateProgressBars();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addNewFood() {
    Food food;

    // TODO: error checks to make sure the QString.toFloat() functions aren't operating on non-numeric characters
    if (ui->foodNameLineEdit->text().isEmpty()) {
        showInputError("Food name is required.");
        return;
    } else {
        food.setName(ui->foodNameLineEdit->text());
    }

    if (ui->categoryComboBox->currentText() == "") {
        showInputError("Food category is required.");
        return;
    } else {
        food.setCategory(ui->categoryComboBox->currentText());
    }

    if (ui->servingSizeLineEdit->text() == "") {
        showInputError("Serving size is required.");
        return;
    } else {
        food.setServingSize(ui->servingSizeLineEdit->text().toFloat());
    }

    if (ui->unitOfMeasureLineEdit->text() == "") {
        showInputError("Serving unit of measure is required.");
        return;
    } else {
        food.setServingMeasurement(ui->unitOfMeasureLineEdit->text());
    }

    if (ui->fatLineEdit->text() != "") {
        food.setFat(ui->fatLineEdit->text().toFloat());
    } else {
        food.setFat(0);
    }

    if (ui->saturatedLineEdit->text() != "") {
        food.setSaturatedFat(ui->saturatedLineEdit->text().toFloat());
    } else {
        food.setSaturatedFat(0);
    }

    if (ui->transLineEdit->text() != "") {
        food.setTransFat(ui->transLineEdit->text().toFloat());
    } else {
        food.setTransFat(0);
    }

    // Calculate unsaturated fats
    if (food.getFat() != 0) {
        food.setUnsaturatedFat(food.getFat() - food.getSaturatedFat() - food.getTransFat());
    } else {
        food.setUnsaturatedFat(0);
    }

    if (ui->cholesterolLineEdit->text() != "") {
        food.setCholesterol(ui->cholesterolLineEdit->text().toFloat());
    } else {
        food.setCholesterol(0);
    }

    if (ui->sodiumLineEdit->text() != "") {
        food.setSodium(ui->sodiumLineEdit->text().toFloat());
    } else {
        food.setSodium(0);
    }

    if (ui->carbsLineEdit->text() != "") {
        food.setCarbs(ui->carbsLineEdit->text().toFloat());
    } else {
        food.setCarbs(0);
    }

    if (ui->fibreLineEdit->text() != "") {
        food.setFibre(ui->fibreLineEdit->text().toFloat());
    } else {
        food.setFibre(0);
    }

    if (ui->sugarLineEdit->text() != "") {
        food.setSugar(ui->sugarLineEdit->text().toFloat());
    } else {
        food.setSugar(0);
    }

    if (ui->proteinLineEdit->text() != "") {
        food.setProtein(ui->proteinLineEdit->text().toFloat());
    } else {
        food.setProtein(0);
    }


    // Micronutrients
    // The absolute values (mg, ug, etc.) are being stored in the DB, so convert DV to an absolute value first
    // TODO: move the DV calculations into FoodModel
    if (ui->biotinLineEdit->text() != "") {
        if (ui->biotonDVRadioButton->isChecked()) {
            food.setBiotin((ui->biotinLineEdit->text().toFloat() / 100) * 30);
        } else {
            food.setBiotin(ui->biotinLineEdit->text().toFloat());
        }
    } else {
        food.setBiotin(0);
    }

    if (ui->calciumLineEdit->text() != "") {
        if (ui->calciumDVRadioButton->isChecked()) {
            food.setCalcium((ui->calciumLineEdit->text().toFloat() / 100) * 1100);
        } else {
            food.setCalcium(ui->calciumLineEdit->text().toFloat());
        }
    } else {
        food.setCalcium(0);
    }

    if (ui->chromiumLineEdit->text() != "") {
        if (ui->chromiumDVRadioButton->isChecked()) {
            food.setChromium((ui->chromiumLineEdit->text().toFloat() / 100) * 120);
        } else {
            food.setChromium(ui->chromiumLineEdit->text().toFloat());
        }
    } else {
        food.setChromium(0);
    }

    if (ui->copperLineEdit->text() != "") {
        if (ui->copperDVRadioButton->isChecked()) {
            food.setCopper((ui->copperLineEdit->text().toFloat() / 100) * 2);
        } else {
            food.setCopper(ui->copperLineEdit->text().toFloat());
        }
    } else {
        food.setCopper(0);
    }

    if (ui->folacinLineEdit->text() != "") {
        if (ui->folacinDVRadioButton->isChecked()) {
            food.setFolacin((ui->folacinLineEdit->text().toFloat() / 100) * 220);
        } else {
            food.setFolacin(ui->folacinLineEdit->text().toFloat());
        }
    } else {
        food.setFolacin(0);
    }

    if (ui->iodideLineEdit->text() != "") {
        if (ui->iodideDVRadioButton->isChecked()) {
            food.setIodide((ui->iodideLineEdit->text().toFloat() / 100) * 160);
        } else {
            food.setIodide(ui->iodideLineEdit->text().toFloat());
        }
    } else {
        food.setIodide(0);
    }

    if (ui->ironLineEdit->text() != "") {
        if (ui->ironDVRadioButton->isChecked()) {
            food.setIron((ui->ironLineEdit->text().toFloat() / 100) * 14);
        } else {
            food.setIron(ui->ironLineEdit->text().toFloat());
        }
    } else {
        food.setIron(0);
    }

    if (ui->magnesiumLineEdit->text() != "") {
        if (ui->magnesiumDVRadioButton->isChecked()) {
            food.setMagnesium((ui->magnesiumLineEdit->text().toFloat() / 100) * 250);
        } else {
            food.setMagnesium(ui->magnesiumLineEdit->text().toFloat());
        }
    } else {
        food.setMagnesium(0);
    }

    if (ui->manganeseLineEdit->text() != "") {
        if (ui->manganeseDVRadioButton->isChecked()) {
            food.setManganese((ui->manganeseLineEdit->text().toFloat() / 100) * 2);
        } else {
            food.setManganese(ui->manganeseLineEdit->text().toFloat());
        }
    } else {
        food.setManganese(0);
    }

    if (ui->molybdenumLineEdit->text() != "") {
        if (ui->molybdenumDVRadioButton->isChecked()) {
            food.setMolybenum((ui->molybdenumLineEdit->text().toFloat() / 100) * 75);
        } else {
            food.setMolybenum(ui->molybdenumLineEdit->text().toFloat());
        }
    } else {
        food.setMolybenum(0);
    }

    if (ui->niacinLineEdit->text() != "") {
        if (ui->niacinDVRadioButton->isChecked()) {
            food.setNiacin((ui->niacinLineEdit->text().toFloat() / 100) * 23);
        } else {
            food.setNiacin(ui->niacinLineEdit->text().toFloat());
        }
    } else {
        food.setNiacin(0);
    }

    if (ui->pantothenateLineEdit->text() != "") {
        if (ui->pantothenateDVRadioButton->isChecked()) {
            food.setPantothenate((ui->pantothenateLineEdit->text().toFloat() / 100) * 7);
        } else {
            food.setPantothenate(ui->pantothenateLineEdit->text().toFloat());
        }
    } else {
        food.setPantothenate(0);
    }

    if (ui->phosphorousLineEdit->text() != "") {
        if (ui->phosphorousDVRadioButton->isChecked()) {
            food.setPhosphorous((ui->phosphorousLineEdit->text().toFloat() / 100) * 1100);
        } else {
            food.setPhosphorous(ui->phosphorousLineEdit->text().toFloat());
        }
    } else {
        food.setPhosphorous(0);
    }

    if (ui->potassiumLineEdit->text() != "") {
        if (ui->potassiumDVRadioButton->isChecked()) {
            food.setPotassium((ui->potassiumLineEdit->text().toFloat() / 100) * 3500);
        } else {
            food.setPotassium(ui->potassiumLineEdit->text().toFloat());
        }
    } else {
        food.setPotassium(0);
    }

    if (ui->riboflavinLineEdit->text() != "") {
        if (ui->riboflavinDVRadioButton->isChecked()) {
            food.setRiboflavin((ui->riboflavinLineEdit->text().toFloat() / 100) * 1.6f);
        } else {
            food.setRiboflavin(ui->riboflavinLineEdit->text().toFloat());
        }
    } else {
        food.setRiboflavin(0);
    }

    if (ui->seleniumLineEdit->text() != "") {
        if (ui->seleniumDVRadioButton->isChecked()) {
            food.setSelenium((ui->seleniumLineEdit->text().toFloat() / 100) * 50);
        } else {
            food.setSelenium(ui->seleniumLineEdit->text().toFloat());
        }
    } else {
        food.setSelenium(0);
    }

    if (ui->thiamineLineEdit->text() != "") {
        if (ui->thiamineDVRadioButton->isChecked()) {
            food.setThiamine((ui->thiamineLineEdit->text().toFloat() / 100) * 1.3f);
        } else {
            food.setThiamine(ui->thiamineLineEdit->text().toFloat());
        }
    } else {
        food.setThiamine(0);
    }

    if (ui->vitaminALineEdit->text() != "") {
        if (ui->vitaminADVRadioButton->isChecked()) {
            food.setVitaminA((ui->vitaminALineEdit->text().toFloat() / 100) * 1000);
        } else {
            food.setVitaminA(ui->vitaminALineEdit->text().toFloat());
        }
    } else {
        food.setVitaminA(0);
    }

    if (ui->vitaminB6LineEdit->text() != "") {
        if (ui->vitaminB6DVRadioButton->isChecked()) {
            food.setVitaminB6((ui->vitaminB6LineEdit->text().toFloat() / 100) * 1.8f);
        } else {
            food.setVitaminB6(ui->vitaminB6LineEdit->text().toFloat());
        }
    } else {
        food.setVitaminB6(0);
    }

    if (ui->vitaminB12LineEdit->text() != "") {
        if (ui->vitaminB12DVRadioButton->isChecked()) {
            food.setVitaminB12((ui->vitaminB12LineEdit->text().toFloat() / 100) * 2);
        } else {
            food.setVitaminB12(ui->vitaminB12LineEdit->text().toFloat());
        }
    } else {
        food.setVitaminB12(0);
    }

    if (ui->vitaminCLineEdit->text() != "") {
        if (ui->vitaminCDVRadioButton->isChecked()) {
            food.setVitaminC((ui->vitaminCLineEdit->text().toFloat() / 100) * 60);
        } else {
            food.setVitaminC(ui->vitaminCLineEdit->text().toFloat());
        }
    } else {
        food.setVitaminC(0);
    }

    if (ui->vitaminDLineEdit->text() != "") {
        if (ui->vitaminDDVRadioButton->isChecked()) {
            food.setVitaminD((ui->vitaminDLineEdit->text().toFloat() / 100) * 5);
        } else {
            food.setVitaminD(ui->vitaminDLineEdit->text().toFloat());
        }
    } else {
        food.setVitaminD(0);
    }

    if (ui->vitaminELineEdit->text() != "") {
        if (ui->vitaminEDVRadioButton->isChecked()) {
            food.setVitaminE((ui->vitaminELineEdit->text().toFloat() / 100) * 10);
        } else {
            food.setVitaminE(ui->vitaminELineEdit->text().toFloat());
        }
    } else {
        food.setVitaminE(0);
    }

    if (ui->zincLineEdit->text() != "") {
        if (ui->zincDVRadioButton->isChecked()) {
            food.setZinc((ui->zincLineEdit->text().toFloat() / 100) * 9);
        } else {
            food.setZinc(ui->zincLineEdit->text().toFloat());
        }
    } else {
        food.setZinc(0);
    }

    if (!mFoodModel->addFood(food)) {
        showInputError("Duplicate food names are not allowed");
        return;
    }

    QMessageBox box(this);
    box.setWindowTitle("Entry Successful");
    box.setText("Food successfully saved into database.");
    box.addButton(QMessageBox::Ok);
    box.exec();

    ui->foodNameLineEdit->setText("");
    ui->categoryComboBox->setCurrentIndex(0);
    ui->servingSizeLineEdit->setText("");
    ui->unitOfMeasureLineEdit->setText("");

    // Reset nutrient lineEdits to nothing
    QList<QLineEdit*> lineEditList = ui->nutritionalInfoGroupBox->findChildren<QLineEdit*>();
    foreach (QLineEdit* lineEdit, lineEditList) {
        lineEdit->setText("");
    }

    // Reset radio buttons to DV button
    QList<QWidget*> leftWidgets = ui->leftWidget->findChildren<QWidget*>();
    foreach (QWidget* widget, leftWidgets) {
        QList<QRadioButton*> buttonList = widget->findChildren<QRadioButton*>();
        if (buttonList.size() > 0) {
            buttonList.at(0)->setChecked(true);
        }
    }
    QList<QWidget*> rightWidgets = ui->rightWidget->findChildren<QWidget*>();
    foreach (QWidget* widget, rightWidgets) {
        QList<QRadioButton*> buttonList = widget->findChildren<QRadioButton*>();
        if (buttonList.size() > 0) {
            buttonList.at(0)->setChecked(true);
        }
    }
}

void MainWindow::tabSelected() {
    ui->intakeCategoryComboBox->setCurrentIndex(0);
    mFoodModel->getFoods(mCategoryModel->index(0).data().toString());
    ui->foodNameComboBox->setCurrentIndex(0);

    updateIntakeTarget(mIntakeTargetModel->getIntakeTarget());
}

void MainWindow::categorySelected() {
    QString string = ui->intakeCategoryComboBox->currentText();
    mFoodModel->getFoods(string);
    ui->foodNameComboBox->setCurrentIndex(0);
}

void MainWindow::targetIntakeSubmitted() {
    QList<QLineEdit*> lineEdits = ui->targets->findChildren<QLineEdit*>();
    foreach (QLineEdit* lineEdit, lineEdits) {
        if (lineEdit->text() == "") {
            showInputError("All input fields must have a non-zero value.");
            return;
        }
    }

    IntakeTarget target;

    if (ui->fatTargetLineEdit->text().toFloat() > 0) {
        target.setFat(ui->fatTargetLineEdit->text().toFloat());
    } else {
        showTargetZeroError();
        return;
    }

    if (ui->cholesterolTargetLineEdit->text().toFloat() > 0) {
        target.setCholesterol(ui->cholesterolTargetLineEdit->text().toFloat());
    } else {
        showTargetZeroError();
        return;
    }

    if (ui->sodiumTargetLineEdit->text().toFloat() > 0) {
        target.setSodium(ui->sodiumTargetLineEdit->text().toFloat());
    } else {
        showTargetZeroError();
        return;
    }

    if (ui->carbsTargetLineEdit->text().toFloat() > 0) {
        target.setCarbs(ui->carbsTargetLineEdit->text().toFloat());
    } else {
        showTargetZeroError();
        return;
    }

    if (ui->fibreTargetLineEdit->text().toFloat() > 0) {
        target.setFibre(ui->fibreTargetLineEdit->text().toFloat());
    } else {
        showTargetZeroError();
        return;
    }

    if (ui->sugarTargetLineEdit->text().toFloat() > 0) {
        target.setSugar(ui->sugarTargetLineEdit->text().toFloat());
    } else {
        showTargetZeroError();
        return;
    }

    if (ui->proteinTargetLineEdit->text().toFloat() > 0) {
        target.setProtein(ui->proteinTargetLineEdit->text().toFloat());
    } else {
        showTargetZeroError();
        return;
    }

    // Micronutrients
    if (ui->biotinTargetLineEdit->text().toFloat() > 0) {
        target.setBiotin(ui->biotinTargetLineEdit->text().toFloat());
    } else {
        showTargetZeroError();
        return;
    }

    if (ui->calciumTargetLineEdit->text().toFloat() > 0) {
        target.setCalcium(ui->calciumTargetLineEdit->text().toFloat());
    } else {
        showTargetZeroError();
        return;
    }

    if (ui->chromiumTargetLineEdit->text().toFloat() > 0) {
        target.setChromium(ui->chromiumTargetLineEdit->text().toFloat());
    } else {
        showTargetZeroError();
        return;
    }

    if (ui->copperTargetLineEdit->text().toFloat() > 0) {
        target.setCopper(ui->copperTargetLineEdit->text().toFloat());
    } else {
        showTargetZeroError();
        return;
    }

    if (ui->folacinTargetLineEdit->text().toFloat() > 0) {
        target.setFolacin(ui->folacinTargetLineEdit->text().toFloat());
    } else {
        showTargetZeroError();
        return;
    }

    if (ui->iodideTargetLineEdit->text().toFloat() > 0) {
        target.setIodide(ui->iodideTargetLineEdit->text().toFloat());
    } else {
        showTargetZeroError();
        return;
    }

    if (ui->ironTargetLineEdit->text().toFloat() > 0) {
        target.setIron(ui->ironTargetLineEdit->text().toFloat());
    } else {
        showTargetZeroError();
        return;
    }

    if (ui->magnesiumTargetLineEdit->text().toFloat() > 0) {
        target.setMagnesium(ui->magnesiumTargetLineEdit->text().toFloat());
    } else {
        showTargetZeroError();
        return;
    }

    if (ui->manganeseTargetLineEdit->text().toFloat() > 0) {
        target.setManganese(ui->manganeseTargetLineEdit->text().toFloat());
    } else {
        showTargetZeroError();
        return;
    }

    if (ui->molybdenumTargetLineEdit->text().toFloat() > 0) {
        target.setMolybenum(ui->molybdenumTargetLineEdit->text().toFloat());
    } else {
        showTargetZeroError();
        return;
    }

    if (ui->niacinTargetLineEdit->text().toFloat() > 0) {
        target.setNiacin(ui->niacinTargetLineEdit->text().toFloat());
    } else {
        showTargetZeroError();
        return;
    }

    if (ui->pantothenateTargetLineEdit->text().toFloat() > 0) {
        target.setPantothenate(ui->pantothenateTargetLineEdit->text().toFloat());
    } else {
        showTargetZeroError();
        return;
    }

    if (ui->phosphorousTargetLineEdit->text().toFloat() > 0) {
        target.setPhosphorous(ui->phosphorousTargetLineEdit->text().toFloat());
    } else {
        showTargetZeroError();
        return;
    }

    if (ui->potassiumTargetLineEdit->text().toFloat() > 0) {
        target.setPotassium(ui->potassiumTargetLineEdit->text().toFloat());
    } else {
        showTargetZeroError();
        return;
    }

    if (ui->riboflavinTargetLineEdit->text().toFloat() > 0) {
        target.setRiboflavin(ui->riboflavinTargetLineEdit->text().toFloat());
    } else {
        showTargetZeroError();
        return;
    }

    if (ui->seleniumTargetLineEdit->text().toFloat() > 0) {
        target.setSelenium(ui->seleniumTargetLineEdit->text().toFloat());
    } else {
        showTargetZeroError();
        return;
    }

    if (ui->thiamineTargetLineEdit->text().toFloat() > 0) {
        target.setThiamine(ui->thiamineTargetLineEdit->text().toFloat());
    } else {
        showTargetZeroError();
        return;
    }

    if (ui->vitaminATargetLineEdit->text().toFloat() > 0) {
        target.setVitaminA(ui->vitaminATargetLineEdit->text().toFloat());
    } else {
        showTargetZeroError();
        return;
    }

    if (ui->vitaminB6TargetLineEdit->text().toFloat() > 0) {
        target.setVitaminB6(ui->vitaminB6TargetLineEdit->text().toFloat());
    } else {
        showTargetZeroError();
        return;
    }

    if (ui->vitaminB12TargetLineEdit->text().toFloat() > 0) {
        target.setVitaminB12(ui->vitaminB12TargetLineEdit->text().toFloat());
    } else {
        showTargetZeroError();
        return;
    }

    if (ui->vitaminCTargetLineEdit->text().toFloat() > 0) {
        target.setVitaminC(ui->vitaminCTargetLineEdit->text().toFloat());
    } else {
        showTargetZeroError();
        return;
    }

    if (ui->vitaminDTargetLineEdit->text().toFloat() > 0) {
        target.setVitaminD(ui->vitaminDTargetLineEdit->text().toFloat());
    } else {
        showTargetZeroError();
        return;
    }

    if (ui->vitaminETargetLineEdit->text().toFloat() > 0) {
        target.setVitaminE(ui->vitaminETargetLineEdit->text().toFloat());
    } else {
        showTargetZeroError();
        return;
    }

    if (ui->zincTargetLineEdit->text().toFloat() > 0) {
        target.setZinc(ui->zincTargetLineEdit->text().toFloat());
    } else {
        showTargetZeroError();
        return;
    }

    mIntakeTargetModel->setIntakeTarget(target);

    QMessageBox box(this);
    box.setWindowTitle("Success");
    box.setText("Intake targets updated successfully.");
    box.addButton(QMessageBox::Ok);
    box.exec();

    updateIntakeTarget(target);
}

void MainWindow::updateIntakeTarget(const IntakeTarget& target) {
    ui->fatTargetLineEdit->setText(QString().setNum(target.getFat()));
    ui->cholesterolTargetLineEdit->setText(QString().setNum(target.getCholesterol()));
    ui->sodiumTargetLineEdit->setText(QString().setNum(target.getSodium()));
    ui->carbsTargetLineEdit->setText(QString().setNum(target.getCarbs()));
    ui->fibreTargetLineEdit->setText(QString().setNum(target.getFibre()));
    ui->sugarTargetLineEdit->setText(QString().setNum(target.getSugar()));
    ui->proteinTargetLineEdit->setText(QString().setNum(target.getProtein()));

    ui->biotinTargetLineEdit->setText(QString().setNum(target.getBiotin()));
    ui->calciumTargetLineEdit->setText(QString().setNum(target.getCalcium()));
    ui->chromiumTargetLineEdit->setText(QString().setNum(target.getChromium()));
    ui->copperTargetLineEdit->setText(QString().setNum(target.getCopper()));
    ui->folacinTargetLineEdit->setText(QString().setNum(target.getFolacin()));
    ui->iodideTargetLineEdit->setText(QString().setNum(target.getIodide()));
    ui->ironTargetLineEdit->setText(QString().setNum(target.getIron()));
    ui->magnesiumTargetLineEdit->setText(QString().setNum(target.getMagnesium()));
    ui->manganeseTargetLineEdit->setText(QString().setNum(target.getManganese()));
    ui->molybdenumTargetLineEdit->setText(QString().setNum(target.getMolybdenum()));
    ui->niacinTargetLineEdit->setText(QString().setNum(target.getNiacin()));
    ui->pantothenateTargetLineEdit->setText(QString().setNum(target.getPantothenate()));
    ui->phosphorousTargetLineEdit->setText(QString().setNum(target.getPhosphorous()));
    ui->potassiumTargetLineEdit->setText(QString().setNum(target.getPotassium()));
    ui->riboflavinTargetLineEdit->setText(QString().setNum(target.getRiboflavin()));
    ui->seleniumTargetLineEdit->setText(QString().setNum(target.getSelenium()));
    ui->thiamineTargetLineEdit->setText(QString().setNum(target.getThiamine()));
    ui->vitaminATargetLineEdit->setText(QString().setNum(target.getVitaminA()));
    ui->vitaminB6TargetLineEdit->setText(QString().setNum(target.getVitaminB6()));
    ui->vitaminB12TargetLineEdit->setText(QString().setNum(target.getVitaminB12()));
    ui->vitaminCTargetLineEdit->setText(QString().setNum(target.getVitaminC()));
    ui->vitaminDTargetLineEdit->setText(QString().setNum(target.getVitaminD()));
    ui->vitaminETargetLineEdit->setText(QString().setNum(target.getVitaminE()));
    ui->zincTargetLineEdit->setText(QString().setNum(target.getZinc()));
}

void MainWindow::showInputError(const QString &message) {
    QMessageBox box(this);
    box.setWindowTitle("Error");
    box.setText(message);
    box.addButton(QMessageBox::Ok);
    box.exec();
}

void MainWindow::showTargetZeroError() {
    showInputError("Values must be greater than 0.");
}

void MainWindow::intakeSubmitted() {
    if (ui->foodNameComboBox->currentText() == "" || ui->intakeSizeLineEdit->text() == "") {
        showInputError("Food name and serving size are required.");
        return;
    }

    QDate date(ui->yearSpinBox->value(), ui->monthComboBox->currentIndex() + 1, ui->daySpinBox->value());

    QString foodName = ui->foodNameComboBox->currentText();
    foodName.truncate(foodName.indexOf(" --- "));

    mIntakeModel->addIntake(foodName, ui->intakeSizeLineEdit->text().toFloat(), date);
    ui->intakeSizeLineEdit->setText("");

    updateProgressBars();
}

void MainWindow::dateChanged() {
    QDate date(ui->yearSpinBox->value(), ui->monthComboBox->currentIndex() + 1, ui->daySpinBox->value());
    mIntakeModel->dateChanged(date);

    updateProgressBars();
}

void MainWindow::setProgressBarsMaxValue() {
    ui->caloriesProgressBar->setMaximum(mProgressMultiplier);
    ui->fatProgressBar->setMaximum(mProgressMultiplier);
    ui->saturatedProgressBar->setMaximum(mProgressMultiplier);
    ui->transProgressBar->setMaximum(mProgressMultiplier);
    ui->unsaturatedProgressBar->setMaximum(mProgressMultiplier);
    ui->cholesterolProgressBar->setMaximum(mProgressMultiplier);
    ui->sodiumProgressBar->setMaximum(mProgressMultiplier);
    ui->carbsProgressBar->setMaximum(mProgressMultiplier);
    ui->fibreProgressBar->setMaximum(mProgressMultiplier);
    ui->sugarProgressBar->setMaximum(mProgressMultiplier);
    ui->proteinProgressBar->setMaximum(mProgressMultiplier);

    ui->biotinProgressBar->setMaximum(mProgressMultiplier);
    ui->calciumProgressBar->setMaximum(mProgressMultiplier);
    ui->chromiumProgressBar->setMaximum(mProgressMultiplier);
    ui->copperProgressBar->setMaximum(mProgressMultiplier);
    ui->folacinProgressBar->setMaximum(mProgressMultiplier);
    ui->iodideProgressBar->setMaximum(mProgressMultiplier);
    ui->ironProgressBar->setMaximum(mProgressMultiplier);
    ui->magnesiumProgressBar->setMaximum(mProgressMultiplier);
    ui->manganeseProgressBar->setMaximum(mProgressMultiplier);
    ui->molybdenumProgressBar->setMaximum(mProgressMultiplier);
    ui->niacinProgressBar->setMaximum(mProgressMultiplier);
    ui->pantothenateProgressBar->setMaximum(mProgressMultiplier);
    ui->phosphorousProgressBar->setMaximum(mProgressMultiplier);
    ui->potassiumProgressBar->setMaximum(mProgressMultiplier);
    ui->riboflavinProgressBar->setMaximum(mProgressMultiplier);
    ui->seleniumProgressBar->setMaximum(mProgressMultiplier);
    ui->thiamineProgressBar->setMaximum(mProgressMultiplier);
    ui->vitaminAProgressBar->setMaximum(mProgressMultiplier);
    ui->vitaminB6ProgressBar->setMaximum(mProgressMultiplier);
    ui->vitaminB12ProgressBar->setMaximum(mProgressMultiplier);
    ui->vitaminCProgressBar->setMaximum(mProgressMultiplier);
    ui->vitaminDProgressBar->setMaximum(mProgressMultiplier);
    ui->vitaminEProgressBar->setMaximum(mProgressMultiplier);
    ui->zincProgressBar->setMaximum(mProgressMultiplier);
}

void MainWindow::updateProgressBars() {
    Food total = mIntakeModel->getDailyTotal();
    Food target = mIntakeTargetModel->getIntakeTarget();

    // QProgressBar won't update the value if it is out of range, so determine if it's valid first
    float temp = (total.getCalories() / target.getCalories()) * mProgressMultiplier;
    if (temp < mProgressMultiplier) { ui->caloriesProgressBar->setValue(temp); }
    else if (temp < 1) { ui->caloriesProgressBar->setValue(0); }
    else { ui->caloriesProgressBar->setValue(mProgressMultiplier); }

    temp = (total.getFat() / target.getFat()) * mProgressMultiplier;
    if (temp < mProgressMultiplier) { ui->fatProgressBar->setValue(temp);}
    else if (temp < 1) { ui->fatProgressBar->setValue(0); }
    else { ui->fatProgressBar->setValue(mProgressMultiplier); }

    temp = (total.getSaturatedFat() / target.getFat()) * mProgressMultiplier;
    if (temp < mProgressMultiplier) { ui->saturatedProgressBar->setValue(temp);}
    else if (temp < 1) { ui->saturatedProgressBar->setValue(0); }
    else { ui->saturatedProgressBar->setValue(mProgressMultiplier); }

    temp = (total.getTransFat() / target.getFat()) * mProgressMultiplier;
    if (temp < mProgressMultiplier) { ui->transProgressBar->setValue(temp);}
    else if (temp < 1) { ui->transProgressBar->setValue(0); }
    else { ui->transProgressBar->setValue(mProgressMultiplier); }

    temp = (total.getUnsaturatedFat() / target.getFat()) * mProgressMultiplier;
    if (temp < mProgressMultiplier) { ui->unsaturatedProgressBar->setValue(temp);}
    else if (temp < 1) { ui->unsaturatedProgressBar->setValue(0); }
    else { ui->unsaturatedProgressBar->setValue(mProgressMultiplier); }

    temp = (total.getCholesterol() / target.getCholesterol()) * mProgressMultiplier;
    if (temp < mProgressMultiplier) { ui->cholesterolProgressBar->setValue(temp);}
    else if (temp < 1) { ui->cholesterolProgressBar->setValue(0); }
    else { ui->cholesterolProgressBar->setValue(mProgressMultiplier); }

    temp = (total.getSodium() / target.getSodium()) * mProgressMultiplier;
    if (temp < mProgressMultiplier) { ui->sodiumProgressBar->setValue(temp);}
    else if (temp < 1) { ui->sodiumProgressBar->setValue(0); }
    else { ui->sodiumProgressBar->setValue(mProgressMultiplier); }

    temp = (total.getCarbs() / target.getCarbs()) * mProgressMultiplier;
    if (temp < mProgressMultiplier) { ui->carbsProgressBar->setValue(temp);}
    else if (temp < 1) { ui->carbsProgressBar->setValue(0); }
    else { ui->carbsProgressBar->setValue(mProgressMultiplier); }

    temp = (total.getFibre() / target.getFibre()) * mProgressMultiplier;
    if (temp < mProgressMultiplier) { ui->fibreProgressBar->setValue(temp);}
    else if (temp < 1) { ui->fibreProgressBar->setValue(0); }
    else { ui->fibreProgressBar->setValue(mProgressMultiplier); }

    temp = (total.getSugar() / target.getSugar()) * mProgressMultiplier;
    if (temp < mProgressMultiplier) { ui->sugarProgressBar->setValue(temp);}
    else if (temp < 1) { ui->sugarProgressBar->setValue(0); }
    else { ui->sugarProgressBar->setValue(mProgressMultiplier); }

    temp = (total.getProtein() / target.getProtein()) * mProgressMultiplier;
    if (temp < mProgressMultiplier) { ui->proteinProgressBar->setValue(temp);}
    else if (temp < 1) { ui->proteinProgressBar->setValue(0); }
    else { ui->proteinProgressBar->setValue(mProgressMultiplier); }

    temp = (total.getBiotin() / target.getBiotin()) * mProgressMultiplier;
    if (temp < mProgressMultiplier) { ui->biotinProgressBar->setValue(temp);}
    else if (temp < 1) { ui->biotinProgressBar->setValue(0); }
    else { ui->biotinProgressBar->setValue(mProgressMultiplier); }

    temp = (total.getCalcium() / target.getCalcium()) * mProgressMultiplier;
    if (temp < mProgressMultiplier) { ui->calciumProgressBar->setValue(temp);}
    else if (temp < 1) { ui->calciumProgressBar->setValue(0); }
    else { ui->calciumProgressBar->setValue(mProgressMultiplier); }

    temp = (total.getChromium() / target.getChromium()) * mProgressMultiplier;
    if (temp < mProgressMultiplier) { ui->chromiumProgressBar->setValue(temp);}
    else if (temp < 1) { ui->chromiumProgressBar->setValue(0); }
    else { ui->chromiumProgressBar->setValue(mProgressMultiplier); }

    temp = (total.getCopper() / target.getCopper()) * mProgressMultiplier;
    if (temp < mProgressMultiplier) { ui->copperProgressBar->setValue(temp);}
    else if (temp < 1) { ui->copperProgressBar->setValue(0); }
    else { ui->copperProgressBar->setValue(mProgressMultiplier); }

    temp = (total.getFolacin() / target.getFolacin()) * mProgressMultiplier;
    if (temp < mProgressMultiplier) { ui->folacinProgressBar->setValue(temp);}
    else if (temp < 1) { ui->folacinProgressBar->setValue(0); }
    else { ui->folacinProgressBar->setValue(mProgressMultiplier); }

    temp = (total.getIodide() / target.getIodide()) * mProgressMultiplier;
    if (temp < mProgressMultiplier) { ui->iodideProgressBar->setValue(temp);}
    else if (temp < 1) { ui->iodideProgressBar->setValue(0); }
    else { ui->iodideProgressBar->setValue(mProgressMultiplier); }

    temp = (total.getIron() / target.getIron()) * mProgressMultiplier;
    if (temp < mProgressMultiplier) { ui->ironProgressBar->setValue(temp);}
    else if (temp < 1) { ui->ironProgressBar->setValue(0); }
    else { ui->ironProgressBar->setValue(mProgressMultiplier); }

    temp = (total.getMagnesium() / target.getMagnesium()) * mProgressMultiplier;
    if (temp < mProgressMultiplier) { ui->magnesiumProgressBar->setValue(temp);}
    else if (temp < 1) { ui->magnesiumProgressBar->setValue(0); }
    else { ui->magnesiumProgressBar->setValue(mProgressMultiplier); }

    temp = (total.getManganese() / target.getManganese()) * mProgressMultiplier;
    if (temp < mProgressMultiplier) { ui->manganeseProgressBar->setValue(temp);}
    else if (temp < 1) { ui->manganeseProgressBar->setValue(0); }
    else { ui->manganeseProgressBar->setValue(mProgressMultiplier); }

    temp = (total.getMolybdenum() / target.getMolybdenum()) * mProgressMultiplier;
    if (temp < mProgressMultiplier) { ui->molybdenumProgressBar->setValue(temp);}
    else if (temp < 1) { ui->molybdenumProgressBar->setValue(0); }
    else { ui->molybdenumProgressBar->setValue(mProgressMultiplier); }

    temp = (total.getNiacin() / target.getNiacin()) * mProgressMultiplier;
    if (temp < mProgressMultiplier) { ui->niacinProgressBar->setValue(temp);}
    else if (temp < 1) { ui->niacinProgressBar->setValue(0); }
    else { ui->niacinProgressBar->setValue(mProgressMultiplier); }

    temp = (total.getPantothenate() / target.getPantothenate()) * mProgressMultiplier;
    if (temp < mProgressMultiplier) { ui->pantothenateProgressBar->setValue(temp);}
    else if (temp < 1) { ui->pantothenateProgressBar->setValue(0); }
    else { ui->pantothenateProgressBar->setValue(mProgressMultiplier); }

    temp = (total.getPhosphorous() / target.getPhosphorous()) * mProgressMultiplier;
    if (temp < mProgressMultiplier) { ui->phosphorousProgressBar->setValue(temp);}
    else if (temp < 1) { ui->phosphorousProgressBar->setValue(0); }
    else { ui->phosphorousProgressBar->setValue(mProgressMultiplier); }

    temp = (total.getPotassium() / target.getPotassium()) * mProgressMultiplier;
    if (temp < mProgressMultiplier) { ui->potassiumProgressBar->setValue(temp);}
    else if (temp < 1) { ui->potassiumProgressBar->setValue(0); }
    else { ui->potassiumProgressBar->setValue(mProgressMultiplier); }

    temp = (total.getRiboflavin() / target.getRiboflavin()) * mProgressMultiplier;
    if (temp < mProgressMultiplier) { ui->riboflavinProgressBar->setValue(temp);}
    else if (temp < 1) { ui->riboflavinProgressBar->setValue(0); }
    else { ui->riboflavinProgressBar->setValue(mProgressMultiplier); }

    temp = (total.getSelenium() / target.getSelenium()) * mProgressMultiplier;
    if (temp < mProgressMultiplier) { ui->seleniumProgressBar->setValue(temp);}
    else if (temp < 1) { ui->seleniumProgressBar->setValue(0); }
    else { ui->seleniumProgressBar->setValue(mProgressMultiplier); }

    temp = (total.getThiamine() / target.getThiamine()) * mProgressMultiplier;
    if (temp < mProgressMultiplier) { ui->thiamineProgressBar->setValue(temp);}
    else if (temp < 1) { ui->thiamineProgressBar->setValue(0); }
    else { ui->thiamineProgressBar->setValue(mProgressMultiplier); }

    temp = (total.getVitaminA() / target.getVitaminA()) * mProgressMultiplier;
    if (temp < mProgressMultiplier) { ui->vitaminAProgressBar->setValue(temp);}
    else if (temp < 1) { ui->vitaminAProgressBar->setValue(0); }
    else { ui->vitaminAProgressBar->setValue(mProgressMultiplier); }

    temp = (total.getVitaminB6() / target.getVitaminB6()) * mProgressMultiplier;
    if (temp < mProgressMultiplier) { ui->vitaminB6ProgressBar->setValue(temp);}
    else if (temp < 1) { ui->vitaminB6ProgressBar->setValue(0); }
    else { ui->vitaminB6ProgressBar->setValue(mProgressMultiplier); }

    temp = (total.getVitaminB12() / target.getVitaminB12()) * mProgressMultiplier;
    if (temp < mProgressMultiplier) { ui->vitaminB12ProgressBar->setValue(temp);}
    else if (temp < 1) { ui->vitaminB12ProgressBar->setValue(0); }
    else { ui->vitaminB12ProgressBar->setValue(mProgressMultiplier); }

    temp = (total.getVitaminC() / target.getVitaminC()) * mProgressMultiplier;
    if (temp < mProgressMultiplier) { ui->vitaminCProgressBar->setValue(temp);}
    else if (temp < 1) { ui->vitaminCProgressBar->setValue(0); }
    else { ui->vitaminCProgressBar->setValue(mProgressMultiplier); }

    temp = (total.getVitaminD() / target.getVitaminD()) * mProgressMultiplier;
    if (temp < mProgressMultiplier) { ui->vitaminDProgressBar->setValue(temp);}
    else if (temp < 1) { ui->vitaminDProgressBar->setValue(0); }
    else { ui->vitaminDProgressBar->setValue(mProgressMultiplier); }

    temp = (total.getVitaminE() / target.getVitaminE()) * mProgressMultiplier;
    if (temp < mProgressMultiplier) { ui->vitaminEProgressBar->setValue(temp);}
    else if (temp < 1) { ui->vitaminEProgressBar->setValue(0); }
    else { ui->vitaminEProgressBar->setValue(mProgressMultiplier); }

    temp = (total.getZinc() / target.getZinc()) * mProgressMultiplier;
    if (temp < mProgressMultiplier) { ui->zincProgressBar->setValue(temp);}
    else if (temp < 1) { ui->zincProgressBar->setValue(0); }
    else { ui->zincProgressBar->setValue(mProgressMultiplier); }
}
