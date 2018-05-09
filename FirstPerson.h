#ifndef FIRSTPERSON_H
#define FIRSTPERSON_H

#include "Camera.h"
#include "InputController.h"
#include "MathsHelper.h"
#include "Player.h"
#include "GameBoard.h"

class FirstPerson:public Camera
{
public:
	FirstPerson(InputController* input, Vector3 startPos);
	~FirstPerson();
	void Update(float timestep);

private:
	InputController* m_input;


	float m_moveSpeed;
	float m_rotationSpeed;
	float m_heightChangeSpeed;

	float m_heading;
	float m_pitch;

};

#endif
