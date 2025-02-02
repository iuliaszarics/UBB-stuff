

#include <QVBoxLayout>
#include <QFormLayout>
#include <QLabel>
#include "UserGUI.h"
#include <process.h>
#include "../services/UserServices.h"

UserGUI::UserGUI(const UserServices& services) {

    _services = services;

    BuildGUI();
}

void UserGUI::BuildGUI() {


    auto* mainLayout = new QHBoxLayout(this);
    auto* rightLayout = new QVBoxLayout();
    auto* leftLayout = new QVBoxLayout();

    auto* formLayout = new QFormLayout();
    auto* lowerLayout = new QHBoxLayout();

    _sizeEdit = new QLineEdit();
    formLayout->addRow("Size", _sizeEdit);

    rightLayout->addLayout(formLayout);
    //rightLayout->addLayout(lowerLayout);

    _basket = new QListWidget();
    auto label = new QLabel("Shopping Basket");

    leftLayout->addWidget(label);
    leftLayout->addWidget(_basket);

    mainLayout->addLayout(leftLayout);
    mainLayout->addLayout(rightLayout);

    _searchButton = new QPushButton("Search");
    _openBasketButton = new QPushButton("Open Basket");

    rightLayout->addWidget(_searchButton);
    rightLayout->addWidget(_openBasketButton);

    QObject::connect(_openBasketButton, &QPushButton::clicked, this, &UserGUI::OnOpenButtonClicked);
    QObject::connect(_searchButton, &QPushButton::clicked, this, &UserGUI::OnSearchButtonClicked);

    // create the basket widget

    CreateBasketWidget();



    _basketWidget->hide();

}

void UserGUI::OnSearchButtonClicked() {

    string size = _sizeEdit->text().toStdString();

    _services.FilterBySize(size);

    _coatText->setText(QString::fromStdString(_services.GetCurrentCoat().ToString()));
    _basketWidget->show();
}

void UserGUI::OnOpenButtonClicked() {

    _services.Open();
}

void UserGUI::CreateBasketWidget() {

    _basketWidget = new QWidget();

    auto* mainLayout = new QVBoxLayout(_basketWidget);

    _coatText = new QLabel();

    mainLayout->addWidget(_coatText);

    auto buttonLayout = new QHBoxLayout();


    _addButton = new QPushButton("Add to basket");
    _nextButton = new QPushButton("Next");
    _viewImageButton = new QPushButton("View image");


    buttonLayout->addWidget(_addButton);
    buttonLayout->addWidget(_nextButton);
    buttonLayout->addWidget(_viewImageButton);

    mainLayout->addLayout(buttonLayout);

    QObject::connect(_addButton, &QPushButton::clicked,this,&UserGUI::OnAddButtonClicked);
    QObject::connect(_nextButton, &QPushButton::clicked,this,&UserGUI::OnNextButtonClicked);
    QObject::connect(_viewImageButton, &QPushButton::clicked,this,&UserGUI::OnViewButtonClicked);
    _basketWidget->hide();

}

void UserGUI::OnAddButtonClicked() {

    _services.AddCurrentCoat();
    UpdateBakset();

}

void UserGUI::OnNextButtonClicked() {

    _services.NextCoat();
    _coatText->setText(QString::fromStdString(_services.GetCurrentCoat().ToString()));
}

void UserGUI::OnViewButtonClicked() {

    string command = "start " + _services.GetCurrentCoat().GetPhoto();
    system(command.c_str());
}

void UserGUI::UpdateBakset() {

    _basket->clear();
    for(auto &i : _services.GetShoppingBasket()){
        _basket->addItem(QString::fromStdString(i.ToString()));
    }

}
