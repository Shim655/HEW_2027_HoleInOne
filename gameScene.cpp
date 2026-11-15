/*
* +-------------------------------------+
* File   : ƒQ[ƒ€ƒV[ƒ“[gameScene.h]
* Author : ’¾„Œ«
* Date   : 2026/11/15
*
*
*
* +-------------------------------------+
*/
#include "camera.h"
#include "stage_000.h"

void InitializeGameScene(void)
{
	InitializeCamera();
	InitializeStage_000();
}

void FinalizeGameScene(void)
{
	FinalizeStage_000();
}

void UpdateGameScene(void)
{
	UpdateCamera();
	UpdateStage_000();
}

void DrawGameScene(void)
{
	DrawStage_000();
}
