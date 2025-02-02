

#include <QWidget>
#include <QPushButton>
#include "../services/AdminServices.h"
#include "../services/UserServices.h"

class UserSaveGUI : public QWidget{

private:

    QPushButton* _csvButton;
    QPushButton* _htmlButton;



    UserServices _userSrv;
public:

    explicit UserSaveGUI(const UserServices& userSrv);

private slots:

    void OnCSVButtonClicked();
    void OnHTMLButtonClicked();

};


