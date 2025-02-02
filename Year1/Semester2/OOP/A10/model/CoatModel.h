
#include <QAbstractTableModel>
#include "../repo/Repo.h"
#include <vector>

class CoatModel : public QAbstractTableModel{
private:
    vector<TrenchCoat> coats;
public:

    explicit CoatModel(vector<TrenchCoat> _repo) : coats(_repo){}

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    ~CoatModel() override = default;
};



