// Code by Lorenzo Herrán, (c) 2022. Code is free use.

#include "RayTracingTools.h"

rtx::Color rtx::RayTracer::TraceRay(glm::vec3 ray_origin, glm::vec3 ray_direction, float t_min, float t_max)
{
	float closest_t = 9999;
	Sphere* closest_sphere = nullptr;
	HitInfo best_hit;

	for (int i = 0; i < scene.spheres.size(); i++)
	{
		HitInfo hit;
		Sphere& sphere = scene.spheres[i];

		hit = IntersectRaySphere(ray_origin, ray_direction, sphere);

		if (hit.distance < closest_t)
		{
			if (hit.distance > t_min && hit.distance < t_max)
			{
				closest_t = hit.distance;
				closest_sphere = &sphere;	
				
				best_hit = hit;
			}
		}

	}

	if (closest_sphere == nullptr)
	{
		return { 0,0,0 };
	}

	rtx::Color final_color = (glm::vec3)closest_sphere->color * glm::clamp(ComputeLighting(best_hit.point, best_hit.normal, -ray_direction, closest_sphere->specular), 0.0f, 1.f);

	return final_color;
}

rtx::HitInfo rtx::RayTracer::IntersectRaySphere(glm::vec3 ray_origin, glm::vec3 ray_direction, Sphere& sphere)
{
	HitInfo hitInfo;

	float r = sphere.radius;
	glm::vec3 distance_from_origin = ray_origin - sphere.position;

	float a = glm::dot(ray_direction, ray_direction);
	float b = 2 * glm::dot(distance_from_origin, ray_direction);
	float c = glm::dot(distance_from_origin, distance_from_origin) - r * r;

	float discriminant = b * b - 4 * a * c;

	if (discriminant < 0)
	{
		hitInfo.distance = std::numeric_limits<float>::max();
		return hitInfo;
	}

	// We ignore the other solution as this one will always be closer
	float t = (-b - glm::sqrt(discriminant)) / 2 * a;

	hitInfo.distance = t;

	hitInfo.point = ray_origin + t * ray_direction;
	hitInfo.normal = glm::normalize(hitInfo.point - sphere.position);

	return hitInfo;
}

float rtx::RayTracer::ComputeLighting(glm::vec3 p, glm::vec3 n, glm::vec3 v, float specular)
{
	float i = 0.f;

	for (int light_index = 0; light_index < scene.lights.size(); light_index++)
	{
		gfx::Light& light = scene.lights[light_index];

		if (light.type == gfx::Light::AMBIENT)
		{
			i += light.intensity;
		}
		else
		{
			glm::vec3 light_dir = glm::vec3(0);

			if (light.type == gfx::Light::POINT)
			{
				light_dir = light.position - p;
			}
			else if (light.type == gfx::Light::DIRECTIONAL)
			{
				light_dir = light.direction;
			}

			// Diffuse...

			float n_dot_l = glm::max(glm::dot(n, light_dir), 0.0f);

			float lengths_multiplied = (glm::length(n) * glm::length(light_dir));

			i += light.intensity * n_dot_l / lengths_multiplied;

			// Specular...

			if (specular != -1)
			{
				glm::vec3 reflex = 2.0f * n * glm::dot(n, light_dir) - light_dir;
				float r_dot_v = glm::max(glm::dot(reflex, v), 0.0f);
				i += light.intensity * glm::pow(r_dot_v / (glm::length(reflex) * glm::length(v)), specular);

			}

		}

		


	}

	return i;
}