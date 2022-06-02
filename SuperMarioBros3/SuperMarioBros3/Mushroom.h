#pragma once
#include "GameObject.h"
#include "Mario.h"



#define	MUSHROOM_STATE_IDLE 100
#define	MUSHROOM_STATE_DROP 101
#define	MUSHROOM_STATE_BOUNCING 102


enum MushroomTypes
{
	MUSHROOM_TYPE_RED,
	MUSHROOM_TYPE_GREEN,
};

#define MUSHROOM_GRAVITY 0.002f
#define MUSHROOM_SPEED 0.04f
#define MUSHROOM_BOUNCING_SPEED 0.4f

#define ID_ANI_RED_MUSHROOM  14500

class CMushroom : public CGameObject
{
	float ax;
	float ay;
	int width;
	int height;
	int type;
	float initialPositionY;
	int ID_ANI_MUSHROOM;

	void GetBoundingBox(float& l, float& t, float& r, float& b);
	void Update(DWORD dt, vector<LPGAMEOBJECT>* coObjects);
	void Render();

	int IsCollidable() { return 1; };
	int IsBlocking();
	void OnNoCollision(DWORD dt);
	void OnCollisionWith(LPCOLLISIONEVENT e);
	//void OnCollisionWithBrick(LPCOLLISIONEVENT e);
public:
	CMushroom(float x, float y, int width, int height, int type, int ID_ANI_MUSHROOM) : CGameObject(x, y)
	{
		vy = 0;
		vx = 0;
		ax = 0;
		ay = 0;
		this->width = width;
		this->height = height;
		this->type = type;
		this->initialPositionY = y;
		this->ID_ANI_MUSHROOM = ID_ANI_MUSHROOM;
		SetState(MUSHROOM_STATE_IDLE);
	}
	void SetState(int state);
	int GetType() { return this->type; }
};
