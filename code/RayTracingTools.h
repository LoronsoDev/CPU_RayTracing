// Code by Lorenzo Herrán, (c) 2022. Code is free use.

#pragma once
#include <glm.hpp>
#include <vector>
#include "RendererTools.h"

namespace rtx
{
	typedef RGB888 Color;

	class Shape
	{
	public:

		glm::vec3 position;
		Color color;

		Shape() = default;
	};

	class Sphere : public Shape
	{
	public:

		float radius;

		Sphere(glm::vec3 position = { 0, 0, 1 }, Color color = {255, 0, 0}, float radius = 1) : radius(radius)
		{
			this->color = color;
			this->position = position;
		}

	};

	struct Scene
	{
	public:
		gfx::Viewport viewport;
		std::vector<Sphere> spheres;

		Scene()
		{
		}
	};

	class RayTracer
	{
	public:

		Scene scene;

		RayTracer(Scene& scene) : scene(scene)
		{

		}

		RayTracer() = default;

		Color TraceRay(glm::vec3 ray_origin, glm::vec3 ray_direction, float t_min, float t_max);
		glm::vec2 IntersectRaySphere(glm::vec3 ray_origin, glm::vec3 ray_direction, Sphere & sphere);
	};
}



