/*
* +-------------------------------------+
* File   : [GameObject.cpp]
* Author : 沈揆賢
* Date   : 2026/11/15
*
*
* 位置、サイズ、回転を持たせる
* +-------------------------------------+
*/
#include "GameObject.h"
#include "texture.h"
#include "RigidBody.h"

void GameObject::SetTextureId(const wchar_t* fileName)
{
	m_textureId = LoadTexture(fileName);
}

void GameObject::ReleaseTextureId(void)
{
	ReleaseTexture(m_textureId);
}

void GameObject::SetRigidBody(b2WorldId worldId, b2BodyType bodyType)
{
	m_rigidBody = std::make_unique<RigidBody>();

	b2BodyDef rigidBody = b2DefaultBodyDef();
	rigidBody.type = bodyType;
	rigidBody.position = { m_position.x,m_position.y };
	rigidBody.rotation = b2MakeRot(m_rotation);
	m_rigidBody->SetBodyID(b2CreateBody(worldId, &rigidBody));
}
