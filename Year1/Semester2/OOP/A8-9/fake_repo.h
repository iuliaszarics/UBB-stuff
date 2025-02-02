#pragma once
#ifndef FAKE_REPO_H
#define FAKE_REPO_H

#include "TrenchCoatRepo.h"
class fake_repo : public TrenchCoatRepo {
public:
	fake_repo();
	~fake_repo();
	void updateTrench(int price, string name, string photo, string size)override;
};


#endif FAKE_REPO_H