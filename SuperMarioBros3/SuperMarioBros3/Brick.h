#pragma once

#include "GameObject.h"
#include "Animation.h"
#include "Animations.h"
#include "Mushroom.h"

#include "PlayScene.h"

#define BRICK_WIDTH 16
#define BRICK_BBOX_WIDTH 16
#define BRICK_BBOX_HEIGHT 16

#define BRICK_STATE_NORMAL	100
#define BRICK_STATE_QUESTIONBRICK	101	
#define BRICK_STATE_BREAK	102

class CBrick : public CGameObject {
public:
	int aniId;
	int numOfItem = 1;
	CBrick(float x, float y, int aniID, int state) : CGameObject(x, y) { this->aniId = aniID; this->state = state; }
	void Render();
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void GetBoundingBox(float& l, float& t, float& r, float& b);
	virtual void SetState(int state);
};