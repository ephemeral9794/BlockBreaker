//#include "Title.h"
#include "stdafx.h"

int Title::Init(int x, int y, int w, int h)
{
	th = LoadGraph(_T("image\\title.png"));
	ph = LoadGraph(_T("image\\press.png"));
	sh = LoadSoundMem(_T("audio\\BGM\\konjiki.ogg"));
	se = LoadSoundMem(_T("audio\\SE\\SE2.ogg"));
	count = 0;
	dflag = true;
	sflag = false;
	enter = false;
	
	menu[0].x = 222;
	menu[0].y = 300;
	LoadDivGraph(_T("image\\start.png"), 2, 2, 1, 197, 30, menu[0].graph);
	menu[0].select = 0;
	//menu[0].name = _T("Game Start");
	//menu[0].color = GetColor(0xff, 0xff, 0xff);
	menu[1].x = 262;
	menu[1].y = 340;
	LoadDivGraph(_T("image\\config.png"), 2, 2, 1, 117, 40, menu[1].graph);
	menu[1].select = 0;
	//menu[1].name = _T("Config");
	//menu[1].color = GetColor(0xff, 0xff, 0xff);

	if (th == -1 || ph == -1 || sh == -1) {
		return -1;
	}
	return 0;
}

int Title::Update(BaseApplication* app)
{
	if (app->GetKeyState(KEY_INPUT_DOWN) == 1 || app->GetKeyState(KEY_INPUT_UP) == 1) {
		select = (select + 1) % 2;
	}
	for (int i = 0; i < 2; i++) {
		if (select == i) {
			menu[i].select = 1;
		}
		else {
			menu[i].select = 0;
		}
	}
	if (app->GetKeyState(KEY_INPUT_RETURN) == 1) {
		PlaySoundMem(se, DX_PLAYTYPE_BACK);	// Œˆ’èŒø‰Ê‰¹
		if (enter == true){
			switch (select){
			case 0:
				app->ChangeState(BaseApplication::STATE_GAME);
				StopSoundMem(sh);
				sflag = false;
				return 1;
			case 1:
				app->ChangeState(BaseApplication::STATE_CONFIG);
				//StopSoundMem(sh);
				//sflag = false;
				return 1;
			}
		}
		if (enter == false){
			enter = true;
			dflag = false;
		}
	}
	if (!sflag) {
		PlaySoundMem(sh, DX_PLAYTYPE_LOOP);
		sflag = true;
	}
	if (sflag){
		ChangeVolumeSoundMem(255 * volume / 100, sh);
		ChangeVolumeSoundMem(255 * sevolume / 100, se);
	}
	if ((++count % 45) == 0 && enter == false) {
		dflag = !dflag;
		count = 0;
	}
	return 0;
}

int Title::Draw()
{
	DrawGraph(37, 110, th, TRUE);
	if (dflag) {
		DrawGraph(171, 340, ph, TRUE);
	}
	if (enter){
		for (int i=0;i < 2; i++){
			//DrawString(menu[i].x, menu[i].y, menu[i].name, menu[i].color);
			DrawGraph(menu[i].x, menu[i].y, menu[i].graph[menu[i].select], TRUE);
		}
	}
	return 0;
}

void Title::End()
{
	DeleteGraph(th);
	DeleteGraph(ph);
	if (CheckSoundMem(sh)) {
		StopSoundMem(sh);
	}
	DeleteSoundMem(sh);
}
