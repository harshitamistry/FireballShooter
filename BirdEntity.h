#pragma once
#include "Entity.h"
#include "AnimatedSprite.h"
#include "SpawnEntity.h"

enum class BIRDTYPE {
	STRAIGHTBIRD,
	SINEBIRD,
	CIRCLEBIRD,
	TOPLAYERBIRD,
};

class BirdEntity :
	public Entity
{
public:
	BirdEntity(float x, float y, AnimatedSprite *sprite, SpawnEntity * spawn,DragonEntity *dragon,BIRDTYPE type,int hit);
	virtual ~BirdEntity();
	virtual void update(int delta, Uint8 const *keys);
	virtual void draw(SDL_Renderer *renderer) const;
	virtual bool message(MessageID id, void *data);
	void changeSprite(AnimatedSprite* mSprite);
	int hit;
private:
	AnimatedSprite *mSprite;
	SpawnEntity *spawner;
	DragonEntity *dragon;
	float speed = 0.25;
	BIRDTYPE type;
	int accumulatedDelta = 0;
	float initialHeight = 0;
	int forwardType = 1;
	int forwardX = mScreenWidth- 200;
	float slope = 0;
};