#pragma once
#include "Entity.h"
#include "DragonEntity.h"

#include <list>
class SpawnEntity :
	public Entity
{
public:
	SpawnEntity();
	virtual ~SpawnEntity();
	virtual void update(int delta, Uint8 const *keys);
	virtual void draw(SDL_Renderer *renderer) const;
	virtual bool message(MessageID id, void *data);
	static bool checkCollision(Entity* it1, Entity* it2);
	bool status = false;;
private:
	std::list<Entity *> mEntities;
	int fireBallCounter = 0;
	float fireBallTime = 0;
	DragonEntity *dragon;
	float lastwavetime = 0;
	int wavenumber = 0;
	
};

