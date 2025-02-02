

#include <QWidget>
#include <QPushButton>
#include "../services/AdminServices.h"
#include "../services/UserServices.h"

class StartGUI : public QWidget {

    private:

    QPushButton* _adminButton;
    QPushButton* _userButton;

    QWidget* _adminWidget;
    QWidget* _userWidget;

    UserServices _userSrv;
    AdminServices _adminSrv;
    public:

        StartGUI(const UserServices& userSrv, const AdminServices& adminSrv);

    private slots:
    void OnAdminButtonClicked();
    void OnUserButtonClicked();
};

