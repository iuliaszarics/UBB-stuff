#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_OOP89.h"

class OOP89 : public QMainWindow
{
    Q_OBJECT

public:
    OOP89(QWidget *parent = nullptr);
    ~OOP89();

private:
    Ui::OOP89Class ui;
};
