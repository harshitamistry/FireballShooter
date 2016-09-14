#include "Game.h"

#include <iostream>

void Game::ProcessEvents()
{
    SDL_Event e;
	while (SDL_PollEvent(&e)) {
		switch (e.type) {
		case SDL_QUIT:
			OnQuit();
			break;
		case SDL_KEYDOWN:
			OnKeyDown(&e.key);
			break;
		case SDL_KEYUP:
			OnKeyUp(&e.key);
			break;
		
		case SDL_WINDOWEVENT:
			if (e.window.event == SDL_WINDOWEVENT_RESIZED) {
				OnWindowResized(e.window.data1, e.window.data2);
			}
			break;
		default:
			break;
		}
	}
}

void Game::OnQuit()
{
	std::cout << "Application was told to quit" << std::endl;

	mShouldQuit = true;
}

void Game::OnWindowResized(int w, int h)
{
	std::cout << "Window resized to " << w << 'x' << h << std::endl;

	mScreenWidth = w;
	mScreenHeight = h;

	Vector2f ss((float)mScreenWidth, (float)mScreenHeight);
	mEntity->message(MessageID::SCREEN_SIZE, &ss);
}

void Game::OnKeyDown(const SDL_KeyboardEvent* kbe)
{
    switch (kbe->keysym.sym) {
    case SDLK_ESCAPE:
        std::cout << "User pressed Escape" << std::endl;
        mShouldQuit = true;  // set quit flag
        break;
	case SDLK_UP:
		std::cout << "User pressed Up" << std::endl;

		break;
	
    }
}

void Game::OnKeyUp(const SDL_KeyboardEvent* kbe)
{
	switch (kbe->keysym.sym) {
		case SDLK_r:
			std::cout << "Reset game to initial state" << std::endl;
			CleanUp();
			Load();
			break;
		
		case SDLK_1:
			//Move this down as we add game types (which are 1 indexed).
			mGameType = kbe->keysym.sym - SDLK_0;
			std::cout << "Game type set to " << (int)mGameType << std::endl
				<< "Press 'R' to reset game to initial state" << std::endl;
			break;
		case SDLK_2:
		case SDLK_3:
		case SDLK_4:
		case SDLK_5:
		case SDLK_6:
			
		case SDLK_7:
		case SDLK_8:
		case SDLK_9:
			
		case SDLK_0:
			//Add this once we get past 9 game types.
//			mGameType = 10;
			break;
	}
}


