/*
* +-------------------------------------+
* File   : [Ball.h]
* Author : íæùÑå´
* Date   : 2026/11/15
*
*
* É{Å[Éã
* +-------------------------------------+
*/
#pragma once

#include "Gimmick.h"

class Ball : public Gimmick
{
public:
	Ball(b2WorldId worldId, DirectX::XMFLOAT2 position, float rotation);

	void Initialize() override;
	void Finalize() override;
	void Update(b2WorldId worldId) override;
	void Draw() const override;

private:

};