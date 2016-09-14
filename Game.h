#ifndef GAME_H_
#define GAME_H_

#include <list>

#include <SDL.h>

#include "Entity.h"

class Game
{
	int mScreenWidth;
	int mScreenHeight;

	SDL_Window *mWindow;
	Uint8 const *mKeys;
	SDL_Renderer *mRenderer;

	bool mShouldQuit;
	Uint8 mGameType;

	//The active entity in the screen.
	Entity *mEntity;
	
public:
	Game();
	~Game();

	bool Run();
	void Load();
	void CleanUp();

private:
	bool Initialize();
	void Shutdown();

	void ProcessEvents();

	void OnQuit();
	void OnWindowResized(int w, int h);
	void OnKeyDown(const SDL_KeyboardEvent* kbe);
	void OnKeyUp(const SDL_KeyboardEvent* kbe);

    void Update();
	void Draw();

	

public:
	static Uint32 const TARGET_FPS = 30;
	static Uint32 const TICKS_PER_SECOND = 1000; //Ticks is in ms.
	static Uint32 const DELTA = TICKS_PER_SECOND / TARGET_FPS;
	int score=0;
	bool status=false;
};

#endif
