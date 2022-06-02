#include "Mushroom.h"
#include "Goomba.h"
#include "Mario.h"
#include "Brick.h"
#include "PlayScene.h"
#include "Game.h"

void CMushroom::GetBoundingBox(float& l, float& t, float& r, float& b)
{
	l = x - width/2;
	t = y - height/2;
	r = l + width;
	b = t + height;
}

int CMushroom::IsBlocking()
{
	if (state == MUSHROOM_STATE_IDLE) return 1;
	else return 0;
}

void CMushroom::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CMushroom::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;
	if (dynamic_cast<CGoomba*>(e->obj)) return;
	if (dynamic_cast<CMushroom*>(e->obj)) return;

	if (e->ny != 0)
		vy = 0;
	else if (e->nx != 0)
		vx = -vx;
	//if (dynamic_cast<CBrick*>(e->obj))
	//	OnCollisionWithBrick(e);
}

/*void CMushroom::OnCollisionWithBrick(LPCOLLISIONEVENT e)
{
	CBrick* brick = dynamic_cast<CBrick*>(e->obj);
	float x_brick, y_brick;
	brick->GetPosition(x_brick, y_brick);
	if (e->ny < 0)
	{
		if (brick->GetState() == BRICK_STATE_BOUNCE &&
			brick->GetState() == BRICK_STATE_BREAK &&
			brick->GetState() == BRICK_STATE_BBRICK)
		{
			SetState(MUSHROOM_STATE_BOUNCING);
			if (x < x_brick - 8) vx = -MUSHROOM_SPEED;
			else vx = MUSHROOM_SPEED;
		}
	}
}*/

void CMushroom::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!isDeleted)
	{
		vy += ay * dt;
		vx += ax * dt;

		if (y <= initialPositionY - 16 && state == MUSHROOM_STATE_DROP)
		{
			y = initialPositionY - 16;
			ay = MUSHROOM_GRAVITY;
			CMario* mario = (CMario*)((LPPLAYSCENE)CGame::GetInstance()->GetCurrentScene())->GetPlayer();
			float x_mario, y_mario;
			mario->GetPosition(x_mario, y_mario);
			if (x < x_mario) vx = -MUSHROOM_SPEED;
			else vx = MUSHROOM_SPEED;
		}
		//seperate idle and moving mushroom
		//unimplemented
	  /*if (state == MUSHROOM_STATE_BOUNCING && vx != 0)
		{

		}*/

		CCollision::GetInstance()->Process(this, dt, coObjects);
	}
}

void CMushroom::Render()
{
	if (!isDeleted)
	{
		CAnimations::GetInstance()->Get(ID_ANI_MUSHROOM)->Render(x, y);
	}
}

void CMushroom::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
	case MUSHROOM_STATE_IDLE:
		vy = 0;
		vx = 0;
		ax = 0;
		ay = 0;
		break;
	case MUSHROOM_STATE_DROP:
		vx = 0;
		ax = 0;
		vy = -MUSHROOM_SPEED;
		break;
	case MUSHROOM_STATE_BOUNCING:
		vy = -MUSHROOM_BOUNCING_SPEED;
	}
}