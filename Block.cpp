/*
* +-------------------------------------+
* File   : [Block.cpp]
* Author : 沈揆賢
* Date   : 2026/11/15
*
*
* ブロック
* +-------------------------------------+
*/
#include "Block.h"
#include "main.h"
#include "sprite.h"
#include "texture.h"
using namespace DirectX;

static constexpr XMFLOAT2 BLOCK_SIZE = { 100.0f,200.0f };


Block::Block()
	: Gimmick(GIMMICK_TYPE::BLOCK)
{
	GameObject::SetSize(BLOCK_SIZE);
}

Block::Block(b2WorldId worldId, DirectX::XMFLOAT2 position, float rotation)
	: Gimmick(GIMMICK_TYPE::BLOCK)
{
	GameObject::SetPosition(position);
	GameObject::SetRotation(rotation);
	GameObject::SetRigidBody(worldId, b2_kinematicBody);//動かないオブジェクトに設定


	//物理属性の設定
	b2ShapeDef shape = b2DefaultShapeDef();
	shape.density = 1.0f;//重さ
	shape.material.friction = 0.5f;//摩擦
	shape.material.restitution = 0.0f;//弾力
	shape.enableContactEvents = true;//衝突判定をオンにする
	shape.userData = this;//衝突判定用のデータ

	//四角形に設定
	b2Polygon boxPolygon = b2MakeBox(BLOCK_SIZE.x * 0.5f, BLOCK_SIZE.y * 0.5f);
	GameObject::SetSize(BLOCK_SIZE);

	const RigidBody* rigidBody = GameObject::GetRigidBody();
	b2CreatePolygonShape(rigidBody->GetBodyID(), &shape, &boxPolygon);
}

void Block::Initialize()
{
	GameObject::SetTextureId(L"Asset\\Fade.png");
}

void Block::Finalize()
{
}

void Block::Update(b2WorldId worldId)
{
}

void Block::Draw() const
{
	const RigidBody* rigidBody = GameObject::GetRigidBody();

	DrawSpriteScroll(
		rigidBody->GetPosition(),
		GameObject::GetSize(),
		rigidBody->GetRotation(),
		GameObject::GetTextureID());
}
