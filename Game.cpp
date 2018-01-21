//#include "Game.h"
#include "stdafx.h"

/*void Game::CheckHit()
{
	int barx = bar->GetX();
	int bary = bar->GetY();
	int ballx = ball->GetX();
	int bally = ball->GetY();
	int ballmx = ball->GetMoveX();
	int ballmy = ball->GetMoveY();
	int blkx = 0, blky = 0;

	// �o�[�ƃ{�[���̓����蔻��
	if (abs(bary-bally) < (ballh / 2) + (barh / 4)){
		if ((barx - barw / 2) < ballx && (barx + barw / 2) > ballx){
			if (ballx < barx - barw / 2 * 2 / 3){	// ���[
				ball->SetMoveX(ballmx * -1);
				ball->SetMoveY(ballmy * -1);
			}else if (ballx > barx + barw / 2 * 2 / 3) {	// �E�[
				ball->SetMoveX(ballmx * -1);
				ball->SetMoveY(ballmy * -1);
			}else {
				ball->SetMoveY(ballmy * -1);
			}
		}
	}

	// �o�[�ƃu���b�N�̓����蔻��
	for (int i=0; i < BLOCK_NUM;i++){
		if (block[i]->GetFlag() == TRUE){	// �L���ȃu���b�N�̂ݏ���
			blkx = block[i]->GetX();
			blky = block[i]->GetY();
			// �㑤�̔���
			if (ballx > blkx - (blkw / 2) && ballx < blkx + (blkw / 2) &&
				bally + (ballh / 2) > blky - (blkh / 2) && bally + (ballh / 2) < blky + (blkh / 2)){
					block[i]->SetFlag(FALSE);
					ball->SetMoveY(ballmy * -1);
			}
			// �����̔���
			else if (ballx > blkx - (blkw / 2) && ballx < blkx + (blkw / 2) &&
					 bally - (ballh / 2) > blky - (blkh / 2) && bally - (ballh / 2) < blky + (blkh / 2)) {
					block[i]->SetFlag(FALSE);
					ball->SetMoveY(ballmy * -1);
			}
			// �����̔���
			else if (bally > blky - (blkh / 2) && bally < blky + (blkh / 2) &&
					 ballx + (ballw / 2) > blkx - (blkw / 2) && ballx + (ballw / 2) < blkx + (blkw / 2)) {
					block[i]->SetFlag(FALSE);
					ball->SetMoveX(ballmx * -1);
			}
			// �E���̔���
			else if (bally > blky - (blkh / 2) && bally < blky + (blkh / 2) &&
					 ballx - (ballw / 2) > blkx - (blkw / 2) && ballx - (ballw / 2) < blkx + (blkw / 2)) {
					block[i]->SetFlag(FALSE);
					ball->SetMoveX(ballmx * -1);
			}
		}
	}
}*/

int Game::Init(int x, int y, int w, int h)
{
	bh = LoadGraph(_T("image\\frame.png"));
	fw = w - 20; fh = h - 20;
	
	stage = new Stage();
	if (stage->Init(10, 10, fw, fh) != 0){
		return -1;
	}

	/*sh = LoadSoundMem(_T("audio\\BGM\\polp.ogg"));
	sflag = false;
	volume = 100;*/

	return 0;
}

int Game::Update(BaseApplication* app)
{
	/*if (!sflag) {
		PlaySoundMem(sh, DX_PLAYTYPE_LOOP);
		sflag = true;
	}
	if (sflag){
		ChangeVolumeSoundMem(255 * volume / 100, sh);
	}*/

	int hr = stage->Update(app);
	if (hr == 1){	// �X�e�[�W�N���A
		app->ChangeState(BaseApplication::STATE_CLEAR);
		//StopSoundMem(sh);
		//sflag = false;
	}else if (hr == -1){	// �Q�[���I�[�o�[
		app->ChangeState(BaseApplication::STATE_OVER);
		//StopSoundMem(sh);
		//sflag = false;
	}

	return 0;
}

int Game::Draw()
{
	stage->Draw();
	DrawGraph(0, 0, bh, TRUE);
	return 0;
}

void Game::End()
{
	if (stage) {
		stage->End();
		delete stage;
		stage = NULL;
	}
	/*if (CheckSoundMem(sh)) {
		StopSoundMem(sh);
	}
	DeleteSoundMem(sh);*/
	DeleteGraph(bh);
}
