/*
* +-------------------------------------+
* File   : [Ball.h]
* Author : 沈揆賢
* Date   : 2026/11/15
*
*
* ボール
* +-------------------------------------+
*/
#include "Ball.h"
#include "main.h"
#include "sprite.h"
#include "texture.h"
#include "color.h"
using namespace DirectX;


Ball::Ball(b2WorldId worldId, DirectX::XMFLOAT2 position, float rotation)
	: Gimmick(GIMMICK_TYPE::BALL)
{
	GameObject::SetPosition(position);
	GameObject::SetRotation(rotation);
	GameObject::SetRigidBody(worldId, b2_dynamicBody);//動くオブジェクトに設定


	//物理属性の設定
	b2ShapeDef shape = b2DefaultShapeDef();
	shape.density = 1.0f;//重さ
	shape.material.friction = 0.5f;//摩擦
	shape.material.restitution = 0.1f;//弾力
	shape.enableContactEvents = true;//衝突判定をオンにする
	shape.userData = this;//衝突判定用のデータ

	//円の形に設定
	b2Circle circle;
	circle.center = { 0.0f,0.0f };//中心
	circle.radius = 25.0f;//半径
	GameObject::SetSize({ circle.radius * 2.0f,circle.radius * 2.0f });

	const RigidBody* rigidBody = GameObject::GetRigidBody();
	b2CreateCircleShape(rigidBody->GetBodyID(), &shape, &circle);
}

void Ball::Initialize()
{
	GameObject::SetTextureId(L"Asset\\Ball.png");
}

void Ball::Finalize()
{
}

void Ball::Update(b2WorldId worldId)
{
	if (CheckHitGimmick(worldId, GIMMICK_TYPE::BLOCK))
	{
		GameObject::SetColor(GetColorCode(COLOR::RED));
	}
	else
	{
		GameObject::SetColor(GetColorCode(COLOR::WHITE));
	}
}

void Ball::Draw() const
{
	const RigidBody* rigidBody = GameObject::GetRigidBody();

	DrawSpriteScroll(
		rigidBody->GetPosition(),
		GameObject::GetSize(),
		rigidBody->GetRotation(),
		GameObject::GetTextureID(),
		GameObject::GetColor());
}
