#include "../GameLib/game_lib.h"
#include "math.h"

#include <random>

namespace math {
	std::mt19937 engine(static_cast<unsigned int>(std::time(nullptr)));

	// 2点間の距離を求める
	float GetAngleBetweenToPoints(VECTOR2 pos1, VECTOR2 pos2)
	{
		VECTOR2 v = pos1 - pos2;
		VECTOR2 nv = vec2Normalize(v); // 正規化
		return atan2(nv.y, nv.x);
	}

	// ディグリーをラジアンに変換
	float ToRadian(float degree) {
		return static_cast<float>(M_PI / 180 * degree);
	}

	// ランダムな範囲の値を返す
	float GenerateRandomNumber(float min, float max) {
		std::uniform_real_distribution<float> distribution(min, max);
		float random_number = distribution(engine);
		return random_number;
	}

	float ease_in_out_quad(float progress) {
		if (progress < 0.5f) {
			return 2 * progress * progress;
		}
		else {
			return -1 + (4 - 2 * progress) * progress;
		}
	}

	float lerp(float a, float b, float t) {
		return a + t * (b - a);
	}
	float frand(float min, float max)
	{
		return static_cast<float>(rand()) / RAND_MAX * (max - min) + min;
	}
}