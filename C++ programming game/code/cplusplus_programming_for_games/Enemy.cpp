#include "Enemy.h"
#include <SDL.h>
#include <iostream>

Enemy::Enemy(SDL_Renderer* sdlRenderer, int _windowWidth, int _windowHeight) {
	renderer = sdlRenderer;
	windowWidth = _windowWidth;
	windowHeight = _windowHeight;
}

void Enemy::init()
{
	SDL_Surface* image = IMG_Load("assets/slime.png");
	if (image == nullptr) {
		std::cout << "Could not load image!" << std::endl;
		std::cout << SDL_GetError() << std::endl;
		return;
	}
	this->texture = SDL_CreateTextureFromSurface(renderer, image);

	portion1 = SDL_Rect(); // Create a rectangle object	
	portion1.x = 0; // Set the position on the X axis
	portion1.y = 0; // Set the position on the Y axis

	float playerWidth = 0.05f * (float)windowWidth;
	float playerHeight = 0.08f * (float)windowHeight;
	portion1.w = (int)playerWidth;
	portion1.h = (int)playerHeight;

	//second enemy
	portion2 = SDL_Rect();
	portion2.x = 0; // Set the position on the X axis
	portion2.y = 830; // Set the position on the Y axis
	portion2.w = (int)playerWidth;
	portion2.h = (int)playerHeight;
	
}

void Enemy::render()
{
	SDL_RenderCopy(renderer, texture, NULL, &portion1);
	SDL_RenderCopy(renderer, texture, NULL, &portion2);
}

void Enemy::clean()
{
	
}	


void Enemy::update() 
{	
	enemyMove();
}


void Enemy::enemyMove()
{
	//first enemy
	if (moveDown == true) {
		portion1.y += speed;
	}
	if (portion1.y + portion1.h >= windowHeight) {		
		moveDown = false;
	}
	if (moveDown == false) {
		portion1.y -= speed;
	}
	if (portion1.y <= 0) {
		moveDown = true;
	}
	//second enemy
	if (moveLeft == false) {
		portion2.x += speed;
	}
	if (portion2.x + portion2.w >= windowWidth) {
		moveLeft = true;
	}
	if (moveLeft == true) {
		portion2.x -= speed;
	}
	if (portion2.x <= 0) {
		moveLeft = false;
	}
	
}