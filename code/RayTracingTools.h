// Code by Lorenzo Herrán, (c) 2022. Code is free use.

#pragma once
#include <glm.hpp>
#include <vector>
#include "RendererTools.h"
#include "Light.h"

namespace rtx
{
	typedef RGB888 Color;

	struct HitInfo
	{
		glm::vec3 normal, point;
		float distance;
	};

	class Shape
	{
	public:

		glm::vec3 position;
		Color color;
		float specular;

		Shape() = default;
	};

	class Sphere : public Shape
	{
	public:

		float radius;

		Sphere(glm::vec3 position = { 0, 0, 1 }, Color color = { 255, 0, 0 }, float specular = 0, float radius = 1) : radius(radius)
		{
			this->specular = specular;
			this->color = color;
			this->position = position;
		}

	};

	struct Scene
	{
	public:
		gfx::Viewport viewport;
		std::vector<Sphere> spheres;
		std::vector<gfx::Light> lights;

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
		HitInfo IntersectRaySphere(glm::vec3 ray_origin, glm::vec3 ray_direction, Sphere & sphere);

		float ComputeLighting(glm::vec3 point, glm::vec3 normal, glm::vec3 v, float specular);
	};
}



