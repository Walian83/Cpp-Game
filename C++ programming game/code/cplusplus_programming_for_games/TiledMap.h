#pragma once
#include <SDL.h>
#include <iostream>

class TiledMap
{
public:
	TiledMap(SDL_Renderer* sdlRenderer, std::string tiledMapFilename);

	int init();
	void render();
	void clean();

private:
	const int sourceTileSizePx = 16;
	const int tileWidth = 89;
	const int tileHeight = 90;

	std::string filename;
	SDL_Renderer* renderer;
	SDL_Texture* texture;
};

const int mapWidth = 18;
const int mapHeight = 10;
const int map[mapHeight][mapWidth] = {
	{23, 53, 23, 53, 37, 53, 23, 53, 52, 53, 23, 9, 11, 53, 23, 37, 53, 23},
	{52, 23, 53, 23, 37, 23, 53, 23, 53, 23, 53, 9, 11, 23, 53, 37, 53, 46},
	{23, 53, 23, 46, 37, 53, 23, 53, 23, 53, 23, 53, 23, 53, 23, 44, 36, 36},
	{53, 23, 53, 23, 37, 23, 53, 23, 53, 52, 23, 9, 11, 53, 52, 53, 23, 52},
	{23, 53, 23, 53, 37, 53, 23, 53, 23, 23, 3, 28, 27, 5, 53, 23, 53, 23},
	{53, 23, 53, 23, 37, 23, 53, 23, 53, 23, 9, 10, 10, 27, 4, 53, 4, 4},
	{36, 36, 36, 36, 39, 36, 38, 36, 36, 53, 9, 10, 21, 16, 16, 23, 16, 16},
	{46, 53, 23, 52, 23, 46, 37, 23, 53, 23, 15, 16, 17, 46, 52, 23, 53, 23},
	{53, 46, 52, 23, 46, 23, 37, 53, 23, 53, 23, 52, 23, 53, 23, 53, 46, 53},
	{52, 53, 23, 52, 23, 53, 37, 23, 53, 23, 53, 23, 53, 23, 53, 23, 53, 23}
};



