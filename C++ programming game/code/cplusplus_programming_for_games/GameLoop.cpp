#include "GameLoop.h"
#include <iostream>
#include <SDL.h>
#include <SDL_mixer.h>
#include "Player.h"

int GameLoop::init()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "could not initialize SDL!" << std::endl;
		std::cout << SDL_GetError() << std::endl;
		return -1;
	}
	window = SDL_CreateWindow(
		"Game Window :D",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		screenWidth, screenHeight,
		SDL_WINDOW_SHOWN
	);
	if (window == NULL)
	{
		std::cout << "could not initialize window!" << std::endl;
		std::cout << SDL_GetError() << std::endl;
		return -1;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL)
	{
		std::cout << "could not initialize renderer!" << std::endl;
		std::cout << SDL_GetError() << std::endl;
		return -1;
	}
	
	screenSurface = SDL_GetWindowSurface(window);

	player = new Player(renderer, screenWidth, screenHeight);
	player->init();

	enemy = new Enemy(renderer, screenWidth, screenHeight);
	enemy->init();

	fontRenderer = std::unique_ptr<FontRenderer>(new FontRenderer(renderer));
	fontRenderer->init();

	tiledMap = std::unique_ptr<TiledMap>(new TiledMap(renderer, "assets/tiledmap.png"));
	tiledMap->init();

	bm = new BulletManager(this->renderer, this->player);
	bm->init();

	/*int init = SDL_Init(SDL_INIT_EVERYTHING);
	int init2 = Mix_Init(0);
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);
	Mix_Music* music = Mix_LoadMUS("assets/");
	Mix_Chunk* soundFX = Mix_LoadWAV("assets/");

	Mix_PlayMusic(music, -1);*/

	audio();

	return 0;
}


void GameLoop::update()
{
	bm->update();
	player->update();
	enemy->update();
	checkCollisions();
	updateScore();
}

void GameLoop::render()
{
	SDL_RenderClear(renderer);
	tiledMap->render();
	player->render();
	enemy->render();
	fontRenderer->render(scoreTxt);

	bm->draw();
	SDL_RenderPresent(renderer);
	SDL_Delay(16);
}

void GameLoop::clean()
{
	fontRenderer->clean();
	tiledMap->clean();
	bm->clean();

	delete player;
	SDL_DestroyWindow(window);
	SDL_Quit();

}

void GameLoop::handleInput(SDL_Scancode& keyScanCode) {
	switch (keyScanCode) {
	case SDL_SCANCODE_D:
		player->moveRight();
		break;
	case SDL_SCANCODE_W:
		player->moveUp();
		break;
	case SDL_SCANCODE_A:
		player->moveLeft();
		break;
	case SDL_SCANCODE_S:
		player->moveDown();
	}
	const Uint8* keys = SDL_GetKeyboardState(NULL);
	bm->processInput((bool*)keys);
}

bool GameLoop::keepalive() {
	SDL_Event userInput;
	while (SDL_PollEvent(&userInput)) {
		if (userInput.type == SDL_QUIT)
		{
			return false;
		}

		if (userInput.type == SDL_KEYDOWN) {
			handleInput(userInput.key.keysym.scancode);
		}
	}
	return true;
}

void GameLoop::checkCollisions() {
	Mix_Chunk* soundFX = Mix_LoadWAV("assets/whip.wav");
	Mix_Chunk* soundFX2 = Mix_LoadWAV("assets/fireball.wav");
	Mix_Chunk* soundFX3 = Mix_LoadWAV("assets/death.wav");

	for (auto& b : bm->bullets) {
		SDL_Rect dest = { b.x, b.y, 10, 30 };
		if (SDL_HasIntersection(&dest, &enemy->portion1)) {
			enemy->portion1.y = -700;
			score += 10;
			Mix_PlayChannel(-1, soundFX3, 0);
		}
		if (SDL_HasIntersection(&dest, &enemy->portion2)) {
			enemy->portion2.x = 2200;
			score += 10;
			Mix_PlayChannel(-1, soundFX3, 0);
		}
	}
	if (SDL_HasIntersection(&player->portion, &enemy->portion1)) {
		enemy->portion1.y = -700;
		score += 10;
		Mix_PlayChannel(-1, soundFX, 0);
	}
	if (SDL_HasIntersection(&player->portion, &enemy->portion2)) {
		enemy->portion2.x = 2200;
		score += 10;
		Mix_PlayChannel(-1, soundFX, 0);
	}

}

void GameLoop::updateScore() {
	auto scoreString = std::to_string(score);
	scoreTxt = "Score: " + scoreString;
}

void GameLoop::audio() {
	Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024);

	Mix_Music* music = Mix_LoadMUS("assets/music2.mp3");
	
	Mix_PlayMusic(music, -1);
	if (!music) {
		cout << "Music Error: " << Mix_GetError() << endl;
	}
}
