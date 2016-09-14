#pragma once
#include "Entity.h"
#include "AnimatedSprite.h"

class GenericEntity :
	public Entity
{
public:
	GenericEntity(float x, float y, AnimatedSprite *sprite);
	virtual ~GenericEntity();

	virtual void update(int delta, Uint8 const *keys);
	virtual void draw(SDL_Renderer *renderer) const;
	virtual bool message(MessageID id, void *data);
private:
	AnimatedSprite *mSprite;
};

