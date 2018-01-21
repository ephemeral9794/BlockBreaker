#pragma once
//#include "Include.h"
//#include "Bar.h"
//#include "Ball.h"
//#include "Block.h"
//#include "Stage.h"

//#define BLOCK_VNUM 7
//#define BLOCK_HNUM 10
//#define BLOCK_NUM 10

class Game : public Object{
private:
	/*Bar* bar;
	Ball* ball;
	Block* block[BLOCK_NUM];
	int barw, barh;
	int ballw, ballh;
	int blkw, blkh;*/

	Stage* stage;

	int bh;	// フレーム画像のハンドル
	int fw, fh;	// フレーム内の高さ、幅
	/*int sh;
	bool sflag;	// 音声再生中であるかのフラグ
	int volume;	// ボリューム*/
private:
	//void CheckHit();
public:
	Game() /*: bar(NULL), ball(NULL), sh(-1), sflag(false)*/{}
	virtual ~Game(){}

	virtual int Init(int x, int y, int w, int h) override;
	virtual int Update(BaseApplication* app) override;
	virtual int Draw() override;
	virtual void End() override;

	void SetVolume(int v) { if (this->stage) { stage->SetVolume(v); } }
	void SetSEVolume(int v) { if (this->stage) { stage->SetSEVolume(v); } }
};
