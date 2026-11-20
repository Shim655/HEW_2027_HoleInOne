#pragma once

/*
* +-------------------------------------+
* File   : [stage_000.h]
* Author : 小原崚介
* Date   : 2026/11/20
*
*
* ステージを作る上で必要なデータの定義
*
* +-------------------------------------+
*/

#include <DirectXMath.h>
#include "Gimmick.h"
//ワールドマップやステージマスターデータが使用する紐づけ用ID
enum class STAGE_ID
{
	TUTORIAL = 0,
	STAGE_1,
	STAGE_2,
	STAGE_3,
	STAGE_4,
	STAGE_5,
	STAGE_MAX

};

//ギミックを作るのに必要な情報
// SetGimmick()を参考にして作成
struct StageObject
{
	GIMMICK_TYPE m_type = GIMMICK_TYPE::BLOCK;
	DirectX::XMFLOAT2 m_position = { 0.0f,0.0f };
	float m_rotation = 0.0f;

};

constexpr int OBJECT_MAX = 2;
//ステージを構成する情報
//マスターデータの作成に使用
struct StageData
{
	DirectX::XMFLOAT2 m_gravity = { 0.0f,0.0f };
	StageObject m_pStageObjects[OBJECT_MAX] = { GIMMICK_TYPE::BLOCK,{0.0f,0.0f},0.0f };


};