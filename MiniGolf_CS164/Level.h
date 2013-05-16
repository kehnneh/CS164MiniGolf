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
	Level();
	~Level();

	void Render(BaseCamera* camera, Shader* shader);

	bool Init(std::string filename);
};

