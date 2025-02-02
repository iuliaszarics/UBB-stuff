

#include <QHBoxLayout>
#include "../gui/StartGUI.h"
#include "../gui/AdminGUI.h"
#include "../gui/UserGUI.h"
#include "../gui/UserSaveGUI.h"
#include "../services/UserServices.h"


void StartGUI::OnAdminButtonClicked() {

    hide();
    _adminWidget = new AdminGUI(_adminSrv);
    _adminWidget->show();

}

void StartGUI::OnUserButtonClicked() {

    hide();
    _userWidget = new UserSaveGUI(_userSrv);
    _userWidget->show();
}

StartGUI::StartGUI(const UserServices& userSrv, const AdminServices& adminSrv) {

    _userSrv = userSrv;
    _adminSrv = adminSrv;

    auto* mainLayout = new QHBoxLayout(this);

    _adminButton = new QPushButton("Admin mode");
    _userButton = new QPushButton("User mode");

    mainLayout->addWidget(_adminButton);
    mainLayout->addWidget(_userButton);

    connect(_adminButton, &QPushButton::clicked, this, &StartGUI::OnAdminButtonClicked);
    connect(_userButton, &QPushButton::clicked, this, &StartGUI::OnUserButtonClicked);
}
