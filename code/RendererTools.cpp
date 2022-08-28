// Code by Lorenzo Herrán, (c) 2022. Code is free use.

#include "RendererTools.h"

using namespace gfx;

Canvas::Canvas(int width, int height) : width(width), height(height)
{
	SDL_Init(SDL_INIT_VIDEO);
	SDL_CreateWindowAndRenderer(width, height, 0, &window, &renderer);
}

Canvas::~Canvas()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void Canvas::PollEventsAndCloseIfAsked()
{
    while (true) {
        SDL_PollEvent(&event);

        if (event.type == SDL_QUIT)
            break;
    }

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int Canvas::ConvertXCoords(int x)
{
    return width / 2 + x;
}

int Canvas::ConvertYCoords(int y)
{
    return height / 2 - y;
}

glm::fvec3 Canvas::CanvasToViewportCoords(int x, int y, Viewport & viewport)
{
    // We only need a change of scale as the viewport is directly in front of the rendering camera.

    float _x = x * (viewport.width / float(width));
    float _y = y * (viewport.height / float(height));
    float _z = float(viewport.distance);

    return { _x, _y, _z };
}
