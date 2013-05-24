#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "Tile.h"
#include "Camera.h"
#include "Golfball.h"

class Level
{
private:
	std::vector<Renderable*> tiles;
	std::vector<Renderable*> others;
	std::string hole_name, hole_name2, hole_name3, course_name;
	unsigned short teeId, cupId, holeAmt, par_val;
	glm::vec3 teePos, cupPos, lightDir;
	glm::vec4 ambientLight;

	Golfball *_ball;

public:
	Level()
		: lightDir(glm::vec3(-1.f, 1.f, -1.f)),
		  ambientLight(glm::vec4(.2f, .2f, .2f, 1.f)),
      _ball(0)
	{}

	~Level()
	{}

	void Render(Camera* camera, Shader* shader);

	bool Init(std::string filename);
	void DeInit();
};

