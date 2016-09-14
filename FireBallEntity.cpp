#include "FireBallEntity.h"





FireBallEntity::FireBallEntity(float x, float y, AnimatedSprite * sprite,SpawnEntity *spawn)
	: Entity(x, y, (float)sprite->getWidth(), (float)sprite->getHeight()), mSprite(sprite)
{
	this->spawner = spawn;
}

FireBallEntity::~FireBallEntity()
{
	delete mSprite;
}

void FireBallEntity::update(int delta, Uint8 const * keys)
{

	
	Vector2f displace(delta*speed, 0);
	this->move(displace);
	mSprite->update(delta);
}
void FireBallEntity::draw(SDL_Renderer * renderer) const
{
	mSprite->draw(renderer, getRect());
}

bool FireBallEntity::message(MessageID id, void * data)
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
		if (this->getRect().x + this->getRect().w > mScreenWidth)
			return true;
	}
	else if (id == MessageID::FIREBALL) {
		return true;
	}
	return Entity::message(id, data);
}