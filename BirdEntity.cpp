#include "BirdEntity.h"
#include<math.h>




BirdEntity::BirdEntity(float x, float y,AnimatedSprite * sprite, SpawnEntity *spawn,DragonEntity *dragon,BIRDTYPE type,int hit)
	: Entity(x, y, (float)sprite->getWidth(), (float)sprite->getHeight()), mSprite(sprite)
{
	this->initialHeight = y;
	this->spawner = spawn;
	this->dragon = dragon;
	this->type = type;
	this->hit = hit;
}

BirdEntity::~BirdEntity()
{
	delete mSprite;
}

void BirdEntity::update(int delta, Uint8 const * keys)
{
	accumulatedDelta += delta;
	switch (type)
	{
	case BIRDTYPE::STRAIGHTBIRD:
	{
		Vector2f displace(-delta*speed,0);
		this->move(displace);
		break;
	}
	case BIRDTYPE::SINEBIRD:
	{
		float x = mScreenWidth - speed*accumulatedDelta;
		float y = 50*std::sin(M_PI*x*0.0075) + initialHeight;
		Vector2f pos(x, y);
		this->setCenter(pos);
		break;
	}
	case BIRDTYPE::CIRCLEBIRD:
	{
		/*
		speed = 0.2;
		float radius = 200;
		int x = mScreenWidth - speed*accumulatedDelta;
		float x2 = forawrdType*((int)(speed*accumulatedDelta) % (int)(radius));
		float y = std::sqrt(std::abs(radius*radius - x2*x2)) + initialHeight;
		if (y == initialHeight) {
			forawrdType = 0 - forawrdType;
		}
		Vector2f pos(x+x2, y);
		this->setCenter(pos);
		*/
		break;
	}
	case BIRDTYPE::TOPLAYERBIRD:
	{
		float y = initialHeight;
		float x = mScreenWidth- accumulatedDelta*speed;
		if (x < forwardX) {
			if (forwardType == 1)
			{
				slope = (float)(dragon->getCenter().y - this->getCenter().y) / ((dragon->getCenter().x - this->getCenter().x));
				forwardType++;
			}
			y = initialHeight + slope*(x - forwardX);
		}
		Vector2f pos(x, y);
		this->setCenter(pos);
		break;
	}
	default:
		break;
	}


	mSprite->update(delta);
}
void BirdEntity::draw(SDL_Renderer * renderer) const
{
	mSprite->draw(renderer, getRect());
}

bool BirdEntity::message(MessageID id, void * data)
{
	if (id == MessageID::STOP_ANIMATION) {
		mSprite->stop();
		return true;
	}
	else if (id == MessageID::START_ANIMATION) {
		mSprite->start();
		return true;
	}
	else if (id == MessageID::REMOVE) {
		if (this->getRect().x < 0)
			return true;
	}
	else if (id == MessageID::BIRD) {
		return true;
	}
	return Entity::message(id, data);
}

void BirdEntity::changeSprite(AnimatedSprite* mSprite) {
	this->mSprite = mSprite;
}