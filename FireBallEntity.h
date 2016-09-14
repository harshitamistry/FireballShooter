#pragma once
#include "Entity.h"
#include "AnimatedSprite.h"
#include "SpawnEntity.h"

class FireBallEntity :
	public Entity
{
public:
	FireBallEntity(float x, float y, AnimatedSprite *sprite,SpawnEntity * spawn);
	virtual ~FireBallEntity();
	virtual void update(int delta, Uint8 const *keys);
	virtual void draw(SDL_Renderer *renderer) const;
	virtual bool message(MessageID id, void *data);
private:
	AnimatedSprite *mSprite;
	SpawnEntity *spawner;
	float speed = 0.5;
	
};

