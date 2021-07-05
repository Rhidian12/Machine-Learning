#pragma once

#include <string>

struct SDL_Texture;
class Texture final
{
public:
	Texture(const std::string& path);

private:
	SDL_Texture* m_pTexture;
};