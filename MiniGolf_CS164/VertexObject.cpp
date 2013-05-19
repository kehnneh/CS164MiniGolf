#include "VertexObject.h"

#include "CommonUtils.h"

#include <glm\gtx\rotate_vector.hpp>

void VertexObject::Init()
{
  _vert = new glm::vec3;
}

void VertexObject::DeInit()
{
  SAFE_DELETE(_vert);
}

void VertexObject::Increment(float x, float y, float z)
{
  IncX(x);
  IncY(y);
  IncZ(z);
}

void VertexObject::IncX(float x)
{
  _vert->x += x;
}

void VertexObject::IncY(float y)
{
  _vert->y += y;
}

void VertexObject::IncZ(float z)
{
  _vert->z += z;
}

void VertexObject::Set(float x, float y, float z)
{
  _vert->x = x;
  _vert->y = y;
  _vert->z = z;
}

const glm::vec3 *VertexObject::Vertex() const
{
  return _vert;
}