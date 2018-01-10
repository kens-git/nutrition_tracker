#include "IntakeTargetModel.hpp"

#include "DatabaseManager.hpp"
#include "IntakeTarget.hpp"

IntakeTargetModel::IntakeTargetModel() : mDatabase(DatabaseManager::instance()) {

}

IntakeTarget IntakeTargetModel::getIntakeTarget() const {
    return mDatabase.mIntakeTargetDAO.getIntake();
}

void IntakeTargetModel::setIntakeTarget(IntakeTarget &target) const {
    mDatabase.mIntakeTargetDAO.setIntake(target);
}
