#pragma once
#include "dataloader.h"

class HTMLDataLoader : public DataLoader {

public:

    void Save(vector<TrenchCoat> vector) override;
    void Open() override;
};