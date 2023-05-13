// Code by Lorenzo Herrán, (c) 2022. Code is free use.

#include "SDL.h"
#include "RendererTools.h"
#include "RayTracingTools.h"
#include <chrono>

int main(int argc, char* argv[])
{
    const int window_width = 800;
    const int window_height = 800;

    gfx::Canvas canvas(window_width, window_height);

    canvas.Clear();

    gfx::Camera camera;
    gfx::Viewport viewport(1, 1, 1);

    rtx::Scene scene;

    //Spheres...
    {
        rtx::Sphere sphere_red({ 0, -1, 3 }, { 255, 0, 0 }, 500);
        rtx::Sphere sphere_blue({ 2, 0, 4 }, { 0, 0, 255 }, 500);
        rtx::Sphere sphere_green({ -2, 0, 4 }, { 0, 255, 0 }, 10);
        rtx::Sphere sphere_yellow({0, -5001, 0}, {255, 255, 0}, 1000.f, 5000);

        scene.spheres.push_back(sphere_red);
        scene.spheres.push_back(sphere_blue);
        scene.spheres.push_back(sphere_green);
        scene.spheres.push_back(sphere_yellow);
    }
    

    //Lights...
    {
        gfx::Light ambient_light;
        ambient_light.type = gfx::Light::AMBIENT;
        ambient_light.intensity = 0.2f;

        gfx::Light point_light;
        point_light.type = gfx::Light::POINT;
        point_light.intensity = 0.6f;
        point_light.position = { 2, 1, 0 };

        gfx::Light directional_light;
        directional_light.type = gfx::Light::DIRECTIONAL;
        directional_light.direction = { 1,4,4 };
        directional_light.intensity = 0.2f;

        scene.lights.push_back(ambient_light);
        scene.lights.push_back(point_light);
        scene.lights.push_back(directional_light);
    }

    scene.viewport = viewport;

    rtx::RayTracer tracer (scene);

    glm::vec3 starting_point = { 0,0,0 };

    float ticks_since_start;

    while (true)
    {
        ticks_since_start = (float) SDL_GetTicks64();

        canvas.Clear();

        //For every pixel
        for (int x = -window_width / 2; x < window_width / 2; x++)
        {
            for (int y = -window_height / 2; y < window_height / 2; y++)
            {
                glm::fvec3 dir = canvas.CanvasToViewportCoords(x, y, viewport);
                rtx::Color color = tracer.TraceRay(starting_point, dir, 1, 999);

                //Canvas admits one more channel.
                gfx::Color canvasColor = { color.r, color.g, color.b, 255 };

                canvas.PutPixel(x, y, canvasColor);
            }
        }

        float ticks_passed = ( (float) SDL_GetTicks64() - ticks_since_start ) / 60.f;

        starting_point.z -= 0.1f * ticks_passed;

        canvas.Render();

        //canvas.PollEventsAndCloseIfAsked();
    }
  

    return 0;
}