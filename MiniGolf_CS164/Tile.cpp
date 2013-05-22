#include "Tile.h"
#include "Renderable.h"

#include <glm\gtx\intersect.hpp>

void Tile::TileInit()
{
	edges = vertices;
	neighbors = new unsigned short[vertices];
  _slope = new glm::vec3(0.f, 0.f, 0.f);
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
  if (up == normalData[0])
  {
    *_slope = glm::vec3(1.f, 0.f, 0.f);
  }
  else
  {
    *_slope = glm::normalize(glm::cross(normalData[0], glm::cross(up, normalData[0])));
  }
}

char DeterminePosition(glm::vec3 norm, glm::vec3 pos)
{
  float p = glm::dot(norm, pos);

  if (p > 0.f)
  {
    return 0x1;
  }
  else if (p < 0.f)
  {
    return 0x2;
  }

  return 0x4;
}

// Move this into the renderable bro. check to see if it collides
// with the floor of the tile. if it doesnt: figure out which imaginary
// bound it has crossed and change tiles accordingly.
// with imaginary bounds of the tile, real bounds of the tile,
bool Tile::IsOnTile(const Moveable* m)
{
  bool result = false;
  glm::vec3 pos = *m->Position();
  float d = 0.f;

  glm::vec3 down(0.f, 1.f, 0.f);
  for (unsigned int i = 0; i < indices; i += 3)
  {
    glm::vec3* norm = &normalData[indexData[i]];
    float d = -glm::dot(vertexData[indexData[i]], *norm);
    
    char posLoc = DeterminePosition(*norm, pos);//,
    //     destLoc = DeterminePosition(*norm, ;
  }

  return result;
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
