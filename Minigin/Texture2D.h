#pragma once
#include <glm/vec2.hpp>

class GameObject;
class Renderer;

struct SDL_Texture;
namespace dae
{
	class Texture2D final
	{
	public:
		SDL_Texture* GetSDLTexture() const;
		explicit Texture2D(SDL_Texture* texture);
		~Texture2D();

		Texture2D(const Texture2D &) = delete;
		Texture2D(Texture2D &&) = delete;
		Texture2D & operator= (const Texture2D &) = delete;
		Texture2D & operator= (const Texture2D &&) = delete;

		glm::ivec2 GetSize() const;

	private:
		SDL_Texture* m_texture;
	};
}
