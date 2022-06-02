#pragma once

#include "GameObject.h"

class CVerticalPlatform : public CGameObject
{
protected:
	int height;				//Unit: cell
	float cellWidth;
	float cellHeight;
	int spriteIdTop, spriteIdMiddle, spriteIdBottom;

public:
	CVerticalPlatform(float x, float y,
		float cell_width, float cell_height, int height,
		int sprite_id_top, int sprite_id_middle, int sprite_id_bottom) :CGameObject(x, y)
	{
		this->height = height;
		this->cellWidth = cell_width;
		this->cellHeight = cell_height;
		this->spriteIdTop = sprite_id_top;
		this->spriteIdMiddle = sprite_id_middle;
		this->spriteIdBottom = sprite_id_bottom;
	}
	void Render();
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void RenderBoundingBox();
};