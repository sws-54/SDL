#include <cstdio>
#include <SDL.h>
#include <SDL_image.h>
#include <string>


// screen sizes
const int Width  = 640;
const int Height = 480;

// start SDL
void Start();

// load images
void LoadImage(std::string);

// end SDL
void End();

// window 
SDL_Window *Window = nullptr;

// renderer
SDL_Renderer *Renderer = nullptr;

// texutre
SDL_Texture *Texture = nullptr;

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

	if(!IMG_Init(IMG_INIT_PNG))
		printf("Error at [IMG_Init] \n%s\n", IMG_GetError());
}

void End()
{
	SDL_DestroyRenderer(Renderer);
	SDL_DestroyWindow(Window);
	SDL_DestroyTexture(Texture);

	Renderer = nullptr;
	Window   = nullptr;
	Texture  = nullptr;

	SDL_Quit();
}

void LoadImage(std::string Path)
{
	// create tmp surface to load img to
	SDL_Surface *TmpSurface = IMG_Load(Path.c_str());
	if(TmpSurface == nullptr)
		printf("Error at [IMG_Load] \n%s\n", IMG_GetError());

	Texture = SDL_CreateTextureFromSurface(Renderer, TmpSurface);
	if(Texture == nullptr)
		printf("Error at [SDL_CreateTextureFromSurface] \n%s\n", SDL_GetError());
}

int main(int argc,char* args[])
{
	Start();
	SDL_Event Events;
	LoadImage("files/viewport.png");

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
		
		// create rect
		SDL_Rect TopLeft;
		TopLeft.x = 0; 
		TopLeft.y = Height/2;
		TopLeft.w = Width/2;
		TopLeft.h = Height / 2;

		// set to rendere at a given Rect 
		SDL_RenderSetViewport(Renderer, &TopLeft);

		// send texture to renderer
		SDL_RenderCopy(Renderer, Texture, nullptr, nullptr);

		SDL_RenderPresent(Renderer);
	}


	End();
	return 0;
}