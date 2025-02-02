#include <iostream>
#include "domain/TrenchCoat.h"
#include "repo/FileRepo.h"
#include "services/UserServices.h"
#include "services/AdminServices.h"
#include "tests/Tests.h"
#include "data_loader/HTMLDataLoader.h"
#include "data_loader/CSVDataLoader.h"
#include "gui/AdminGUI.h"
#include "gui/UserGUI.h"
#include "gui/StartGUI.h"

#include <QTWidgets/QApplication>
#include <QtWidgets/QLabel>


int main(int argc, char** argv) {

        //Tests::TestAll();

        QApplication a(argc, argv);

        string filename = "../data.txt";
        FileRepo repo(filename);
        AdminServices services(&repo);
        UserServices userServices(&repo);

        StartGUI startGUI(userServices, services);
        startGUI.show();

        return QApplication::exec();
}
