/*
* +-------------------------------------+
* File   : タイトルシーン[titleScene.cpp]
* Author : 沈揆賢 山田行人
* Date   : 2026/11/15　11/27
*
*
*
* +-------------------------------------+
*/
#include "main.h"
#include "sprite.h"
#include "keyboard.h"
#include "GameObject.h"

static GameObject g_background({ (float)SCREEN_WIDTH * 0.5f,(float)SCREEN_HEIGHT * 0.5f }, { (float)SCREEN_WIDTH,(float)SCREEN_HEIGHT }, 0.0f);

void InitializeTitleScene(void)
{
	
	g_background.SetTextureId(L"Asset\\WorldMapBackground.png");
}

void FinalizeTitleScene(void)
{
	
}

void UpdateTitleScene(void)
{
	if (Keyboard_IsKeyTrigger(KK_ENTER))
	{
		//スーっと暗くなるやつ入れる　フェードアウトフェードイン
		SetScene(SCENE::GAME);
	}
}

void DrawTitleScene(void)
{
	DrawSprite(g_background.GetPosition(), g_background.GetSize(), 0.0f, g_background.GetTextureID());
}
