/*
* +-------------------------------------+
* File   : [Animation.cpp]
* Author : 沈揆賢
* Date   : 2026/11/20
*
*
* アニメションクラス
* +-------------------------------------+
*/
#include "Animation.h"
#include "texture.h"
using namespace DirectX;

void Animation::Initialize(const wchar_t* fileName, int numU, int numV)
{
	m_textureID = LoadTexture(fileName);
	m_numU = numU;
	m_numV = numV;
	m_textureSize = { 1.0f / (float)numU,1.0f / (float)numV };

	m_frameCount = 0;
	m_isEnd = false;
}

void Animation::Finalize()
{
	ReleaseTexture(m_textureID);
}

void Animation::Update()
{
	const int numSprites = m_numU * m_numV;
	const int textureDrawing = (m_frameCount / m_frameSpeed) % numSprites;

	m_textureCoordinate.x = m_textureSize.x * (textureDrawing % m_numU);
	m_textureCoordinate.y = m_textureSize.y * (textureDrawing / m_numU);

	if (textureDrawing + 1 == numSprites)
	{
		m_isEnd = true;
	}

	m_frameCount++;
}

bool Animation::IsAnimeEnd()
{
	const int textureDrawing = (m_frameCount / m_frameSpeed) % (m_numU * m_numV);

	if (textureDrawing == 0 && m_isEnd)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void Animation::SetAnimeSpeed(int speed)
{
	if (speed == 0)
	{
		return;
	}
	m_frameSpeed = speed;
}
