#ifndef CATEGORYMODEL_HPP
#define CATEGORYMODEL_HPP

#include <QStringListModel>
class QStringList;

class CategoryModel : public QStringListModel {
    public:
        CategoryModel();

    private:
        QStringList* mStringList;
};

#endif // CATEGORYMODEL_HPP
