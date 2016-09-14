#include "AnimatedSprite.h"



AnimatedSprite::AnimatedSprite(SDL_Texture *texture, SDL_Rect textureRect, int numFrames, int frameTime, AnimationDirection direction, AnimationType type, bool started)
	:	Sprite(texture, textureRect), mDirection(direction), mType(type), mCurrentFrame(0), FRAME_TIME(frameTime), mAccumulatedFrameTime(0), mRunning(started)
{
	int frameWidth = textureRect.w / numFrames;
	//First we create the subrects for the animation.
	for (int i = 0; i < numFrames; i++) {
		SDL_Rect frame = textureRect;
		frame.w = frameWidth;
		frame.x = frameWidth * i;
		mFrameRectangles.push_back(frame);
	}
	mSrcRect = mFrameRectangles[0];
	if (started) {
		start();
	}
}


AnimatedSprite::~AnimatedSprite()
{
}

void AnimatedSprite::start()
{
	mRunning = true;
}

void AnimatedSprite::stop()
{
	mRunning = false;
}

void AnimatedSprite::update(int delta)
{
	if (mRunning) {
		mAccumulatedFrameTime += delta;
		if (mAccumulatedFrameTime > FRAME_TIME) {
			mAccumulatedFrameTime -= FRAME_TIME;
			mCurrentFrame++;
			if (mCurrentFrame >= mFrameRectangles.size()) {
				if (mType == AnimationType::SINGLE) {
					mCurrentFrame--;
					mRunning = false;
				}
				else if (mType == AnimationType::LOOP ) {
					mCurrentFrame = 0;
				}
				else if (mType == AnimationType::BOUNCE) {
					mCurrentFrame = 1;
					if (mDirection == AnimationDirection::FORWARD) {
						mDirection = AnimationDirection::REVERSE;
					} else if (mDirection == AnimationDirection::REVERSE) {
						mDirection = AnimationDirection::FORWARD;
					}
				}
			}
			//This has the very small quirk of jumping to the wrong frame when you stop a reversing animation.
			int actualCurrentFrame = mDirection == AnimationDirection::REVERSE ? mFrameRectangles.size() - mCurrentFrame - 1 : mCurrentFrame;
			mSrcRect = mFrameRectangles[actualCurrentFrame];
		}
	}
}
