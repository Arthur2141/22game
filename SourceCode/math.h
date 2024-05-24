#pragma once
#include"../GameLib/vector.h"

namespace math
{
	float GetAngleBetweenToPoints(VECTOR2 pos1, VECTOR2 pos2);

	float ToRadian(float degree);

	float GenerateRandomNumber(float min, float max);

	float ease_in_out_quad(float progress);

	float lerp(float a, float b, float t);
	float frand(float min, float max);
}