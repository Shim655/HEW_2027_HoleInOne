/*
* +-------------------------------------+
* File   : [Block.h]
* Author : ’¾„Œ«
* Date   : 2026/11/15
*
*
* ƒuƒƒbƒN
* +-------------------------------------+
*/
#pragma once

#include "Gimmick.h"

class Block : public Gimmick
{
public:
	Block();
	Block(b2WorldId worldId, DirectX::XMFLOAT2 position, float rotation);

	void Initialize() override;
	void Finalize() override;
	void Update(b2WorldId worldId) override;
	void Draw() const override;

private:

};