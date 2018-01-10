#ifndef INTAKEMODEL_HPP
#define INTAKEMODEL_HPP

#include <QAbstractTableModel>
#include <QVariant>
#include <QString>
#include <QVector>
#include <QDate>

#include "Food.hpp"
class DatabaseManager;

class IntakeModel : public QAbstractTableModel {
    public:
        IntakeModel(QObject* parent = nullptr);

        QVariant data(const QModelIndex &index, int role) const override;

        int rowCount(const QModelIndex &parent) const override;
        int columnCount(const QModelIndex &parent) const override;
        QVariant headerData(int section, Qt::Orientation orientation, int role) const override;
        Qt::ItemFlags flags(const QModelIndex &index) const override;

        void addIntake(const QString& foodName, float servingSize, const QDate& date);
        // called when the user selects a new date, changes the intake TableView to the set date
        void dateChanged(QDate& date);

        // returns the current daily total intake
        Food getDailyTotal();

    private:
        DatabaseManager& mDatabase;
        QVector<Food>* mIntake;

        // used to keep track of the daily total intake
        void updateTotal();
        Food* mTotal;

        const unsigned int NUM_COLUMNS = 39;
};

#endif // INTAKEMODEL_HPP
