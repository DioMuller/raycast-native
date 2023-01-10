#include <stdio.h>
#include <SDL2/SDL.h>
#include "constants.h"

BOOL initializeWindow();
void setup();
void processInput();
void update();
void render();
void destroyWindow();

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

BOOL isGameRunning;

int main(int argc, char* argv[])
{
	isGameRunning = initializeWindow();

	if (isGameRunning)
	{
		setup();

		while (isGameRunning)
		{
			processInput();
			update();
			render();
		}
	}

	destroyWindow();

	return 0;
}

BOOL initializeWindow()
{
	if(SDL_Init(SDL_INIT_EVERYTHING) != 0)
	{
		fprintf(stderr, "Error Initializing SDL: %s.\n", SDL_GetError());
		return FALSE;
	}

	window = SDL_CreateWindow("Raycast", 
		SDL_WINDOWPOS_CENTERED, 
		SDL_WINDOWPOS_CENTERED, 
		WINDOW_WIDTH, 
		WINDOW_HEIGHT,
		SDL_WINDOW_BORDERLESS
	);

	if (!window)
	{
		fprintf(stderr, "Error Creating Window: %s.\n", SDL_GetError());
		return FALSE;
	}

	renderer = SDL_CreateRenderer(window,-1, 0);

	if (!renderer)
	{
		fprintf(stderr, "Error Creating Renderer: %s.\n", SDL_GetError());
		return FALSE;
	}

	if( SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND) != 0)
	{
		fprintf(stderr, "Error Setting Renderer Blend Mode: %s.\n", SDL_GetError());
		return FALSE;
	}

	return TRUE;
}

void setup()
{

}

void processInput()
{
	SDL_Event event;

	SDL_PollEvent(&event);

	switch (event.type)
	{
		case SDL_QUIT:
		{
			isGameRunning = FALSE;
			break;
		}

		case SDL_KEYDOWN:
		{
			if (event.key.keysym.sym == SDLK_ESCAPE)
				isGameRunning = FALSE;

			break;
		}
	}
}

void update()
{

}

void render()
{
	// Clear Screen
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	// TODO: Render all game objects for the current frame.

	// Present Render
	SDL_RenderPresent(renderer);
}

void destroyWindow()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}