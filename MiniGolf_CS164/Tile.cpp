#include "Tile.h"
#include "Renderable.h"

#include <glm\gtx\intersect.hpp>

void Tile::TileInit()
{
	edges = vertices;
	neighbors = new unsigned short[vertices];
  _slope = new glm::vec3;
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
  *_slope = glm::normalize(glm::cross(normalData[0], glm::cross(up, normalData[0])));
}

bool Tile::IsOnTile(const Moveable* m)
{
  glm::vec3 something;
  glm::vec3 down(0.f, -1.f, 0.f);
  for (unsigned int i = 0; i < indices; i += 3)
  {
    if (glm::intersectRayTriangle(*m->Position(), down, vertexData[i], vertexData[i + 1], vertexData[i + 2], something))
    {
      return true;
    }
  }
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
