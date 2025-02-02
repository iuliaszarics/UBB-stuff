#include "domain.h"
#include "controller.h"
#include "repository.h"
#include <cassert>
#include <string>
#include <iostream>
#include "tests.h"

void testDomain()
{
    TrenchCoat auxTrenchCoat = TrenchCoat();
    assert(auxTrenchCoat.getTrenchID() == 0);
    if (auxTrenchCoat == TrenchCoat())
        assert(true);

    TrenchCoat trenchCoat(1, 2, "red", 3, 4, "link");
    assert((trenchCoat == TrenchCoat(1, 6, "red", 3, 4, "link") == false));
    assert(trenchCoat.getTrenchID() == 1);
    assert(trenchCoat.getTrenchSize() == 2);
    assert(trenchCoat.getTrenchColour() == "red");
    assert(trenchCoat.getTrenchPrice() == 3);
    assert(trenchCoat.getTrenchQuantity() == 4);
    assert(trenchCoat.getTrenchPhotographyLink() == "link");

    trenchCoat.setTrenchID(5);
    assert(trenchCoat.getTrenchID() == 5);

    trenchCoat.setTrenchSize(6);
    assert(trenchCoat.getTrenchSize() == 6);

    trenchCoat.setTrenchColour("blue");
    assert(trenchCoat.getTrenchColour() == "blue");

    trenchCoat.setTrenchPrice(7);
    assert(trenchCoat.getTrenchPrice() == 7);

    trenchCoat.setTrenchQuantity(8);
    assert(trenchCoat.getTrenchQuantity() == 8);

    trenchCoat.setTrenchPhotographyLink("link2");
    assert(trenchCoat.getTrenchPhotographyLink() == "link2");

    std::cout << "Domain tests passed!" << std::endl;
}

void testController() {
    Repository repository;
    Controller controller(repository);
    assert(controller.addTrenchCoat(1, 2, "red", 3, 4, "photo") == true);
    assert(controller.addTrenchCoat(1, 2, "red", 3, 4, "photo") == false);
    assert(controller.addTrenchCoat(2, 2, "red", 3, 4, "photo") == true);
    assert(controller.addTrenchCoat(3, 2, "red", 3, 4, "photo") == true);
    assert(controller.addTrenchCoat(4, 2, "red", 3, 4, "photo") == true);
    assert(controller.addTrenchCoat(5, 2, "red", 3, 4, "photo") == true);
    assert(controller.addTrenchCoat(6, 2, "red", 3, 4, "photo") == true);
    assert(controller.addTrenchCoat(7, 2, "red", 3, 4, "photo") == true);
    assert(controller.addTrenchCoat(8, 2, "red", 3, 4, "photo") == true);
    assert(controller.addTrenchCoat(9, 2, "red", 3, 4, "photo") == true);
    assert(controller.addTrenchCoat(10, 2, "red", 3, 4, "photo") == true);
    assert(controller.addTrenchCoat(11, 2, "red", 3, 4, "photo") == true);
    assert(controller.addTrenchCoat(12, 2, "red", 3, 4, "photo") == true);
    assert(controller.addTrenchCoat(13, 2, "red", 3, 4, "photo") == true);
    assert(controller.addTrenchCoat(14, 2, "red", 3, 4, "photo") == true);
    assert(controller.addTrenchCoat(15, 2, "red", 3, 4, "photo") == true);

    assert(controller.removeTrenchCoat(1) == true);
    assert(controller.removeTrenchCoat(1) == false);
    assert(controller.removeTrenchCoat(2) == true);
    assert(controller.updateTrenchCoat(3, 2, 5, "blue", 6, 7, "photo2") == true);
    assert(controller.updateTrenchCoat(3, 2, 5, "blue", 6, 7, "photo2") == false);
    assert(controller.updateTrenchCoat(2, 3, 5, "blue", 6, 7, "photo2") == true);

    assert(controller.trenchCoatExists(3));

    assert(controller.getTrenchCoat(3).getTrenchID() == 3);

    assert(controller.getSize() == 13);

    controller.setFileName("test.txt");
    assert(controller.getFileName() == "test.txt");

    std::vector<TrenchCoat> trenchCoats = controller.getAllTrenchCoats();
    assert(trenchCoats.size() == 13);

    std::vector<TrenchCoat> filteredTrenchCoats = controller.filterBySize(2);
    assert(filteredTrenchCoats.size() == 12);

    controller.saveProgress();

    for (auto& trenchCoat : trenchCoats)
        controller.removeTrenchCoat(trenchCoat.getTrenchID());
    assert(controller.getSize() == 0);

    controller.loadFromFile();
    assert(controller.getSize() == 13);
    std::cout << "Controller tests passed!" << std::endl;
}

void testRepository() {
    std::cout << "Testing Repository" << std::endl;
    Repository repository;
    repository.addTrenchCoat(1, 2, "red", 3, 4, "link");
    assert(repository.getSize() == 1);

    repository.addTrenchCoat(2, 4, "blue", 4, 5, "link2");
    repository.addTrenchCoat(3, 4, "green", 5, 6, "link3");
    repository.addTrenchCoat(4, 5, "yellow", 6, 7, "link4");
    repository.addTrenchCoat(5, 6, "black", 7, 8, "link5");
    assert(repository.getSize() == 5);
    assert(repository.validID(1));
    assert(repository.addTrenchCoat(5, 6, "black", 7, 8, "link5") == false);

    repository.removeTrenchCoat(1);
    assert(repository.getSize() == 4);
    assert(!repository.validID(1));

    repository.updateTrenchCoat(2, 1, 2, "red", 3, 4, "link");
    assert(repository.getTrenchCoat(1).getTrenchID() == 1);
    assert(repository.getTrenchCoat(1).getTrenchSize() == 2);

    TrenchCoat trenchCoat = repository.getTrenchCoat(1);
    assert(trenchCoat.getTrenchID() == 1);

    std::vector<TrenchCoat> trenchCoats = repository.getAllTrenchCoats();
    assert(trenchCoats.size() == 4);

    repository.setFileName("test.txt");
    assert(repository.getFileName() == "test.txt");

    repository.writeToFile();
    repository.readFromFile();
    assert(repository.getSize() == 8);

    assert(repository.getTrenchCoat(1).getTrenchID() == 1);

    TrenchCoat trenchCoat1 = repository.getTrenchCoat(20);
    assert(trenchCoat1.getTrenchID() == -1);

}