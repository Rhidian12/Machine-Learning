#include <iostream>

#include "FMatrix/FMatrix.h"

#ifdef UNIT_TESTS

#define CATCH_CONFIG_MAIN
#include "catch.hpp"

TEST_CASE("Test FMatrix")
{
	FMatrix originalMatrix{ 4,4 };

	const uint32_t nrOfRows{ originalMatrix.GetNumberOfRows() };
	const uint32_t nrOfCols{ originalMatrix.GetNumberOfColumns() };

	REQUIRE(nrOfRows == 4);
	REQUIRE(nrOfCols == 4);

	for (uint32_t r{}; r < nrOfRows; ++r)
		for (uint32_t c{}; c < nrOfCols; ++c)
			REQUIRE(originalMatrix.Get(r, c) == 0.f);

	originalMatrix.Set(2, 2, 15.f);
	REQUIRE(originalMatrix.Get(2, 2) == 15.f);

	originalMatrix.SetAll(42.f);
	for (uint32_t r{}; r < nrOfRows; ++r)
		for (uint32_t c{}; c < nrOfCols; ++c)
			REQUIRE(originalMatrix.Get(r, c) == 42.f);

	FMatrix copyConstructorMatrix{ originalMatrix };
	REQUIRE(originalMatrix == copyConstructorMatrix);
	REQUIRE_FALSE(originalMatrix != copyConstructorMatrix);

	FMatrix moveConstructorMatrix{ std::move(copyConstructorMatrix) };
	REQUIRE(originalMatrix == moveConstructorMatrix);
	REQUIRE(copyConstructorMatrix.GetNumberOfRows() == 0);

	FMatrix copyOperatorMatrix{ originalMatrix };
	REQUIRE(originalMatrix == copyOperatorMatrix);

	FMatrix moveOperatorMatrix{ std::move(copyOperatorMatrix) };
	REQUIRE(originalMatrix == moveOperatorMatrix);
	REQUIRE(copyOperatorMatrix.GetNumberOfRows() == 0);
}

#else

#include <SDL.h>
#include <SDL_opengl.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>
#include <SDL_video.h>
#include <GL\GLU.h>

SDL_Window* InitSDL();

int main(int, char*[])
{
	InitSDL();



	return 0;
}

SDL_Window* InitSDL()
{
	uint32_t width = 640;
	uint32_t height = 480;

#pragma region SDL Stuff
	//Create window + surfaces
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_AUDIO) == -1)
	{
		std::cout << SDL_GetError() << std::endl;
	}

	SDL_Window* pWindow = SDL_CreateWindow(
		"Programming 4 Assignment - Rhidian De Wit",
		SDL_WINDOWPOS_CENTERED,
		SDL_WINDOWPOS_CENTERED,
		width, height,
		SDL_WINDOW_OPENGL);

	if (!pWindow)
	{
		std::cerr << "Error: m_pWindow failed in App::Initialize()\n";
		return nullptr;
	}

	SDL_GLContext context = SDL_GL_CreateContext(pWindow);
	if (context == nullptr)
		std::cerr << "App::Initialize() CreateContext() failed\n";

	if (SDL_GL_SetSwapInterval(1) < 0)
	{
		std::cerr << "App::Initialize() error when calling SDL_GL_SetSwapInterval " << SDL_GetError() << std::endl;
		return nullptr;
	}

	// Set the Projection matrix to the identity matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	// Set up a two-dimensional orthographic viewing region.
	gluOrtho2D(0, width, 0, height); // y from bottom to top

	// Set the viewport to the client window area
	// The viewport is the rectangu	lar region of the window where the image is drawn.
	glViewport(0, 0, width, height);

	// Set the Modelview matrix to the identity matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// Enable color blending and use alpha blending
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	//Initialize PNG loading
	const int pngFlags{ IMG_INIT_PNG };
	const int jpgFlags{ IMG_INIT_JPG };
	if (!(IMG_Init(pngFlags) & pngFlags) || !(IMG_Init(jpgFlags) & jpgFlags))
		std::cerr << "SDL_image could not initialize! SDL_image Error: %s\n";

	if (TTF_Init() != 0)
		std::cerr << SDL_GetError() << std::endl;

	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 4, 2048) == -1)
	{
		std::cout << Mix_GetError() << std::endl;;
	}
	const int mixerFlags{ MIX_INIT_FLAC | MIX_INIT_MOD | MIX_INIT_MP3 | MIX_INIT_OGG };
	if ((Mix_Init(mixerFlags) & mixerFlags) != mixerFlags)
	{
		std::cout << Mix_GetError() << std::endl;
	}
#pragma endregion

	// == Seed rand() ==
	srand(static_cast<unsigned int>(time(nullptr)));

	std::cout << "Initialisation done" << std::endl;

	return pWindow;
}

#endif