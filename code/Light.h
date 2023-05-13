// Code by Lorenzo Herr�n, (c) 2022. Code is free use.

#pragma once


namespace gfx
{
	struct Light
	{
		enum Type
		{
			AMBIENT,
			POINT,
			DIRECTIONAL
		} type;

		float intensity;

		union { glm::vec3 position, direction; };
	};
}
