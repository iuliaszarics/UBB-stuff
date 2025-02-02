

#include "CoatModel.h"

int CoatModel::rowCount(const QModelIndex &parent) const {
    return coats.size();
}

int CoatModel::columnCount(const QModelIndex &parent) const {
    return 5;
}

QVariant CoatModel::data(const QModelIndex &index, int role) const {
    int row = index.row();
    int col = index.column();

    TrenchCoat p = coats[row];

    if (role == Qt::DisplayRole)
    {
        switch (col)
        {
            case 0:
                return QString::number(p.GetSize());
            case 1:
                return QString::fromStdString(p.GetColour());
            case 2:
                return QString::number(p.GetQuantity());
            case 3:
                return QString::number(p.GetPrice());
            case 4:
                return QString::fromStdString(p.GetPhoto());
            default:
                break;
        }
    }

    return QVariant();
}

QVariant CoatModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role == Qt::DisplayRole && orientation == Qt::Horizontal)
    {
        switch (section)
        {
            case 0:
                return "Size";
            case 1:
                return "Color";
            case 2:
                return "Quantity";
            case 3:
                return "Price";
            case 4:
                return "Photo";
            default:
                break;
        }
    }

    return QVariant();
}
