#include "MatrixObject.h"

#include "CommonUtils.h"
#include <glm\gtx\transform.hpp>
#include <glm\gtc\quaternion.hpp>

#define UPDATE_ROTATION 0x1
#define UPDATE_POSITION 0x2

void MatrixObject::Init()
{
  _mat = new glm::mat4;
  _posmat = new glm::mat4;
  _rotmat = new glm::mat4;
  _pos = new glm::vec3;
  _rot = new glm::vec3;
}

void MatrixObject::DeInit()
{
  SAFE_DELETE(_rot);
  SAFE_DELETE(_pos);
  SAFE_DELETE(_rotmat);
  SAFE_DELETE(_posmat);
  SAFE_DELETE(_mat);
}

void IncrementDegreesWrap(float& val, float degrees, float limit)
{
  val += degrees;

  if (val > limit)
  {
    val -= limit;
  }
  else if (val < 0.f)
  {
    val += limit;
  }
}

void IncrementDegrees(float& val, float degrees, float limit)
{
  val += degrees;
  if (val > limit)
  {
    val = limit - 0.1f;
  }
  else if (val < -limit)
  {
    val = 0.1f - limit;
  }
}

// Increments the Pitch (X-Rotation) by the specified amount in degrees, then
// flags the matrix for updating
void MatrixObject::IncPitch(float degrees)
{
  // If this matrix is for a camera, prevent wrapping there
	// IncrementDegrees(_rot->x, degrees, 90.f);
  IncrementDegreesWrap(_rot->x, degrees, 360.f);
	_updateFlags |= UPDATE_ROTATION;
}

// Increments the Yaw (Y-Rotation) by the specified amount in degrees, then
// flags the matrix for updating
void MatrixObject::IncYaw(float degrees)
{
  IncrementDegreesWrap(_rot->y, degrees, 360.f);
	_updateFlags |= UPDATE_ROTATION;
}

// Increments the Roll (Z-Rotation) by the specified amount in degrees, then
// flags the matrix for updating
void MatrixObject::IncRoll(float degrees)
{
  IncrementDegreesWrap(_rot->z, degrees, 360.f);
	_updateFlags |= UPDATE_ROTATION;
}

void MatrixObject::Tick()
{
  if (_updateFlags & UPDATE_ROTATION)
  {
    *_rotmat = glm::mat4_cast(glm::quat(*_rot));
  }

  if (_updateFlags & UPDATE_POSITION)
  {
    *_posmat = glm::translate(*_pos);
  }

  if (_updateFlags)
  {
    *_mat = *_rotmat * *_posmat;
    _updateFlags = 0x0;
  }
}