#include "Koopa.h"

CKoopa::CKoopa(float x, float y, int state) :CGameObject(x, y)
{
	this->ax = 0;
	this->ay = KOOPAS_GRAVITY;
	vx = 0;
	left = 0;
	right = 2000;
	die_start = -1;
	SetState(state);
}

void CKoopa::GetBoundingBox(float& left, float& top, float& right, float& bottom)
{
	if (state == KOOPAS_STATE_WALKING)
	{
		left = x - KOOPAS_BBOX_WIDTH / 2;
		top = y - KOOPAS_BBOX_HEIGHT / 2;
		right = left + KOOPAS_BBOX_WIDTH;
		bottom = top + KOOPAS_BBOX_HEIGHT;
	}
	else
	{
		left = x - KOOPAS_BBOX_WIDTH / 2;
		top = y - KOOPAS_BBOX_SHELL_HEIGHT / 2;
		right = left + KOOPAS_BBOX_WIDTH;
		bottom = top + KOOPAS_BBOX_SHELL_HEIGHT;
	}

}
	

int CKoopa::IsBlocking()
{
	return 0;
}


void CKoopa::OnNoCollision(DWORD dt)
{
	x += vx * dt;
	y += vy * dt;
}

void CKoopa::OnCollisionWith(LPCOLLISIONEVENT e)
{
	
	if (state == KOOPAS_STATE_SHELL_MOVE)
	{
		if (dynamic_cast<CGoomba*>(e->obj))
		{
			CGoomba* goomba = dynamic_cast<CGoomba*>(e->obj);
			goomba->SetState(GOOMBA_STATE_DIE);
		}
	}
	if (state == KOOPAS_STATE_WALKING)
	{
		if (dynamic_cast<CHollowPlatformBBox*>(e->obj))
		{
			CHollowPlatformBBox* platform = dynamic_cast<CHollowPlatformBBox*>(e->obj);
			platform->GetBoundingBox(left, top, right, bot);		
		}
	}

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

void CKoopa::Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects)
{
	if (!isDeleted)
	{
		vy += ay * dt;
		vx += ax * dt;
		if (state == KOOPAS_STATE_WALKING)
		{
			if (x<=left+1 || x>=right-1)
			{
				vx = -vx;
			}
		}
		
		CGameObject::Update(dt, coObjects);
		CCollision::GetInstance()->Process(this, dt, coObjects);

	}
}

void CKoopa::Render()
{
	int aniId = ID_ANI_KOOPAS_WALKING_LEFT;
	
	if (state == KOOPAS_STATE_WALKING)
	{
		if (vx < 0)  aniId = ID_ANI_KOOPAS_WALKING_LEFT;
		if (vx > 0)  aniId = ID_ANI_KOOPAS_WALKING_RIGHT;
	}
	
	if (state == KOOPAS_STATE_SHELL_STAND)
	{
		aniId = ID_ANI_KOOPAS_SHELL_STAND;
	}

	if (state == KOOPAS_STATE_SHELL_MOVE)
	{
		aniId = ID_ANI_KOOPAS_SHELL_MOVE;
	}
	
	CAnimations::GetInstance()->Get(aniId)->Render(x, y);
	RenderBoundingBox();
}

void CKoopa::SetState(int state)
{
	CGameObject::SetState(state);
	switch (state)
	{
		case KOOPAS_STATE_WALKING:
			if (vx == 0)
			{
				vx = -KOOPAS_WALKING_SPEED;
			}
			break;
		case KOOPAS_STATE_SHELL_STAND:
			vx = 0;
			break;
		case KOOPAS_STATE_SHELL_MOVE:
			break;
	}
}

void CKoopa::SetShellStateMoveSpeedLeft()
{
	vx = -0.2f;
}

void CKoopa::SetShellStateMoveSpeedRight()
{
	vx = 0.2f;
}

void CKoopa::SetYWhenColide()
{
	vy = -0.1f;
}
