#pragma once

#include "GameObject.h"


class CHollowPlatform : public CGameObject
{
protected:
	int length, height;				// Unit: cell 
	float cellWidth;
	float cellHeight;
	int spriteIdTopLeft, spriteIdTopBody, spriteIdTopRight, 
		spriteIdBotLeft, spriteIdBotBody, spriteIdBotRight, 
		spriteIdMidLeft, spriteIdMidBody, spriteIdMidRight;

public:
	CHollowPlatform(float x, float y,
		float cell_width, float cell_height, int length, int height,
		int sprite_id_tLeft, int sprite_id_tBody, int sprite_id_tRight, 
		int sprite_id_bLeft, int sprite_id_bBody, int sprite_id_bRight,
		int sprite_id_mLeft, int sprite_id_mBody, int sprite_id_mRight) :CGameObject(x, y)
	{
		this->length = length;
		this->height = height;
		this->cellWidth = cell_width;
		this->cellHeight = cell_height;
		this->spriteIdTopLeft = sprite_id_tLeft;
		this->spriteIdTopBody = sprite_id_tBody;
		this->spriteIdTopRight = sprite_id_tRight;
		this->spriteIdBotLeft = sprite_id_bLeft;
		this->spriteIdBotBody = sprite_id_bBody;
		this->spriteIdBotRight = sprite_id_bRight;
		this->spriteIdMidLeft = sprite_id_mLeft;
		this->spriteIdMidBody = sprite_id_mBody;
		this->spriteIdMidRight = sprite_id_mRight;
	}

	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void RenderBoundingBox();
};
