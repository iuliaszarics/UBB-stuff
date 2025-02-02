

#include "DataLoader.h"

class CSVDataLoader : public DataLoader {

public:

    void Save(vector<TrenchCoat> vector) override;
    void Open() override;
};