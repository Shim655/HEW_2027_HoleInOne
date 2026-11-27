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
#include "color.h"
#include "WorldMapPlayer.h"
#include "gamePadControl.h"

using namespace DirectX;

//ステージシンボルをまとめて管理
WorldMapStage* g_pWorldMapStage[(int)STAGE_ID::STAGE_MAX] = { nullptr };

//最後に選択したステージのID
STAGE_ID g_selectStageId = STAGE_ID::TUTORIAL;

//プレイヤー
static WorldMapPlayer g_player({ 100.0f,300.0f }, { 150.0f,150.0f }, 0.0f);

//背景
static GameObject g_background({ (float)SCREEN_WIDTH * 0.5f,(float)SCREEN_HEIGHT * 0.5f }, { (float)SCREEN_WIDTH,(float)SCREEN_HEIGHT }, 0.0f);

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
	g_player.Initialize();
	g_background.SetTextureId(L"Asset\\WorldMapBackground.png");
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

	g_player.Finalize();
	g_background.ReleaseTextureId();
}

void UpdateWorldMap(void)
{
	//全てのシンボルステージの当たり判定を取る
	for (int i = 0; i < (int)STAGE_ID::STAGE_MAX; i++)
	{
		if (g_pWorldMapStage[i] == nullptr) continue;

		g_pWorldMapStage[i]->Update();

		//当たり判定
		if (g_pWorldMapStage[i]->CheckBoxCollider(g_player.GetPosition(), g_player.GetSize()))
		{
			//当たってたらグローバル変数に記録する
			g_selectStageId = g_pWorldMapStage[i]->GetStageId();



			//ENTER KEY or マウス右クリックでシーン切り替え
			if (Keyboard_IsKeyTrigger(KK_ENTER) ||
				GetMouseState(MOUSE::BUTTON_LEFT_UP) || GetStateGamePad(BUTTONSTATE::A_TRIGGER))
			{
				SetScene(SCENE::GAME);
				return;
			}
		}
	}


	g_player.Update();

}

void DrawWorldMap(void)
{
	DrawSprite(g_background.GetPosition(), g_background.GetSize(), 0.0f, g_background.GetTextureID());

	for (int i = 0; i < (int)STAGE_ID::STAGE_MAX; i++)
	{
		if (g_pWorldMapStage[i] == nullptr) continue;

		g_pWorldMapStage[i]->Draw();

	}

	g_player.Draw();

	//仮表示
#if _DEBUG

	const XMFLOAT2 playerPosition = g_player.GetPosition();
	const std::wstring text0 = std::wstring{ L"最後に選択したステージID:" } + std::to_wstring((int)g_selectStageId);

	DrawSpriteText(text0, { playerPosition.x - 100.0f,playerPosition.y - 50.0f }, 0.5f, GetColorCode(COLOR::BLACK));

	DrawSpriteText(L"プレイヤーがステージに当たっている & Enter or 左クリックでシーン切り替え", { 20.0f,20.0f }, 0.5f, GetColorCode(COLOR::BLACK));

#endif 

}

const STAGE_ID GetSelectStageId()
{
	return g_selectStageId;
}