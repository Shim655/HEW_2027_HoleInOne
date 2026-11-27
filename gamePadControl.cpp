/*
* +-------------------------------------+
* File   : [gamePadControl.cpp]
* Author : 小原崚介
* Date   : 2026/11/27
*
*
* ゲームパッドの状態管理と受け渡しを行う
*
* +-------------------------------------+
*/
#include "gamePadControl.h"
#include "GamePad.h"

using namespace DirectX;

static std::unique_ptr<GamePad> g_gamePad;

static GamePad::ButtonStateTracker g_tracker;

void InitializeGamePad()
{
	g_gamePad = std::make_unique<GamePad>();
}
void FinalizeGamePad(void)
{

}
void UpdateGamePad(void)
{

	g_tracker.Update(g_gamePad->GetState(0));

	if (g_tracker.b == GamePad::ButtonStateTracker::ButtonState::HELD)
	{
		DrawGamePad();
	}




}
void DrawGamePad(void)
{

}

bool GetGamePadConnected()
{
	return g_gamePad->GetState(0).connected;
}
GamePad::ButtonStateTracker GetTracker()
{
	return g_tracker;
}
GamePad::State GetGamePadState()
{
	return g_gamePad->GetState(0);
}

//左スティックの倒し具合を二次元XMFLOATで返します [ 範囲 -1.0f ~ 1.0f 倒していない場合は0.0f]
XMFLOAT2 GetLeftStickPos()
{
	GamePad::State state = g_gamePad->GetState(0);

	if (!state.connected) return { 0.0f,0.0f };

	return { state.thumbSticks.leftX,state.thumbSticks.leftY };

}

//右スティックの倒し具合を二次元XMFLOATで返します [ 範囲 -1.0f ~ 1.0f 倒していない場合は0.0f]
XMFLOAT2 GetRightStickPos()
{
	GamePad::State state = g_gamePad->GetState(0);

	if (!state.connected) return { 0.0f,0.0f };

	return { state.thumbSticks.rightX,state.thumbSticks.rightY };

}


bool GetStateGamePad(BUTTONSTATE state)
{
	if (!g_gamePad->GetState(0).connected) return false;
	
	switch (state)
	{
	case BUTTONSTATE::A_TRIGGER:

		if (g_tracker.b == GamePad::ButtonStateTracker::ButtonState::PRESSED)
			return true;
		break;
	case BUTTONSTATE::B_TRIGGER:
		if (g_tracker.a == GamePad::ButtonStateTracker::ButtonState::PRESSED)
			return true;
		break;
	case BUTTONSTATE::Y_TRIGGER:
		if (g_tracker.x == GamePad::ButtonStateTracker::ButtonState::PRESSED)
			return true;
		break;
	case BUTTONSTATE::X_TRIGGER:
		if (g_tracker.y == GamePad::ButtonStateTracker::ButtonState::PRESSED)
			return true;
		break;
	case BUTTONSTATE::DPAD_LEFT_TRIGGER:
		if (g_tracker.dpadLeft == GamePad::ButtonStateTracker::ButtonState::PRESSED)
			return true;
		break;
	case BUTTONSTATE::DPAD_RIGHT_TRIGGER:
		if (g_tracker.dpadRight == GamePad::ButtonStateTracker::ButtonState::PRESSED)
			return true;
		break;
	case BUTTONSTATE::DPAD_DOWN_TRIGGER:
		if (g_tracker.dpadDown == GamePad::ButtonStateTracker::ButtonState::PRESSED)
			return true;
		break;
	case BUTTONSTATE::DPAD_UP_TRIGGER:
		if (g_tracker.dpadUp == GamePad::ButtonStateTracker::ButtonState::PRESSED)
			return true;
		break;
	case BUTTONSTATE::R1_TRIGGER:
		if (g_tracker.rightTrigger == GamePad::ButtonStateTracker::ButtonState::PRESSED)
			return true;
		break;
	case BUTTONSTATE::R2_TRIGGER:
		if (g_tracker.rightShoulder == GamePad::ButtonStateTracker::ButtonState::PRESSED)
			return true;
		break;
	case BUTTONSTATE::L1_TRIGGER:
		if (g_tracker.leftTrigger == GamePad::ButtonStateTracker::ButtonState::PRESSED)
			return true;
		break;
	case BUTTONSTATE::L2_TRIGGER:
		if (g_tracker.leftShoulder == GamePad::ButtonStateTracker::ButtonState::PRESSED)
			return true;
		break;
	case BUTTONSTATE::START_TRIGGER:
		if (g_tracker.start == GamePad::ButtonStateTracker::ButtonState::PRESSED)
			return true;
		break;
	case BUTTONSTATE::MENU_TRIGGER:
		if (g_tracker.menu == GamePad::ButtonStateTracker::ButtonState::PRESSED)
			return true;
		break;
	case BUTTONSTATE::LEFTSTICK_TIGGER:
		if (g_tracker.leftStickDown == GamePad::ButtonStateTracker::ButtonState::PRESSED)
			return true;
		break;
	case BUTTONSTATE::RIGHTSTICK_TRIGGER:
		if (g_tracker.rightStickDown == GamePad::ButtonStateTracker::ButtonState::PRESSED)
			return true;
		break;
	case BUTTONSTATE::A_PRESS:
		break;
	case BUTTONSTATE::B_PRESS:
		break;
	case BUTTONSTATE::Y_PRESS:
		break;
	case BUTTONSTATE::X_PRESS:
		break;
	case BUTTONSTATE::DPAD_LEFT_PRESS:
		break;
	case BUTTONSTATE::DPAD_RIGHT_PRESS:
		break;
	case BUTTONSTATE::DPAD_DOWN_PRESS:
		break;
	case BUTTONSTATE::DPAD_UP_PRESS:
		break;
	case BUTTONSTATE::R1_PRESS:
		break;
	case BUTTONSTATE::R2_PRESS:
		break;
	case BUTTONSTATE::L1_PRESS:
		break;
	case BUTTONSTATE::L2_PRESS:
		break;
	case BUTTONSTATE::START_PRESS:
		break;
	case BUTTONSTATE::MENU_PRESS:
		break;
	case BUTTONSTATE::LEFTSTICK_PRESS:
		break;
	case BUTTONSTATE::RIGHTSTICK_PRESS:
		break;
	case BUTTONSTATE::A_RELESE:
		break;
	case BUTTONSTATE::B_RELESE:
		break;
	case BUTTONSTATE::Y_RELESE:
		break;
	case BUTTONSTATE::X_RELESE:
		break;
	case BUTTONSTATE::DPAD_LEFT_RELESE:
		break;
	case BUTTONSTATE::DPAD_RIGHT_RELESE:
		break;
	case BUTTONSTATE::DPAD_DOWN_RELESE:
		break;
	case BUTTONSTATE::DPAD_UP_RELESE:
		break;
	case BUTTONSTATE::R1_RELESE:
		break;
	case BUTTONSTATE::R2_RELESE:
		break;
	case BUTTONSTATE::L1_RELESE:
		break;
	case BUTTONSTATE::L2_RELESE:
		break;
	case BUTTONSTATE::START_RELESE:
		break;
	case BUTTONSTATE::MENU_RELESE:
		break;
	case BUTTONSTATE::LEFTSTICK_RELESE:

		break;
	case BUTTONSTATE::RIGHTSTICK_RELESE:
		break;
	default:
		break;
	}
	return false;
}