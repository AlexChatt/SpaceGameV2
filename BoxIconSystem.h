#pragma once

#include "System.h"
#include <vector>

class BoxIconSystem : public ACC::System
{
private:

	std::vector<std::shared_ptr<ACC::entity>> boxobjects;
	std::shared_ptr<ACC::entity> player;

public:

	BoxIconSystem(std::shared_ptr<world> w);

	void soiwant(std::vector<std::shared_ptr<ACC::entity>> ent);

	void update(float &dt, bool &go);

	std::string returnname()
	{
		return my_System_Name;
	}

	void doihave(std::vector<std::shared_ptr<ACC::entity>> ent);

};