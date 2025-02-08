#include <stdbool.h>
#include <stdio.h>
#include <SDL.h>


// Just using a number is generally bad practice, so here we define the return values the app will use.
#define ERROR_NO_ERROR (0)
#define ERROR_INIT_FAILED (1)
#define ERROR_WINDOW_FAILED (2)
#define ERROR_RENDERER_FAILED (3)


// Definition of a new window
typedef struct {
	int width;
	int height;
	const char* title;
} NewWindow;


const NewWindow windowDef = {800, 600, "Hello World"};


int main(int argc, char *argv[]) {
	// Start SDL, we are using video and events, events will init automatically when we as for video.
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("Error: Unable to initialise SDL. SDL Error: %s\n", SDL_GetError());
		return ERROR_INIT_FAILED;
	}

	// We want to be able to see whats happening so open a window.
	SDL_Window* window = SDL_CreateWindow(windowDef.title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, windowDef.width, windowDef.height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
	if (window == NULL) {
		printf("Error: Window could not be created! SDL Error: %s\n", SDL_GetError());
		SDL_Quit();
		return ERROR_WINDOW_FAILED;
	}

	// And in this window we want to render something
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (renderer == NULL) {
		printf("Error: Renderer could not be created! SDL Error: %s\n", SDL_GetError());
		SDL_DestroyWindow(window);
		SDL_Quit();
		return ERROR_RENDERER_FAILED;
	}

	// Setup variables for game loop, rect could be moved into the loop but very slightly better performance having it set outside.
	const SDL_Rect rect = {windowDef.width / 4, windowDef.height / 4, windowDef.width / 2, windowDef.height / 2};
	bool appIsRunning = true;

	// Main loop
	while (appIsRunning) {
		// check for sdl events (only for quit so far, mostly close window button clicked)
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) { // When we click the close window button set the appIsRunning to exit the main loop.
				appIsRunning = false;     // We still render one frame but that really is a no biggy
			}
		}

		// Render
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 128, 128, 128, 255);
		SDL_RenderFillRect(renderer, &rect);
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);

		// Tell sdl to show the rendered buffer
		SDL_RenderPresent(renderer);
		SDL_Delay(0);
	}

	// Quit the app, tidy up first
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return ERROR_NO_ERROR;
}
