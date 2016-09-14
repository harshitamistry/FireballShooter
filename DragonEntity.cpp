#include "DragonEntity.h"





DragonEntity::DragonEntity(float x, float y, AnimatedSprite * sprite) 
	: Entity(x, y, (float)sprite->getWidth(), (float)sprite->getHeight()), mSprite(sprite)
{

}

DragonEntity::~DragonEntity()
{
	delete mSprite;
}

void DragonEntity::update(int delta, Uint8 const * keys)
{

	if(speed > -0.45f)
		speed += accel*delta;
	if ((this->getRect().y + this->getRect().h < Entity::mScreenHeight || accel!=0) && (this->getRect().y >= 0 || accel==0)) {
		Vector2f displace(0, delta*speed);
		this->move(displace);
	}
	if (keys[SDL_SCANCODE_W] == 1) {
		accel = -0.001;
	}
	else {
		accel = 0;
		speed = 0.05;
	}
	if (keys[SDL_SCANCODE_A] == 1 && this->getRect().x > 0 ) {
		Vector2f displace(-0.5*delta, 0);
		this->move(displace);
	}
	else if (keys[SDL_SCANCODE_D] == 1 && (this->getRect().x  + this->getRect().w) < Entity::mScreenWidth) {
		Vector2f displace(0.5*delta, 0);
		this->move(displace);
	}
	
	mSprite->update(delta);
}
void DragonEntity::draw(SDL_Renderer * renderer) const
{
	mSprite->draw(renderer, getRect());
}

bool DragonEntity::message(MessageID id, void * data)
{
	if (id == MessageID::STOP_ANIMATION) {
		mSprite->stop();
		return true;
	}
	else if (id == MessageID::START_ANIMATION) {
		mSprite->start();
		return true;
	}
	else if (id == MessageID::DRAGON) {
		return true;
	}
	return Entity::message(id, data);
}
