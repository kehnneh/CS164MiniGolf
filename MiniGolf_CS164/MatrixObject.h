#pragma once

#include <glm\glm.hpp>

class MatrixObject
{
private:
	glm::mat4 *_mat, *_rotmat, *_posmat;
	glm::vec3 *_pos, *_rot;

  unsigned char _updateFlags;

public:
	MatrixObject()
		: _mat(0), _posmat(0), _rotmat(0),
      _pos(0), _rot(0),
      _updateFlags(0)
	{}
	~MatrixObject()
	{}

  // Rotation setters
  void Rotation(float x, float y, float z);
  void Rotation(glm::vec3 rot);
  
  // Rotation incrementers
  void IncPitch(float degrees);
  void IncYaw(float degrees);
  void IncRoll(float degrees);

  // Position setters
  void Position(float x, float y, float z);
  void Position(glm::vec3 pos);

  // Position incrementers
  void IncX(float x);
  void IncY(float y);
  void IncZ(float z);
  
  // Relative position incrementers
  void MoveForward(float amt);
  void MoveRight(float amt);
  void MoveUp(float amt);

	void Init();
	void DeInit();

  void Tick();
};

