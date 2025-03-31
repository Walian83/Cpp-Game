#include "Player.h"
#include <SDL.h>
#include <iostream>


Player::Player(SDL_Renderer* sdlRenderer, int _windowWidth, int _windowHeight) {
	renderer = sdlRenderer;
	windowWidth = _windowWidth;
	windowHeight = _windowHeight;
}

void Player::init()
{
	SDL_Surface* image = IMG_Load("assets/mage-right.png");
	if (image == nullptr) {
		std::cout << "Could not load image!" << std::endl;
		std::cout << SDL_GetError() << std::endl;
		return;
	}
	this->texture = SDL_CreateTextureFromSurface(renderer, image);

	portion = SDL_Rect(); // Create a rectangle object	
	portion.x = 400; // Set the position on the X axis
	portion.y = 400; // Set the position on the Y axis

	float playerWidth = 0.07f * (float)windowWidth;
	float playerHeight = 0.05f * (float)windowWidth;
	portion.w = (int)playerWidth;
	portion.h = (int)playerHeight;
}

void Player::render()
{
	SDL_RenderCopy(renderer, texture, NULL, &portion);
}

//void Player::draw()
//{
//	SDL_Rect r = { 640 / 2 - (98 / 4), 480 / 2 - (75 / 4), 98 / 2, 75 / 2 };
//	SDL_Point rotationCenter = { 98 / 4,75 / 4 };
//	SDL_RenderCopyEx(this->renderer, this->texture, 0, &r, this->rotationAngle, &rotationCenter, SDL_FLIP_NONE);
//}

void Player::update()
{
	playerX = portion.x;
	playerY = portion.y;
}

void Player::clean()
{
	SDL_DestroyTexture(this->texture);
}

void Player::moveRight() {
	portion.x += 10;
	textureRight();
	rotationAngle = 90;
	//right screen border
	if (portion.x + portion.w  >= windowWidth) {
		portion.x = windowWidth - portion.w;
	}
	//water collision
	//very top
	if ((portion.x + portion.w >= 1000 && portion.x + portion.w <= 1050)&&(portion.y <= 110)) {
		portion.x = 1000 - portion.w;
	}
	//below bridge
	if ((portion.x + portion.w >= 1000 && portion.x + portion.w <= 1060) && (portion.y >= 200 && portion.y <= 300)) {
		portion.x = 1000 - portion.w;
	}
	//left side of water
	if ((portion.x + portion.w >= 920 && portion.x + portion. w <= 950) && (portion.y >= 300 && portion.y <= 650)) {
		portion.x = 920 - portion.w;
	}
	//second bridge
	if ((portion.x + portion.w >= 1440) && (portion.y >= 390 && portion.y <=550)) {
		portion.x = 1440 - portion.w;
	}
	
}

void Player::moveLeft() {
	portion.x -= 10;
	textureLeft();
	rotationAngle = 270;
	//left screen border
	if (portion.x <= 0) {
		portion.x = 0;
	}
	//water collision
	//very top
	if ((portion.x <= 1130 && portion.x >= 1100)&&(portion.y <= 110)) {
		portion.x = 1130;
	}
	//below bridge
	if ((portion.x >= 920 && portion.x <= 1130) && (portion.y >= 200 && portion.y <= 300)) {
		portion.x = 1130;
	}
	//below previous
	if ((portion.x >= 920 && portion.x <= 1200) && (portion.y >= 300 && portion.y <= 405)) {
		portion.x = 1210;
	}
	//second bridge
	if ((portion.x <= 1320 && portion.x >= 1290) && (portion.y >= 390 && portion.y <= 550)) {
		portion.x = 1320;
	}
	//lowest left water tile
	if ((portion.x <= 1110 && portion.x >= 1100) && (portion.y >= 550 && portion.y <= 650)) {
		portion.x = 1110;
	}
	
}

void Player::moveUp() {
	portion.y -= 10;
	textureUp();
	rotationAngle = 0;
	//top screen border
	if (portion.y <= 0) {
		portion.y = 0;
	}
	//water collision
	//bridge
	if ((portion.y <= 130) && (portion.x + portion.w >= 1020 && portion.x <= 1110)) {
		portion.y = 130;
	}
	//lowest upper water tile
	if ((portion.y <= 660 && portion.y >= 600) && (portion.x + portion.w >= 930 && portion.x <= 1100)) {
		portion.y = 660;
	}
	//below second bridge (left)
	if ((portion.y <= 570 && portion.y >= 510) && (portion.x + portion.w >= 1130 && portion.x <= 1310)) {
		portion.y = 570;
	}
	//below second bridge (right)
	if ((portion.y <= 570 && portion.y >= 510) && (portion.x + portion.w >= 1450)) {
		portion.y = 570;
	}
	
}

void Player::moveDown() {
	portion.y += 10;
	textureDown();
	rotationAngle = 180;
	//bottom screen border
	if (portion.y + portion.h >= windowHeight) {
		portion.y = windowHeight - portion.h;
	}
	//water collision
	//bridge
	if ((portion.y + portion.h >= 270 && portion.y + portion.h <= 290) && (portion.x + portion.w >= 1020 && portion.x <= 1110)) {
		portion.y = 270 - portion.h;
	}
	//below bridge (left)
	if ((portion.y + portion.h >= 370 && portion.y + portion.h <= 390) && (portion.x + portion.w >= 930 && portion.x <= 970)) {
		portion.y = 370 - portion.h;
	}
	//below bridge(right)
	if ((portion.y + portion.h >= 370 && portion.y + portion.h <= 390) && (portion.x + portion.w >= 1120 && portion.x <= 1200)) {
		portion.y = 370 - portion.h;
	}
	//below previous, above second bridge (left)
	if ((portion.y + portion.h >= 460 && portion.y + portion.h <= 480) && (portion.x + portion.w >= 1220 && portion.x <= 1310)) {
		portion.y = 460 - portion.h;
	}
	//above second bridge (right)
	if ((portion.y + portion.h >= 460 && portion.y + portion.h <= 480) && (portion.x + portion.w >= 1450)) {
		portion.y = 460 - portion.h;
	}
	
}

void Player::textureUp() {
	clean();
	SDL_Surface* image = IMG_Load("assets/mage-up.png");
	texture = SDL_CreateTextureFromSurface(renderer, image);
}

void Player::textureDown() {
	clean();
	SDL_Surface* image = IMG_Load("assets/mage-down.png");
	texture = SDL_CreateTextureFromSurface(renderer, image);
}

void Player::textureLeft() {
	clean();
	SDL_Surface* image = IMG_Load("assets/mage-left.png");
	texture = SDL_CreateTextureFromSurface(renderer, image);
}

void Player::textureRight() {
	clean();
	SDL_Surface* image = IMG_Load("assets/mage-right.png");
	texture = SDL_CreateTextureFromSurface(renderer, image);
}

