// Code by Lorenzo Herrán, (c) 2022. Code is free use.

#include "RayTracingTools.h"

rtx::Color rtx::RayTracer::TraceRay(glm::vec3 ray_origin, glm::vec3 ray_direction, float t_min, float t_max)
{
	float closest_t = 9999;
	Sphere* closest_sphere = nullptr;

	for (int i = 0; i < scene.spheres.size(); i++)
	{
		Sphere& sphere = scene.spheres[i];

		glm::vec2 ts = IntersectRaySphere(ray_origin, ray_direction, sphere);

		if (ts[0] < closest_t)
		{
			if (ts[0] > t_min && ts[0] < t_max)
			{
				closest_t = ts[0];
				closest_sphere = &sphere;		
			}
		}

		if (ts[1] < closest_t)
		{
			if (ts[1] > t_min && ts[1] < t_max)
			{
				closest_t = ts[1];
				closest_sphere = &sphere;
			}
		}

	}

	if (closest_sphere == nullptr)
	{
		return { 0,0,0 };
	}

	return closest_sphere->color;
}

glm::vec2 rtx::RayTracer::IntersectRaySphere(glm::vec3 ray_origin, glm::vec3 ray_direction, Sphere& sphere)
{
	float r = sphere.radius;
	glm::vec3 distance_from_origin = ray_origin - sphere.position;

	float a = glm::dot(ray_direction, ray_direction);
	float b = 2 * glm::dot(distance_from_origin, ray_direction);
	float c = glm::dot(distance_from_origin, distance_from_origin) - r * r;

	float discriminant = b * b - 4 * a * c;

	if (discriminant < 0)
	{
		return { std::numeric_limits<float>::max(), std::numeric_limits<float>::max() };
	}

	float t1 = (-b + glm::sqrt(discriminant)) / 2 * a;
	float t2 = (-b - glm::sqrt(discriminant)) / 2 * a;

	return { t1,t2 };
}