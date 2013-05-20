#pragma once

#include "Renderable.h"
#include "Moveable.h"
#include "MatrixObject.h"

class Golfball : public Moveable
{
private:
  Renderable *_sphere;
  MatrixObject *_transform;

public:
  Golfball() :
      _sphere(0), _transform(0)
  {}

  ~Golfball()
  {}

  bool Init();
  void DeInit();

  void Tick(double t);

  // Position Setter
  void Position(const glm::vec3 pos);
};

