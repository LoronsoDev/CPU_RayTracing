// Code by Lorenzo Herrán, (c) 2022. Code is free use.

#pragma once
#include <SDL.h>
#include <glm.hpp>

typedef glm::u8vec4 RGBA8888;
typedef glm::u8vec3 RGB888;

namespace gfx
{
	typedef RGBA8888 Color;


	class Viewport
	{
	public:

		float distance;
		int height, width;

		Viewport() : distance(1), height(1), width(1)
		{

		}

		Viewport(float distance, int height, int width) : distance(distance), height(height), width(width)
		{

		}

		Viewport(int height, int width) : distance(1), height(height), width(width)
		{

		}
	};


	class Canvas
	{
	private:

		RGBA8888 selectedColor;

		SDL_Renderer* renderer;
		SDL_Window* window;
		SDL_Event event;

		int height, width;

	public:
		
		Canvas(int width, int height);
		~Canvas();


		inline void PutPixel(int x, int y)
		{
			SDL_RenderDrawPoint(renderer, ConvertXCoords(x), ConvertYCoords(y));
		}

		inline void PutPixel(int x, int y, RGBA8888 color)
		{
			selectedColor = color;
			SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);

			SDL_RenderDrawPoint(renderer, ConvertXCoords(x), ConvertYCoords(y));
		}

		inline void ChangeDrawingColor(RGBA8888 color)
		{
			selectedColor = color;
			SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
		}

		inline void Render()
		{
			SDL_RenderPresent(renderer);
		}

		inline void Clear()
		{
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
			SDL_RenderClear(renderer);
		}

		void PollEventsAndCloseIfAsked();

		glm::fvec3 CanvasToViewportCoords(int x, int y, Viewport & viewport);

	private:

		/// <summary>
		/// Converts SDL coordinates to readable coordinates (originating from the center).
		/// </summary>
		int ConvertXCoords(int x);

		/// <summary>
		/// Converts SDL coordinates to readable coordinates (originating from the center).
		/// </summary>
		int ConvertYCoords(int y);
	};

	class Camera
	{
		glm::vec3 position;
		/// <summary>
		/// 0,0,0 is pointing to Z so:
		/// Z+ is front;
		/// Y+ is up;
		/// X+ is right;
		/// </summary>
		glm::vec3 rotation;

	public:
		Camera()
			:
			position(0, 0, 0),
			rotation(0, 0, 0)
		{

		}

		Camera(glm::vec3 pos) 
			:
			position(pos)
		{

		}

		Camera(glm::vec3 pos, glm::vec3 rot)
			:
			position(pos),
			rotation(rot)
		{

		}
	};
}
