#pragma once
#include <SDL.h>
#include <SDL_image.h>

#include <vector>
#include <math.h>
#include <algorithm>

#include "Player.h"

#define PI 3.14159265

using namespace std;

class BulletManager
{
public:
	BulletManager(SDL_Renderer* renderer, Player* player) : renderer(renderer), player(player) {}

	struct Bullet {
			float x, y, rotation, distance;
	};

	//void init();
	void init() {
		//load the texture for the lazer
		SDL_Surface* surface = IMG_Load("assets/lazer.png");
		this->bulletTexture = SDL_CreateTextureFromSurface(this->renderer, surface);
		SDL_FreeSurface(surface);
	}

	//void processInput(bool* keyDown);
	void processInput(bool* keyDown) {
		if (keyDown[SDL_SCANCODE_SPACE]) {
			if (SDL_GetTicks() - lastShot > SHOOT_TIMER_MS) {
				bullets.push_back(Bullet{ player->playerX + 90, player->playerY + 40, player->getAngle(), 0.0f });
				lastShot = SDL_GetTicks();
				Mix_Chunk* soundFX4 = Mix_LoadWAV("assets/fireball.wav");
				Mix_PlayChannel(-1, soundFX4, 0);
			}
		}
	}

	void update() {
		for (auto& b : bullets) {
			b.x += sin(b.rotation * PI / 180.0f) * BULLET_VELOCITY;
			b.y -= cos(b.rotation * PI / 180.0f) * BULLET_VELOCITY;
			b.distance += BULLET_VELOCITY;
		}
		//remove bullet after they have travelled approx 1000 pixels.
		auto remove = std::remove_if(bullets.begin(), bullets.end(),
			[](const Bullet& b) { return b.distance > 1000; });
		bullets.erase(remove, bullets.end());
	}

	void draw() {
		SDL_Point center = { 5, 5 };
		for (auto& b : bullets) {
			SDL_Rect dest = { b.x, b.y, 10, 30 };
			SDL_RenderCopyEx(renderer, bulletTexture, 0, &dest, b.rotation, &center, SDL_FLIP_NONE);
		}
	}

	void clean() {
		SDL_DestroyTexture(this->bulletTexture);
	}

	vector<Bullet> bullets;

private:
	SDL_Renderer* renderer;
	SDL_Texture* bulletTexture;
	//need a reference to the player to get the angle
	Player* player;

	//time limit between shots
	const int SHOOT_TIMER_MS = 500;
	//number of pixels travelled per frame
	const float BULLET_VELOCITY = 10.0;
	unsigned int lastShot = 0;
};




