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

	Tile()
		: tileId(0),
		  edges(0),
		  neighbors(0)
	{}
	Tile(unsigned short Id)
		: tileId(Id),
		  edges(0),
		  neighbors(0)
	{}
	~Tile()
	{}

	void TileInit();

	void DeInit();

	bool SetNeighbor(unsigned short edgeId, unsigned short neighborTileId);

	void Finalize();
	void RenderBorders(BaseCamera* c);
};

