#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>


class Player
{
public:
	Player(SDL_Renderer* sdlRenderer, int _windowWidth, int _windowHeight);

	void init();
	void render();
	void update();
	void clean();

	void textureUp();
	void textureDown();
	void textureLeft();
	void textureRight();
	
	void processInput(bool* keyDown);
	void draw();

	void moveRight();
	void moveLeft();
	void moveUp();
	void moveDown();

	float getAngle() const {
		return rotationAngle;
	}

	float playerX;
	float playerY;

	SDL_Rect portion;

private:
	int x = 0;
	int y = 0;

	int windowWidth = 0;
	int windowHeight = 0;

	SDL_Renderer* renderer = nullptr;
	SDL_Texture* texture = nullptr;

	float rotationAngle;
};



