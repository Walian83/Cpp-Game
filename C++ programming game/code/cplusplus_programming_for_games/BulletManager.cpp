//#include "BulletManager.h"
//
//#include <SDL.h>
//#include <SDL_image.h>
//#include <vector>
//#include <math.h>
//#include <algorithm>
//
//void BulletManager::init() {
//	//load the texture for the lazer
//	SDL_Surface* surface = IMG_Load("cache/lazer.png");
//	this->bulletTexture = SDL_CreateTextureFromSurface(this->renderer, surface);
//	SDL_FreeSurface(surface);
//}
//
//void BulletManager::processInput(bool* keyDown) {
//	if (keyDown[SDL_SCANCODE_SPACE]) {
//		if (SDL_GetTicks() - lastShot > SHOOT_TIMER_MS) {
//			bullets.push_back(Bullet{ 315.0f, 230.0f, player->getAngle(), 0.0f });
//			lastShot = SDL_GetTicks();
//		}
//	}
//}