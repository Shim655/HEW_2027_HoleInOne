/*
* +-------------------------------------+
* File   : [WorldMapPlayer.cpp]
* Author : 沈揆賢
* Date   : 2026/11/22
*
*
* ワールドマップ上で動くプレイヤー
* +-------------------------------------+
*/
#include "WorldMapPlayer.h"
#include "Animation.h"
#include "keyboard.h"
#include "sprite.h"
using namespace DirectX;

WorldMapPlayer::WorldMapPlayer(DirectX::XMFLOAT2 position, DirectX::XMFLOAT2 size, float rotation)
{
	GameObject::SetPosition(position);
	GameObject::SetSize(size);
	GameObject::SetRotation(rotation);
}

void WorldMapPlayer::Initialize(void)
{
	m_animations[(int)STATE::IDLE] = new Animation;
	m_animations[(int)STATE::IDLE]->Initialize(L"asset\\WorldMapPlayer_Walk.png", 10, 1);
	m_animations[(int)STATE::IDLE]->SetAnimeSpeed(5);

	m_animations[(int)STATE::WALK] = new Animation;
	m_animations[(int)STATE::WALK]->Initialize(L"asset\\WorldMapPlayer_Walk.png", 10, 1);
	m_animations[(int)STATE::WALK]->SetAnimeSpeed(5);

	m_state = STATE::IDLE;
	m_velocity = { 0.0f,0.0f };
	m_flip = false;
}

void WorldMapPlayer::Finalize(void)
{
	for (Animation*& animation : m_animations)
	{
		if (animation)
		{
			animation->Finalize();
			delete animation;
			animation = nullptr;
		}
	}
}

void WorldMapPlayer::Update(void)
{
	m_state = STATE::IDLE;

	if (Keyboard_IsKeyDown(KK_A))
	{
		m_velocity.x -= MOVE_SPEED;
		m_state = STATE::WALK;
		m_flip = true;
	}
	if (Keyboard_IsKeyDown(KK_D))
	{
		m_velocity.x += MOVE_SPEED;
		m_state = STATE::WALK;
		m_flip = false;
	}
	if (Keyboard_IsKeyDown(KK_W))
	{
		m_velocity.y -= MOVE_SPEED;
		m_state = STATE::WALK;
	}
	if (Keyboard_IsKeyDown(KK_S))
	{
		m_velocity.y += MOVE_SPEED;
		m_state = STATE::WALK;
	}

	m_animations[(int)m_state]->Update();

	const XMFLOAT2 position = GameObject::GetPosition();
	GameObject::SetPosition({ position.x + m_velocity.x,position.y + m_velocity.y });
	m_velocity = { 0.0f,0.0f };
}

void WorldMapPlayer::Draw() const
{
	DrawSpriteAnimeScroll(
		GameObject::GetPosition(),
		GameObject::GetSize(),
		GameObject::GetRotation(),
		*m_animations[(int)m_state],
		m_flip);
}
