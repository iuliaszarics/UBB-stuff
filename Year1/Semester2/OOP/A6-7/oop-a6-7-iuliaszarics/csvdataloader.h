#pragma once
#include "dataloader.h"

class CSVDataLoader : public DataLoader {

public:

    void Save(vector<TrenchCoat> vector) override;
    void Open() override;
};