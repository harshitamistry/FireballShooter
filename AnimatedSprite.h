#pragma once
#include "Sprite.h"
#include <vector>

enum class AnimationDirection {
	FORWARD,
	REVERSE
};

enum class AnimationType {
	SINGLE,
	LOOP,
	BOUNCE
};

class AnimatedSprite :
	public Sprite
{
public:
	AnimatedSprite(SDL_Texture *texture, SDL_Rect textureRect, int numFrames, int frameTime, AnimationDirection direction, AnimationType type, bool started = true);
	virtual ~AnimatedSprite();

	void start();
	void stop();

	void update(int delta);

private:
	std::vector<SDL_Rect> mFrameRectangles;
	AnimationDirection mDirection;
	AnimationType mType;
	int mCurrentFrame;
	int const FRAME_TIME;
	int mAccumulatedFrameTime;
	bool mRunning;
};

