#include <cstdio>
#include <SDL.h>

// window dimantion
int const WindowWidth = 640;
int const WindowHight = 480;
// start sdl
void Start();

// load image
void LoadMedia();

// end sdl
void End();

// the window
SDL_Window *Window = nullptr;

// the surface
SDL_Surface *Surface = nullptr;

// image surface
SDL_Surface *Image = nullptr;

int main(int argc, char* args[])
{
	Start();

	LoadMedia();

	// fast surface copy to a destination surface
	SDL_BlitSurface(Image, nullptr, Surface, nullptr);

	// to copy the window surface to the window
	SDL_UpdateWindowSurface(Window);

	SDL_Delay(2000);

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

void LoadMedia()
{
	// load image to image surface
	Image = SDL_LoadBMP("files/img.bmp");
	if (Image == nullptr)
		printf("ERROR AT SDL_LoadBMP\n\n");

}

void End()
{
	SDL_FreeSurface(Image);
	Image = nullptr;

	SDL_FreeSurface(Surface);
	Surface = nullptr;

	SDL_DestroyWindow(Window);
	Window = nullptr;

	SDL_Quit();
}