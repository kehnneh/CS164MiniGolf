#include "Golfball.h"
#include "CommonUtils.h"

bool Golfball::Init()
{
  _sphere = new Renderable();
  if (!_sphere->Init("Models/golfball.obj"))
  {
    return false;
  }

  _sphere->GenerateColor(glm::vec4(1.f, 1.f, 1.f, 1.f));

  _transform = new MatrixObject;
  _transform->Init();

  return true;
}

void Golfball::DeInit()
{
  SAFE_DELETE(_sphere);
}

void Golfball::Tick(double t)
{
  Moveable::Tick(t);
  
  // If _tile has
  // check if the ball went in the hole?
}

void Golfball::Position(const glm::vec3 pos)
{
  _sphere->SetPosition(pos);
  _transform->Position(pos);
}