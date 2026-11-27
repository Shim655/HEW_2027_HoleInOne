/*
* +-------------------------------------+
* File   : ゲームシーン[gameScene.h]
* Author : 沈揆賢
* Date   : 2026/11/15
*
*
*
* +-------------------------------------+
*/
#include "camera.h"
#include "worldMap.h"
#include "stage.h"
void InitializeGameScene(void)
{
	InitializeCamera();

	//選択したステージのIDを取得
	
	const STAGE_ID stageId = GetSelectStageId();

	//選択したステージIDに応じたステージを初期化
	InitializeStage(stageId);
}

void FinalizeGameScene(void)
{
	FinalizeStage();
}

void UpdateGameScene(void)
{
	//UpdateCamera();
	UpdateStage();
}

void DrawGameScene(void)
{
	DrawStage();
}
