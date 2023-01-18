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

float playerX, playerY;
int ticksLastFrame = 0;

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
	playerX = 0;
	playerY = 0;
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
	int timeToWait = FRAME_TIME_LENGTH - (SDL_GetTicks() - ticksLastFrame);
	if (timeToWait > 0) SDL_Delay(timeToWait);

	float deltaTime = (SDL_GetTicks() - ticksLastFrame)/ 1000.0f;
	ticksLastFrame = SDL_GetTicks();

	playerX += (20.0f * deltaTime);
	playerY += (20.0f * deltaTime);
}

void render()
{
	// Clear Screen
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	// TODO: Render all game objects for the current frame.
	SDL_Rect rect = { (int) playerX, (int) playerY, 20, 20 };
	SDL_SetRenderDrawColor(renderer, 255, 255, 0, 255);
	SDL_RenderFillRect(renderer, &rect);

	// Present Render
	SDL_RenderPresent(renderer);
}

void destroyWindow()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}