#include "toenemycapship.h"
#include "entity.h"
#include "world.h"
#include "OctTree.h"

void toenemycapship::setcaptarget(std::shared_ptr<ACC::entity> captar)
{
	capattack = captar;
}

void toenemycapship::start()
{

	mytrans = me->getcomponent<transposecomponent>();
	myphys = me->getcomponent<physics>();
	mydir = me->getcomponent<directioncomponent>();
	myai = me->getcomponent<AIcomp>();
	mycol = me->getcomponent<collisioncomp>();

	captrans = capattack->getcomponent<transposecomponent>();
}

void toenemycapship::run(float dt, std::shared_ptr<world> myworld)
{
	float lookahead = glm::max((glm::length(myphys->velocity) / myphys->maxspeed) * 80, mycol->mysphere->rad);

	if (glm::length(mytrans->position - captrans->position) < 50)
	{
		time = 0;
	}
	else
	{
		glm::vec3 seekforce = myai->MovCon.seekobject(captrans->position) * 0.7f;
		glm::vec3 avoidforce = glm::vec3(0, 0, 0);

		Ray newray;
		newray.pos = mytrans->position;
		newray.dir = mydir->newdirect;
		std::vector<int> idstomiss{ me->returnID() };
		myworld->returnoct()->getclosesttoray(newray, idstomiss, lookahead);

		raycollinfo raycol = myworld->returnoct()->returnraycol();
		if (raycol.hit == true)
		{
			avoidforce = myai->MovCon.avoidobject(raycol.hitpoint, raycol.center);
		}
		myphys->force = seekforce + avoidforce;
	}

	glm::vec3 attackvec = myphys->velocity + mytrans->position;

	if (attackvec.x == mytrans->position.x && attackvec.z == mytrans->position.z)
	{
		attackvec.x += 1;
	}

	glm::mat4 lookatmatrix = glm::transpose(glm::lookAt(attackvec, mytrans->position, glm::vec3(0.0f, 1.0f, 0.0f)));
	glm::quat newrotation = glm::toQuat(lookatmatrix);
	float angleofRot = glm::clamp(2.0f * dt, 0.0f, 1.0f);
	mytrans->myquat = glm::slerp(mytrans->myquat, newrotation, angleofRot);
	mydir->newdirect = mytrans->myquat * mydir->direction;

	time -= dt;

}

void toenemycapship::end()
{


}

