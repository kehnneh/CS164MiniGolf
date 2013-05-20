#include "Moveable.h"
#include "CommonUtils.h"

// This could be a little more dynamic, if we stored the World's Up
// vector and used that as the direction in which gravity operates.
const glm::vec3 *Moveable::_gravity = new glm::vec3(0.f, -9.81f, 0.f);

void Moveable::Init()
{
  _velocity = new glm::vec3;
}

void Moveable::DeInit()
{
  SAFE_DELETE(_velocity);
}

void Moveable::Tick(double t)
{
  // Has the object changed tiles?
  // - Yes:
  //    + Update the _tile reference
  // - No:
}

void Moveable::Impulse(float s)
{
  _speed = s;
}