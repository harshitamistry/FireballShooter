#pragma once

#include <SDL.h>

#include "Sprite.h"
#include "Vector2f.h"

enum class MessageID {
	STOP_ANIMATION,
	START_ANIMATION,
	HIT,
	ATTACH_PLAYER,
	SCREEN_SIZE,
	REMOVE,
	DRAGON,
	BIRD,
	FIREBALL,
	WAVE,
	CHECKBIRDS,
	CHECKDRAGON,
};


class Entity {
	static int const OUTLINE_OFFSET = 3;

public:
	static int const mScreenWidth = 1000;
	static int const mScreenHeight = 650;

public:
	Entity(float x, float y, float w, float h)
		: mPosition(x, y), mSize(w,h) {

	}
	virtual ~Entity() { }

	SDL_Rect getRect() const {
		SDL_Rect r;
		r.x = (int)mPosition.x;
		r.y = (int)mPosition.y;
		r.w = (int)mSize.x;
		r.h = (int)mSize.y;
		return r;
	}

	Vector2f getCenter() const {
			return Vector2f(mPosition.x + mSize.x * 0.5f, mPosition.y + mSize.y * 0.5f);
	}

	void move(Vector2f displacement) {
		mPosition.x += displacement.x;
		mPosition.y += displacement.y;
	}

	bool contains(Vector2f displacement) const {
		return	displacement.x >= mPosition.x &&
				displacement.x <= (mPosition.x + mSize.x) &&
				displacement.y >= mPosition.y &&
				displacement.y <= (mPosition.y + mSize.y);
	}

	void setCenter(Vector2f newCenterPos) {
		mPosition.x = newCenterPos.x - (mSize.x * 0.5f);
		mPosition.y = newCenterPos.y - (mSize.y * 0.5f);
	}

	//delta is in ms, keys is the array holding the keyboard state
	virtual void update(int delta, Uint8 const *keys) {
		
	}
	virtual void draw(SDL_Renderer *renderer) const {
		SDL_Rect dst;
		dst.x = (int)mPosition.x;
		dst.y = (int)mPosition.y;
		dst.w = (int)mSize.x;
		dst.h = (int)mSize.y;
		SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
		SDL_RenderFillRect(renderer, &dst);
	}

	
	virtual bool message(MessageID id, void *data) {
		return false;
	}

	
protected:
	//Try to treat these as read only - don't go
	// messing with them by changing their values,
	// use move() and setCenterPos() instead.
	//You have been warned.
	Vector2f mPosition; //Position information
	Vector2f mSize; //Size information
	
};