#include <cstdio>
#include <string>
#include <SDL.h>
#include <SDL_image.h>


// window dimantion
int const WindowWidth = 640;
int const WindowHight = 480;
// start sdl
void Start();

// load image
SDL_Texture * LoadMedia(std::string path);

// end sdl
void End();

// the window
SDL_Window *Window = nullptr;

// the texutre
SDL_Texture *Texture = nullptr;

// the renderer
SDL_Renderer *Renderer = nullptr;

int main(int argc, char* args[])
{
	Start();

	// quit flag
	bool Quit = false;

	// event handeler 
	SDL_Event Event; // an enumeration of the types of events that can be delivered.


	// current surface to load
	Texture = LoadMedia("files/img.png");

	// main loop
	while (Quit != true)
	{
		// event loop
		while (SDL_PollEvent(&Event) != 0) //  Returns 1 if there is a pending event or 0 if there are none available.
		{
			if (Event.type == SDL_QUIT)
				Quit = true;
		}

		// clear renderer 
		SDL_RenderClear(Renderer);

		// send texutre to renderer 
		SDL_RenderCopy(Renderer, Texture, nullptr, nullptr);

		// show renderer to the window
		SDL_RenderPresent(Renderer);

	}

	End();

	return 0;
}

void Start()
{
	// start sdl
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
		printf("ERROR AT SDL_Init\n\n");

	// create window
	Window = SDL_CreateWindow("SDL SWS", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WindowWidth, WindowHight, SDL_WINDOW_SHOWN);
	if (Window == nullptr)
		printf("ERROR AT SDL_CreateWindow\n\n");

	// creating renderer to the window
	Renderer = SDL_CreateRenderer(Window, -1, SDL_RENDERER_ACCELERATED);
	if (Renderer == nullptr)
		printf("ERROR AT SDL_CreateRenderer\n\n");

	// setting up the starting draw color
	SDL_SetRenderDrawColor(Renderer, 0xFF, 0xFF, 0xFF, 0xFF);

	if (!IMG_Init(IMG_INIT_PNG))
		printf("ERROR AT IMG_Init\n\n");
}

SDL_Texture * LoadMedia(std::string path)
{
	// load image to image surface
	SDL_Surface *tmp = IMG_Load(path.c_str());
	if (tmp == nullptr)
		printf("ERROR AT IMG_Load\n\n");

	SDL_Texture * Tex = SDL_CreateTextureFromSurface(Renderer, tmp);
	if (Tex == nullptr)
		printf("ERROR AT SDL_CreateTextureFromSurface\n\n");

	SDL_FreeSurface(tmp);
	return Tex;
}


void End()
{


	SDL_DestroyWindow(Window);
	Window = nullptr;

	SDL_Quit();
}