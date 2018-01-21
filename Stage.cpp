//#include "Stage.h"
#include "stdafx.h"

int Stage::Init(int x, int y, int w, int h) 
{
	ox = x; oy = y;
	ow = w, oh = h;
	
	sh = LoadSoundMem(_T("audio\\BGM\\polp.ogg"));
	sflag = false;
	volume = 100;
	se = LoadSoundMem(_T("audio\\SE\\SE1.ogg"));
	sevolume = 100;
	bg = LoadGraph(_T("image\\stars.png"));

	bar = new Bar();
	if (bar->Init(x, y, w, h) != 0) {	// バーの初期化
		return -1;
	}
	ball = new Ball();
	if (ball->Init(x, y, w, h) != 0) {	// ボールの初期化
		return -2;
	}
	for (int i=0;i < V_BLOCKNUM;i++){	// ブロックの初期化
		for (int j=0;j < H_BLOCKNUM;j++){
			block[i][j] = new Block();
			if (block[i][j]->Init(x, y, w, h) != 0) {
				return -3;
			}
			//block[i][j]->SetKind(GetRand(7));
			//block[i][j]->SetPosition((x + 15) + (blkw * j), (y + 15) + (blkh * i));
		}
	}

	barw = bar->GetWidth();
	barh = bar->GetHeight();
	ballw = ball->GetWidth();
	ballh = ball->GetHeight();
	blkw = block[0][0]->GetWidth();
	blkh = block[0][0]->GetHeight();

	for (int i=0;i < V_BLOCKNUM;i++){	// ブロックの仮配置
		for (int j=0;j < H_BLOCKNUM;j++){
			block[i][j]->SetKind(GetRand(7));
			block[i][j]->SetPosition(x + ((blkw + 15) * j), y + ((blkh + 15) * i));
		}
	}

	return 0;
}

void Stage::CheckHit()
{
	if (!sflag) {
		PlaySoundMem(sh, DX_PLAYTYPE_LOOP);
		sflag = true;
	}
	if (sflag){
		ChangeVolumeSoundMem(255 * volume / 100, sh);
	}
	
	int barx = bar->GetX();
	int bary = bar->GetY();
	int ballx = ball->GetX();
	int bally = ball->GetY();
	int ballmx = ball->GetMoveX();
	int ballmy = ball->GetMoveY();
	int blkx = 0, blky = 0;

	// バーとボールの当たり判定
	if (abs(bary-bally) < (ballh / 2) + (barh / 4)){
		if ((barx - barw / 2) < ballx && (barx + barw / 2) > ballx){
			if (ballx < barx - barw / 2 * 2 / 3){	// 左端
				ball->SetMoveX(ballmx * -1);
				ball->SetMoveY(ballmy * -1);
			}else if (ballx > barx + barw / 2 * 2 / 3) {	// 右端
				ball->SetMoveX(ballmx * -1);
				ball->SetMoveY(ballmy * -1);
			}else {
				ball->SetMoveY(ballmy * -1);
			}
		}
	}

	// バーとブロックの当たり判定
	bool seflag = false;
	for (int i=0;i < V_BLOCKNUM;i++){
		for (int j=0;j < H_BLOCKNUM;j++){
			if (block[i][j]->GetFlag() == true){	// 有効なブロックのみ処理
				blkx = block[i][j]->GetX();
				blky = block[i][j]->GetY();
				// 上側の判定
				if (ballx > blkx - (blkw / 2) && ballx < blkx + (blkw / 2) &&
					bally + (ballh / 2) > blky - (blkh / 2) && bally + (ballh / 2) < blky + (blkh / 2)){
						block[i][j]->SetFlag(false);
						ball->SetMoveY(ballmy * -1);
						seflag = true;
				}
				// 下側の判定
				else if (ballx > blkx - (blkw / 2) && ballx < blkx + (blkw / 2) &&
						 bally - (ballh / 2) > blky - (blkh / 2) && bally - (ballh / 2) < blky + (blkh / 2)) {
						block[i][j]->SetFlag(false);
						ball->SetMoveY(ballmy * -1);
						seflag = true;
				}
				// 左側の判定
				else if (bally > blky - (blkh / 2) && bally < blky + (blkh / 2) &&
						 ballx + (ballw / 2) > blkx - (blkw / 2) && ballx + (ballw / 2) < blkx + (blkw / 2)) {
						block[i][j]->SetFlag(false);
						ball->SetMoveX(ballmx * -1);
						seflag = true;
				}
				// 右側の判定
				else if (bally > blky - (blkh / 2) && bally < blky + (blkh / 2) &&
						 ballx - (ballw / 2) > blkx - (blkw / 2) && ballx - (ballw / 2) < blkx + (blkw / 2)) {
						block[i][j]->SetFlag(false);
						ball->SetMoveX(ballmx * -1);
						seflag = true;
				}
				if (seflag){
					ChangeVolumeSoundMem(255 * sevolume / 100, se);
					PlaySoundMem(se, DX_PLAYTYPE_BACK);
					seflag = false;
				}
			}
		}
	}
}

int Stage::Update(BaseApplication* app)
{
	bar->Update(app);
	if (ball->Update(app) == 1){
		//app->ChangeState(BaseApplication::STATE_OVER);
		StopSoundMem(sh);
		return -1;	// ゲームオーバー
	}
	int count = 0;
	for (int i=0;i < V_BLOCKNUM;i++){
		for (int j=0;j < H_BLOCKNUM;j++){
			if (block[i][j]->Update(app) == 1) {
				count++;
			}
		}
	}
	if (V_BLOCKNUM*H_BLOCKNUM <= count){
		//app->ChangeState(BaseApplication::STATE_CLEAR);
		StopSoundMem(sh);
		return 1;	// ステージクリア
	}

	CheckHit();

	return 0;
}

int Stage::Draw()
{
	DrawGraph(0, 0, bg, TRUE);
	
	bar->Draw();
	ball->Draw();
	for (int i=0;i < V_BLOCKNUM;i++){
		for (int j=0;j < H_BLOCKNUM;j++){
			block[i][j]->Draw();
		}
	}
	return 0;
}

void Stage::End()
{
	if (bar) {
		bar->End();
		delete bar;
		bar = NULL;
	}
	if (ball) {
		ball->End();
		delete ball;
		ball = NULL;
	}
	for (int i=0;i < V_BLOCKNUM;i++){
		for (int j=0;j < H_BLOCKNUM;j++){
			if (block[i][j]) {
				block[i][j]->End();
				delete block[i][j];
				block[i][j] = NULL;
			}
		}
	}
}