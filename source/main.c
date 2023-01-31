#pragma warning( disable: 26451 )

#include <stdio.h>
#include <SDL2/SDL.h>
#include "constants.h"

typedef struct Player_t
{
	float x;
	float y;
	float width;
	float height;
	DIRECTION turnDirection;
	DIRECTION walkDirection;
	float rotationAngle;
	float walkSpeed;
	float turnSpeed;
} Player;

const TILE map[MAP_NUM_ROWS][MAP_NUM_COLS] =
{
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 ,1, 1, 1, 1, 1, 1, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 1, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
	{1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1, 1}
};

Player player;

BOOL initializeWindow();
void setup();
void processInput();
void update();
void render();
void destroyWindow();

void renderMap();
void renderPlayer();
void renderRays();

SDL_Window* window = NULL;
SDL_Renderer* renderer = NULL;

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
	player.x = WINDOW_WIDTH	/ 2;
	player.y = WINDOW_HEIGHT / 2;
	player.width = 5;
	player.height = 5;
	player.turnDirection = NONE;
	player.walkDirection = NONE;
	player.rotationAngle = PI / 2;
	player.walkSpeed = 100;
	player.turnSpeed = 45 * RAD;
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
}

void render()
{
	// Clear Screen
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderClear(renderer);

	// TODO: Render all game objects for the current frame.
	renderMap();
	renderPlayer();
	renderRays();

	// Present Render
	SDL_RenderPresent(renderer);
}

void destroyWindow()
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
}

////////////////////////////////
// Rendering
////////////////////////////////
void renderMap()
{
	for (int i = 0; i < MAP_NUM_ROWS; i++)
	{
		for (int j = 0; j < MAP_NUM_COLS; j++)
		{
			int tileX = j * TILE_SIZE;
			int tileY = i * TILE_SIZE;
			int tileColor = map[i][j] != 0 ? 255 : 0;

			SDL_SetRenderDrawColor(renderer, tileColor, tileColor, tileColor, 255);
			SDL_Rect mapTileRect = {
				(int) (tileX * MINIMAP_SCALE_FACTOR),
				(int)(tileY * MINIMAP_SCALE_FACTOR),
				(int)(TILE_SIZE * MINIMAP_SCALE_FACTOR),
				(int)(TILE_SIZE * MINIMAP_SCALE_FACTOR)
			};
			SDL_RenderFillRect(renderer, &mapTileRect);
		}
	}
}

void renderPlayer()
{

}

void renderRays()
{

}