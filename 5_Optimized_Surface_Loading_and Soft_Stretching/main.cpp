#include <cstdio>
#include <SDL.h>
#include <string>


// window dimantion
int const WindowWidth = 640;
int const WindowHight = 480;
// start sdl
void Start();

// load image
SDL_Surface * LoadMedia(std::string path);


// end sdl
void End();

// the window
SDL_Window *Window = nullptr;

// the surface
SDL_Surface *Surface = nullptr;


int main(int argc, char* args[])
{
	Start();

	// quit flag
	bool Quit = false;

	// event handeler 
	SDL_Event Event; // an enumeration of the types of events that can be delivered.


	// current surface to load
	SDL_Surface *Current = LoadMedia("files/img.bmp");

	// main loop
	while (Quit != true)
	{
		// event loop
		while (SDL_PollEvent(&Event) != 0) //  Returns 1 if there is a pending event or 0 if there are none available.
		{
			if (Event.type == SDL_QUIT)
				Quit = true;
		}

		// surface copy to a destination surface and stretch the surface
		SDL_Rect DImage;
		DImage.h = WindowHight;
		DImage.w = WindowWidth;
		DImage.x = 0;
		DImage.y = 0;

		SDL_BlitScaled(Current, nullptr, Surface, &DImage);

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

	SDL_Surface *optm = SDL_ConvertSurface(tmp, Surface->format, NULL);
	if (optm == nullptr)
		printf("ERROR AT SDL_ConvertSurface\n\n");

	SDL_FreeSurface(tmp);
	return optm;
}


void End()
{

	SDL_FreeSurface(Surface);
	Surface = nullptr;

	SDL_DestroyWindow(Window);
	Window = nullptr;

	SDL_Quit();
}