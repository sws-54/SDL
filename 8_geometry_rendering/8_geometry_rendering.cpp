#include <cstdio>
#include <SDL.h>


// screen sizes
const int Width  = 640;
const int Height = 480;

// start SDL
void Start();

// end SDL
void End();

// window 
SDL_Window *Window = nullptr;

// renderer
SDL_Renderer *Renderer = nullptr;

void Start()
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		printf("Error at [SDL_INIT_VIDEO] \n%s\n", SDL_GetError());

	Window = SDL_CreateWindow("title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, Width, Height, SDL_WINDOW_SHOWN);
	if(Window == nullptr)
		printf("Error at [SDL_CreateWindow] \n%s\n", SDL_GetError());

	Renderer = SDL_CreateRenderer(Window, -1, 0);
	if(Renderer == nullptr)
		printf("Error at [SDL_CreateRenderer] \n%s\n", SDL_GetError());
}

void End()
{
	SDL_DestroyRenderer(Renderer);
	SDL_DestroyWindow(Window);
	
	Renderer = nullptr;
	Window = nullptr;

	SDL_Quit();
}

int main(int argc,char* args[])
{
	Start();
	SDL_Event Events;

	bool Quit = false;

	while (Quit == false)
	{
		while (SDL_PollEvent(&Events))
		{
			if (Events.type == SDL_QUIT)
				Quit = true;
		}

		SDL_SetRenderDrawColor(Renderer, 255, 255, 255, 255);
		SDL_RenderClear(Renderer);
		
		// create rect struct
		// x 3rdd postition
		// y 6oool postition
		// h size 6ool 
		// w size 3rdd

		SDL_Rect Rect1;
		Rect1.x = 200;
		Rect1.y = 200;
		Rect1.h = 50;
		Rect1.w = 50;
		// set the draw color to the next render
		SDL_SetRenderDrawColor(Renderer, 255, 0, 0, 255);
		// render rect
		SDL_RenderFillRect(Renderer, &Rect1);

		SDL_RenderPresent(Renderer);
	}


	End();
	return 0;
}