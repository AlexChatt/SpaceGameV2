#pragma once

#include "System.h"
#include <vector>

class PhysicsSystsem  : public ACC::System
{
private:

	std::vector<std::shared_ptr<ACC::entity>> physicsobjects;

public:

	PhysicsSystsem(std::shared_ptr<world> w);

	void soiwant(std::vector<std::shared_ptr<ACC::entity>> ent);

	void update(float &dt, bool &go);

	std::string returnname()
	{
		return my_System_Name;
	}

	void doihave(std::vector<std::shared_ptr<ACC::entity>> ent);



};