#pragma once

/*
* +-------------------------------------+
* File   : [gamePadControl.h]
* Author : 小原崚介
* Date   : 2026/11/27
*
*
* ゲームパッドの状態管理と受け渡しを行う
*
* +-------------------------------------+
*/

#include "GamePad.h"
#include "main.h"

using namespace DirectX;

void InitializeGamePad();
void FinalizeGamePad(void);
void UpdateGamePad(void);
void DrawGamePad(void);


enum class BUTTONSTATE
{
	A_TRIGGER,
	B_TRIGGER,
	Y_TRIGGER,
	X_TRIGGER,
	DPAD_LEFT_TRIGGER,
	DPAD_RIGHT_TRIGGER,
	DPAD_DOWN_TRIGGER,
	DPAD_UP_TRIGGER,
	R1_TRIGGER,
	R2_TRIGGER,
	L1_TRIGGER,
	L2_TRIGGER,
	START_TRIGGER,
	MENU_TRIGGER,
	LEFTSTICK_TIGGER,
	RIGHTSTICK_TRIGGER,



	A_PRESS,
	B_PRESS,
	Y_PRESS,
	X_PRESS,
	DPAD_LEFT_PRESS,
	DPAD_RIGHT_PRESS,
	DPAD_DOWN_PRESS,
	DPAD_UP_PRESS,
	R1_PRESS,
	R2_PRESS,
	L1_PRESS,
	L2_PRESS,
	START_PRESS,
	MENU_PRESS,
	LEFTSTICK_PRESS,
	RIGHTSTICK_PRESS,



	A_RELESE,
	B_RELESE,
	Y_RELESE,
	X_RELESE,
	DPAD_LEFT_RELESE,
	DPAD_RIGHT_RELESE,
	DPAD_DOWN_RELESE,
	DPAD_UP_RELESE,
	R1_RELESE,
	R2_RELESE,
	L1_RELESE,
	L2_RELESE,
	START_RELESE,
	MENU_RELESE,
	LEFTSTICK_RELESE,
	RIGHTSTICK_RELESE,
};
GamePad::State GetGamePadState();

bool GetGamePadConnected();

XMFLOAT2 GetLeftStickPos();

XMFLOAT2 GetRightStickPos();

GamePad::ButtonStateTracker GetTracker();

bool GetStateGamePad(BUTTONSTATE state);