#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "Tile.h"
#include "BaseCamera.h"

class Level
{
private:
	std::vector<Renderable*> tiles;
	std::vector<Renderable*> others;
	unsigned short teeId, cupId;
	glm::vec3 teePos, cupPos, lightDir;
	glm::vec4 ambientLight;

public:
	Level()
		: lightDir(glm::vec3(5.f, 10.f, 0.f)),
		  ambientLight(glm::vec4(.2f, .2f, .2f, 1.f))
	{}
	~Level()
	{}

	void Render(BaseCamera* camera, Shader* shader);

	bool Init(std::string filename);
	void DeInit();
};

