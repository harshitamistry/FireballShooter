#include "GenericEntity.h"


GenericEntity::GenericEntity(float x, float y, AnimatedSprite * sprite)
	:	Entity(x, y, (float)sprite->getWidth(), (float)sprite->getHeight()), mSprite(sprite)
{
}

GenericEntity::~GenericEntity()
{
	delete mSprite;
}

void GenericEntity::update(int delta, Uint8 const * keys)
{
	mSprite->update(delta);
}

void GenericEntity::draw(SDL_Renderer * renderer) const
{
	mSprite->draw(renderer, getRect());
}

bool GenericEntity::message(MessageID id, void * data)
{
	if (id == MessageID::STOP_ANIMATION) {
		mSprite->stop();
		return true;
	}
	else if (id == MessageID::START_ANIMATION) {
		mSprite->start();
		return true;
	}
	return Entity::message(id, data);
}
