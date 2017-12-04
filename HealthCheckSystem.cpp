#include "HealthCheckSystem.h"
#include "OctTree.h"

HealthCheckSystem::HealthCheckSystem(std::shared_ptr<world> w, std::shared_ptr<EventSystem> EventSys) : System(w, EventSys)
{
	my_System_Name = "HealthCheckSystem";
}

void HealthCheckSystem::damageevents()
{
	std::vector<std::shared_ptr<Event>> allevents = myEventsSystem->getmyevents();

	for (int i = 0; i < allevents.size(); i++)
	{
		if (allevents[i]->mytype == healthdamage)
		{
			std::shared_ptr<healthevenet> newhealthevent = std::static_pointer_cast<healthevenet>(allevents[i]);
			std::shared_ptr<ACC::entity> healthent = myworld->returnmanager()->getentfromid(newhealthevent->takingdamageID);
			std::shared_ptr<healthcomponent> healthE = healthent->getcomponent<healthcomponent>();

			if (healthE->hitdelete.first == true)
			{
				healthE->hitdelete.second = true;
			}
			else if (newhealthevent->damagedealerID != -1)
			{
				std::shared_ptr<ACC::entity> damageent = myworld->returnmanager()->getentfromid(newhealthevent->damagedealerID);
				std::shared_ptr<damagedelt> damagetodo = damageent->getcomponent<damagedelt>();
				healthE->health -= damagetodo->damage;

				std::shared_ptr<soundComponet> newsound = std::make_shared<soundComponet>();
				newsound->mysound = damagetodo->damagesound;
				newsound->mytype = newsound->onetime;
				newsound->position = newhealthevent->position;
				myworld->returnmanager()->createsound(newsound);
			}
		}

		allevents.erase(allevents.begin() + i);
		i--;
	}

	myEventsSystem->setevents(allevents);
}

void HealthCheckSystem::soiwant(std::vector<std::shared_ptr<ACC::entity>> ent)
{
	for (int i = 0; i < ent.size(); i++)
	{
		if (ent[i]->doihave(healthcomponent::TypeID))
		{
			healthobjects.push_back(ent[i]);
		}
	}

}

void HealthCheckSystem::update(float & dt, bool & go)
{
	damageevents();

	OctTree *root = myworld->returnoct();
	bool removefrom = false;

	for (auto num : healthobjects)
	{
		std::shared_ptr<healthcomponent> healthobjects = num->getcomponent<healthcomponent>();
		removefrom = false;

		if (healthobjects->health <= 0 || healthobjects->hitdelete.second == true)
		{
			myworld->returnmanager()->addtodeletelist(num);
			root->removethis(num->returnID(), removefrom);

			if (healthobjects->deathsound.second)
			{
				std::shared_ptr<transposecomponent> mytrans = num->getcomponent<transposecomponent>();
				std::shared_ptr<soundComponet> newsound = std::make_shared<soundComponet>();
				newsound->mysound = healthobjects->deathsound.first;
				newsound->mytype = newsound->onetime;
				newsound->position = mytrans->position;
				myworld->returnmanager()->createsound(newsound);
			}

			std::shared_ptr<thingsiown> mythings = num->getcomponent<thingsiown>();
			if (mythings != NULL)
			{
				for (int i = 0; i < mythings->stuffiown.size(); i++)
				{
					myworld->returnmanager()->addtodeletelist(mythings->stuffiown[i]);
				}
			}
		}
	}
}

void HealthCheckSystem::doihave(std::vector<std::shared_ptr<ACC::entity>> ent)
{

	std::vector<std::shared_ptr<ACC::entity>> ents = ent;

	for (int i = 0; i < healthobjects.size(); i++)
	{
		for (int j = 0; j < ents.size(); j++)
		{
			if (healthobjects[i] == ents[j])
			{
				healthobjects.erase(healthobjects.begin() + i);
				ents.erase(ents.begin() + j);
				j--;
				i--;
				break;
			}
		}

		if (ents.size() == 0)
		{
			break;
		}
	}


}
