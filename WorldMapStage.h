#pragma once
/*
* +-------------------------------------+
* File   : [WorldMapStage.h]
* Author : 小原 崚介
* Date   : 2026/11/20
*
*
* ワールドマップ上のステージの情報
* +-------------------------------------+
*/

#include <DirectXMath.h>
#include "GameObject.h"
#include "StageData.h"

class WorldMapStage : public GameObject
{
private:

	STAGE_ID m_id{ STAGE_ID::TUTORIAL };
public:
	WorldMapStage(STAGE_ID id);
	
	const STAGE_ID GetStageId() const { return m_id; }

	bool CheckBoxCollider(DirectX::XMFLOAT2 targetPos, DirectX::XMFLOAT2 targetSize);

	void Initialize();

	//削除はワールドマップの削除でいい？？

	void Update();

	void Draw();
};