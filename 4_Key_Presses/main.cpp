#include <cstdio>
#include <SDL.h>
#include <string>

// KEY ENUM
enum KEYS
{
	KEY_DUFFULT,KEY_UP, KEY_DOWN, KEY_RIGHT, KEY_LEFT,KEY_TOTAL
};

// window dimantion
int const WindowWidth = 640;
int const WindowHight = 480;
// start sdl
void Start();

// load image
SDL_Surface * LoadMedia(std::string path);

// load all images 
void LoadAllMedia();

// end sdl
void End();

// the window
SDL_Window *Window = nullptr;

// the surface
SDL_Surface *Surface = nullptr;

// image surface
SDL_Surface *AlImage[KEY_TOTAL];

int main(int argc, char* args[])
{
	Start();

	LoadAllMedia();

	// quit flag
	bool Quit = false;

	// event handeler 
	SDL_Event Event; // an enumeration of the types of events that can be delivered.


	// current surface to load
	SDL_Surface *Current = AlImage[KEY_DUFFULT];

	// main loop
	while (Quit != true)
	{
		// event loop
		while (SDL_PollEvent(&Event) != 0) //  Returns 1 if there is a pending event or 0 if there are none available.
		{
			if (Event.type == SDL_QUIT)
				Quit = true;

			if (Event.type == SDL_KEYDOWN)
			{
				switch (Event.key.keysym.sym)
				{
				case SDLK_UP:
					Current = AlImage[KEY_UP];
					break;
				case SDLK_DOWN:
					Current = AlImage[KEY_DOWN];
					break;
				case SDLK_RIGHT:
					Current = AlImage[KEY_RIGHT];
					break;
				case SDLK_LEFT:
					Current = AlImage[KEY_LEFT];
					break;
				
				}
			}
			
		}
		if (Current == nullptr)
			printf("error current \n\n");

		// surface copy to a destination surface
		SDL_BlitSurface(Current, nullptr, Surface, nullptr);

		// function to copy the window surface to the window
		SDL_UpdateWindowSurface(Window);
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

	// to get the SDL surface associated with the window
	Surface = SDL_GetWindowSurface(Window);
	if (Surface == nullptr)
		printf("ERROR AT SDL_GetWindowSurface\n\n");

}

SDL_Surface * LoadMedia(std::string path)
{
	// load image to image surface
	SDL_Surface *tmp = SDL_LoadBMP(path.c_str());
	if (tmp == nullptr)
		printf("ERROR AT SDL_LoadBMP\n\n");

	return tmp;
}

void LoadAllMedia()
{
	AlImage[KEY_UP]    = LoadMedia("files/up.bmp");
	AlImage[KEY_DOWN]  = LoadMedia("files/down.bmp");
	AlImage[KEY_RIGHT] = LoadMedia("files/right.bmp");
	AlImage[KEY_LEFT]  = LoadMedia("files/left.bmp");
	AlImage[KEY_DUFFULT] = LoadMedia("files/press.bmp");
}

void End()
{
	for (int i = 0; i < KEY_TOTAL; ++i)
	{
		SDL_FreeSurface(AlImage[i]);
		AlImage[i] = NULL;
	}

	SDL_FreeSurface(Surface);
	Surface = nullptr;

	SDL_DestroyWindow(Window);
	Window = nullptr;

	SDL_Quit();
}