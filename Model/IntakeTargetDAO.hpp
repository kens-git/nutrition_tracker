#ifndef INTAKETARGETDAO_HPP
#define INTAKETARGETDAO_HPP

class QSqlDatabase;

class IntakeTarget;

class IntakeTargetDAO {
    public:
        IntakeTargetDAO(QSqlDatabase& database);
        void init() const;

        void setIntake(IntakeTarget& target) const;
        IntakeTarget getIntake() const;

    private:
        QSqlDatabase& mDatabase;
};

#endif // INTAKETARGETDAO_HPP
