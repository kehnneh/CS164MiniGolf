#pragma once

#include <glm\glm.hpp>

class Moveable
{
private:
	glm::vec3 _velocity;

public:
	Moveable() :
	  _velocity(0.f, 0.f, 0.f)
	{}

	~Moveable()
	{}
};

