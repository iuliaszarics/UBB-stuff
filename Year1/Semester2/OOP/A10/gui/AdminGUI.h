
#pragma once


#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QStringListModel>
#include <QTableView>

#include "../services/AdminServices.h"

class AdminGUI : public QWidget {

private:

    AdminServices _services;

    QListWidget* _coatListWidget;

    QLineEdit* _sizeEdit;
    QLineEdit* _priceEdit;
    QLineEdit* _colorEdit;
    QLineEdit* _quantityEdit;
    QLineEdit* _photoEdit;

    QPushButton* _addButton;
    QPushButton* _removeButton;
    QPushButton* _updateButton;
    QPushButton* _showGraphicButton;

    QPushButton* _undoButton;
    QPushButton* _redoButton;

    QTableView* _tableView;

public:
    explicit AdminGUI(AdminServices _services);

private:

    void BuildGUI();

    void PopulateList();

private slots:

    void OnAddButtonClicked();
    void OnRemoveButtonClicked();
    void OnUpdateButtonClicked();
    void OnShowGraphicButtonClicked();
    void OnUndo();
    void OnRedo();
};

