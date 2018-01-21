//#include "Ball.h"
#include "stdafx.h"

int Ball::Init(int x, int y, int w, int h)
{
	bh = LoadGraph(_T("image\\ball.png"));
	GetGraphSize(bh, &width, &height);
	this->x = (w / 2) - (width / 2);
	this->y = 200;
	this->ox = x; this->oy = y;
	ow = w; oh = h;
	mx = 2; my = -2;
	if (GetRand(1) == 0){
		mx = -mx;
	}
	
	return 0;
}

int Ball::Update(BaseApplication * app)
{
	if (x + (width / 2) < ox || x + (width / 2) > ow + ox){	// 左右の壁に当たった場合
		mx = -mx;
	}
	if (y + (height / 2) < oy){	// 上の壁に当たった場合
		my = -my;
	}

	if (y > oh + oy){	// 下の壁に当たった場合(ゲームオーバー)
		return 1;
	}

	x += mx;
	y += my;
	
	return 0;
}

int Ball::Draw()
{
	DrawGraph(x, y, bh, TRUE);
	return 0;
}

void Ball::End()
{
	DeleteGraph(bh);
}
