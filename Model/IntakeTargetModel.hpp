#ifndef INTAKETARGETMODEL_HPP
#define INTAKETARGETMODEL_HPP

class DatabaseManager;
class IntakeTarget;

class IntakeTargetModel {
    public:
        IntakeTargetModel();

        IntakeTarget getIntakeTarget() const;
        void setIntakeTarget(IntakeTarget& target) const;

    private:
        DatabaseManager& mDatabase;
};

#endif // INTAKETARGETMODEL_HPP
