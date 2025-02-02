

#pragma once

#include "../utils/validator.h"
#include "../domain/TrenchCoat.h"
#include "../repo/Repo.h"
#include "../services/AdminServices.h"
#include "../services/UserServices.h"

#include <cassert>
#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::find;

class Tests {

public:
    static void TestAll();
private:
    static void TestRepo();
    static void TestValidator();
    static void TestTrenchCoat();
    static void TestAdminServices();
    static void TestUserServices();
    static void TestDataLoader();
};


