#pragma once

#include <glm\glm.hpp>

class VertexObject
{
private:
  glm::vec3 *_vert;

public:
  VertexObject()
    : _vert(0)
  {}
  ~VertexObject()
  {}

  void Init();
  void DeInit();

  float Length() const;

  // Rotate
  

  void Increment(float x, float y, float z);
  void IncX(float x);
  void IncY(float y);
  void IncZ(float z);

  void Set(float x, float y, float z);
  const glm::vec3 *Vertex() const;
};
