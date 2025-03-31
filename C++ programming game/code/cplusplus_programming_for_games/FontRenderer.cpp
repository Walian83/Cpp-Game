#include "FontRenderer.h"

FontRenderer::FontRenderer(SDL_Renderer* sdlRenderer) {
	renderer = sdlRenderer;
}
void FontRenderer::init() {
	int init = TTF_Init();
	if (init != 0) {
		std::cout << SDL_GetError() << std::endl;
	}
	font = TTF_OpenFont("assets/OpenSans-Regular.ttf", 12);
	if (font == NULL) {
		std::cout << SDL_GetError() << std::endl;
	}

	


}

void FontRenderer::clean() {
	// Free up all the resources we used to render
	TTF_CloseFont(font);
}

void FontRenderer::render(std::string text) {
	SDL_Color colour = SDL_Color();
	colour.r = 120; // Red
	colour.g = 0; // Green
	colour.b = 60; // Blue
	colour.a = 255; // Transparency

	SDL_Rect portion = SDL_Rect(); // Create a rectangle object	
	portion.x = 20; // Set the position on the X axis
	portion.y = 0; // Set the position on the Y axis

	portion.h = 100;
	portion.w = 300;

	// The following creates an image representing the text that we input
	SDL_Surface* textImage = TTF_RenderText_Solid(font, text.c_str(), colour);
	// Render it the same way as the player
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textImage);
	SDL_RenderCopy(renderer, texture, NULL, &portion);

	// Text rendered, no texture needed
	SDL_DestroyTexture(texture);
	SDL_FreeSurface(textImage);
}
