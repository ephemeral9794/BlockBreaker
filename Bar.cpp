//#include "Bar.h"
#include "stdafx.h"

int Bar::Init(int x, int y, int w, int h)
{
	ow = w; oh = h;
	bh = LoadGraph(_T("image\\bar.png"));
	if (bh == -1) {
		return -1;
	}
	GetGraphSize(bh, &width, &height);
	this->ox = x;
	this->oy = y;
	this->x = ((ow + ox) / 2) - (width / 2);	// �J�n���͐^��
	this->y = ((oh + oy) - 10) - (height / 2);	// Y���W�͌Œ�
	m = 3;	// �����̑傫��
	return 0;
}

int Bar::Update(BaseApplication* app)
{
	if (app->GetKeyState(KEY_INPUT_LEFT) > 0 && app->GetKeyState(KEY_INPUT_RIGHT) == 0 && x + (width / 2) > ox) {
		x -= m;
	}
	else if (app->GetKeyState(KEY_INPUT_RIGHT) > 0 && app->GetKeyState(KEY_INPUT_LEFT) == 0 && x + (width / 2) < ow + ox) {
		x += m;
	}
	return 0;
}

int Bar::Draw()
{
	DrawGraph(x, y, bh, TRUE);
	return 0;
}

void Bar::End() 
{
	DeleteGraph(bh);
}
