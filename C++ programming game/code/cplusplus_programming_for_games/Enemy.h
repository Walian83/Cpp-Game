#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>


class Enemy
{
public:
	Enemy(SDL_Renderer* sdlRenderer, int _windowWidth, int _windowHeight);

	void init();
	void render();
	void update();
	void clean();

	void processInput(bool* keyDown);
	void draw();

	void enemyMove();

	float getAngle() const {
		return rotationAngle;
	}

	float playerX;
	float playerY;

	SDL_Rect portion1;
	SDL_Rect portion2;

private:
	int x = 0;
	int y = 0;

	int speed = 5;
	bool moveDown = true;
	bool moveLeft = true;

	int windowWidth = 0;
	int windowHeight = 0;

	//SDL_Rect portion1;
	//SDL_Rect portion2;
	SDL_Renderer* renderer = nullptr;
	SDL_Texture* texture = nullptr;

	float rotationAngle;
};

