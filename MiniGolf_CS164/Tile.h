#pragma once

#include <glm\glm.hpp>
#include "Renderable.h"

#include <vector>

class BaseCamera;

class Tile : public Renderable
{
protected:
	unsigned short edges;
	unsigned short* neighbors;

	std::vector<Renderable*> borders;

	void GenerateColor();

public:
	unsigned int tileId;

	Tile();
	Tile(unsigned short Id);
	~Tile();

	void TileInit();

	bool SetNeighbor(unsigned short edgeId, unsigned short neighborTileId);

	void Finalize();
	void RenderBorders(BaseCamera* c);
};

