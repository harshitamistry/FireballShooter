#pragma once
#include "Game.h"
#include "Entity.h"
#include "AnimatedSprite.h"

class DragonEntity :
	public Entity
{
public:
	DragonEntity(float x, float y, AnimatedSprite *sprite);
	virtual ~DragonEntity();
	virtual void update(int delta, Uint8 const *keys);
	virtual void draw(SDL_Renderer *renderer) const;
	virtual bool message(MessageID id, void *data);
private:
	AnimatedSprite *mSprite;
	float speed = 0.05;
	float accel = 0;
};

