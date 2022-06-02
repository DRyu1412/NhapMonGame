#include "Brick.h"

void CBrick::Render()
{
	if (state == BRICK_STATE_BREAK)	aniId = 12000;
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(aniId)->Render(x, y);
	//RenderBoundingBox();

}

void CBrick::GetBoundingBox(float &l, float &t, float &r, float &b)
{
	l = x - BRICK_BBOX_WIDTH/2;
	t = y - BRICK_BBOX_HEIGHT/2;
	r = l + BRICK_BBOX_WIDTH;
	b = t + BRICK_BBOX_HEIGHT;
}

void CBrick::SetState(int state)
{
	CGameObject::SetState(state);
}

void CBrick::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (state == BRICK_STATE_BREAK && numOfItem > 0)
	{
		CGameObject* object = NULL;
		{ object = new CMushroom(x, y, BRICK_BBOX_WIDTH, BRICK_BBOX_HEIGHT, MUSHROOM_TYPE_RED, ID_ANI_RED_MUSHROOM); }
		((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->AddObject(object);
		numOfItem = 0;
		CCollision::GetInstance()->Process(object, dt, coObjects);
	}
	CCollision::GetInstance()->Process(this, dt, coObjects);
}