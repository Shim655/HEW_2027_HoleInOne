/*
* +-------------------------------------+
* File   : [worldMap.cpp]
* Author : 小原崚介
* Date   : 2026/11/20
*
*
* マスターデータに基づいたステージの作成
* 当たり判定、ステージをまとめて管理
*
* +-------------------------------------+
*/
#include "worldMap.h"
#include "main.h"
#include "WorldMapStage.h"
#include "mouse.h"
#include "sprite.h"
#include "text.h"
#include "keyboard.h"

//ステージシンボルをまとめて管理
WorldMapStage* g_pWorldMapStage[(int)STAGE_ID::STAGE_MAX] = { nullptr };

//最後に選択したステージのID
STAGE_ID g_selectStageId = STAGE_ID::TUTORIAL;

//デバッグ用プレイヤー
DirectX::XMFLOAT2 g_playerPosition = {0.0f,0.0f};

DirectX::XMFLOAT2 g_playerSize = { 0.0f,0.0f };

void InitializeWorldMap()
{
	for (int i = 0; i < (int)STAGE_ID::STAGE_MAX; i++)
	{
		//マスターデータに基づいてステージシンボルを作成する
		g_pWorldMapStage[i] = new WorldMapStage((STAGE_ID)i);

		if (g_pWorldMapStage[i])
		{
			//newと分けなくてもいいかも
			g_pWorldMapStage[i]->Initialize();
		}
	}

	g_selectStageId = STAGE_ID::TUTORIAL;

	//仮のプレイヤーデータ プレイヤー作成時に消す
	g_playerPosition = { 0.0f,0.0f };

	g_playerSize = { 100.0f,100.0f };
}
void FinalizeWorldMap(void)
{
	//不要になったワールドを削除
	for (int i = 0; i < (int)STAGE_ID::STAGE_MAX; i++)
	{
		if (g_pWorldMapStage[i])
		{
			delete g_pWorldMapStage[i];
			g_pWorldMapStage[i] = nullptr;
		}
	}
}

void UpdateWorldMap(void)
{
	//仮プレイヤー情報
	DirectX::XMINT2 mousePosition = GetMousePosition();

	//当たり判定の引数として渡すためにfloatにする
	g_playerPosition = {(float)mousePosition.x,(float)mousePosition.y};

	//全てのシンボルステージの当たり判定を取る
	for (int i = 0; i < (int)STAGE_ID::STAGE_MAX; i++)
	{
		if (g_pWorldMapStage[i] == nullptr) continue;

		g_pWorldMapStage[i]->Update();

		//当たり判定
		if (g_pWorldMapStage[i]->CheckBoxCollider(g_playerPosition, g_playerSize))
		{
			//当たってたらグローバル変数に記録する
			g_selectStageId = g_pWorldMapStage[i]->GetStageId();

			//ENTER KEY or マウス右クリックでシーン切り替え
			if (Keyboard_IsKeyTrigger(KK_ENTER) ||
				GetMouseState(MOUSE::BUTTON_LEFT_UP))
			{
				SetScene(SCENE::GAME);
			}
		}
	}


	

}

void DrawWorldMap(void)
{
	for (int i = 0; i < (int)STAGE_ID::STAGE_MAX; i++)
	{
		if (g_pWorldMapStage[i] == nullptr) continue;

		g_pWorldMapStage[i]->Draw();

	}

	//仮表示
#if _DEBUG


	DrawSpriteText(L"最後に選択したステージID", {100.0f,50.0f}, 2.0f);

	DrawSpriteText(std::to_wstring((int)g_selectStageId), { 900.0f,50.0f }, 2.0f);

	DrawSpriteText(L"マウスがステージに当たっている & Enter or 左クリックでシーン切り替え", { 20.0f,550.0f }, 1.1f);

#endif 

}

const STAGE_ID GetSelectStageId()
{
	return g_selectStageId;
}