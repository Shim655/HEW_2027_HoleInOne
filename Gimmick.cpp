/*
* +-------------------------------------+
* File   : [Gimmick.cpp]
* Author : 沈揆賢
* Date   : 2026/11/15
*
*
* 全てのギミックの親クラス
* +-------------------------------------+
*/
#include "Gimmick.h"

bool Gimmick::CheckHitGimmick(b2WorldId worldId, GIMMICK_TYPE gimmickCheck)
{
	//Box2Dの衝突判定の結果を取得
	const b2ContactEvents event = b2World_GetContactEvents(worldId);

	//衝突が起きた回数だけ繰り返す
	for (int i = 0;i < event.beginCount; i++)
	{
		const b2ContactBeginTouchEvent touchEvent = event.beginEvents[i];

		const Gimmick* objectA = static_cast<Gimmick*>(b2Shape_GetUserData(touchEvent.shapeIdA));
		const Gimmick* objectB = static_cast<Gimmick*>(b2Shape_GetUserData(touchEvent.shapeIdB));
		if (objectA == nullptr || objectB == nullptr)
		{
			continue;
		}

		if (objectA->GetGimmickType() == gimmickCheck || objectB->GetGimmickType() == gimmickCheck)
		{
			return true;
		}
	}

	return false;
}
