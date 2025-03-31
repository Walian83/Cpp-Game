#pragma once

#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <iostream>
#include <SDL_mixer.h>
#include "Player.h"
#include "FontRenderer.h"
#include "TiledMap.h"
#include "BulletManager.h"
#include "Enemy.h"

const int screenWidth = 1600;
const int screenHeight = 900;

class GameLoop
{
public:
	int init();

	void update();
	void render();
	void handleInput(SDL_Scancode& keyScanCode);

	bool keepalive();

	void clean();

	void checkCollisions();

	std::string scoreTxt = "";
	int score;

	void updateScore();

	void audio();

	int init2 = Mix_Init(MIX_INIT_MP3);
	//Mix_Music* music = Mix_LoadMUS("assets/music2.mp3");
	Mix_Chunk* soundFX = Mix_LoadWAV("assets/whip.wav");

private:
	SDL_Window* window = nullptr;
	SDL_Surface* screenSurface = nullptr;
	SDL_Renderer* renderer = nullptr;

	std::unique_ptr<FontRenderer> fontRenderer;
	std::unique_ptr<TiledMap> tiledMap;

	Player* player = nullptr;
	Enemy* enemy = nullptr;
	BulletManager* bm;

};

