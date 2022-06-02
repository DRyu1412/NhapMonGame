#include "HollowPlatform.h"

#include "Sprite.h"
#include "Sprites.h"

#include "Textures.h"

void CHollowPlatform::RenderBoundingBox()
{
	D3DXVECTOR3 p(x, y, 0);
	RECT rect;

	LPTEXTURE bbox = CTextures::GetInstance()->Get(ID_TEX_BBOX);

	float l, t, r, b;

	GetBoundingBox(l, t, r, b);
	rect.left = 0;
	rect.top = 0;
	rect.right = (int)r - (int)l;
	rect.bottom = (int)b - (int)t;

	float cx, cy;
	CGame::GetInstance()->GetCamPos(cx, cy);

	float xx = x - this->cellWidth / 2 + rect.right / 2;

	CGame::GetInstance()->Draw(xx - cx, y - cy, bbox, nullptr, BBOX_ALPHA, rect.right - 1, rect.bottom - 1);
}

void CHollowPlatform::Render()
{
	if ((this->length <= 1)||(this->height <= 1)) return;
	float xx = x;
	float yy = y;
	CSprites* s = CSprites::GetInstance();
	//Draw first row with top row sprites
	s->Get(this->spriteIdTopLeft)->Draw(xx, yy);
	xx += this->cellWidth;
	if (this->length > 1)
	{
		for (int i = 1; i < this->length - 1; i++)
		{
			s->Get(this->spriteIdTopBody)->Draw(xx, yy);
			xx += this->cellWidth;
		}
	}
	s->Get(this->spriteIdTopRight)->Draw(xx, yy);
	yy += this->cellHeight;
	xx = x;
	//Draw 2nd to second-to-last row if height > 2, with mid rows sprites
	if (this->height > 2)
	{
		for (int i = 1; i < this->height - 1; i++)
		{
			s->Get(this->spriteIdMidLeft)->Draw(xx, yy);
			xx += this->cellWidth;
			if (this->length > 1)
			{
				for (int j = 1; j < this->length - 1; j++)
				{
					s->Get(this->spriteIdMidBody)->Draw(xx, yy);
					xx += this->cellWidth;
				}
			}
			s->Get(this->spriteIdMidRight)->Draw(xx, yy);
			xx = x;
			yy += this->cellHeight;
		}
	}
	//Draw last row with last row sprites
	s->Get(this->spriteIdBotLeft)->Draw(xx, yy);
	xx += this->cellWidth;
	if (this->length > 1)
	{
		for (int i = 1; i < this->length - 1; i++)
		{
			s->Get(this->spriteIdBotBody)->Draw(xx, yy);
			xx += this->cellWidth;
		}
	}
	s->Get(this->spriteIdBotRight)->Draw(xx, yy);

	/*RenderBoundingBox();*/
}

void CHollowPlatform::GetBoundingBox(float& l, float& t, float& r, float& b)
{
}