#pragma once

#include "Renderable.h"
#include "Moveable.h"
#include "MatrixObject.h"

class Golfball : public Moveable
{
private:
  Renderable *_sphere;
  MatrixObject *_transform;

  float _radius;

public:
  Golfball() :
      _sphere(0), _transform(0), _radius(0.f)
  {}

  ~Golfball()
  {}

  bool Init();
  void DeInit();

  void Tick(double t);

  // Position Setter
  void Position(const glm::vec3 pos);
};

