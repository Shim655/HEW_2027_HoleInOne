/*
* +-------------------------------------+
* File   : [WorldMapPlayer.h]
* Author : 沈揆賢
* Date   : 2026/11/22
*
*
* ワールドマップ上で動くプレイヤー
* +-------------------------------------+
*/
#pragma once

#include <DirectXMath.h>
#include "GameObject.h"

class Animation;

class WorldMapPlayer : public GameObject
{
public:
	WorldMapPlayer(DirectX::XMFLOAT2 position, DirectX::XMFLOAT2 size, float rotation);

	void Initialize(void);
	void Finalize(void);
	void Update(void);
	void Draw() const;

private:
	static constexpr float MOVE_SPEED = 3.0f;

	enum class STATE
	{
		IDLE,
		WALK,
		SIZE_STATE
	};

	STATE m_state{ STATE::IDLE };
	DirectX::XMFLOAT2 m_velocity{ 0.0f,0.0f };
	Animation* m_animations[(int)STATE::SIZE_STATE]{nullptr};
	bool m_flip{ false };
};