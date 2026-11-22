/*
* +-------------------------------------+
* File   : [Animation.h]
* Author : 沈揆賢
* Date   : 2026/11/20
*
*
* アニメションクラス
* +-------------------------------------+
*/
#pragma once

#include <DirectXMath.h>

class Animation
{
public:
	Animation() = default;

	void Initialize(const wchar_t* fileName, int numU, int numV);
	void Finalize();
	void Update();
	bool IsAnimeEnd();

	void SetAnimeSpeed(int speed);

	unsigned int GetTextureID() const
	{
		return m_textureID;
	}
	DirectX::XMFLOAT2 GetTextureCoordinate() const
	{
		return m_textureCoordinate;
	}
	DirectX::XMFLOAT2 GetTextureSize() const
	{
		return m_textureSize;
	}

private:
	unsigned int m_frameCount{ 0 };
	unsigned int m_frameSpeed{ 1 };
	int m_textureID{ -1 };
	int m_numU{ 1 };
	int m_numV{ 1 };
	DirectX::XMFLOAT2 m_textureCoordinate{ 0.0f,0.0f };
	DirectX::XMFLOAT2 m_textureSize{ 0.0f,0.0f };
	bool m_isEnd = false;
};
