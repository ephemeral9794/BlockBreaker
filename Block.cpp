//#include "Block.h"
#include "stdafx.h"

int Block::Init(int x, int y, int w, int h) 
{
	//bh = LoadGraph(_T("image\\block.png"));
	LoadDivGraph(_T("image\\block.png"), 8, 4, 2, 30, 30, bh);
	GetGraphSize(bh[0], &width, &height);
	x = y = 0;
	kind = BLOCK_RED;
	flag = true;
	alpha = 255;
	return 0;
}

int Block::Update(BaseApplication* app)
{
	if (flag == false && alpha > 0){
		alpha -= 8;
		if (alpha < 0)
			alpha = 0;
	}

	if (flag == false && alpha <= 0){
		return 1;
	}else {
		return 0;
	}
}

int Block::Draw()
{
	if (kind < 8 && kind >= 0){
		SetDrawBlendMode(DX_BLENDMODE_ALPHA, alpha);
		DrawGraph(x, y, bh[kind], TRUE);
		SetDrawBlendMode(DX_BLENDMODE_NOBLEND, 0);
	}
	return 0;
}

void Block::End()
{
	for (int i=0;i<8;i++){
		DeleteGraph(bh[i]);
	}
}