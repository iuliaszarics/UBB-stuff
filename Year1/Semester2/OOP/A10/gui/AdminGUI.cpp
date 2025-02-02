

#include <QHBoxLayout>
#include <QLabel>
#include "AdminGUI.h"
#include "../utils/validator.h"
#include "../model/CoatModel.h"
#include <QGraphicsScene>
#include <QGraphicsView>

//#include <QChart>
//#include <QBarSeries>
//#include <QBarCategoryAxis>
//#include <QValueAxis>
//#include <QBarSet>

AdminGUI::AdminGUI(AdminServices services){

    _services = services;

    BuildGUI();
    PopulateList();
}

void AdminGUI::BuildGUI() {


    QHBoxLayout* mainLayout = new QHBoxLayout(this);


    _tableView = new QTableView();
    mainLayout->addWidget(_tableView);

    auto* rightLayout = new QVBoxLayout();

    QLabel* sizeLabel = new QLabel("Size");
    _sizeEdit = new QLineEdit();
    QLabel* priceLabel = new QLabel("Price");
    _priceEdit = new QLineEdit();
    QLabel* colorLabel = new QLabel("Color");
    _colorEdit = new QLineEdit();
    QLabel* quantityLabel = new QLabel("Quantity");
    _quantityEdit = new QLineEdit();
    QLabel* photoLabel = new QLabel("Photo");
    _photoEdit = new QLineEdit();

    auto* gridLayout = new QGridLayout();

    gridLayout->addWidget(sizeLabel, 0, 0);
    gridLayout->addWidget(_sizeEdit, 0, 1);
    gridLayout->addWidget(priceLabel, 1, 0);
    gridLayout->addWidget(_priceEdit, 1, 1);
    gridLayout->addWidget(colorLabel, 2, 0);
    gridLayout->addWidget(_colorEdit, 2, 1);
    gridLayout->addWidget(quantityLabel, 3, 0);
    gridLayout->addWidget(_quantityEdit, 3, 1);
    gridLayout->addWidget(photoLabel, 4, 0);
    gridLayout->addWidget(_photoEdit, 4, 1);

    auto* horizontalLayout = new QHBoxLayout();

    _showGraphicButton = new QPushButton("Show Graphic");
    _addButton = new QPushButton("Add");
    _removeButton = new QPushButton("Remove");
    _updateButton = new QPushButton("Update");
    _undoButton = new QPushButton("Undo");
    _redoButton = new QPushButton("Redo");

    horizontalLayout->addWidget(_addButton);
    horizontalLayout->addWidget(_removeButton);
    horizontalLayout->addWidget(_updateButton);
    horizontalLayout->addWidget(_undoButton);
    horizontalLayout->addWidget(_redoButton);
    //horizontalLayout->addWidget(_showGraphicButton);

    rightLayout->addLayout(gridLayout);
    rightLayout->addLayout(horizontalLayout);

    mainLayout->addLayout(rightLayout);

    // set slots
    QObject::connect(_addButton, &QPushButton::clicked, this, &AdminGUI::OnAddButtonClicked);
    QObject::connect(_removeButton, &QPushButton::clicked, this, &AdminGUI::OnRemoveButtonClicked);
    QObject::connect(_updateButton, &QPushButton::clicked, this, &AdminGUI::OnUpdateButtonClicked);
    QObject::connect(_showGraphicButton, &QPushButton::clicked, this, &AdminGUI::OnShowGraphicButtonClicked);

    QObject::connect(_undoButton, &QPushButton::clicked, this, &AdminGUI::OnUndo);
    QObject::connect(_redoButton, &QPushButton::clicked, this, &AdminGUI::OnRedo);

    QAction* undo = new QAction(this);
    undo->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Z));
    addAction(undo);
    connect(undo, &QAction::triggered, this, &AdminGUI::OnUndo);

    QAction* redo = new QAction(this);
    redo->setShortcut(QKeySequence(Qt::CTRL + Qt::Key_Y));
    addAction(redo);
    connect(redo, &QAction::triggered, this, &AdminGUI::OnRedo);
}


void AdminGUI::PopulateList() {


//    _coatListWidget->clear();
//
//    for(auto& coat : _services.GetData()) {
//        QListWidgetItem* item = new QListWidgetItem(QString::fromStdString(coat.ToString()));
//        _coatListWidget->addItem(item);
//    }

    auto* model = new CoatModel(_services.GetData());
    _tableView->setModel(model);

    _tableView->resizeColumnsToContents();
    _tableView->resizeRowsToContents();
    _tableView->show();
}

void AdminGUI::OnAddButtonClicked() {


    string size = _sizeEdit->text().toStdString();
    string price = _priceEdit->text().toStdString();
    string color = _colorEdit->text().toStdString();
    string quantity = _quantityEdit->text().toStdString();
    string photo = _photoEdit->text().toStdString();

    try{
        Validator::ValidateSize(size);
        Validator::ValidatePrice(price);
        Validator::ValidateColour(color);
        Validator::ValidateQuantity(quantity);
        Validator::ValidatePhoto(photo);
    }
    catch(std::exception& e) {
        QWidget* warning = new QWidget();
        QLabel* label = new QLabel(e.what());
        QVBoxLayout* layout = new QVBoxLayout();
        layout->addWidget(label);
        warning->setLayout(layout);
        warning->show();
        return;
    }

    _services.Add(size, color, price, quantity, photo);

    PopulateList();
}

void AdminGUI::OnRemoveButtonClicked() {

    int position = _tableView->currentIndex().row();

    if(position == -1) {
        QWidget* warning = new QWidget();
        QLabel* label = new QLabel("No item selected");
        QVBoxLayout* layout = new QVBoxLayout();
        layout->addWidget(label);
        warning->setLayout(layout);
        warning->show();
        return;
    }

    TrenchCoat coat = _services.GetCoat(position);

    string size = std::to_string(coat.GetSize());
    string color = coat.GetColour();
    _services.Delete(size, color);

    PopulateList();
}

void AdminGUI::OnUpdateButtonClicked() {

    int position = _tableView->currentIndex().row();

    if(position == -1) {
        QWidget* warning = new QWidget();
        QLabel* label = new QLabel("No item selected");
        QVBoxLayout* layout = new QVBoxLayout();
        layout->addWidget(label);
        warning->setLayout(layout);
        warning->show();
        return;
    }

    TrenchCoat coat = _services.GetCoat(position);
    string size = std::to_string(coat.GetSize());
    string color = coat.GetColour();

    string price = _priceEdit->text().toStdString();
    string quantity = _quantityEdit->text().toStdString();
    string photo = _photoEdit->text().toStdString();

    try{
        if(!price.empty()){
            Validator::ValidatePrice(price);
        }
        else price = std::to_string(coat.GetPrice());
        if(!quantity.empty()) {
            Validator::ValidateQuantity(quantity);
        }
        else quantity = std::to_string(coat.GetQuantity());

        if(!photo.empty()) {
            Validator::ValidatePhoto(photo);
        }
        else photo = coat.GetPhoto();
    }
    catch(std::exception& e) {
        QWidget* warning = new QWidget();
        QLabel* label = new QLabel(e.what());
        QVBoxLayout* layout = new QVBoxLayout();
        layout->addWidget(label);
        warning->setLayout(layout);
        warning->show();
        return;
    }

    _services.Update(size, color, price, quantity, photo);
    PopulateList();
}

void AdminGUI::OnUndo() {
    try{
        _services.Undo();
    }
    catch(std::exception& e) {
        QWidget* warning = new QWidget();
        QLabel* label = new QLabel(e.what());
        QVBoxLayout* layout = new QVBoxLayout();
        layout->addWidget(label);
        warning->setLayout(layout);
        warning->show();
    }
    PopulateList();
}

void AdminGUI::OnRedo() {
    try{
        _services.Redo();
    }
    catch(std::exception& e) {
        QWidget* warning = new QWidget();
        QLabel* label = new QLabel(e.what());
        QVBoxLayout* layout = new QVBoxLayout();
        layout->addWidget(label);
        warning->setLayout(layout);
        warning->show();
    }
    PopulateList();
}

void AdminGUI::OnShowGraphicButtonClicked() {

    auto* widget = new QWidget();

//    // create a bar chart with the colors of the coats
//
//
//    auto* scene = new QGraphicsScene();
//    auto* view = new QGraphicsView(scene);
//
//
//    // create a bar chart with the colors of the coats
//    auto* chart = new QChart();
//    auto* series = new QBarSeries();
//    auto* axisX = new QBarCategoryAxis();
//    auto* axisY = new QValueAxis();
//
//    // add the coats to the chart
//    for(auto& coat : _services.GetData()) {
//        auto* set = new QBarSet(QString::fromStdString(coat.GetColour()));
//        *set << coat.GetQuantity();
//        series->append(set);
//    }
//
//    chart->addSeries(series);
//
//    // add the scene to the view
//
//    view->setScene(scene);
//    view->show();

    widget->show();

}
