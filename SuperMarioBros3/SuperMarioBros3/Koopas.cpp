#include "Koopas.h"

CKoopas::CKoopas(float x, float y, int state) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = KOOPAS_GRAVITY;
	vx = 0;
	die_start = -1;
	SetState(state);
}

void CKoopas::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	left = x - KOOPAS_BBOX_WIDTH / 2;
	top = y - KOOPAS_BBOX_HEIGHT / 2;
	right = left + KOOPAS_BBOX_WIDTH;
	bottom = top + KOOPAS_BBOX_HEIGHT;
}

void CKoopas::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CKoopas::OnCollisionWith(LPCOLLISIONEVENT e)
{
	if (!e->obj->IsBlocking()) return;

	if (e->ny != 0)
	{
		vy = 0;
	}
	else if (e->nx != 0)
	{
		vx = -vx;
	}
}

void CKoopas::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	vy += ay * dt;
	vx += ax * dt;

	CGameObject::Update(dt, coObjects);
	CCollision::GetInstance()->Process(this, dt, coObjects);
}

void CKoopas::Render()
{
	int aniId = ID_ANI_KOOPAS_WALKING_LEFT;
	
	if (state == KOOPAS_STATE_WALKING)
	{
		if (vx < 0)  aniId = ID_ANI_KOOPAS_WALKING_LEFT;
		if (vx > 0)  aniId = ID_ANI_KOOPAS_WALKING_RIGHT;
	}
	
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CKoopas::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
		case KOOPAS_STATE_WALKING:
			if (vx == 0)
			{
				vx = -KOOPAS_WALKING_SPEED;
			}

		/*case KOOPAS_STATE_SHELL:
			vx = 0;
			vy = 0;*/

	}
}
