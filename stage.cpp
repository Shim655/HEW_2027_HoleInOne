//Box2Dライブラリーライセンス
/*
MIT License

Copyright (c) 2022 Erin Catto

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/

/*
* +-------------------------------------+
* File   : [stage.cpp]
* Author : 小原崚介
* Date   : 2026/11/20
*
*
* ステージIDを受け取り、ステージの初期化、更新、描画、後始末を行う
*
* +-------------------------------------+
*/
#include <box2d.h>
#include "main.h"
#include "sprite.h"
#include "texture.h"
#include "camera.h"
#include "keyboard.h"
#include "mouse.h"
#include "Gimmick.h"
#include "Ball.h"
#include "Block.h"
#include "stage.h"
#include "StageData.h"
#include "text.h"
using namespace DirectX;

static constexpr int MAX_GIMMICK = 100;
static constexpr float ROTATION_SPEED = 0.03f;
static constexpr XMFLOAT2 RESET_POSITION = { 200.0f,10.0f };


static enum class STAGE_STATE
{
	SETTING,
	RUN,
};


static Gimmick* g_pGimmicks[MAX_GIMMICK]{ nullptr };
static Gimmick* g_pPlayer{ nullptr };
static STAGE_STATE g_stageState{ STAGE_STATE::SETTING };

//Box2Dの物理エンジン用の変数
//Box2DはIDでオブジェクトを管理している
static b2WorldId g_worldId;


static void SetGimmick(GIMMICK_TYPE type, XMFLOAT2 position, float rotation);
static void PlayerGetGimmick(GIMMICK_TYPE type);
static void Setting(void);
static void Run(void);

//ゲームプレイのステージマスターデータ
static const StageData g_stageData[(int)STAGE_ID::STAGE_MAX] =
{
	//チュートリアル
	{
		{0.0f,100.0f},//重力
	{
		//オブジェクト情報 今のところ2個まで　ポインタにするか等は要検討
	{GIMMICK_TYPE::BLOCK,{150.0f,100.0f},-1.0f},
	{GIMMICK_TYPE::BLOCK,{500.0f,300.0f},2.0f}

	}},
	
	
	//ステージ1
	{
		{0.0f,100.0f},//重力
	{
		//オブジェクト情報 今のところ2個まで　ポインタにするか等は要検討
	{GIMMICK_TYPE::BLOCK,{150.0f,100.0f},2.0f},
	{GIMMICK_TYPE::BLOCK,{700.0f,300.0f},0.0f}
	}},
	
	
	//ステージ2
	{
			{0.0f,150.0f},//重力
	{
		//オブジェクト情報 今のところ2個まで　ポインタにするか等は要検討
	{GIMMICK_TYPE::BLOCK,{150.0f,150.0f},7.0f},
	{GIMMICK_TYPE::BLOCK,{700.0f,300.0f},3.0f}
	}},


	//ステージ3
	{
		{50.0f,150.0f},//重力
	{
		//オブジェクト情報 今のところ2個まで　ポインタにするか等は要検討
	{GIMMICK_TYPE::BLOCK,{500.0f,100.0f},6.0f},
	{GIMMICK_TYPE::BLOCK,{300.0f,300.0f},0.0f}
	}},
	
	
	//ステージ4
		{{100.0f,100.0f},//重力
	{
		//オブジェクト情報 今のところ2個まで　ポインタにするか等は要検討
	{GIMMICK_TYPE::BLOCK,{300.0f,100.0f},3.0f},
	{GIMMICK_TYPE::BLOCK,{600.0f,300.0f},0.0f}
	}},
	
	
	//ステージ5
	{
		{500.0f,300.0f},//重力
	{
		//オブジェクト情報 今のところ2個まで　ポインタにするか等は要検討
	{GIMMICK_TYPE::BLOCK,{600.0f,100.0f},3.0f},
	{GIMMICK_TYPE::BLOCK,{900.0f,550.0f},1.0f}
	}}

};

//デバッグ表示用 デバッグ表示以外では使い道が今の所ないので、
//後々削除推奨
static int g_stageId = 0;

void InitializeStage(STAGE_ID id)
{
	const int stageId = (int)id;
	
	//デバッグ表示をするために記録
	g_stageId = stageId;
	//-------------------------------------
	//ここからBox2Dを使った物理エンジンの設定
	//Worldを作成
	b2WorldDef world;
	world = b2DefaultWorldDef();
	
	//重力設定
	world.gravity = { 
	g_stageData[stageId].m_gravity.x,
	g_stageData[stageId].m_gravity.y
	};
	
	g_worldId = b2CreateWorld(&world);


	//ここまで
	//-------------------------------------

	g_stageState = STAGE_STATE::SETTING;

	SetGimmick(GIMMICK_TYPE::BALL, RESET_POSITION, 0.0f);

	for (int i = 0; i < OBJECT_MAX; i++)
	{
		SetGimmick(g_stageData[stageId].m_pStageObjects[i].m_type,
			g_stageData[stageId].m_pStageObjects[i].m_position,
			g_stageData[stageId].m_pStageObjects[i].m_rotation);
	}
	PlayerGetGimmick(GIMMICK_TYPE::BLOCK);
}

void FinalizeStage(void)
{
	if (g_pPlayer)
	{
		delete g_pPlayer;
		g_pPlayer = nullptr;
	}

	for (int i = 0;i < MAX_GIMMICK;i++)
	{
		if (g_pGimmicks[i])
		{
			delete g_pGimmicks[i];
			g_pGimmicks[i] = nullptr;
		}
	}

	//Box2dのWorldを破壊
	b2DestroyWorld(g_worldId);
}

void UpdateStage(void)
{
	switch (g_stageState)
	{
	case STAGE_STATE::SETTING:
		Setting();
		break;

	case STAGE_STATE::RUN:
		Run();
		break;

	default:
		break;
	}


#if _DEBUG
	if (Keyboard_IsKeyTrigger(KK_ESCAPE))
	{
		SetScene(SCENE::STAGE_SELECT);
	}
#endif
}

void DrawStage(void)
{
	for (const Gimmick* gimmick : g_pGimmicks)
	{
		if (gimmick == nullptr)
		{
			continue;
		}

		gimmick->Draw();
	}

	switch (g_stageState)
	{
	case STAGE_STATE::SETTING:
		if (g_pPlayer)
		{
			const XMINT2 mousePosition = GetMousePosition();
			const XMFLOAT2 drawPosition{ (float)mousePosition.x,(float)mousePosition.y };
			DrawSpriteZoom(drawPosition, g_pPlayer->GetSize(), g_pPlayer->GetRotation(), g_pPlayer->GetTextureID(), g_pPlayer->GetColor());
		}
		break;

	case STAGE_STATE::RUN:
		break;

	default:
		break;
	}


#if _DEBUG
	DrawSpriteText(L"重力",{40.0f,600.0f},1.2f);

	//重力表示
	DrawSpriteText(L"x = " + std::to_wstring(g_stageData[g_stageId].m_gravity.x) + L" y = " + std::to_wstring(g_stageData[g_stageId].m_gravity.y), {150.0f,600.0f}, 1.2f);

	DrawSpriteText(L"ESC でステージセレクトに戻るよ!", { 400.0f,40.0f },1.5f);
#endif
}

void SetGimmick(GIMMICK_TYPE type, XMFLOAT2 position, float rotation)
{
	for (int i = 0;i < MAX_GIMMICK;i++)
	{
		if (g_pGimmicks[i])
		{
			continue;
		}

		switch (type)
		{
		case GIMMICK_TYPE::BALL:
			g_pGimmicks[i] = new Ball(g_worldId, position, rotation);
			break;

		case GIMMICK_TYPE::BLOCK:
			g_pGimmicks[i] = new Block(g_worldId, position, rotation);
			break;

		case GIMMICK_TYPE::JUMP:
			break;

		default:
			break;
		}

		g_pGimmicks[i]->Initialize();
		break;
	}
}

void PlayerGetGimmick(GIMMICK_TYPE type)
{
	if (g_pPlayer)
	{
		return;
	}


	switch (type)
	{
	case GIMMICK_TYPE::BLOCK:
		g_pPlayer = new Block;
		break;

	case GIMMICK_TYPE::JUMP:
		break;

	default:
		break;
	}

	g_pPlayer->Initialize();
}

void Setting(void)
{
	//Player
	if (g_pPlayer)
	{
		XMFLOAT2 playerPosition = g_pPlayer->GetPosition();
		//マウスの座標をカメラに合わせて補正
		const XMINT2 mousePosition = GetMousePosition();
		const XMFLOAT3 cameraOffset = GetCameraOffset();
		const float centerX = SCREEN_WIDTH * 0.5f;
		const float centerY = SCREEN_HEIGHT * 0.5f;
		playerPosition.x = (float)mousePosition.x;
		playerPosition.y = (float)mousePosition.y;
		playerPosition.x = centerX + (playerPosition.x - centerX) / cameraOffset.z;
		playerPosition.y = centerY + (playerPosition.y - centerY) / cameraOffset.z;
		playerPosition.x -= cameraOffset.x;
		playerPosition.y -= cameraOffset.y;
		g_pPlayer->SetPosition(playerPosition);

		//回転
		if (Keyboard_IsKeyDown(KK_Q))
		{
			g_pPlayer->SetRotation(g_pPlayer->GetRotation() - ROTATION_SPEED);
		}
		if (Keyboard_IsKeyDown(KK_E))
		{
			g_pPlayer->SetRotation(g_pPlayer->GetRotation() + ROTATION_SPEED);
		}

		//配置
		if (GetMouseState(MOUSE::BUTTON_LEFT_UP))
		{
			SetGimmick(GIMMICK_TYPE::BLOCK, g_pPlayer->GetPosition(), g_pPlayer->GetRotation());
		}
	}

	if (Keyboard_IsKeyTrigger(KK_ENTER))
	{
		g_stageState = STAGE_STATE::RUN;
	}
}

void Run(void)
{
	if (Keyboard_IsKeyTrigger(KK_ENTER))
	{
		//ボールの位置を元に戻す

		g_stageState = STAGE_STATE::SETTING;
	}


	//-------------------------------------
	//ここから物理のシミュレーション
	//更新フレーム
	constexpr float timeStep = 1.0f / 60.0f;//60fps

	//シミュレーションする回数
	//数字が高いほどリアルになるが、処理が重くなる
	constexpr int subStepCount = 6;

	b2World_Step(g_worldId, timeStep, subStepCount);

	//ここまで
	//-------------------------------------

	for (Gimmick* gimmick : g_pGimmicks)
	{
		if (gimmick == nullptr)
		{
			continue;
		}

		gimmick->Update(g_worldId);
	}
}
