// Code by Lorenzo Herrán, (c) 2022. Code is free use.

#include "SDL.h"
#include "RendererTools.h"
#include "RayTracingTools.h"

int main(int argc, char* argv[])
{
    const int window_width = 800;
    const int window_height = 800;

    gfx::Canvas canvas(window_width, window_height);

    canvas.Clear();

    gfx::Camera camera;
    gfx::Viewport viewport(1, 1, 1);

    rtx::Scene scene;

    rtx::Sphere sphere_red({ 0, -1, 3 } ,    { 255, 0, 0 });
    rtx::Sphere sphere_blue({ 2, 0, 4 }  ,    { 0, 0, 255 });
    rtx::Sphere sphere_green({ -2, 0, 4 } ,    { 0, 255, 0 });

    scene.spheres.push_back(sphere_red);
    scene.spheres.push_back(sphere_blue);
    scene.spheres.push_back(sphere_green);

    scene.viewport = viewport;

    rtx::RayTracer tracer (scene);

    glm::vec3 starting_point = { 0,0,0 };

    canvas.PutPixel(250, 100, { 0, 255, 0, 255 });

    //For every pixel
    for (int x = -window_width/2; x < window_width/2; x++)
    {
        for (int y = -window_height / 2; y < window_height/2; y++)
        {
            glm::fvec3 dir = canvas.CanvasToViewportCoords(x, y, viewport);
            rtx::Color color = tracer.TraceRay(starting_point, dir, 1, 999);

            //Canvas admits one more channel.
            gfx::Color canvasColor = { color.r, color.g, color.b, 255 };

            if (color.r == 255)
            {
               const char* debug = "";
            }

            canvas.PutPixel(x, y, canvasColor);
        }
    }

    canvas.Render();

    canvas.PollEventsAndCloseIfAsked();

    return 0;
}