/*
* +-------------------------------------+
* File   : ステージセレクトシーン[stageSelectScene.cpp]
* Author : 小原崚介
* Date   : 2026/11/20
*
*ステージセレクトシーン
*
* +-------------------------------------+
*/
#include "camera.h"
#include "worldMap.h"

void InitializeStageSelectScene(void)
{
	InitializeCamera();
	
	InitializeWorldMap();
}

void FinalizeStageSelectScene(void)
{
	FinalizeWorldMap();

}

void UpdateStageSelectScene(void)
{
	UpdateCamera();
	
	UpdateWorldMap();

}

void DrawStageSelectScene(void)
{
	DrawWorldMap();
}
