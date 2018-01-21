//#include "Ending.h"
#include "stdafx.h"

int Ending::Init(int x, int y, int w, int h) 
{
	//count = 0;
	flag = false;
	ox = x; oy = y;
	ow = w, oh = h;
	sh = LoadSoundMem(_T("audio\\BGM\\death_tone.ogg"));
	bh1 = LoadGraph(_T("image\\clear.png"));
	bh2 = LoadGraph(_T("image\\over.png"));
	//volume = 100;
	sflag = false;
	return 0;
}

int Ending::Update(BaseApplication* app)
{
	if (!sflag) {
		PlaySoundMem(sh, DX_PLAYTYPE_LOOP);
		sflag = true;
	}
	if (sflag){
		ChangeVolumeSoundMem(255 * volume / 100, sh);
	}

	if (app->GetKeyState(KEY_INPUT_RETURN) == 1){	// エンターキーでタイトルに戻る
		if (sflag){
			StopSoundMem(sh);
			sflag = false;
		}
		app->InitState(BaseApplication::STATE_ALL);
		app->ChangeState(BaseApplication::STATE_TITLE);
		//app->InitState(BaseApplication::STATE_TITLE);
		//app->InitState(BaseApplication::STATE_GAME);
	}
	/*if (count == 300){	// ５秒待つ
		app->ChangeState(BaseApplication::STATE_TITLE);
		//app->InitState(BaseApplication::STATE_TITLE);
		//app->InitState(BaseApplication::STATE_GAME);
		app->InitState(BaseApplication::STATE_ALL);
		count = 0;
	}
	count++;*/
	return 0;
}

int Ending::Draw()
{
	if (flag){
		//DrawString(ox, oy, _T("げーむくりあー(*´ω｀*)"), GetColor(0xff, 0x80, 0x00));
		DrawGraph(ox, oy, bh1, TRUE);
	}else {
		//DrawString(ox, oy, _T("げーむおーばー(´・ω・｀)"), GetColor(0xff, 0x80, 0x00));
		DrawGraph(ox, oy, bh2, TRUE);
	}
	return 0;
}

void Ending::End(){
	
}