
#include "Tests.h"
#include "../data_loader/CSVDataLoader.h"

void Tests::TestAll() {

    std::cout<<"Starting testing...\n";

    Tests::TestValidator();
    Tests::TestTrenchCoat();
    Tests::TestRepo();
    Tests::TestAdminServices();
    Tests::TestUserServices();
    Tests::TestDataLoader();

    std::cout<<"All tests passed!\n";
}

void Tests::TestTrenchCoat(){
    // Test Trench Coat getters

    TrenchCoat coat = TrenchCoat(10, 100, 1, "red", "photo1");

    assert(coat.GetSize() == 10);

    assert(coat.GetPrice() == 100);

    assert(coat.GetQuantity() == 1);

    assert(coat.GetColour() == "red");

    assert(coat.GetPhoto() == "photo1");

    // Test Trenchcoat string

    assert(coat.ToString() == "Size: 10 Price: 100 Quantity: 1 Colour: red Photo: photo1");

    std::cout<<"TrenchCoat tests passed!\n";
}

void Tests::TestValidator() {

    //Test ValidateSize

    try
    {
        Validator::ValidateSize("1");
    }
    catch (...)
    {
        assert(false);
    }

    try
    {
        Validator::ValidateSize("a");
        assert(false);
    }
    catch (std::exception& e)
    {
        assert(std::string(e.what()) == std::string("Size must be a number"));
    }

    //Test ValidatePrice

    try
    {
        Validator::ValidatePrice("1");
    }
    catch (...)
    {
        assert(false);
    }

    try
    {
        Validator::ValidatePrice("a");
        assert(false);
    }
    catch (std::exception& e)
    {
        assert(std::string(e.what()) == std::string("Price must be a number"));
    }

    //Test ValidateQuantity

    try
    {
        Validator::ValidateQuantity("1");
    }
    catch (...)
    {
        assert(false);
    }

    try
    {
        Validator::ValidateQuantity("a");
        assert(false);
    }
    catch (std::exception& e)
    {
        assert(std::string(e.what()) == std::string("Quantity must be a number"));
    }

    //Test ValidateColour

    try
    {
        Validator::ValidateColour("red");
    }
    catch (...)
    {
        assert(false);
    }

    try
    {
        Validator::ValidateColour("");
        assert(false);
    }
    catch (std::exception& e)
    {
        assert(std::string(e.what()) == std::string("Colour must not be empty"));
    }

    //Test ValidatePhotograph

    try
    {
        Validator::ValidatePhoto("photo1");
    }
    catch (...)
    {
        assert(false);
    }

    try
    {
        Validator::ValidatePhoto("");
        assert(false);
    }
    catch (std::exception& e)
    {
        assert(std::string(e.what()) == std::string("Photo must not be empty"));
    }

    std::cout<<"Validator tests passed!\n";

}

void Tests::TestRepo() {

        Repo repo;
        TrenchCoat coat1 = TrenchCoat(1, 1, 1, "red", "photo1");
        TrenchCoat coat2 = TrenchCoat(2, 2, 2, "blue", "photo2");
        TrenchCoat coat3 = TrenchCoat(33, 33, 33, "green", "photo3");

        //Test Add

        repo.Add(coat1);
        repo.Add(coat2);
        repo.Add(coat3);
        try {
            repo.Add(coat1);
            assert(false);
        }
        catch (RepoException& e){
            assert(e.what() == std::string("The coat is already in the repo!"));
        }

        //Test Delete

        repo.Delete(coat2);

        try {
            repo.Delete(coat2);
            assert(false);
        }
        catch (RepoException& e){
            assert(e.what() == std::string("The coat is not in the repo!"));
        }

        //Test Update

        repo.Update(coat1, coat2);

        try {
            repo.Update(coat1, coat2);
            assert(false);
        }
        catch (RepoException& e){
            assert(e.what() == std::string("The coat is not in the repo!"));
        }

        //Test GetData
        vector<TrenchCoat> vector = repo.GetData();

        assert(vector[0] == coat2);
        assert(vector[1] == coat3);

        std::cout<<"Repo tests passed!\n";
}

void Tests::TestAdminServices() {

    Repo repo;

    repo.Add(TrenchCoat(1, 1, 1, "red", "photo1"));
    repo.Add(TrenchCoat(2, 2, 2, "blue", "photo2"));
    repo.Add(TrenchCoat(3, 3, 3, "green", "photo3"));

    AdminServices adminServices(&repo);

    //Test Add
    try {
        adminServices.Add("1", "red", "1", "1", "photo1");
        assert(false);
    }
    catch (std::exception& e){
        assert(e.what() == std::string("The coat is already in the repo!"));
    }

    try {
        adminServices.Add("4", "yellow", "4", "4", "photo4");
        assert(true);
    }
    catch (std::exception& e){
        assert(false);
    }

    //Test Remove

    try {
        adminServices.Delete("1", "red");
        assert(true);
    }
    catch (std::exception& e){
        assert(false);
    }

    try {
        adminServices.Delete("1", "red");
        assert(false);
    }
    catch (std::exception& e){
        assert(e.what() == std::string("The coat is not in the repo!"));
    }


    //Test Update

    try {
        adminServices.Update("2", "blue", "20", "2", "photo2");
        assert(true);
    }
    catch (std::exception& e){
        assert(false);
    }

    try {
        adminServices.Update("211", "blue", "20", "2", "photo2");

        assert(false);
    }
    catch (std::exception& e){
        assert(e.what() == std::string("The coat is not in the repo!"));
    }

    //Test GetData
    auto vector = adminServices.GetData();

    assert(vector.size() == 3);

    assert(vector[0] == TrenchCoat(2, 1, 1, "blue", "photo1"));
    assert(vector[1] == TrenchCoat(3, 3, 3, "green", "photo3"));
    assert(vector[2] == TrenchCoat(4, 4, 4, "yellow", "photo4"));


    std::cout<<"AdminServices tests passed!\n";
}

void Tests::TestDataLoader() {

        CSVDataLoader dataLoader;

        dataLoader.Save(vector<TrenchCoat>{TrenchCoat(1, 1, 1, "red", "photo1"),
                                        TrenchCoat(2, 2, 2, "blue", "photo2"),
                                        TrenchCoat(3, 3, 3, "green", "photo3")});

        //dataLoader.Open();

        std::cout<<"DataLoader tests passed!\n";

}

void Tests::TestUserServices() {

    Repo repo;
    CSVDataLoader dataLoader;

    repo.Add(TrenchCoat(1, 1, 1, "red", "photo1"));
    repo.Add(TrenchCoat(1, 2, 2, "blue", "photo2"));
    repo.Add(TrenchCoat(2, 3, 3, "green", "photo3"));

    UserServices userServices(&repo, &dataLoader);
    //Test FilterBySize

    userServices.FilterBySize("1");

    userServices.FilterBySize("");

    // Test UserAdd

    userServices.FilterBySize("1");

    userServices.AddCurrentCoat();

    try
    {
        userServices.AddCurrentCoat();
        assert(false);
    }
    catch (std::exception& e)
    {
        assert(e.what() == std::string("The coat is out of stock!"));
    }

    assert(userServices.GetTotalPrice() == 1);

    userServices.NextCoat();

    assert(userServices.GetCurrentCoat() == TrenchCoat(1, 2, 2, "blue", "photo2"));

    userServices.AddCurrentCoat();
    userServices.AddCurrentCoat();

    assert(userServices.GetTotalPrice() == 5);

    userServices.NextCoat();

    assert(userServices.GetCurrentCoat() == TrenchCoat(1, 1, 1, "red", "photo1"));

    auto array = userServices.GetShoppingBasket();

    assert(array.size() == 2);


    std::cout<<"UserServices tests passed!\n";
}
