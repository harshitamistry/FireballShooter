#include "Game.h"
#include "Sprite.h"

#include "SpawnEntity.h"
#include "TextureManager.h"

#include <iostream>
 
Game::Game()
	: mScreenWidth(1000)
	, mScreenHeight(650)
	, mWindow(nullptr)
	, mKeys(nullptr)
	, mRenderer(nullptr)
	, mShouldQuit(false)
	, mGameType(1) //Just a couple of Entities hanging around
{
}

Game::~Game() {
	
}

bool Game::Run()
{
	
	// setup
	if (!Initialize()) {
		std::cerr << "*** Game initialization failed" << std::endl;
		return false;
	}

	Uint32 currentTime = SDL_GetTicks();
	Uint32 gameTime = currentTime;
	
	// game loop
	while (!mShouldQuit) {
		ProcessEvents();
		while ((currentTime = SDL_GetTicks()) > gameTime) {
			gameTime += DELTA;
			std::string str;
			if (status && score==0) {
				str = "Game Over! Score: " + std::to_string(gameTime/1000);
				SDL_SetWindowTitle(mWindow, str.c_str());
				score = gameTime;
			}
			else if (!status) {
				str = "Score: " + std::to_string(gameTime / 1000);
				SDL_SetWindowTitle(mWindow, str.c_str());
			}
			
			Update();
		}
		Draw();
	}

	// cleanup
	Shutdown();

	return true;
}

void Game::Load()
{
	
	switch(mGameType) {
		case 1: {
			mEntity = new SpawnEntity();
		} break;
		
		default:
			std::cout << "Invalid Game Type " << (int)mGameType << std::endl;
			break;
	}
}

void Game::CleanUp()
{
	
	delete mEntity;
	mEntity = nullptr;
}

bool Game::Initialize()
{
	
    std::cout << "Initializing game" << std::endl;
	
	//
	// initialize SDL
	//
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
		std::cerr << "*** Failed to initialize SDL: " << SDL_GetError() << std::endl;
		return false;
	}

	//
	// create a window
	//
	mWindow = SDL_CreateWindow("Hello, SDL2!",
								SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
								mScreenWidth, mScreenHeight,
								SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (!mWindow) {
		std::cerr << "*** Failed to create window: " << SDL_GetError() << std::endl;
		return false;
	}

	//
	// get a pointer to keyboard state managed by SDL
	//
	mKeys = SDL_GetKeyboardState(NULL);

	//
	// create a renderer that takes care of drawing stuff to the window
	//
	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED);
	if (!mRenderer) {
		std::cerr << "*** Failed to create renderer: " << SDL_GetError() << std::endl;
		return false;
	}

	TextureManager::getInstance().init(mRenderer);
	
	Load();

	return true;
}


void Game::Shutdown()
{
    std::cout << "Shutting down game" << std::endl;

	CleanUp();

	//Delete the textures, renderers, and the window.
	TextureManager::getInstance().cleanUp();
	SDL_DestroyRenderer(mRenderer);
	mRenderer=nullptr;
	SDL_DestroyWindow(mWindow);
	mWindow=nullptr;

	// this closes the window and shuts down SDL
    SDL_Quit();
}

void Game::Update()
{
	if(mEntity != nullptr) {
		mEntity->update(DELTA, mKeys);
		if( ((SpawnEntity*)mEntity)->status == true)
			status = true;
	}
	
}

void Game::Draw()
{
	// clear the screen
	SDL_SetRenderDrawColor(mRenderer, 100, 149, 237, 255);
	SDL_RenderClear(mRenderer);

	if (mEntity != nullptr) {
		mEntity->draw(mRenderer);
	}

	// tell the renderer to display everything we just drew
	SDL_RenderPresent(mRenderer);
}