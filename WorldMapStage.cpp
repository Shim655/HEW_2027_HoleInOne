/*
* +-------------------------------------+
* File   : [WorldMapStage.cpp]
* Author : 小原 崚介
* Date   : 2026/11/20
*
*
* ワールドマップ上のステージの情報
* +-------------------------------------+
*/
#include "WorldMapStage.h"
#include "sprite.h"
#include "text.h"

//idに応じた位置、サイズ等のデータを持ったWorldStageMapを返す マスターデータにすることを検討
WorldMapStage::WorldMapStage(STAGE_ID id)
{
	DirectX::XMFLOAT2 position{0.0f,0.0f};
	DirectX::XMFLOAT2 size{0.0f,0.0f};
	
	m_id = id;

	switch (id)
	{
	case STAGE_ID::TUTORIAL:

		position = { 50.0f,400.0f };
		size = { 50.0f,50.0f };
		
		break;
	case STAGE_ID::STAGE_1:

		position = { 700.0f,100.0f };
		size = { 50.0f,50.0f };

		break;
	case STAGE_ID::STAGE_2:

		position = { 400.0f,300.0f };
		size = { 50.0f,50.0f };
		break;
	case STAGE_ID::STAGE_3:

		position = { 500.0f,600.0f };
		size = { 50.0f,50.0f };
		break;
	case STAGE_ID::STAGE_4:

		position = { 800.0f,600.0f };
		size = { 50.0f,50.0f };
		break;
	case STAGE_ID::STAGE_5:

		position = { 1000.0f,300.0f };
		size = { 100.0f,100.0f };
		break;
	case STAGE_ID::STAGE_MAX:
		break;
	default:
		break;
	}


	GameObject::SetPosition(position);
	GameObject::SetSize(size);
	GameObject::SetRotation(0.0f);
	GameObject::SetColor({ 1.0f,1.0f,1.0f,1.0f });


}

void WorldMapStage::Initialize()
{
	//分けなくても良いかも??
	switch (m_id)
	{
	case STAGE_ID::TUTORIAL:

		GameObject::SetTextureId(L"Asset\\Block.png");

		break;
	case STAGE_ID::STAGE_1:

		GameObject::SetTextureId(L"Asset\\Block.png");

		break;
	case STAGE_ID::STAGE_2:

		GameObject::SetTextureId(L"Asset\\Block.png");

		break;
	case STAGE_ID::STAGE_3:

		GameObject::SetTextureId(L"Asset\\Block.png");

		break;
	case STAGE_ID::STAGE_4:

		GameObject::SetTextureId(L"Asset\\Block.png");

		break;
	case STAGE_ID::STAGE_5:

		GameObject::SetTextureId(L"Asset\\rocket.png");

		break;
	case STAGE_ID::STAGE_MAX:
		break;
	default:
		break;
	}

}

//ターゲットの 位置 と サイズ を引数とし、当たっているかどうかを返します
bool WorldMapStage::CheckBoxCollider(DirectX::XMFLOAT2 targetPos, DirectX::XMFLOAT2 targetSize)
{
	const DirectX::XMFLOAT2 pos = GameObject::GetPosition();
	const DirectX::XMFLOAT2 size = GameObject::GetSize();

	float stageTop = pos.y + size.y / 2;	// ステージの上端
	float stageBottom = pos.y - size.y / 2;	// ステージの下端
	float stageRight = pos.x + size.x / 2;	// ステージの右端
	float stageLeft = pos.x - size.x / 2;	// ステージの左端

	float targetTop = targetPos.y + targetSize.y / 2;   // ターゲットの上端
	float targetBottom = targetPos.y - targetSize.y / 2;// ターゲットの下端
	float targetRight = targetPos.x + targetSize.x / 2; // ターゲットの右端
	float targetLeft = targetPos.x - targetSize.x / 2;  // ターゲットの左端

	if ((stageRight >= targetLeft) &&
		(stageLeft <=  targetRight) &&
		(stageBottom <=targetTop) &&
		(stageTop >= targetBottom))
	{
		// 当たっている
		return true;
	}

	// 当たっていない
	return false;
}
void WorldMapStage::Update()
{

}

void WorldMapStage::Draw()
{

	DrawSpriteScroll(
		GameObject::GetPosition(),
		GameObject::GetSize(),
		GameObject::GetRotation(),
		GameObject::GetTextureID());

	 //デバッグ用数字出力
#if _DEBUG
	DrawSpriteText(std::to_wstring((int)m_id), GameObject::GetPosition(),2.0f);
#endif
}