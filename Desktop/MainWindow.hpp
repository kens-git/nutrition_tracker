#ifndef MAINWINDOW_HPP
#define MAINWINDOW_HPP

#include <QMainWindow>

class FoodModel;
class CategoryModel;
class IntakeTargetModel;
class IntakeTarget;
class IntakeModel;

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

    private:
        Ui::MainWindow *ui;

        FoodModel* mFoodModel;
        CategoryModel* mCategoryModel;
        IntakeTargetModel* mIntakeTargetModel;
        IntakeModel* mIntakeModel;

        void showInputError(const QString& message);
        void showTargetZeroError();

        // used to set the resolution of the progress bars
        const float mProgressMultiplier = 10000;

        void setProgressBarsMaxValue();
        void updateProgressBars();

    private slots:
        void addNewFood();
        void tabSelected();
        void categorySelected();
        void targetIntakeSubmitted();
        void updateIntakeTarget(const IntakeTarget& target);
        void intakeSubmitted();
        void dateChanged();
};

#endif // MAINWINDOW_HPP
