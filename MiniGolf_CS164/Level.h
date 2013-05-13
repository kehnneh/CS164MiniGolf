#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "Tile.h"
#include "Camera.h"

class Level
{
private:
	std::vector<Renderable*> tiles;
	std::vector<Renderable*> others;
	unsigned short teeId, cupId;
	glm::vec3 teePos, cupPos, lightDir;

public:
	Level();
	~Level();

	void Render(Camera* camera, Shader* shader);

	bool Init(std::string filename);
};

