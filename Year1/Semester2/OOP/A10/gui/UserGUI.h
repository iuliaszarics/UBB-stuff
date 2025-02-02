

#pragma once

#include <QWidget>
#include <QListWidget>
#include <QPushButton>
#include <QLineEdit>
#include <QLabel>
#include "../services/UserServices.h"

class UserGUI : public QWidget{


private:

    UserServices _services;

    QListWidget* _basket;

    QLineEdit* _sizeEdit;

    QPushButton* _searchButton;
    QPushButton* _openBasketButton;

    QWidget* _basketWidget;
    QLabel* _coatText;
    QPushButton* _addButton;
    QPushButton* _nextButton;
    QPushButton* _viewImageButton;

public:

    explicit UserGUI(const UserServices& services);

private:
    void BuildGUI();

    void OnSearchButtonClicked();
    void OnOpenButtonClicked();
    void OnAddButtonClicked();
    void OnNextButtonClicked();
    void OnViewButtonClicked();
    void CreateBasketWidget();


    void UpdateBakset();
};


