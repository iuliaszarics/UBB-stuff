

#include <QHBoxLayout>
#include "UserSaveGUI.h"
#include "../data_loader/CSVDataLoader.h"
#include "UserGUI.h"
#include "../data_loader/HTMLDataLoader.h"

UserSaveGUI::UserSaveGUI(const UserServices &userSrv) {
    _userSrv = userSrv;

    auto* mainLayout = new QHBoxLayout(this);

    _csvButton = new QPushButton("Save to CSV");
    _htmlButton = new QPushButton("Save to HTML");

    mainLayout->addWidget(_csvButton);
    mainLayout->addWidget(_htmlButton);

    connect(_csvButton, &QPushButton::clicked, this, &UserSaveGUI::OnCSVButtonClicked);
    connect(_htmlButton, &QPushButton::clicked, this, &UserSaveGUI::OnHTMLButtonClicked);

}

void UserSaveGUI::OnCSVButtonClicked() {
    hide();

    _userSrv.InitCSVLoader();
    auto* userGUI = new UserGUI(_userSrv);

    userGUI->show();
}

void UserSaveGUI::OnHTMLButtonClicked() {
    hide();

    _userSrv.InitHTMLLoader();
    auto* userGUI = new UserGUI(_userSrv);

    userGUI->show();
}
