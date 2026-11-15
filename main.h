/*
* +-------------------------------------+
* File   : main[main.h]
* Author : 沈揆賢
* Date   : 2026/11/12
*
*
* HEW_2027_HoleInOne
* 皆で頑張って作って行こう！
*
* +-------------------------------------+
*/
#pragma once

#pragma warning(push)
#pragma warning(disable:4005)
#pragma warning(pop)

#define _CRT_SECURE_NO_WARNINGS	//scanfのwarning防止
#define DIRECTINPUT_VERSION 0x0800	//警告対処

#include <DirectXMath.h>
#include <d3d11.h>
#include <d3dcompiler.h>

#include "dinput.h"
#include "mmsystem.h"	//時間やサウンド



#define SCREEN_WIDTH	(1280)
#define SCREEN_HEIGHT	(720)

enum class SCENE
{
	NONE,
	TITLE,
	GAME,
	RESULT
};

DirectX::XMFLOAT2 GetWindowSize(void);
void SetScene(SCENE nextScene);
void Transition(SCENE nextScene);