// Using SDL and standard IO
#include <SDL.h>
#include <stdio.h>

// Screen dimension constants
const int SCREEN_WIDTH = 1280;
const int SCREEN_HEIGHT = 720;

class Player
{
private:
	//
public:
	SDL_FRect rect;
	float speed;

	Player(SDL_FRect rect, float speed);
	~Player();
};
Player::Player(SDL_FRect r, float s)
{
	this->rect = r;
	this->speed = s;
}
Player::~Player() {}

int main(int argc, char *args[])
{
	// The window we'll be rendering to
	SDL_Window *window = NULL;

	// The surface contained by the window
	SDL_Surface *screenSurface = NULL;

	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
	}
	else
	{
		// Create window
		window = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (window == NULL)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		}
		else
		{
			// Setup renderer
			SDL_Renderer *renderer = NULL;
			renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC );

			SDL_FRect r;
			r.x = 380;
			r.y = 200;
			r.h = 64;
			r.w = 64;

			Player p(r, 0.1);

			// Hack to get window to stay up
			// Game Loop
			SDL_Event e;
			bool
				quit = false;
			while (quit == false)
			{

				SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
				SDL_RenderClear(renderer);

				SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
				SDL_RenderFillRectF(renderer, &p.rect);
				SDL_RenderPresent(renderer);

				p.rect.x += p.speed;

				const Uint8 *keystate = SDL_GetKeyboardState(NULL);
				if (keystate[SDL_SCANCODE_UP])
					p.speed += 0.1;
				else if (keystate[SDL_SCANCODE_DOWN])
					p.speed -= 0.1;

				while (SDL_PollEvent(&e))
				{
					if (e.type == SDL_QUIT)
						quit = true;
				}

				if (p.rect.x > SCREEN_WIDTH ){
					p.rect.x = -(p.rect.w);
				}
				if (p.rect.x < -(p.rect.w) ){
					p.rect.x = SCREEN_WIDTH;
				}

			}
		}
	}
	// Destroy window
	SDL_DestroyWindow(window);

	// Quit SDL subsystems
	SDL_Quit();

	return 0;
}
