#include "Tile.h"
#include "Renderable.h"

void Tile::TileInit()
{
	edges = vertices;
	neighbors = new unsigned short[vertices];
}

bool Tile::SetNeighbor(unsigned short edgeId, unsigned short neighborTileId)
{
	if (edgeId < edges)
	{
		neighbors[edgeId] = neighborTileId;
		return true;
	}
	return false;
}

void Tile::GenerateColor()
{
	colorData = new glm::vec4[vertices];

	for (unsigned int i = 0; i < vertices; i++)
	{
		colorData[i].r = .0f;
		colorData[i].g = 1.f;
		colorData[i].b = .0f;
		colorData[i].a = 1.f;
	}
}

void Tile::Finalize()
{
	// check each neighbor
	for (unsigned int i = 0; i < vertices; i++)
	{
		// do we need to make a border?
		if (neighbors[i] <= 0)
		{
			// need to make 4 vertices, in CCW order, from two base vertices
			// and two vertices above that
			glm::vec3* border = new glm::vec3[4];
			border[3] = vertexData[i];
			border[2] = vertexData[i + 1 == vertices ? 0 : i + 1];
			border[1] = vertexData[i + 1 == vertices ? 0 : i + 1];
			border[1].y += .25f;
			border[0] = vertexData[i];
			border[0].y += .25f;

			Renderable *r = new Renderable;
			if (!r->Init(border, 4))
			{
				// log error
			}

			borders.push_back(r);
		}
	}
}

void Tile::RenderBorders(BaseCamera* c)
{
	for (std::vector<Renderable*>::iterator it = borders.begin(); it != borders.end(); ++it)
	{
		(*it)->Render(c);
	}
}

void Tile::DeInit()
{
	if (neighbors) delete neighbors;
	for (std::vector<Renderable*>::iterator it = borders.begin(); it != borders.end(); ++it)
	{
		delete *it;
	}

	Renderable::DeInit();
}
