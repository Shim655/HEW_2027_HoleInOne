/*
* +-------------------------------------+
* File   : [Gimmick.h]
* Author : 沈揆賢
* Date   : 2026/11/15
*
*
* 全てのギミックの親クラス
* +-------------------------------------+
*/
#pragma once

#include "GameObject.h"

enum class GIMMICK_TYPE
{
	BALL,
	BLOCK,
	JUMP,
};

class Gimmick : public GameObject
{
public:
	Gimmick(GIMMICK_TYPE type)
		: m_gimmickType{ type }
	{

	}
	virtual ~Gimmick() {};

	virtual void Initialize() = 0;
	virtual void Finalize() = 0;
	virtual void Update(b2WorldId worldId) = 0;
	virtual void Draw() const = 0;

	bool CheckHitGimmick(b2WorldId worldId, GIMMICK_TYPE gimmickCheck);

	GIMMICK_TYPE GetGimmickType(void) const
	{
		return m_gimmickType;
	}

private:
	GIMMICK_TYPE m_gimmickType;
};
