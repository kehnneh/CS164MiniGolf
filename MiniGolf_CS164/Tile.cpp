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

			r->GenerateColor(glm::vec4(1.f, .0f, .0f, 1.f));
			borders.push_back(r);
		}
	}

  ComputeSlope(glm::vec3(0.f, 1.f, 0.f));
}

void Tile::ComputeSlope(const glm::vec3 up)
{

}

void Tile::RenderBorders(Camera* c)
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
