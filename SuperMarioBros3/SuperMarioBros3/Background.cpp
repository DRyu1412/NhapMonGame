#include "Background.h"

void CBackground::Render()
{
	CAnimations* animations = CAnimations::GetInstance();
	animations->Get(50000)->Render(x, y);
	//RenderBoundingBox();
}
