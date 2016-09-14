#pragma once
#include "Entity.h"
#include "AnimatedSprite.h"
#include "SpawnEntity.h"
#include "BirdEntity.h"


class WaveEntity :
	public Entity
{
public:
	WaveEntity(float x, float y, SpawnEntity * spawn, DragonEntity *dragon, BIRDTYPE type,int size);
	virtual ~WaveEntity();
	virtual void update(int delta, Uint8 const *keys);
	virtual void draw(SDL_Renderer *renderer) const;
	virtual bool message(MessageID id, void *data);
private:
	std::list<Entity *> mEntities;
	SpawnEntity *spawner;
	DragonEntity *dragon;
	BIRDTYPE type;
	int size;
};