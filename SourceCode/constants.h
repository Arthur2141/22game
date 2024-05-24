#pragma once

namespace constants {
	// 当たり判定のオフセット
	// 見た目より大きくしたければ正の値
	// 見た目より小さくしたければ負の値
	const float PLAYER_COLLISION_OFFSET = -2;
	const float BULLET_COLLISION_OFFSET = -2;
	const float AREA_COLLISION_OFFSET = 0;
	const float BOSS_COLLISION_OFFSET = 0;
}