#pragma once
#include "GameObject.h"


class CHollowPlatformBBox : public CGameObject
{
protected:
	int length, height;				// Unit: cell 
	float cellWidth;
	float cellHeight;
public:
	CHollowPlatformBBox(float x, float y,
		float cell_width, float cell_height, int length, int height) :CGameObject(x, y)
	{
		this->length = length;
		this->height = height;
		this->cellWidth = cell_width;
		this->cellHeight = cell_height;
	}
	void Render() {}
	void Update(DWORD dt) {}
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void BlockDirection(int& l, int& t, int& r, int& b) { l = 0; t = 1; r = 0; b = 0; }
};
